#pragma once
#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include <vector>
#include<SFML\Audio.hpp>
class Output	//The application manager should have a pointer to this class
{
private:

	//private update window for sfml


	//Added by us ------- CHOSEN AS POINTERS BECAUSE THEY ARE USED IN CONST FUNCTIONS
	sf::RenderWindow* pWind;	//Pointer to the Graphics Window
	sf::Text *statusMessage;		//message text
	sf::Text ZoomPercent;		//message text
	sf::Font messageFont;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	sf::SoundBuffer shapeBuffer[4];
	sf::Sound shapeSound[4];


	sf::RectangleShape *toolbarBackGround;
	sf::RectangleShape *toolbarLine;
	sf::RectangleShape *windowBackGround;			//background rectangle
	sf::RectangleShape *stbar;						//statusbar rectangle
	sf::Texture MenuItemImages[DRAW_ITM_COUNT];		//Menu items images
	sf::Sprite MenuItemSprites[DRAW_ITM_COUNT];		//Menu items sprites
	sf::Texture MenuPlayImages[PLAY_ITM_COUNT];		//Play items images
	sf::Sprite MenuPlaySprites[PLAY_ITM_COUNT];		//Play items sprites

	sf::Texture ZoomImages[2];		//Zoom images
	sf::Sprite ZoomSprites[2];		//Zoom sprites

	vector<sf::Shape*> *drawnObjects;	//vector to redraw shapes any new events

	string fileName;
	//////////////////////////////////////////////////////////////////////////////////

public:
	Output();

	sf::RenderWindow* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void UpdateWindow() const;
	void DrawGuideCircle(Point center, float raduis) const;
	void DrawGuideTriangle(Point p1, Point p2, Point p3) const;
	void DrawGuideRectangle(Point P1, Point P2) const;
	void DrawGuideLine(Point P1, Point P2) const;
	void DrawPopMenu(int x, int y);
	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area


								// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a rectangle
	void PlayRectangleSound();
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const; //Draw a line
	void PlayLineSound();
	void DrawCirc(Point C, float R, GfxInfo CircGfxInfo, bool selected) const;       //Draw a circle
	void PlayCircleSound();
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const; //Draw a triangle
	void PlayTriangleSound();

	// -- Window appearance functions	
	void dimIcons(int *iconsIndex, int size);//dim specific icons
	void brightIcons(int * iconsIndex, int size);
	void brightAllDrawIcons();
	void SetWindowTitle(string title);
	void PrintMessage(string msg) const;	//Print a message on Status bar
	void UpdateZoomString();

	void createCreditsWindow();

	sf::Color getCrntDrawColor() const;	//get current drwawing color
	sf::Color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	bool getCrntIsFilled() const;		//get current is filled status


	~Output();

};

#endif
