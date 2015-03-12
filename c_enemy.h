/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#ifndef C_ENEMY_H
#define C_ENEMY_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define ENEMY_FRICTION 0.95

class c_enemy
{
private:
    static HGE*     hge;
    hgeVector       Position;
    hgeVector       Velocity;
    hgeAnimation*   Sprite;
    hgeRect         BoundingBox; //Collision Detection
    float           Speed;
    short           Health;
/*
    float           CenterY;
    float           Radius;
    float           Angle;
    bool            bCenterYSet;
    bool            bOscillate;
    */
public:
    c_enemy(hgeVector Position, hgeVector Velocity, short Health, HTEXTURE Texture);
    ~c_enemy();

    void Render(float x, float y);
    bool Update(float delta);

    short   GetHealth() { return Health; };
    void    SetHealth(short health) {Health = health;};
    //void    SetOscillate(bool Val) { bOscillate = Val;};
    float   GetSpeed() { return Speed; };
    void    SetSpeed(float speed) { Speed = speed;};
    hgeRect GetBoundingBox() {return BoundingBox; };
    hgeVector   GetPosition() { return Position; };
};

#endif
