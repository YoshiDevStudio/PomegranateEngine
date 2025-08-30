#include "Game.h"

const float playerSpeed = 200.0f;

Entity* player;
Entity* box;

glm::vec2 playerVelocity = glm::vec2(0, 0);

void Game::Start()
{
    //Loads all Images in Folder given
    File::LoadIMGsInFolder("textures");

    //Initializes Entity and sets the name assigned to it
    player = new Entity("Player");

    //When creating a SpriteRenderer, the argument passed to it is the name of one of the Images that has been loaded
    SpriteRenderer* sprite = new SpriteRenderer("Circle");

    //For a circle collision, the argument passed in the constructor is the radius, so we multiply by 0.5
    CircleCollision* playerCollision = new CircleCollision(sprite->GetTexture()->size.x * 0.5f * player->transform->localScale.x);

    //Collision Layers and Masks are used for preventing collisions with certain objects
    //Two Entities will only collide if one Entities Layer equals the other Entities Mask
    playerCollision->SetCollisionLayer(1);

    //Adds Physics to Entity such as pushing away from Collisions, and adding Gravity to the Entity
    //PhysicsBody should only be added to Entity if that Entity has a Collision Component attached to it
    PhysicsBody* playerBody = new PhysicsBody();

    player->AddComponent(sprite);
    player->AddComponent(playerCollision);
    player->AddComponent(playerBody);

    //When creating a new Camera it will automatically set itself to be the main camera, you can pass false in the argument to prevent that
    Camera* camera = new Camera();
    player->AddComponent(camera);

    //Sets the amount of pixels to be rendered, this is not affected by window size
    camera->SetSize(640, 480);

    box = new Entity("box");
    box->transform->localPosition = glm::vec2(200, 200);
    box->transform->localScale = glm::vec2(3, 3);

    SpriteRenderer* boxSprite = new SpriteRenderer("block");
    BoxCollision* boxCollision = new BoxCollision(boxSprite->GetTexture()->size * box->transform->localScale);

    //Here the Collision Mask is set to match the playerCollision variable so the box and player are able to collide
    boxCollision->SetCollisionMask(1);

    //The StaticBody Component doesn't allow any Gravity or Impulses to be applied to the Entity it is attached to
    //However, any Entity with a PhysicsBody Component will still be pushed away when the two collide
    StaticBody* boxBody = new StaticBody();

    box->AddComponent(boxSprite);
    box->AddComponent(boxCollision);
    box->AddComponent(boxBody);

    //Adding an Entity to Level will add it to the main game loop
    Level->AddChild(player);
    Level->AddChild(box);

}

void Game::Update()
{
    //Makes a glm::vec2 out of the Inputs passed into the function
    //This uses the SDL Input Macros and only supports keyboard Inputs for now
    playerVelocity = Input::MakeVector(SDLK_W, SDLK_S, SDLK_D, SDLK_A);

    //if playerVelocity is zero on both axis, glm::normalize will return NaN
    if(playerVelocity.x != 0 || playerVelocity.y != 0)
    {
        playerVelocity = glm::normalize(playerVelocity) * playerSpeed * Time::deltaTime;
        player->transform->localPosition += playerVelocity;
    }

    //Sets the Ray origin and direction
    Ray ray(player->transform->globalPosition, Input::GetWorldMousePosition() - player->transform->globalPosition);
    RaycastHit hitInfo;

    //Shoots a Ray from the Ray origin into the Ray Direction and returns if anything is hit
    //if a collision is detected, the RaycastHit variable passed in will have more information about the collision.
    Physics::Raycast(ray, hitInfo);
}