#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,	//Draw Rectangle
	DRAW_CIRC,		//Draw Circle
	DRAW_TRI,		//Draw Triangle
	DRAW_LINE,		//Draw Line	
	CHNG_CLR,		//change color
	ZOOM,           //To zoom
	RESIZE,			//Resize a figure(s)
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	CUT,            //To cut
	COPY,           //To copy
	PASTE,          //To Paste 
	DEL,			//Delete a figure(s)
	UNDO,           //Undo action
	REDO,           //Redo action
	SEND_BACK,		//Send a figure to the back of all figures
	BRNG_FRNT,		//Bring a figure to the front of all figures
	EXIT,			//Exit the application

	//******************************************************************************************
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	MOVE,			//Move a figure(s)
	ROTATE			//Rotate a figure(s)
	///TODO: Add more action types (if needed)
};

enum ChangeColor {
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	CHNG_BK_CLR,	//Change background color
};

enum Zoom {
	ZOOM_IN,       //To zoomIn
	ZOOM_OUT       //T zoomOut
};

enum Resize {
	RESIZE_QUARTER,
	RESIZE_HALF,
	RESIZE_DOUBLE,
	RESIZE_FOUR
};

enum Rotate {
	NINTY,
	EIGHTY,
	SEVENTY
};
struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif