/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

#include "c_player.h"
#include <stdio.h>


HGE* c_player::hge = 0;

c_player::c_player(hgeVector position, hgeVector velocity) : Position(position), Velocity(velocity)
{
    hge = hgeCreate(HGE_VERSION);   //Get interface to hge

    Texture = hge->Texture_Load("images/Spritesheet_48x44.png");
    Sprite = new hgeAnimation(Texture,6,4,0,0,30,50);
    Sprite->SetHotSpot(0, 0);
    Sprite->SetSpeed(10);
    Sprite->Play();

    //SpriteAlt = new hgeAnimation(Texture,6,4,0,36,54,72);
    //SpriteAlt->SetHotSpot(0, 0);
    Controlled = true;
    Speed = 0.18;
    JumpDuration = 0;
    MaxJumpDuration = 12;
    FacingRight = true;

    TopOffset = 2.0f;
    BotOffset = 50.0f;
    LeftOffset = 2.0f;
    RightOffset = 28.0f;

    AttackOffset = hgeVector(40, 20);
}

c_player::~c_player()
{
    hge->Texture_Free(Texture);
    delete Sprite;
    //delete SpriteAlt;

    hge->Release();
}

void c_player::ResetJump()
{
    JumpDuration = MaxJumpDuration;
};

void c_player::RemoveJump()
{
    JumpDuration = 0;
};

void c_player::UpdateBound()
{
    BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
}

bool c_player::Update(float delta)
{
    //Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
    Velocity.y += PLAYER_GRAVITY;

    if((hge->Input_GetKeyState(HGEK_LEFT)) && Position.x > 0 && Controlled)
    {
        Velocity.x -= Speed;
        Sprite->SetFlip(true, false, false);
        //SpriteAlt->SetFlip(true, false, false);
        FacingRight = false;
    }
    else if((hge->Input_GetKeyState(HGEK_RIGHT)) && Controlled)
    {
        Velocity.x += Speed;
        Sprite->SetFlip(false, false, false);
        //SpriteAlt->SetFlip(false, false, false);
        FacingRight = true;
    }
    if(hge->Input_GetKeyState(HGEK_UP) && Controlled)
    {
        aimup = true;
    }
    else
    {
        aimup = false;
    }

    //JUMPING
    if(((hge->Input_GetKeyState(HGEK_SPACE)) || (hge->Input_GetKeyState(HGEK_UP))) && JumpDuration > 0 && Controlled)
    {
        JumpDuration--;
        Velocity.y = -(JUMP_STR);
    }
    else if(JumpDuration < MaxJumpDuration)
    {
        JumpDuration = 0;
        //Sprite->SetFrame(1);
    }

    if(hge->Input_GetKeyState(HGEK_DOWN)) Velocity.y = +(JUMP_STR);


    Position.x += Velocity.x;
    Position.y += Velocity.y;
    BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);

    Velocity.x *= PLAYER_FRICTION;
    Velocity.y *= PLAYER_FRICTION;

    //else if((hge->Input_GetKeyState(HGEK_S) || hge->Input_GetKeyState(HGEK_DOWN)) && Position.y < 600);

    //if(Position.x > 800) { Position.x -= 1; Velocity.x = -Velocity.x;};
    if(Position.x < 0) { Position.x += 1; Velocity.x = -Velocity.x;};
    if(Position.y < 0) { Position.y += 1; Velocity.y = -Velocity.y;};
    //if(Position.y > 600) { Position.y -= 1; Velocity.y = -Velocity.y;};

    Sprite->Update(delta);
    if(JumpDuration < MaxJumpDuration) Sprite->SetFrame(2);
    else if( !(hge->Input_GetKeyState(HGEK_LEFT)) && !(hge->Input_GetKeyState(HGEK_LEFT)) && !(hge->Input_GetKeyState(HGEK_RIGHT)))
    {
        Sprite->SetFrame(0);
    }
    if(!Controlled)
    {
        Sprite->SetFrame(0);
    }
    return false;
}

void c_player::Render(float x, float y)
{
    Sprite->Render(((int)(Position.x +x)), ((int)(Position.y + y)));
}

bool c_player::Collision(hgeRect tile)
{
    if(tile.Intersect(&BoundingBox))
    return true;
    return false;
}


void c_player::TileReactFine(hgeRect tile)
{
	    if(Velocity.y > 0)
	    {
	        if(Velocity.x > 0)
	        {
                float intersection = (BoundingBox.x2 - tile.x1) - (BoundingBox.y2 - tile.y1) * (Velocity.x/Velocity.y);
                if(intersection > 2 && intersection < 28)
                {
                    Position = (hgeVector(Position.x, tile.y1 - BotOffset));
                    Velocity = (hgeVector(Velocity.x, 0));
                    JumpDuration = MaxJumpDuration;;
                }
                else
                {
                    Position = (hgeVector(tile.x1 - RightOffset, Position.y ));
                    Velocity = (hgeVector(0, Velocity.y));
                }
	        }
	        else if(Velocity.x < 0)
	        {
                //printf("should fall left");
                float intersection = (BoundingBox.x1 - tile.x1) - (BoundingBox.y2 - tile.y1) * (Velocity.x/Velocity.y);
                if(intersection > 2 && intersection < 28)
                {
                    Position = (hgeVector(Position.x, tile.y1 - BotOffset));
                    Velocity = (hgeVector(Velocity.x, 0));
                    JumpDuration = MaxJumpDuration;
                }
                else
                {
                    Position = (hgeVector(tile.x2 - LeftOffset, Position.y ));
                    Velocity = (hgeVector(0, Velocity.y));
                }
            }
	    }
	    else if(Velocity.y < 0)
	    {
	        if(Velocity.x > 0)
	        {
                //printf("should rise right");
                float intersection = (BoundingBox.x2 - tile.x1) - (BoundingBox.y1 - tile.y2) * (Velocity.x/Velocity.y);
                if(intersection > 2 && intersection < 28)
                {
                    Position = (hgeVector(Position.x, tile.y2 - TopOffset));
                    Velocity = (hgeVector(Velocity.x, 0));
                    JumpDuration = 0;
                }
                else
                {
                    Position = (hgeVector(tile.x1 - RightOffset, Position.y ));
                    Velocity = (hgeVector(0, Velocity.y));
                }
	        }
	        else if(Velocity.x < 0)
	        {
                float intersection = (BoundingBox.x1 - tile.x1) - (BoundingBox.y1 - tile.y2) * (Velocity.x/Velocity.y);
                if(intersection > 2 && intersection < 28)
                {
                    Position = (hgeVector(Position.x, tile.y2 - TopOffset));
                    Velocity = (hgeVector(Velocity.x, 0));
                    JumpDuration = 0;
                }
                else
                {
                    Position = (hgeVector(tile.x2 - LeftOffset, Position.y ));
                    Velocity = (hgeVector(0, Velocity.y));
                }
	        }
	    }
}

bool c_player::TileReact(hgeRect tile)
{
    //if()
    //return false;
    bool checked = true;
    if(Velocity.y > 0.0f) // if falling
    {
        // falling right
        if(Velocity.x > 0.0f)
        {
            //Checking bottom left points
            if(tile.TestPoint(BoundingBox.x1, BoundingBox.y2) || tile.TestPoint(BoundingBox.x1+22, BoundingBox.y2))
            {
                Position = (hgeVector(Position.x, tile.y1 - BotOffset));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(Velocity.x, 0));
                JumpDuration = MaxJumpDuration;
                checked = false;
            }
            //Checking top right points
            if(tile.TestPoint(BoundingBox.x2, BoundingBox.y1) || tile.TestPoint(BoundingBox.x2, BoundingBox.y1+22))
            {
                Position = (hgeVector(tile.x1-RightOffset, Position.y));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(0, Velocity.y));
                checked = false;
            }
        }
        // End falling right
        // falling left
        else if(Velocity.x < 0.0f)
        {
            //Checking bottom points
            if(tile.TestPoint(BoundingBox.x2, BoundingBox.y2) || tile.TestPoint(BoundingBox.x2-22, BoundingBox.y2))
            {
                Position = (hgeVector(Position.x, tile.y1 - BotOffset));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(Velocity.x, 0));
                JumpDuration = MaxJumpDuration;
                checked = false;
            }
            //Checking left points
            if(tile.TestPoint(BoundingBox.x1, BoundingBox.y1) || tile.TestPoint(BoundingBox.x1, BoundingBox.y1+22))
            {
                Position = (hgeVector(tile.x2-LeftOffset, Position.y));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(0, Velocity.y));
                checked = false;
            }
        }
        // end falling left
        // falling straight down
        else
        {
            Position = (hgeVector(Position.x, tile.y1 - BotOffset));
            BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
            Velocity = (hgeVector(Velocity.x, 0));
            JumpDuration = MaxJumpDuration;
            checked = false;
        }
    }
    else if(Velocity.y < 0.0f) // if going up
    {
        // going up right
        if(Velocity.x > 0.0f)
        {
            // top  check
            if(tile.TestPoint(BoundingBox.x1, BoundingBox.y1) || tile.TestPoint(BoundingBox.x1+22, BoundingBox.y1))
            {
                Position = (hgeVector(Position.x, tile.y2 - TopOffset));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(Velocity.x, 0));
                JumpDuration = 0;
                checked = false;
            }
            //  right check
            if(tile.TestPoint(BoundingBox.x2, BoundingBox.y2) || tile.TestPoint(BoundingBox.x2, BoundingBox.y2-22))
            {
                Position = (hgeVector(tile.x1 - RightOffset, Position.y));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(0, Velocity.y));
                checked = false;
            }
        }
        // going up left
        else if(Velocity.x < 0.0f)
        {
            //top collision
            if(tile.TestPoint(BoundingBox.x2, BoundingBox.y1) || tile.TestPoint(BoundingBox.x2-22, BoundingBox.y1)) //if top contacting tile
            {
                Position = (hgeVector(Position.x, tile.y2 - TopOffset));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(Velocity.x, 0));
                JumpDuration = 0;
                checked = false;
            }
            //left collision
            if(tile.TestPoint(BoundingBox.x1, BoundingBox.y2) || tile.TestPoint(BoundingBox.x1, BoundingBox.y2-22)) //if left contacting tile
            {
                Position = (hgeVector(tile.x2 - LeftOffset, Position.y));
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
                Velocity = (hgeVector(0, Velocity.y));
                checked = false;
            }
        }
        else
        {
            Position = hgeVector(Position.x, tile.y2 - TopOffset);
            BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
            Velocity = hgeVector(Velocity.x, 0);
            JumpDuration = 0;
            checked = false;
        }
    }
    else if(Velocity.x > 0.0f) // going purely right
    {
        if(tile.TestPoint(BoundingBox.x2, BoundingBox.y1) || tile.TestPoint(BoundingBox.x2, BoundingBox.y1+22))
        {
            Position = (hgeVector(tile.x1-RightOffset, Position.y));
            BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
            Velocity = (hgeVector(0, Velocity.y));
            checked = false;
        }
    }
    else if(Velocity.x < 0.0f) // going purely left
    {
        if(tile.TestPoint(BoundingBox.x1, BoundingBox.y1) || tile.TestPoint(BoundingBox.x1, BoundingBox.y1+22))
        {
            Position = (hgeVector(tile.x2 - LeftOffset, Position.y));
            BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
            Velocity = (hgeVector(0, Velocity.y));
            checked = false;
        }
    }
    return checked;
}



bool c_player::TileReactSlope(hgeRect tile, int tileType)
{
    int calcType = tileType%10;
    if(calcType == 1 || calcType == 2)
    {   //if lower left corner is beneath slope
        if(BoundingBox.x1 <= tile.x1-2)
        {
            Position.y = tile.y1-BotOffset;
            Velocity = (hgeVector(Velocity.x, 0));
            JumpDuration = MaxJumpDuration;
            BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
        }
        else if(BoundingBox.x1 <= tile.x2 - 2)
        {
            float underTile = BoundingBox.y2-(tile.y1+0.5*(BoundingBox.x1-tile.x1)) - 6;
            if(underTile > 0)
            {
                Position.y -= underTile; //rise up appropriate units
                Velocity = (hgeVector(Velocity.x, 0));
                JumpDuration = MaxJumpDuration;
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
            }
        }
    }
    else if(calcType == 3 || calcType == 4)
    {
        if(BoundingBox.x2 >= tile.x2+2)
        {
            Position.y = tile.y1-BotOffset;
            Velocity = (hgeVector(Velocity.x, 0));
            JumpDuration = MaxJumpDuration;
            BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
        }
        else if(BoundingBox.x2 >= tile.x1 + 2)
        {
            float underTile = BoundingBox.y2-(tile.y1+0.5*(tile.x2 - BoundingBox.x2)) - 6;
            if(underTile > 0)
            {
                Position.y -= underTile; //rise up appropriate units
                Velocity = (hgeVector(Velocity.x, 0));
                JumpDuration = MaxJumpDuration;
                BoundingBox = hgeRect(Position.x+LeftOffset, Position.y+TopOffset, Position.x+RightOffset, Position.y+BotOffset);
            }
        }
    }
    return false;
}

