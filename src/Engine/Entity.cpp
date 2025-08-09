#include "Entity.h"

Entity::Entity()
{
    Initialize();
}

Entity::Entity(std::string name)
{
    Initialize();
    SetName(name);
}

Entity::~Entity()
{
    //Destroy all children
    for(int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

//!!TODO: Create Transform component and Initialize it here
void Entity::Initialize()
{
    Start();

    //Init any components already attached
    for(int i = 0; i < components.size(); i++)
    {
        components[i]->Initialize();
    }
}

void Entity::Start()
{
    for(int i = 0; i < components.size(); i++)
    {
        components[i]->Start();
    }
}

void Entity::Update()
{
    for(int i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
}

//Returns true if child added successfully and false if it fails
bool Entity::AddChild(Entity* child)
{
    if(child == nullptr)
        return false;
    //check if child already is already in children
    for(int i = 0; i < children.size(); i++)
    {
        if(child->GetName() == children[i]->GetName())
            return false;
    }
    child->childIndex = children.size();
    children.push_back(child);
    child->SetParent(this);
    return true;
}

//Returns true if child was found and erased successfully and false if it fails
bool Entity::RemoveChild(Entity* child)
{
    if(child == nullptr)
        return false;

    for(int i = 0; i < children.size(); i++)
    {
        if(child->GetName() == children[i]->GetName())
        {
            child->childIndex = -1;
            children.erase(children.begin() + i);
            child->SetParent(nullptr);
            return true;
        }
    }
    return false;
}

//If name begins with '/', begins search from root Entity if it exists, if root Entity is nullptr function returns nullptr
//else, any '/' found will try to search from that entities child
//If name begins with '../', begins search from parent of current Entity
Entity* Entity::GetChild(std::string name)
{
    size_t slashIndex = name.find("/");

    if(slashIndex == std::string::npos)
    {
        for(int i = 0; i < children.size(); i++)
        {
            if(name == children[i]->GetName())
                return children[i];
        }

        LOG_ERROR("Entity: " + name + " could not be found");
        return nullptr;
    }

    //Search from root Entity
    if(slashIndex == 0)
    {
        Entity* rootEntity = GetRootEntity();
        if(rootEntity == nullptr)
        {
            LOG_ERROR("Root could not be found for Entity: " + this->GetName());
            return nullptr;
        }

        return rootEntity->GetChild(name.substr(1));
    }

    size_t backIndex = name.find("../");
    if(backIndex != std::string::npos)
    {
        if(this->parent == nullptr)
        {
            LOG_ERROR(this->GetName() + " does not have a parent");
            return nullptr;
        }
        return this->parent->GetChild(name.substr(backIndex + 3));
    }

    Entity* lastChildEntity = this;
    //if a slash was found in the path
    while(slashIndex != std::string::npos)
    {
        if (slashIndex == 0)
        {
            //Set lastChildEntity to the next child in the list without beginning slash
            std::string currentEntityName = name.substr(1);
            lastChildEntity = lastChildEntity->GetChild(currentEntityName);
            break;
        }
        //set lastChildEntity to the next child in the list
        std::string currentEntityName = name.substr(0, slashIndex);
        if(lastChildEntity->GetChild(currentEntityName) == nullptr)
        {
            LOG_ERROR("Could not find Child with given name: " + currentEntityName + " from: " + lastChildEntity->GetName());
            return nullptr;
        }
        lastChildEntity = lastChildEntity->GetChild(currentEntityName);
        //remove last childs name from name and find next slash
        name = name.substr(slashIndex);
        slashIndex = name.find("/");
    }
    return lastChildEntity;
}

Entity* Entity::GetChildByIndex(int index)
{
    if(index >= children.size())
        return nullptr;
    
    return children[index];
}

int Entity::GetChildIndex()
{
    return this->childIndex;
}

Entity* Entity::GetRootEntity()
{
    if(rootEntity != nullptr)
        return rootEntity;

    //go up Entity Tree
    Entity* entity = this;
    while(entity->parent != nullptr)
    {
        entity = entity->parent;
    }
    rootEntity = entity;
    return entity;
}

std::string Entity::GetPath()
{
    std::string path(name);
    Entity* entity = this;
    while (entity->parent->parent != nullptr)
    {
        entity = entity->parent;
        path.insert(0, entity->name + "/");
    }
    return path;
}

//setter for parent
//Use AddChild() for Entity Hierarchy Structure
void Entity::SetParent(Entity* parent)
{
    this->parent = parent;
}

void Entity::SetName(std::string name)
{
    if(parent == nullptr)
        this->name = name;
    else
    {
        //Check for matching names
        int timesFound = 0;
        for(int i = 0; i < parent->children.size(); i++)
        {
            if(name == parent->children[i]->GetName())
            {
                timesFound++;
                if(timesFound != 0)
                {
                    name.erase(name.end() - 2, name.end());
                }
                name.append(" " + timesFound);
            }
        }
    }
}

std::string Entity::GetName()
{
    return this->name;
}

void Entity::AddComponent(Component* component)
{
    //check for matching component
    for(int i = 0; i < components.size(); i++)
    {
        if(component == components[i])
        {
            LOG_ERROR("Component already exists on Entity: " + this->GetName());
            return;
        }
    }
    if(component->entity != nullptr)
    {
        component->entity->RemoveComponent(component);
    }
    component->entity = this;
    components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
    for(int i = 0; i < components.size(); i++)
    {
        if(component == components[i])
        {
            component->entity = nullptr;
            components.erase(components.begin() + i);
        }
    }
}