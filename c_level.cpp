/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#include "c_block.h"
#define BLOCK_SIZE 24

HGE* c_block::hge = 0;

c_block::c_block(hgeVector position, short type, HTEXTURE &Texture) : Position(position), TileType(type)
{
    hge = hgeCreate(HGE_VERSION);   //Get interface to hge

    short modType = type % 10;
    Sprite = new hgeSprite(Texture, BLOCK_SIZE*(modType),0,BLOCK_SIZE,BLOCK_SIZE);

    if(modType == 0)
    {
        Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
    }
    else if(modType == 1 || modType == 3 || modType == 5)
    {
        BoundingBox = hgeRect(Position.x, Position.y + BLOCK_SIZE/2, Position.x + BLOCK_SIZE, Position.y + BLOCK_SIZE*3/2);
    }
    else if(modType == 2 || modType == 4)
    {
        BoundingBox = hgeRect(Position.x, Position.y, Position.x + BLOCK_SIZE, Position.y + BLOCK_SIZE);
    }
    Sprite->SetHotSpot(0, 0);
}

c_block::~c_block()
{
    delete Sprite;

    hge->Release();
}

void c_block::Render(float x, float y)
{
    Sprite->Render((int)(Position.x + x), (int)(Position.y + y));
}
