#include "Input.h"

bool Input::keys[322];
bool Input::prevKeys[322];
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
    prevKeys[e.key] = keys[e.key];
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
    if(key < 0 || key >= 322)
        return false;
    return keys[key] == true;
}

bool Input::IsKeyReleased(int key)
{
    if(key < 0 || key >= 322)
        return false;
    return keys[key] == false;
}

bool Input::IsKeyJustPressed(int key)
{
    if(key < 0 || key >= 322)
        return false;
    bool keyState = prevKeys[key] == false && keys[key] == true;

    prevKeys[key] = keys[key];

    return keyState;
}

bool Input::IsKeyJustReleased(int key)
{
    if(key < 0 || key >= 322)
        return false;
    bool keyState = prevKeys[key] == true && keys[key] == false;

    prevKeys[key] = keys[key];

    return keyState;
}