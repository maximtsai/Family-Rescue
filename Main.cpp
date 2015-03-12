
// Copy the files "menu.wav", "font1.fnt", "font1.png",
// "bg.png" and "cursor.png" from the folder "precompiled"
// to the folder with executable file. Also copy hge.dll
// and bass.dll to the same folder.

//yyyyyyy
#include "hge.h"
#include "hgesprite.h"
#include "hgevector.h"
#include "hgefont.h"


#include <list>
#include <math.h>
#include "c_player.h"
#include "c_bullet.h"
#include "c_enemy.h"
#include "c_block.h"
#include "menubutton.h"


//For printf
#include <stdio.h>

#define BLOCK_BIGNESS 48
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 576

#define MAP_WIDTH 60
#define MAP_HEIGHT 16

// Pointer to the HGE interface.
// Helper classes require this to work.
HGE* hge=0;

c_player* Player1 = NULL;
MenuButton* button1 = NULL;
MenuButton* buttonx = NULL;
MenuButton* button2 = NULL;
MenuButton* buttony = NULL;
MenuButton* button3 = NULL;
MenuButton* buttonz = NULL;
MenuButton* button4 = NULL;

std::list<c_bullet*> Bullets;
std::list<c_enemy*> Enemies;
std::list<c_block*> Blocks;
std::list<c_block*> Slopes;
std::list<c_block*> Backgrounds;

std::list<c_block*> Blocks2;
std::list<c_block*> Slopes2;
std::list<c_block*> Spikes2;
std::list<c_block*> Backgrounds2;

std::list<c_block*> Blocks3;
std::list<c_block*> Slopes3;
std::list<c_block*> Spikes3;
std::list<c_block*> Backgrounds3;

HTEXTURE    g_tEColors[5]   = {0};
HTEXTURE    g_tEBlocks[1]   = {0};
// Some resource handles
HTEXTURE    g_tBackground    = 0;
HTEXTURE	g_tCursor         = 0;
HTEXTURE    g_tBGGapFix      = 0;
HTEXTURE    g_tBullet        = 0;
HTEXTURE    family          = 0;


HEFFECT     g_eBGMusic       = 0;

// Pointers to the HGE objects we will use

hgeFont				*fnt;
hgeSprite*			momsprite = NULL;
hgeSprite*			dadsprite = NULL;
hgeSprite*			mesprite = NULL;
hgeSprite*			sissprite = NULL;

hgeSprite*			stand_block = NULL;
hgeSprite*			g_sBackground = NULL;
hgeSprite*          g_sBGGapFix = NULL;
hgeSprite*          g_sCursor = NULL;

c_block* Block = NULL;


short g_nBGAlpha = 255;
float mouseposx;
float mouseposy;
float ActualOffsetX = 0;
float ActualOffsetY = 0;

int gamemode = 0; // 0 for menu, 1 for lvl 1, 2 for lvl 2, 3 for lvl 3
int gamesave = 1; // 1 for lvl 1 available, 2 for lvl 2, 3 for lvl 3 available.

//-1 is empty space, 10 is tile, rest is background
short Map3[MAP_HEIGHT][MAP_WIDTH] = {{00,00,00,16,16,00,16,16,00,16,00,16,00,00,00,00,00,16,00,00,00,00,16,00,16,16,00,00,00,00,00,00,00,00,00,16,16,16,00,00,00,16,16,16,00,00,00,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
                                        {00,16,-1,-1,16,-1,-1,16,-1,16,-1,16,16,16,16,16,-1,-1,-1,16,16,-1,16,-1,-1,16,16,16,16,00,00,00,16,16,-1,16,16,16,16,16,-1,-1,-1,16,16,00,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,00,16,16,-1,-1,16,16,-1,-1,16,-1,-1,-1,-1,16,00,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {16,-1,-1,-1,-1,13,15,15,15,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,16,-1,-1,-1,16,16,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 10
                                        {16,-1,-1,-1,10,16,16,00,00,00,12,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,10,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {00,16,-1,-1,-1,-1,16,16,00,00,00,16,15,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {00,16,-1,-1,-1,-1,-1,-1,16,00,00,00,00,16,12,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,10,12,15,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {16,16,10,-1,-1,-1,-1,-1,-1,16,00,00,00,00,16,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,13,14,16,00,00,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {16,-1,-1,-1,15,15,-1,-1,-1,-1,16,00,00,00,-1,-1,-1,-1,-1,10,-1,-1,-1,16,-1,-1,-1,-1,00,00,00,00,00,16,-1,-1,-1,-1,-1,15,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1},
                                        {16,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,00,00,00,-1,-1,-1,-1,-1,16,-1,-1,-1,16,-1,-1,-1,-1,00,00,00,00,16,-1,-1,-1,-1,-1,-1,16,-1,-1,13,15,-1,16,17,-1,-1,-1,-1,-1,-1,10,16,-1,-1,-1,-1,-1},
                                        {16,12,-1,-1,-1,-1,-1,10,10,-1,-1,16,00,00,12,-1,-1,-1,17,16,-1,-1,17,16,17,-1,-1,17,00,00,00,00,16,-1,-1,10,10,-1,-1,-1,-1,-1,16,16,-1,16,16,15,-1,-1,-1,-1,10,16,16,-1,-1,-1,-1,-1},
                                        {00,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,00,00,16,-1,17,17,16,16,17,-1,16,00,00,17,-1,00,00,00,00,00,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,00,16,-1,-1,-1,10,16,00,16,10,10,10,10,10}, // 20
                                        {00,16,-1,-1,-1,10,10,-1,-1,-1,14,16,00,00,16,17,16,00,00,00,16,-1,00,00,00,00,-1,00,00,00,16,16,16,12,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,00,00,10,10,10,16,00,00,00,00,00,00,00,00},
                                        {00,16,-1,-1,-1,-1,-1,-1,-1,-1,16,00,00,00,00,00,00,00,00,00,16,-1,00,00,00,00,-1,16,16,00,00,00,00,00,00,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,16,00,00,16,00,00,00,00,00,00,00,00,00,00,00},
                                        {00,00,12,11,-1,-1,-1,13,14,10,00,00,00,00,00,00,00,00,00,00,00,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,14,16,16,16,-1,-1,-1,13,17,11,-1,-1,-1,16,00,00,00,16,00,00,00,00,00,00,00,00,00,00,00},
                                        {00,00,00,00,10,10,10,00,00,00,00,00,00,00,00,00,00,00,00,00,00,10,10,10,10,10,10,10,10,10,16,00,00,00,16,16,10,10,16,16,16,10,10,17,00,00,00,00,16,00,00,00,00,00,00,00,00,00,00,00}
};

short introMap[MAP_HEIGHT][MAP_WIDTH] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 10
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,16,-1,-1,-1,-1,-1,-1},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,15,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,00,00,10,10,10,10,10,10},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,16,16,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,00,00,00,00,00,00,00,00,00},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,13,15,-1,-1,16,-1,-1,-1,16,10,-1,-1,-1,-1,-1,-1,10,00,00,00,00,00,00,00,00,00,00},
                                        {-1,-1,-1,-1,-1,-1,-1,-1,13,15,15,11,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,13,16,11,-1,-1,-1,13,14,10,16,16,-1,-1,16,-1,-1,-1,16,16,10,-1,-1,-1,-1,10,00,00,00,00,00,00,00,00,00,00,00},
                                        {10,10,10,10,10,10,10,10,16,16,16,16,10,10,10,10,10,10,10,10,16,10,10,10,16,16,16,10,10,10,16,16,16,16,16,10,10,16,10,10,10,16,16,16,10,10,10,10,00,00,00,00,00,00,00,00,00,00,00,00} // 20
};

short Map2[MAP_HEIGHT][MAP_WIDTH] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 15
                                        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,10,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1}, // 15
                                        {10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,16,-1,-1,-1,-1,-1,-1}, // 15
                                        {16,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,00,16,10,10,10,10,10,10}, // 15
                                        {16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,00,00,00,00,00,00,00,00,00}, // 15
                                        {16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,16,-1,-1,16,10,-1,-1,-1,-1,-1,10,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,00,00,00,00,00,00,00,00,00,00}, // 15
                                        {16,15,11,-1,-1,-1,-1,-1,13,-1,-1,-1,10,00,16,-1,-1,16,00,10,-1,-1,-1,17,16,16,17,-1,-1,-1,-1,17,17,17,-1,-1,15,-1,-1,17,17,17,17,17,17,-1,-1,-1,10,00,00,00,00,00,00,00,00,00,00,00}, // 15
                                        {00,00,16,10,10,10,10,10,16,17,10,10,00,00,16,10,10,16,00,00,10,10,10,16,16,16,16,10,10,10,10,16,16,16,10,16,16,16,10,16,16,16,16,16,16,10,10,10,00,00,00,00,00,00,00,00,00,00,00,00}
};
hgeVector g_vBGPosition = hgeVector(0,0);

float FindIntersect(float x, float y, float slope)
{
    return x-y*slope;
}

// every block in allBlocks that contacts Bound will replace the blocks in contBlocks
/*
void FindContactBlocks(c_block *allBlocks, c_block *contBlocks, hgeRect Bound)
{

}
*/

bool FrameFunc()
{
    float dt = hge->Timer_GetDelta();

    hge->Input_GetMousePos(&mouseposx, &mouseposy);

    if(gamemode == 0)
    {
        button1->MouseOver(mouseposx, mouseposy);
        button2->MouseOver(mouseposx, mouseposy);
        button3->MouseOver(mouseposx, mouseposy);
        button4->MouseOver(mouseposx, mouseposy);

        if(hge->Input_KeyDown(HGEK_LBUTTON))
        {
            if(button1->CheckPressed(mouseposx, mouseposy))
            {
                Player1 = new c_player(hgeVector(100, 500), hgeVector(2,0));
                gamemode = 1;
                for(short y = 0; y < MAP_HEIGHT; y++)
                {
                    for(short x = 0; x < MAP_WIDTH; x++)
                    {
                        short modMap = introMap[y][x] % 10;
                        if(introMap[y][x] < 10 && introMap[y][x] >= 0)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), 0, g_tEBlocks[0]);
                            Backgrounds.push_back(Block);
                        }
                        else if(modMap == 0 || modMap == 5 || modMap == 6)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), introMap[y][x], g_tEBlocks[0]);
                            Blocks.push_back(Block);
                        }
                        else if(modMap > 0)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), introMap[y][x], g_tEBlocks[0]);
                            Slopes.push_back(Block);
                        }
                    }
                }
            }
            if(button2->IsAvailable() && button2->CheckPressed(mouseposx, mouseposy))
            {
                Player1 = new c_player(hgeVector(180, 500), hgeVector(2,0));
                gamemode = 2;
                //c_block* Block;
                for(short y = 0; y < MAP_HEIGHT; y++)
                {
                    for(short x = 0; x < MAP_WIDTH; x++)
                    {
                        short modMap = Map2[y][x] % 10;
                        if(Map2[y][x] < 10 && Map2[y][x] >= 0)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), 0, g_tEBlocks[0]);
                            Backgrounds2.push_back(Block);
                        }
                        else if(modMap == 0 || modMap == 5 || modMap == 6)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), Map2[y][x], g_tEBlocks[0]);
                            Blocks2.push_back(Block);
                        }
                        else if(modMap == 7)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), Map2[y][x], g_tEBlocks[0]);
                            Spikes2.push_back(Block);
                        }
                        else if(modMap > 0)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), Map2[y][x], g_tEBlocks[0]);
                            Slopes2.push_back(Block);
                        }
                    }
                }
            }
            if(button3->IsAvailable() && button3->CheckPressed(mouseposx, mouseposy))
            {
                Player1 = new c_player(hgeVector(180, 640), hgeVector(1,0));
                gamemode = 3;
                //c_block* Block;
                for(short y = 0; y < MAP_HEIGHT; y++)
                {
                    for(short x = 0; x < MAP_WIDTH; x++)
                    {
                        short modMap = Map3[y][x] % 10;
                        if(Map3[y][x] < 10 && Map3[y][x] >= 0)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), 0, g_tEBlocks[0]);
                            Backgrounds3.push_back(Block);
                        }
                        else if(modMap == 0 || modMap == 5 || modMap == 6)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), Map3[y][x], g_tEBlocks[0]);
                            Blocks3.push_back(Block);
                        }
                        else if(modMap == 7)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), Map3[y][x], g_tEBlocks[0]);
                            Spikes3.push_back(Block);
                        }
                        else if(modMap > 0)
                        {
                            Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), Map3[y][x], g_tEBlocks[0]);
                            Slopes3.push_back(Block);
                        }
                    }
                }
            }
            if(button4->CheckPressed(mouseposx, mouseposy))
            {
                return true;
            }
        }
    }
    else {
        // SCREEN SCROLLING
        //if(g_vBGPosition.x <= SCREEN_WIDTH) g_vBGPosition.x += 0.02*(mouseposx-400);
        //else g_vBGPosition = hgeVector(-982,0);
        // My own addition
        if(g_vBGPosition.x < -982) g_vBGPosition = hgeVector(SCREEN_WIDTH,0);

        g_nBGAlpha = (short) (0.25*mouseposx);

        if(hge->Input_GetKeyState(HGEK_ESCAPE))
        {
            printf("hello");
            gamemode = 0;
            delete Player1;
            printf("bye");
        }
    //GENERALSTUFF ENENMIES
        if(gamemode == 1)
        {
            if(Player1->GetPosition().x > 2600)
            {
                Player1->SetControl(false);
                if(gamesave <= 1)
                {
                    gamesave = 2;
                    button2->Lighten();
                }
                //fnt->SetColor(0xFFFFFFFF);
            }
            /*
            if(Enemies.size() < 5)
            {
                short Health = hge->Random_Int(50, 100);
                c_enemy* Enemy = new c_enemy( hgeVector(830, hge->Random_Int(50, 550)), hgeVector(-hge->Random_Int(2,8), hge->Random_Int(-4, 4)), Health, g_tEColors[hge->Random_Int(0,4)]);
                Enemies.push_back(Enemy);
            }
            */

            for(std::list<c_enemy*>::iterator i = Enemies.begin(); i != Enemies.end(); /**/)
            {
                if((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
                {
                    delete (*i);
                    i = Enemies.erase(i);
                }
                else
                {
                    (*i)->Update(dt);
                    i++;
                }
            }

        //PLAYER GRAVITY
            Player1->UpdateBound();
            Player1->Update(dt);
            Player1->UpdateBound();


        //TERRAIN COLLISION
            //float pheight = Player1->GetHeight();

            bool finecheck = false;
            c_block* fineBlock;
            bool OnGround = false;
            // loops through all tiles looking for collision

            for(std::list<c_block*>::iterator i = Slopes.begin(); i != Slopes.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    OnGround = true;
                    Player1->TileReactSlope((*i)->GetBoundingBox(), (*i)->GetTileType());
                }
            }

            for(std::list<c_block*>::iterator i = Blocks.begin(); i != Blocks.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    OnGround = true;
                    finecheck = true;
                    if(!Player1->TileReact((*i)->GetBoundingBox()))     finecheck = false;
                    else    fineBlock = (*i);
                }
            }

            if(!OnGround && !((hge->Input_GetKeyState(HGEK_SPACE)) || (hge->Input_GetKeyState(HGEK_UP))))	Player1->RemoveJump();
            // more refined check for tiles
            if(finecheck)
            {
                Player1->TileReactFine(fineBlock->GetBoundingBox());
            }
            // escape
        }
        else if(gamemode == 2)
        {
            if(Player1->GetPosition().x > 2600)
            {
                Player1->SetControl(false);
                if(gamesave <= 2)
                {
                    gamesave = 3;
                    button3->Lighten();
                }
                //fnt->SetColor(0xFFFFFFFF);
            }

            for(std::list<c_enemy*>::iterator i = Enemies.begin(); i != Enemies.end(); /**/)
            {
                if((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
                {
                    delete (*i);
                    i = Enemies.erase(i);
                }
                else
                {
                    (*i)->Update(dt);
                    i++;
                }
            }

        //PLAYER GRAVITY
            Player1->UpdateBound();
            Player1->Update(dt);
            Player1->UpdateBound();


        //TERRAIN COLLISION
            //float pheight = Player1->GetHeight();

            bool finecheck = false;
            c_block* fineBlock;
            bool OnGround = false;
            // loops through all tiles looking for collision

            for(std::list<c_block*>::iterator i = Slopes2.begin(); i != Slopes2.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    OnGround = true;
                    Player1->TileReactSlope((*i)->GetBoundingBox(), (*i)->GetTileType());
                }
            }
            for(std::list<c_block*>::iterator i = Spikes2.begin(); i != Spikes2.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    Player1->SetPosition(hgeVector(160, 540));
                }
            }

            for(std::list<c_block*>::iterator i = Blocks2.begin(); i != Blocks2.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    OnGround = true;
                    finecheck = true;
                    if(!Player1->TileReact((*i)->GetBoundingBox()))     finecheck = false;
                    else    fineBlock = (*i);
                }
            }

            if(!OnGround && !((hge->Input_GetKeyState(HGEK_SPACE)) || (hge->Input_GetKeyState(HGEK_UP))))	Player1->RemoveJump();
            // more refined check for tiles
            if(finecheck)
            {
                Player1->TileReactFine(fineBlock->GetBoundingBox());
            }
            // escape
        }
        else if(gamemode == 3)
        {
            if(Player1->GetPosition().x > 2640)
            {
                Player1->SetControl(false);
                if(gamesave <= 3)
                {
                    gamesave = 4;
                }
                //fnt->SetColor(0xFFFFFFFF);
            }
            /*
            if(Enemies.size() < 5)
            {
                short Health = hge->Random_Int(50, 100);
                c_enemy* Enemy = new c_enemy( hgeVector(830, hge->Random_Int(50, 550)), hgeVector(-hge->Random_Int(2,8), hge->Random_Int(-4, 4)), Health, g_tEColors[hge->Random_Int(0,4)]);
                Enemies.push_back(Enemy);
            }
            */

            for(std::list<c_enemy*>::iterator i = Enemies.begin(); i != Enemies.end(); /**/)
            {
                if((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
                {
                    delete (*i);
                    i = Enemies.erase(i);
                }
                else
                {
                    (*i)->Update(dt);
                    i++;
                }
            }

        //PLAYER GRAVITY
            Player1->UpdateBound();
            Player1->Update(dt);
            Player1->UpdateBound();


        //TERRAIN COLLISION
            //float pheight = Player1->GetHeight();

            bool finecheck = false;
            c_block* fineBlock;
            bool OnGround = false;
            // loops through all tiles looking for collision

            for(std::list<c_block*>::iterator i = Slopes3.begin(); i != Slopes3.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    OnGround = true;
                    Player1->TileReactSlope((*i)->GetBoundingBox(), (*i)->GetTileType());
                }
            }
            for(std::list<c_block*>::iterator i = Spikes3.begin(); i != Spikes3.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    Player1->SetPosition(hgeVector(640, 240));
                }
            }
            for(std::list<c_block*>::iterator i = Blocks3.begin(); i != Blocks3.end(); i++)
            {
                if(Player1->Collision((*i)->GetBoundingBox()))
                {
                    OnGround = true;
                    finecheck = true;
                    if(!Player1->TileReact((*i)->GetBoundingBox()))     finecheck = false;
                    else    fineBlock = (*i);
                }
            }

            if(!OnGround && !((hge->Input_GetKeyState(HGEK_SPACE)) || (hge->Input_GetKeyState(HGEK_UP))))	Player1->RemoveJump();
            // more refined check for tiles
            if(finecheck)
            {
                Player1->TileReactFine(fineBlock->GetBoundingBox());
            }
            // escape
        }


    }
	return false;
}


bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	g_sBackground->Render(g_vBGPosition.x, g_vBGPosition.y);
	if(g_vBGPosition.x > -1)
	g_sBackground->Render(g_vBGPosition.x - 982 - SCREEN_WIDTH, 0);
	g_sBGGapFix->Render(g_vBGPosition.x - 28, 0);
    fnt->SetColor(0xFFFFFFFF);

    if(gamemode == 0)
    {
        button2->Render();
        button1->Render();
        button3->Render();
        button4->Render();

        g_sCursor->Render(mouseposx, mouseposy);
        stand_block->Render(220, 460);
        stand_block->Render(330, 460);
        stand_block->Render(440, 460);
        stand_block->Render(550, 460);
        static int momjump = 410;
        static int sisjump = 410;
        static int mejump = 410;
        static int dadjump = 410;

        momsprite->Render(226, momjump);
        if(gamesave > 3)
        {
            sissprite->Render(342, sisjump);
            fnt->SetColor(0xFF181111);
            fnt->Render(385, 122, HGETEXT_CENTER, "HAPPY BIRTHDAY MOM!");
            fnt->SetColor(0xFFFF3333);
            fnt->Render(384, 120, HGETEXT_CENTER, "HAPPY BIRTHDAY MOM!");
            fnt->SetColor(0xFFEEEEEE);
            static int momjumps = 0;
            static int sisjumps = 0;
            static int mejumps = 0;
            static int dadjumps = 0;
            momjump -= momjumps;
            sisjump -= sisjumps;
            mejump -= mejumps;
            dadjump -= dadjumps;

            momjumps -= 1;
            sisjumps -= 1;
            mejumps -= 1;
            dadjumps -= 1;

            if(momjump >= 410)
            {
                momjump = 410;
                momjumps = 7;
            }
            if(sisjump >= 410)
            {
                sisjump = 410;
                sisjumps = 5;
            }
            if(mejump >= 410)
            {
                mejump = 410;
                mejumps = 6;
            }
            if(dadjump >= 410)
            {
                dadjump = 410;
                dadjumps = 7;
            }
        }
        if(gamesave > 2)
        {
            mesprite->Render(450, mejump);
        }
        if(gamesave > 1)
        {
            dadsprite->Render(562, dadjump);
        }
    }
    else
    {
        float TargetOffsetX;
        if(Player1->GetFacingRight())
        {
            TargetOffsetX = -Player1->GetPosition().x + SCREEN_WIDTH/2 - 150;
        }
        else
        {
            TargetOffsetX = -Player1->GetPosition().x + SCREEN_WIDTH/2 + 150;
        }
        float TargetOffsetY = -Player1->GetPosition().y + SCREEN_HEIGHT/2;
        ActualOffsetX += (TargetOffsetX - ActualOffsetX)/40;
        ActualOffsetY += (TargetOffsetY - ActualOffsetY)/40;
        if(ActualOffsetY > 0)
        {
            ActualOffsetY = 0;
        }
        else if(ActualOffsetY < -192)
        {
            ActualOffsetY = -192;
        }
        if(ActualOffsetX > 0)
        {
            ActualOffsetX = 0;
        }
        else if(ActualOffsetX < -2112)
        {
            ActualOffsetX = -2112;
        }
        //float OffsetXAdjust = -ActualOffsetX;
        //float OffsetYAdjust = ActualOffsetY;

        Player1->Render(ActualOffsetX, ActualOffsetY);
        if(gamemode == 1)
        {
            for(std::list<c_block*>::iterator i = Blocks.begin(); i!= Blocks.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Slopes.begin(); i!= Slopes.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Backgrounds.begin(); i!= Backgrounds.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            dadsprite->Render((int)(2720+ActualOffsetX), (int)(476+ActualOffsetY));
            if(gamesave > 1)
            {
                fnt->Render(384, 170, HGETEXT_CENTER, "CONGRATULATIONS! YOU FOUND DAD!");
                fnt->Render(384, 210, HGETEXT_CENTER, "PRESS ESCAPE FOR THE NEXT LEVEL");
            }
        }
        else if(gamemode == 2)
        {
            for(std::list<c_block*>::iterator i = Blocks2.begin(); i!= Blocks2.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Spikes2.begin(); i!= Spikes2.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Slopes2.begin(); i!= Slopes2.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Backgrounds2.begin(); i!= Backgrounds2.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            mesprite->Render((int)(2720+ActualOffsetX), (int)(476+ActualOffsetY));
            if(gamesave > 2)
            {
                fnt->Render(384, 170, HGETEXT_CENTER, "CONGRATULATIONS! YOU FOUND MAX!");
                fnt->Render(384, 210, HGETEXT_CENTER, "PRESS ESCAPE FOR THE NEXT LEVEL");
            }
        }
        else if(gamemode == 3)
        {
            for(std::list<c_block*>::iterator i = Blocks3.begin(); i!= Blocks3.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Spikes3.begin(); i!= Spikes3.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Slopes3.begin(); i!= Slopes3.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            for(std::list<c_block*>::iterator i = Backgrounds3.begin(); i!= Backgrounds3.end(); i++)
            {
                (*i)->Render(ActualOffsetX, ActualOffsetY);
            }
            sissprite->Render((int)(2760+ActualOffsetX), (int)(476+ActualOffsetY));
            if(gamesave > 3)
            {
                fnt->Render(384, 170, HGETEXT_CENTER, "CONGRATULATIONS! YOU FOUND ESTER!");
                fnt->Render(384, 210, HGETEXT_CENTER, "PRESS ESCAPE");
            }
        }
    }
	hge->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	//hge->System_SetState(HGE_LOGFILE, "hge_tut06.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Zikis");
	hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_FPS, 50);
	if(hge->System_Initiate())
	{

	    g_tEColors[0]   = hge->Texture_Load("images/eSpritesheet_40x30.png");
	    g_tEColors[1]   = hge->Texture_Load("images/eSpritesheet_40x30_hue1.png");
	    g_tEColors[2]   = hge->Texture_Load("images/eSpritesheet_40x30_hue2.png");
	    g_tEColors[3]   = hge->Texture_Load("images/eSpritesheet_40x30_hue3.png");
	    g_tEColors[4]   = hge->Texture_Load("images/eSpritesheet_40x30_hue4.png");

	    g_tEBlocks[0]   = hge->Texture_Load("images/block1.png");


	    g_eBGMusic      = hge->Effect_Load("sounds/momv.ogg");
        hge->Effect_PlayEx(g_eBGMusic, 40, 0, 0, true);

        g_tBullet       = hge->Texture_Load("images/bullet.png");
        family          = hge->Texture_Load("images/Spritesheet_48x44.png");
        g_tBackground   = hge->Texture_Load("images/farback.jpg");
        g_tCursor       = hge->Texture_Load("images/cursor.png");
        g_tBGGapFix     = hge->Texture_Load("images/bg_gapfix.jpg");

		fnt=new hgeFont("font1.fnt");

        g_sBGGapFix     = new hgeSprite(g_tBGGapFix, 0, 0, 64, SCREEN_HEIGHT);

        momsprite         = new hgeSprite(family, 0, 0, 30, 50);
        sissprite         = new hgeSprite(family, 0, 50, 30, 52);
        mesprite         = new hgeSprite(family, 30, 50, 30, 52);
        dadsprite         = new hgeSprite(family, 60, 50, 30, 52);

        g_sBackground   = new hgeSprite(g_tBackground, 0, 0, 1782, SCREEN_HEIGHT);
        g_sCursor        = new hgeSprite(g_tCursor, 0, 0, 16, 20);
        g_vBGPosition   = hgeVector(982, 0);

        stand_block     = new hgeSprite(g_tEBlocks[0], 0, 0, 48, 48);

        button1 = new MenuButton(fnt, 390, 200, "Level 1");
        button1->Lighten();


        button2 = new MenuButton(fnt, 390, 240, "Level 2");
        button3 = new MenuButton(fnt, 390, 280, "Level 3");
        buttonz = new MenuButton(fnt, 390, 240, "Level 2"); // weird bug
        button4 = new MenuButton(fnt, 390, 320, "Exit");
        button4->Lighten();

// MAKING TERRAIN
/*
        c_block* Block;
        for(short y = 0; y < MAP_HEIGHT; y++)
        {
            for(short x = 0; x < MAP_WIDTH; x++)
            {
                short modMap = introMap[y][x] % 10;
                if(introMap[y][x] < 10 && introMap[y][x] >= 0)
                {
                    Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), 0, g_tEBlocks[0]);
                    Backgrounds.push_back(Block);
                }
                else if(modMap == 0 || modMap == 5)
                {
                    Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), introMap[y][x], g_tEBlocks[0]);
                    Blocks.push_back(Block);
                }
                else if(modMap > 0)
                {
                    Block = new c_block(hgeVector(x*BLOCK_BIGNESS,y*BLOCK_BIGNESS), introMap[y][x], g_tEBlocks[0]);
                    Slopes.push_back(Block);
                }
            }
        }
*/
        hge->Input_SetMousePos(400.0f, 300.0f);
        hge->System_Start();
	}
    else
    {
      MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }

	// Clean up and shutdown
    hge->Effect_Free(g_eBGMusic);

	hge->Texture_Free(g_tBullet);
	hge->Texture_Free(family);
    hge->Texture_Free(g_tBackground);
    hge->Texture_Free(g_tCursor);
    hge->Texture_Free(g_tBGGapFix);

    for(short i = 0; i<5; i++) hge->Texture_Free(g_tEColors[i]);

    for(short i = 0; i<1; i++) hge->Texture_Free(g_tEBlocks[i]);


    for(std::list<c_bullet*>::iterator i = Bullets.begin(); i != Bullets.end(); i++)
    {
        delete (*i);
        i = Bullets.erase(i);
    }

    for(std::list<c_enemy*>::iterator i = Enemies.begin(); i != Enemies.end(); i++)
    {
        delete(*i);
        i = Enemies.erase(i);
    }


    for(std::list<c_block*>::iterator i = Blocks.begin(); i != Blocks.end(); i++)
    {
        delete(*i);
        i = Blocks.erase(i);
    }
    for(std::list<c_block*>::iterator i = Slopes.begin(); i != Slopes.end(); i++)
    {
        delete(*i);
        i = Slopes.erase(i);
    }
    for(std::list<c_block*>::iterator i = Backgrounds.begin(); i != Backgrounds.end(); i++)
    {
        delete(*i);
        i = Backgrounds.erase(i);
    }



    delete g_sBGGapFix;
    delete g_sBackground;
    delete momsprite;
    delete dadsprite;
    delete mesprite;
    delete sissprite;
    delete stand_block;

    delete g_sCursor;
    delete fnt;

    delete button1;
    delete button2;
    delete button3;
    delete button4;
    delete buttonx;
    delete buttony;
    delete buttonz;


	hge->System_Shutdown();
	hge->Release();
	return 0;
}
