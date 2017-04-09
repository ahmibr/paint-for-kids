#include "Input.h"
#include "Output.h"


Input::Input(sf::RenderWindow* pW)
{
	pWind = pW; //point to the passed window
	userEvent = new sf::Event;
}

void Input::GetPointClicked(int &x, int &y) const
{
	bool pressed = false;
	while (!pressed)
	{
		while (pWind->pollEvent(*userEvent))
		{
			// Close window: exit
			if (userEvent->type == sf::Event::Closed)
				pWind->close();
			if (userEvent->type == sf::Event::MouseButtonPressed) {
				x = userEvent->mouseButton.x;	//Wait for mouse click
				y = userEvent->mouseButton.y;
				pressed = true;
			}
		}

	}

}

string Input::GetSrting(Output *pO) const
{
	string Label;
	char Key;
	while (true)
		while (pWind->pollEvent(*userEvent))
		{
			if (userEvent->type == sf::Event::Closed)
				pWind->close();

			if (userEvent->type == sf::Event::TextEntered) {
				Key = userEvent->text.unicode;
				if (Key == 27)	//ESCAPE key is pressed
					return "";	//returns nothing as user has cancelled label
				if (Key == 13)	//ENTER key is pressed
					return Label;
				if (Key == 8)	//BackSpace is pressed
					Label.resize( (Label.size() == 0) ? 0 : Label.size() - 1);
				else
					Label += Key;
				pO->PrintMessage(Label);
			}
		}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;

	bool pressed = false;
	while (!pressed)	//Get the coordinates of the user click
	{
		while (pWind->pollEvent(*userEvent))
		{
			// Close window: exit
			if (userEvent->type == sf::Event::Closed)
				pWind->close();
			if (userEvent->type == sf::Event::MouseButtonPressed) {
				x = userEvent->mouseButton.x;	//Wait for mouse click
				y = userEvent->mouseButton.y;
				pressed = true;
			}
		}

	}

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_Tri: return DRAW_TRI;
			case ITM_Line: return DRAW_LINE;
			case ITM_Color: return CHNG_DRAW_CLR;
			case ITM_Zoom: return ZOOM;
			case ITM_Resize: return RESIZE;
			case ITM_Save: return SAVE;
			case ITM_Load: return LOAD;
			case ITM_Cut: return CUT;
			case ITM_Copy: return COPY;
			case ITM_Paste: return PASTE;
			case ITM_Front: return BRNG_FRNT;
			case ITM_Back: return SEND_BACK;
			case ITM_Del: return DEL;
			case ITM_Undo: return UNDO;
			case ITM_Redo: return REDO;
			case ITM_Play: return TO_PLAY;
			case ITM_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action

		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_Pick: return PICK;
			case ITM_Find: return FIND;
			case ITM_Draw: return TO_DRAW;
			case ITM_EXIT2: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;


		//return TO_PLAY;	//just for now. This should be updated
	}

}
/////////////////////////////////



//Added a function to return graphix of shape
GfxInfo Input::GraphicsInfo() {
	sf::RenderWindow colorPalette(sf::VideoMode(300, 350), "Color Palette", sf::Style::Close);

	sf::RectangleShape bckGrnd(sf::Vector2f(300, 350));		//background color
	sf::RectangleShape color[3][3];

	bool fillColorSelected = false;

	sf::Font f;
	f.loadFromFile("Resource Files\\Arial.ttf");

	sf::Text colorType("Draw Color", f, 20);
	colorType.setFillColor(sf::Color::Black);
	colorType.setPosition(0, 10);

	sf::Text transparentOption("", f, 15);
	transparentOption.setFillColor(sf::Color::Red);
	transparentOption.setPosition(150, 15);

	bckGrnd.setFillColor(UI.BkGrndColor);

	GfxInfo choice;
	choice.isFilled = false;			//default if closed the window
	choice.DrawClr = sf::Color::Black;
	choice.BorderWdth = 3;


	int counter = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			color[i][j].setSize(sf::Vector2f(100, 100));
			color[i][j].setPosition(i * 100, j * 100 + 50);
		}
	}

	color[0][0].setFillColor(sf::Color(0, 0, 0));		//black
	color[1][0].setFillColor(sf::Color(255, 255, 255));	//white
	color[2][0].setFillColor(sf::Color(0, 255, 0));		//green
	color[0][1].setFillColor(sf::Color(255, 0, 0));		//red
	color[1][1].setFillColor(sf::Color(0, 0, 255));		//blue
	color[2][1].setFillColor(sf::Color(0, 255, 255));	//terquaz
	color[0][2].setFillColor(sf::Color(255, 255, 127.5));	//yellow
	color[1][2].setFillColor(sf::Color(255, 127.5, 0));	//red + blue
	color[2][2].setFillColor(sf::Color(127.5, 127.5, 127.5));	//grey

	//drawing colors in small window
	colorPalette.draw(bckGrnd);
	colorPalette.draw(colorType);
	colorPalette.draw(transparentOption);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			colorPalette.draw(color[i][j]);
		}
	}
	colorPalette.display();
	//////////////////////////////////////////////

	while (colorPalette.isOpen())
	{
		// Process events
		sf::Event event;
		while (colorPalette.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				colorPalette.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (!fillColorSelected) {		//didnt choose the draw color yet
					if (event.mouseButton.y > 50) {		//clicked inside colors
						choice.DrawClr = color[event.mouseButton.x / 100][(event.mouseButton.y - 50) / 100].getFillColor();

						fillColorSelected = true;

						transparentOption.setString("Transparent");

						colorType.setString("Fill Color");

						//drawing colors in small window again with change in name
						colorPalette.clear();

						colorPalette.draw(bckGrnd);
						colorPalette.draw(colorType);
						colorPalette.draw(transparentOption);

						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								colorPalette.draw(color[i][j]);
							}
						}
						colorPalette.display();
						/////////////////////////////////////////////////////////////
					}
				}
				else {
					if (event.mouseButton.y > 50) {		//clicked inside colors
						choice.FillClr = color[event.mouseButton.x / 100][(event.mouseButton.y - 50) / 100].getFillColor();

						choice.isFilled = true;
					}
					else		//clicked outside colors and chose transparent
					{
						choice.isFilled = false;
					}
					colorPalette.close();
				}
			}

		}
	}


	return choice;

}

Input::~Input()
{
}
