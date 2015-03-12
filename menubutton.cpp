/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Tutorial 06 - Creating menus
*/

// In menuitem.cpp/h we define the
// behaviour of our custom GUI control

#include "menubutton.h"

// This is a GUI control constructor,
// we should initialize all the variables here
MenuButton::MenuButton(hgeFont *_fnt, float _x, float _y, char *_title)
{
	float w;
    float offset = 0;
	fnt=_fnt;
	title=_title;

	color.SetHWColor(0xFF777777);
	scolor.SetHWColor(0x88070707);
	available = false;

	w=fnt->GetStringWidth(title);
	menurect.Set(_x-w/2, _y, _x+w/2, _y+fnt->GetHeight());
}

// This method is called when the control should be rendered
void MenuButton::Render()
{
    fnt->SetColor(scolor.GetHWColor());
	fnt->Render(menurect.x1+offset, menurect.y1+offset, HGETEXT_LEFT, title);
	fnt->SetColor(color.GetHWColor());
	fnt->Render(menurect.x1, menurect.y1-offset-1, HGETEXT_LEFT, title);
}

void MenuButton::Lighten()
{
    available = true;
    color.SetHWColor(0xFFDDDDDD);
}

void MenuButton::MouseOver(float x, float y)
{
    if(available)
    {
        if(menurect.TestPoint(x,y))
        {
            color.SetHWColor(0xFFFFFFFF);
            offset = 1;
        }
        else
        {
            color.SetHWColor(0xFFDDDDDD);
            offset = 0;
        }
    }

}

// This method is called to notify the control
// that the left mouse button state has changed.
// If it returns true - the caller will receive
// the control's ID
bool MenuButton::CheckPressed(float x, float y)
{
	return menurect.TestPoint(x,y);
}

bool MenuButton::IsAvailable()
{
    return available;
}
