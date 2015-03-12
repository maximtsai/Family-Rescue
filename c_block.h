/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#ifndef C_BLOCK_H
#define C_BLOCK_H
#pragma once

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgerect.h>


class c_block
{
private:
    static HGE* hge;
    hgeVector   Position;
    hgeSprite*  Sprite;
    hgeRect     BoundingBox;
    short         TileType; // 1 is default block

public:
    c_block(hgeVector Position, short TileType, HTEXTURE &Texture);
    ~c_block();

    void Render(float x, float y);

    short GetTileType() { return TileType; };
    hgeRect GetBoundingBox() { return BoundingBox; };
    hgeVector GetPosition() { return Position; };
};

#endif
