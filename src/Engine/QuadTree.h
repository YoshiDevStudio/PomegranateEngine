#pragma once

#include <functional>
#include <list>

#include "Core.h"

template <class T>
class QuadTree;

template <class T>
struct DLL_API QuadTreeEntry
{
    glm::vec2 pos;
    glm::vec2 size;
    T object;

    QuadTreeEntry(T obj, glm::vec2 pos, glm::vec2 size)
    {
        object = obj;
        this->pos = pos;
        this->size = size;
    }
};

template <class T>
class DLL_API QuadTreeNode
{
public:
    typedef std::function<void(std::list<QuadTreeEntry<T>>&)> QuadTreeFunc;

    void OperateOnContents(QuadTreeFunc& func)
    {
        if(children)
        {
            for(int i = 0; i < 4; i++)
            {
                children[i].OperateOnContents(func);
            }
        }
        else
        {
            if(!contents.empty())
            {
                func(contents);
            }
        }
    }

    void Split()
    {
        glm::vec2 halfSize = size / 2.0f;
        children = new QuadTreeNode<T>[4];
        children[0] = QuadTreeNode<T>(position + glm::vec2(-halfSize.x, halfSize.y), halfSize);
        children[1] = QuadTreeNode<T>(position + glm::vec2(halfSize.x, halfSize.y), halfSize);
        children[2] = QuadTreeNode<T>(position + glm::vec2(-halfSize.x, -halfSize.y), halfSize);
        children[3] = QuadTreeNode<T>(position + glm::vec2(halfSize.x, -halfSize.y), halfSize);

    }

    void Insert(T& object, const glm::vec2 objectPos, const glm::vec2 objectSize, int depthLeft, int maxSize)
    {
        if(!Collision::AABBTest(objectPos, position, objectSize, size))
            return;
        
        if(children) //not a leaf node, descend tree
        {
            for(int i = 0; i < 4; i++)
            {
                children[i].Insert(object, objectPos, objectSize, depthLeft - 1, maxSize);
            }
        }
        else    //leaf node, just expand
        {
            contents.push_back(QuadTreeEntry<T>(object, objectPos, objectSize));
            if((int)contents.size() > maxSize && depthLeft > 0)
            {
                if(!children)
                {
                    Split();
                    //reinsert contents so far
                    for(const auto& i : contents)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            auto entry = i;
                            children[j].Insert(entry.object, entry.pos, entry.size, depthLeft - 1, maxSize);
                        }
                    }
                    contents.clear();
                }
            }
        }
    }

protected:
    friend class QuadTree<T>;

    QuadTreeNode()
    {

    }
    QuadTreeNode(glm::vec2 pos, glm::vec2 size)
    {
        children = nullptr;
        this->position = pos;
        this->size = size;
    }
    ~QuadTreeNode() { delete[] children; }

    std::list<QuadTreeEntry<T>> contents;

    glm::vec2 position;
    glm::vec2 size;

    QuadTreeNode<T>* children;
};

template <class T>
class DLL_API QuadTree
{
public:
    QuadTree(glm::vec2 size, int maxDepth = 6, int maxSize = 5)
    {
        root = new QuadTreeNode<T>(glm::vec2(0, 0), size);
        this->maxDepth = maxDepth;
        this->maxSize = maxSize;
    }
    ~QuadTree()
    {
        delete root;
    }
    void Insert(T object, const glm::vec2& pos, const glm::vec2& size)
    {
        root->Insert(object, pos, size, maxDepth, maxSize);
    }

    void OperateOnContents(typename QuadTreeNode<T>::QuadTreeFunc func)
    {
        root->OperateOnContents(func);
    }

protected:
    QuadTreeNode<T>* root;
    int maxDepth;
    int maxSize;
};