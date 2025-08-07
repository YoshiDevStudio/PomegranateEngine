#include "Input.h"

bool Input::keys[322];
Event<void, Input::KeyEvent>* Input::keyEvent;

//Constructor
void Input::Initialize()
{
    keyEvent = new Event<void, KeyEvent>();
    for(int i = 0; i < 322; i++)
    {
        keys[i] = false;
    }
}

//Deconstructor
void Input::Uninitialize()
{

}

//!!TODO:: Handle Mod Input
void Input::OnKeyEvent(KeyEvent e)
{
    if(e.key == -1)
        return;
    
    //if key is mod
    if(e.key > 0x80)
    {
        return;
    }
    switch(e.type)
    {
        case KeyEventType::KeyDown:
            keys[e.key] = true;
            break;
        case KeyEventType::KeyUp:
            keys[e.key] = false;
            break;
    }
    keyEvent->Invoke(e);
}

bool Input::IsKeyPressed(int key)
{
    try
    {
        return keys[key] == true;
    }
    catch(std::exception e) 
    {
        LOG_ERROR(e.what());
        return false;
    }
}

bool Input::IsKeyReleased(int key)
{
    try
    {
        return keys[key] == false;
    }
    catch(std::exception e) 
    {
        LOG_ERROR(e.what());
        return false;
    }
}