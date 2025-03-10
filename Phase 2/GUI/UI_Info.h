#pragma once
#ifndef UI_INFO_H
#define UI_INFO_H

#include "SFML\Graphics.hpp"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,		//Recangle item in menu
	ITM_CIRC,		//Circle item in menu

					//TODO: Add more items names here
	ITM_Tri,
	ITM_Line,
	ITM_Color,
	ITM_BackGround,
	ITM_Resize,
	ITM_Rotate,
	ITM_Save,
	ITM_Load,
	ITM_Cut,
	ITM_Copy,
	ITM_Paste,
	ITM_Front,
	ITM_Back,
	ITM_Del,
	ITM_Undo,
	ITM_Redo,
	ITM_Play,
	ITM_EXIT,		//Exit item

	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here

	//TODO: Add more items names here
	ITM_Pick,
	ITM_Find,
	ITM_Draw,
	ITM_EXIT2,
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth,		//Width of each item in toolbar menu
		PopMenuWidth, PopMenuHeight;	//Width of pop up menu
	UI_Info() {
		zoomFactor = 1;
	}

	sf::Color DrawColor;		//Drawing color
	sf::Color FillColor;		//Filling color
	sf::Color HighlightColor;	//Highlighting color
	sf::Color MsgColor;			//Messages color
	sf::Color BkGrndColor;		//Background color
	sf::Color StatusBarColor;	//Status bar color
	sf::Color nonFillColor;	//Non filled color
	int PenWidth;			//width of the pen that draws shapes

							/// Add more members if needed
	float zoomFactor;
	int infoWidth;
	int zoomIconWidth;

}UI;	//create a global object UI

#endif
