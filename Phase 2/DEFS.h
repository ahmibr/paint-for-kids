#ifndef DEFS_H
#define DEFS_H

#include <SFML/Graphics.hpp>

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_CIRC,		//Draw Circle
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_BK_CLR,	//Change background color
	DEL,			//Delete a figure(s)
	MOVE,			//Move a figure(s)
	RESIZE,			//Resize a figure(s)
	ROTATE,			//Rotate a figure(s)
	SEND_BACK,		//Send a figure to the back of all figures
	BRNG_FRNT,		//Bring a figure to the front of all figures
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application
	DRAWING_AREA,
	SELECT,
	MULTI_SELECT,
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar

	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,			//Switch interface to Play mode

	///TODO: Add more action types (if needed)
	UNDO,
	REDO,
	ZOOM_IN,
	ZOOM_OUT,
	CUT,
	COPY,
	PASTE,

	MOVE_DRAG,
	RESIZE_DRAG,
	ROTATE_DRAG,

	PICK,			//PLAY MODE
	FIND
};

struct Point	//To be used for figures points
{
	int x, y;
	Point() { x = 0, y = 0; }
	Point(int _x, int _y) :x(_x), y(_y) {}
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	sf::Color DrawClr;	//Draw color of the figure
	sf::Color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders
	GfxInfo() {
		DrawClr = sf::Color::Black;
		FillClr = sf::Color::White;
		isFilled = true;
		BorderWdth = 2;
	}
};

#endif