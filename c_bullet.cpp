/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#include "c_bullet.h"

HGE* c_bullet::hge = 0;

c_bullet::c_bullet(hgeVector position, hgeVector velocity, HTEXTURE &Texture, int damage, int duration, float rotation) : Position(position), Velocity(velocity), Damage(damage), Duration(duration), Rotation(rotation)
{
    hge = hgeCreate(HGE_VERSION);   //Get interface to hge

    Sprite = new hgeSprite(Texture,0,0,12,6);
    Sprite->SetHotSpot(0, 0);
    Speed = 0.15;

    //CenterY     = 0;
    //Radius      = hge->Random_Float(50.0f, 80.0f);
    //Angle       = 0.0f;
    //bCenterYSet = false;
    //bOscillate  = false;
    //bOscillateReverse = true;
}

c_bullet::~c_bullet()
{
    delete Sprite;

    hge->Release();
}

void c_bullet::Update()
{
    Velocity.x *= BULLET_FRICTION;
    Velocity.y *= BULLET_FRICTION;

    Position.x += Velocity.x;
    Position.y += Velocity.y;

    Duration--;
    /*
    if(!bOscillate) Position.y += Velocity.y;
    else
    {
        if(!bCenterYSet)
        {
            CenterY = Position.y;
            bCenterYSet = true;
        }
        if(!bOscillateReverse) Position.y = CenterY - sin(Angle) * Radius;
        else Position.y = CenterY + sin(Angle) * Radius;
        Angle += 5 * hge->Timer_GetDelta();
    }
    */

    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
}

void c_bullet::Render(float x, float y)
{
    Sprite->RenderEx((int)(Position.x + x), (int)(Position.y + y), Rotation, 1.0f, 0.0f);
}
