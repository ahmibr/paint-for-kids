#include "Output.h"
#include <cmath>
#include<SFML\Graphics.hpp>

#define PI acos(-1)
Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1280;
	UI.height = 720;
	UI.wx = 5;
	UI.wy = 5;

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 64;

	UI.DrawColor = sf::Color::Blue;	//Drawing color
	UI.FillColor = sf::Color::Green;	//Filling color
	UI.MsgColor = sf::Color::Red;		//Messages color
	UI.BkGrndColor = sf::Color(255, 250, 205);	//Background color
	UI.nonFillColor = sf::Color(0, 0, 0, 0); //added by student for transparent object
	UI.HighlightColor = sf::Color::Magenta;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = sf::Color(64, 224, 208);
	UI.PenWidth = 3;	//width of the figures frames


	//------------------------------------------------Added by student-----------------------------------------------//
	//initializing some variables about message text
	messageFont.loadFromFile("Resource Files\\Arial.ttf");
	statusMessage = new sf::Text("", messageFont, 20);
	statusMessage->setFillColor(UI.MsgColor);
	statusMessage->setPosition(sf::Vector2f(0, UI.height - UI.StatusBarHeight));

	//initailizing the line under toolbar
	toolbarLine = new sf::RectangleShape((sf::Vector2f(UI.width, 3)));

	//initializing boxes of status bar | window background | Menu items
	stbar = new sf::RectangleShape(sf::Vector2f(UI.width, UI.height));
	windowBackGround = new sf::RectangleShape(sf::Vector2f(UI.width, UI.height));

	///////////////////////////////////////////////////////////////////////////////////////////////
	//initializing boxes of status bar | window background | Menu items

	MenuItemImages[ITM_RECT].loadFromFile("images\\MenuItems\\Menu_Rect.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_CIRC].loadFromFile("images\\MenuItems\\Menu_Circ.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Tri].loadFromFile("images\\MenuItems\\Menu_Tri.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Line].loadFromFile("images\\MenuItems\\Menu_Line.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Color].loadFromFile("images\\MenuItems\\Menu_Color.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Zoom].loadFromFile("images\\MenuItems\\Menu_Zoom.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Resize].loadFromFile("images\\MenuItems\\Menu_Resize.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Save].loadFromFile("images\\MenuItems\\Menu_Save.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Load].loadFromFile("images\\MenuItems\\Menu_Load.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Cut].loadFromFile("images\\MenuItems\\Menu_Cut.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Copy].loadFromFile("images\\MenuItems\\Menu_Copy.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Paste].loadFromFile("images\\MenuItems\\Menu_Paste.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Front].loadFromFile("images\\MenuItems\\Menu_Front.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Back].loadFromFile("images\\MenuItems\\Menu_Back.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Del].loadFromFile("images\\MenuItems\\Menu_Del.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Undo].loadFromFile("images\\MenuItems\\Menu_Undo.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Redo].loadFromFile("images\\MenuItems\\Menu_Redo.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_Play].loadFromFile("images\\MenuItems\\Menu_Play.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuItemImages[ITM_EXIT].loadFromFile("images\\MenuItems\\Menu_Exit.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));

	MenuPlayImages[ITM_Pick].loadFromFile("images\\MenuItems\\Menu_Pick.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuPlayImages[ITM_Find].loadFromFile("images\\MenuItems\\Menu_Find.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuPlayImages[ITM_Draw].loadFromFile("images\\MenuItems\\Menu_Draw.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));
	MenuPlayImages[ITM_EXIT2].loadFromFile("images\\MenuItems\\Menu_Exit.jpg", sf::IntRect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight));

	//Draw a line under the toolbar
	toolbarLine->setOutlineColor(sf::Color::Red);
	toolbarLine->setFillColor(sf::Color::Red);
	toolbarLine->setPosition(sf::Vector2f(0, UI.ToolBarHeight));

	for (int i = 0; i < DRAW_ITM_COUNT; i++)
	{
		MenuItemSprites[i].setTexture(MenuItemImages[i]);
		MenuItemSprites[i].setPosition(sf::Vector2f(i * UI.MenuItemWidth, 0));
	}

	for (int i = 0; i < PLAY_ITM_COUNT; i++)
	{
		MenuPlaySprites[i].setTexture(MenuPlayImages[i]);
		MenuPlaySprites[i].setPosition(sf::Vector2f(i * UI.MenuItemWidth, 0));
	}

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->setTitle("Paint for Kids - Programming Techniques Project");

	//a vector to hold drawn objects on screen
	drawnObjects = new vector<sf::Drawable*>;

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

sf::RenderWindow* Output::CreateWind(int w, int h, int x, int y) const
{
	sf::RenderWindow* pW = new sf::RenderWindow(sf::VideoMode(w, h), "Paint for Kids - Programming Techniques Project", sf::Style::Close);
	pW->setPosition(sf::Vector2i(x, y));

	windowBackGround->setOutlineColor(UI.BkGrndColor);
	windowBackGround->setFillColor(UI.BkGrndColor);
	windowBackGround->setPosition(0, 0);

	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	stbar->setOutlineColor(UI.StatusBarColor);
	stbar->setFillColor(UI.StatusBarColor);
	stbar->setPosition(sf::Vector2f(0, UI.height - UI.StatusBarHeight));

	UpdateWindow();
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by making the text hold null
	statusMessage->setString("");

	UpdateWindow();
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	//TODO: Prepare images for each menu item and add it to the list
	//Draw menu item one image at a time

	UpdateWindow();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	UpdateWindow();

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{

	for (int i = 0; i < drawnObjects->size(); i++)
	{
		delete drawnObjects->at(i);
	}
	drawnObjects->clear();

	UpdateWindow();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	statusMessage->setString(msg);

	UpdateWindow();
}
//////////////////////////////////////////////////////////////////////////////////////////

sf::Color Output::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

sf::Color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	sf::Color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	sf::RectangleShape *rect = new sf::RectangleShape(sf::Vector2f(abs(P1.x - P2.x), abs(P1.y - P2.y)));

	int x, y;

	if (P1.x < P2.x)
		x = P1.x;
	else
		x = P2.x;
	if (P1.y < P2.y)
		y = P1.y;
	else
		y = P2.y;

	rect->setPosition(x, y);
	rect->setOutlineColor(DrawingClr);
	rect->setOutlineThickness(RectGfxInfo.BorderWdth);

	//Set Drawing color & width

	if (RectGfxInfo.isFilled)
	{
		rect->setFillColor(RectGfxInfo.FillClr);
	}
	else
		rect->setFillColor(UI.nonFillColor);

	drawnObjects->push_back(rect);

	UpdateWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	sf::Color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.FillClr;

	sf::RectangleShape *line = new sf::RectangleShape(sf::Vector2f(sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2)), LineGfxInfo.BorderWdth));

	if (P1.x > P2.x)
		swap(P1, P2);

	line->setPosition(sf::Vector2f(P2.x, P2.y));
	line->rotate(180 * atan2(P1.y - P2.y, P1.x - P2.x) / PI);

	line->setFillColor(DrawingClr);

	drawnObjects->push_back(line);

	UpdateWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCirc(Point C, Point R, GfxInfo CircGfxInfo, bool selected) const
{
	sf::Color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircGfxInfo.DrawClr;

	float raduis = sqrt(pow(R.y - C.y, 2) + pow(R.x - C.x, 2));

	sf::CircleShape *circ = new sf::CircleShape(raduis);

	circ->setPosition(sf::Vector2f(sf::Vector2f(abs(C.x), abs(C.y))));
	circ->setOutlineColor(DrawingClr);
	circ->setOutlineThickness(CircGfxInfo.BorderWdth);
	circ->setOrigin(raduis, raduis);

	if (CircGfxInfo.isFilled)
	{
		circ->setFillColor(CircGfxInfo.FillClr);
	}
	else
		circ->setFillColor(UI.nonFillColor);

	drawnObjects->push_back(circ);

	UpdateWindow();

}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const {

	sf::ConvexShape *triangle;

	triangle = new sf::ConvexShape(3);

	triangle->setPoint(0, sf::Vector2f(P1.x, P1.y));
	triangle->setPoint(1, sf::Vector2f(P2.x, P2.y));
	triangle->setPoint(2, sf::Vector2f(P3.x, P3.y));

	if (TriangleGfxInfo.isFilled)
		triangle->setFillColor(TriangleGfxInfo.FillClr);
	else
		triangle->setFillColor(UI.nonFillColor);

	if (selected)
		triangle->setOutlineColor(UI.HighlightColor);
	else
		triangle->setOutlineColor(TriangleGfxInfo.DrawClr);

	triangle->setOutlineThickness(TriangleGfxInfo.BorderWdth);

	drawnObjects->push_back(triangle);

	UpdateWindow();
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::UpdateWindow() const {

	pWind->clear();

	pWind->draw(*windowBackGround);

	for (int i = 0; i < drawnObjects->size(); i++)
	{
		pWind->draw(*drawnObjects->at(i));
	}
	if (UI.InterfaceMode == MODE_DRAW)
		for (int i = 0; i < DRAW_ITM_COUNT; i++)
		{
			pWind->draw(MenuItemSprites[i]);
		}
	else
		for (int i = 0; i < PLAY_ITM_COUNT; i++)
		{
			pWind->draw(MenuPlaySprites[i]);
		}

	pWind->draw(*toolbarLine);

	pWind->draw(*stbar);

	pWind->draw(*statusMessage);

	pWind->display();
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

