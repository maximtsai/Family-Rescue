/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#ifndef C_LEVEL_H
#define C_LEVEL_H
#pragma once

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgerect.h>
#include "c_enemy.h"
#include "c_block.h"

class c_level
{
private:
    static HGE* hge;
    float MaxWidth;
    float MaxHeight;
    short introMap[][];

public:
    c_level(hgeVector Position, short TileType, HTEXTURE &Texture);
    ~c_block();

    void Render(float x, float y);

    short GetTileType() { return TileType; };
    hgeRect GetBoundingBox() { return BoundingBox; };
    hgeVector GetPosition() { return Position; };
};

#endif
