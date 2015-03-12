/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#ifndef C_BULLET_H
#define C_BULLET_H
#pragma once

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgerect.h>

#define BULLET_FRICTION 0.99

class c_bullet
{
private:
    static HGE* hge;
    hgeVector   Position;
    hgeVector   Velocity;
    hgeSprite*  Sprite;
    hgeRect     BoundingBox;
    float       Speed;
    int       Damage;
    int         Duration;
    float       Rotation;

    //float       CenterY;
    //float       Radius;
    //float       Angle;
    //bool        bCenterYSet;
    //bool        bOscillate;
    //bool        bOscillateReverse;

public:
    c_bullet(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture, int Damage, int Duration, float Rotation);
    ~c_bullet();

    void Update();
    void Render(float x, float y);

    void    TickDuration() {Duration--;};
    int    GetDuration() {return Duration;};
    void    SetDamage(int dmg) { Damage = dmg; };
    int   GetDamage() {return Damage;};
    float   GetRotation() {return Rotation;};
    //void    SetOscillateReverse(bool val) { bOscillateReverse = val; };
    //void    SetOscillate(bool val) { bOscillate = val; };
    hgeRect GetBoundingBox() {return BoundingBox; };
    hgeVector GetPosition() { return Position; };
};

#endif
