/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#ifndef C_PLAYER_H
#define C_PLAYER_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define PLAYER_FRICTION 0.95
#define PLAYER_GRAVITY 0.35
#define JUMP_STR 8.3


class c_player
{
private:
    static HGE*     hge;
    hgeVector       Position;
    hgeVector       Velocity;
    hgeVector       AttackOffset;
    HTEXTURE        Texture;
    hgeAnimation*   Sprite;
    hgeRect         BoundingBox; //Collision Detection
    bool            FacingRight;
    float           Speed;
    int           JumpDuration; // How long pressing the up button will make you rise
    int           MaxJumpDuration;
    float             TopOffset;
    float             BotOffset;
    float             LeftOffset;
    float             RightOffset;
    bool            aimup;
    bool            Controlled;

public:
    c_player(hgeVector Position, hgeVector Velocity);
    ~c_player();

    bool GetFacingRight(){return FacingRight;};
    bool GetAimUp(){return aimup;};
    bool TileReactSlope(hgeRect tile, int tileType);
    bool TileReact(hgeRect tile);
    void TileReactFine(hgeRect tile);
    bool Collision(hgeRect tile);

    void Render(float x, float y);
    bool Update(float delta);
    void UpdateBound();
    void SetControl(bool x) {Controlled = x;};

    void ResetJump();
    void RemoveJump();

    void    SetVelocity(hgeVector vel) { Velocity = vel;};
    void    SetPosition(hgeVector pos)
    {
        Position = pos;
        BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
    };
    hgeVector  GetVelocity() { return Velocity; };
    hgeVector GetPosition() { return Position; };

    hgeRect GetBoundingBox() { return BoundingBox; };
    float     GetLeftSide() { return LeftOffset; };
    float     GetRightSide() { return RightOffset; };
    float     GetTopSide() { return TopOffset; };
    float     GetBotSide() { return BotOffset; };

    float     GetHeight() { return BotOffset; };
    float     GetWidth() { return RightOffset-LeftOffset; };

    hgeVector GetAttackOffset() {return Position + AttackOffset + hgeVector(0, Velocity.y);};

};

#endif
