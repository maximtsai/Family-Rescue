/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

// In menuitem.cpp/h we define the
// behaviour of our custom GUI control

#include "hge.h"
#include "hgegui.h"
#include "hgefont.h"
#include "hgecolor.h"


class MenuButton
{
public:
	MenuButton(hgeFont *fnt, float x, float y, char *title);

	 void	Render();
    void    MouseOver(float x, float y);
    void    Lighten();
    bool    CheckPressed(float x, float y);
    bool    IsAvailable();

	 bool	MouseLButton(bool bDown);

private:

	hgeFont		*fnt;
	char		*title;
	hgeRect     menurect;

    bool        available;
	hgeColor	color, scolor;
	float		offset;
};
