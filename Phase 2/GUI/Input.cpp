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
					Label.resize((Label.size() == 0) ? 0 : Label.size() - 1);
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
				return EXIT;

			if (userEvent->type == sf::Event::MouseButtonPressed) { //normal Actions
				if (userEvent->key.code == sf::Mouse::Left) {
					x = userEvent->mouseButton.x;	//Wait for mouse click
					y = userEvent->mouseButton.y;
					pressed = true;
				}
				else if (userEvent->key.code == sf::Mouse::Right && UI.InterfaceMode == MODE_DRAW) {
					return POP_MENU;
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && UI.InterfaceMode == MODE_DRAW)
				return MULTI_SELECT;

			if (userEvent->type == sf::Event::MouseWheelScrolled && UI.InterfaceMode == MODE_DRAW) {
				if (userEvent->mouseWheelScroll.delta > 0) {
					return ZOOM_IN;
				}
				else {
					return ZOOM_OUT;
				}
			}

			if (userEvent->type == sf::Event::KeyPressed) {
				if (UI.InterfaceMode == MODE_DRAW) {
					if (UI.zoomFactor == 1) {
						if (userEvent->key.code == sf::Keyboard::C && userEvent->key.control) {
							return COPY;
						}
						if (userEvent->key.code == sf::Keyboard::X && userEvent->key.control) {
							return CUT;
						}
						if (userEvent->key.code == sf::Keyboard::V && userEvent->key.control) {
							return PASTE;
						}
					}

					if (userEvent->key.code == sf::Keyboard::Z && userEvent->key.control) {
						return UNDO;
					}
					if (userEvent->key.code == sf::Keyboard::Y && userEvent->key.control) {
						return REDO;
					}
					if (userEvent->key.code == sf::Keyboard::D) {
						return MOVE_DRAG;
					}
					if (userEvent->key.code == sf::Keyboard::Delete) {
						return DEL;
					}
					if (userEvent->key.code == sf::Keyboard::S) {
						return RESIZE_DRAG;
					}
					if (userEvent->key.code == sf::Keyboard::R) {
						return ROTATE_DRAG;
					}
				}
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

			case ITM_Color: return CHNG_DRAW_CLR;
			case ITM_BackGround: return CHNG_BK_CLR;
			case ITM_Resize: return RESIZE;
			case ITM_Rotate: return ROTATE;
			case ITM_Save: return SAVE;
			case ITM_Load: return LOAD;

			case ITM_Front: return BRNG_FRNT;
			case ITM_Back: return SEND_BACK;
			case ITM_Del: return DEL;
			case ITM_Undo: return UNDO;
			case ITM_Redo: return REDO;
			case ITM_Play: return TO_PLAY;
			case ITM_EXIT: return EXIT;
			}

			if (UI.zoomFactor == 1) {
				switch (ClickedItemOrder)
				{

				case ITM_RECT: return DRAW_RECT;
				case ITM_CIRC: return DRAW_CIRC;
				case ITM_Tri: return DRAW_TRI;
				case ITM_Line: return DRAW_LINE;
				case ITM_Cut: return CUT;
				case ITM_Copy: return COPY;
				case ITM_Paste: return PASTE;

				default: return EMPTY;	//A click on empty place in desgin toolbar
				}
			}
			else {
				return ZOOM_NOT_SUPPORTED;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;
		}

		//[3] User clicks on the status bar
		if (UI.width - x < UI.infoWidth) {
			return EMPTY;
		}
		else if (UI.width - x < UI.infoWidth + UI.zoomIconWidth) {
			return ZOOM_OUT;
		}
		else if (UI.width - x < UI.infoWidth + 2 * UI.zoomIconWidth) {
			return ZOOM_IN;
		}
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
			case ITM_Find: return SCRAMBLE_FIND;
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

//Added a function to return graphix of shape through creating a window
void Input::GraphicsInfo(GfxInfo &choice) {
	sf::RenderWindow colorPalette(sf::VideoMode(300, 400), "Color Palette", sf::Style::Close);

	sf::RectangleShape bckGrnd(sf::Vector2f(300, 400));		//background color
	sf::RectangleShape color[3][3];

	sf::Font f;
	f.loadFromFile("Resource Files\\Arial.ttf");

	sf::RectangleShape currColor(sf::Vector2f(60, 20));
	currColor.setOutlineColor(sf::Color::Black);
	currColor.setOutlineThickness(2);

	int operation = 0;

	sf::Text colorType("Draw Color", f, 20);
	colorType.setFillColor(sf::Color::Black);
	colorType.setPosition(0, 10);

	sf::Text transparentOption("", f, 15);
	transparentOption.setFillColor(sf::Color::Red);
	transparentOption.setPosition(150, 15);

	sf::Text nextOperation("No change in Draw Color go to Fill Color.\nCurrent color is ", f, 15);
	nextOperation.setFillColor(sf::Color::Black);
	nextOperation.setPosition(0, 350);
	currColor.setPosition(sf::Vector2f(110, 368));
	currColor.setFillColor(choice.DrawClr);


	bckGrnd.setFillColor(UI.BkGrndColor);

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
	color[2][1].setFillColor(sf::Color(0, 255, 127.5));	//terquaz
	color[0][2].setFillColor(sf::Color(255, 255, 127.5));	//yellow
	color[1][2].setFillColor(sf::Color(255, 127.5, 0));	//red + blue
	color[2][2].setFillColor(sf::Color(127.5, 127.5, 127.5));	//grey




																///drawing colors in small window
	colorPalette.draw(bckGrnd);
	colorPalette.draw(colorType);
	colorPalette.draw(transparentOption);
	colorPalette.draw(nextOperation);
	colorPalette.draw(currColor);

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
				if (operation == 0) {		//didnt choose the draw color yet
					if (event.mouseButton.y > 50) {		//clicked inside colors
						if (event.mouseButton.y < 350) {
							choice.DrawClr = color[event.mouseButton.x / 100][(event.mouseButton.y - 50) / 100].getFillColor();
						}

						operation++;

						transparentOption.setString("Transparent");
						colorType.setString("Fill Color");
						nextOperation.setString("No change in Fill Color go to Border width.\nCurrent color is ");
						currColor.setPosition(sf::Vector2f(110, 368));
						currColor.setFillColor(choice.FillClr);
						//drawing colors in small window again with change in name
						colorPalette.clear();


						colorPalette.draw(bckGrnd);
						colorPalette.draw(colorType);
						colorPalette.draw(transparentOption);
						colorPalette.draw(nextOperation);
						colorPalette.draw(currColor);
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
				else if (operation == 1) {

					if (event.mouseButton.y < 50) {		//clicked inside colors
						choice.isFilled = false;
						choice.FillClr = UI.nonFillColor;
					}
					else if (event.mouseButton.y < 350)		//clicked outside colors and chose transparent
					{
						choice.FillClr = color[event.mouseButton.x / 100][(event.mouseButton.y - 50) / 100].getFillColor();
						choice.isFilled = true;
					}
					operation++;

					string str("");
					str += '0' + choice.BorderWdth;
					nextOperation.setString("No change in Border width.\nCurrent width is " + str);
					colorType.setString("Border Width");

					//drawing colors in small window again with change in name
					colorPalette.clear();

					colorPalette.draw(bckGrnd);
					colorPalette.draw(colorType);
					colorPalette.draw(nextOperation);

					transparentOption.setFillColor(sf::Color::Black);
					transparentOption.setCharacterSize(40);

					for (int i = 0; i < 7; i++)
					{
						transparentOption.setString(to_string(i + 1));
						transparentOption.setPosition(150, i * 40 + 45);
						colorPalette.draw(transparentOption);
					}
					colorPalette.display();
					/////////////////////////////////////////////////////////////

				}
				else {

					if (event.mouseButton.y > 45 && event.mouseButton.y < 325)		//clicked outside colors and chose transparent
					{
						choice.BorderWdth = (event.mouseButton.y - 45) / 40 + 1;
						colorPalette.close();
					}
					else if (event.mouseButton.y > 325)
						colorPalette.close();
				}
			}

		}
	}
}

//Added a function to return background color through creating a window
void Input::BackgrndColor() {
	sf::RenderWindow backgrndWindow(sf::VideoMode(400, 150), "Background Color", sf::Style::Close);
	sf::RectangleShape backgrndColor(sf::Vector2f(400, 150));
	backgrndColor.setFillColor(UI.BkGrndColor);


	sf::Font f;
	f.loadFromFile("Resource Files\\Arial.ttf");

	sf::Text title("Background Color", f, 45);
	title.setFillColor(sf::Color::Black);

	sf::RectangleShape Color[4];

	Color[0].setFillColor(sf::Color(190, 190, 190));
	Color[1].setFillColor(sf::Color(255, 250, 205));
	Color[2].setFillColor(sf::Color(220, 220, 220));
	Color[3].setFillColor(sf::Color(0, 200, 200));

	backgrndWindow.clear();
	backgrndWindow.draw(backgrndColor);
	backgrndWindow.draw(title);

	for (int i = 0; i < 4; i++)
	{
		Color[i].setSize(sf::Vector2f(100, 100));
		Color[i].setPosition(i * 100, 50);
		backgrndWindow.draw(Color[i]);
	}
	backgrndWindow.display();

	while (backgrndWindow.isOpen())
	{
		// Process events
		sf::Event event;
		while (backgrndWindow.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				backgrndWindow.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.y > 50) {
					UI.BkGrndColor = Color[event.mouseButton.x / 100].getFillColor();

					return;
				}
			}
		}
	}

}

//Added a function to return size of shape through creating a window
float Input::Resize_wind()
{
	sf::RenderWindow New_window(sf::VideoMode(200, 50), "Resize ", sf::Style::Close);
	sf::RectangleShape backgrnd(sf::Vector2f(200, 50));		//background color
	backgrnd.setFillColor(UI.BkGrndColor);

	sf::Font f;
	f.loadFromFile("Resource Files\\Arial.ttf");

	sf::Text multiply[4];
	multiply[0].setString("x0.25");
	multiply[1].setString("x0.5");
	multiply[2].setString("x2");
	multiply[3].setString("x4");

	New_window.clear();
	New_window.draw(backgrnd);

	for (int i = 0; i < 4; i++)
	{
		multiply[i].setFillColor(sf::Color::Black);
		multiply[i].setFont(f);
		multiply[i].setCharacterSize(20);
		multiply[i].setPosition(i * 55, 15);
		New_window.draw(multiply[i]);
	}
	New_window.display();

	while (New_window.isOpen())
	{
		// Process events
		sf::Event event;
		while (New_window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				New_window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.x / 55 == 0)
					return 0.25f;
				if (event.mouseButton.x / 55 == 1)
					return 0.5f;
				if (event.mouseButton.x / 55 == 2)
					return 2;
				if (event.mouseButton.x / 55 == 3)
					return 4;
			}
		}
	}

	return 1;

}

//Added a function to return rotation of shape through creating a window
float Input::Rotate_wind()
{
	sf::RenderWindow New_window(sf::VideoMode(150, 50), "Rotate ", sf::Style::Close);
	sf::RectangleShape backgrnd(sf::Vector2f(150, 50));		//background color
	backgrnd.setFillColor(UI.BkGrndColor);

	sf::Font f;
	f.loadFromFile("Resource Files\\Arial.ttf");

	sf::Text multiply[3];
	multiply[0].setString("90");
	multiply[1].setString("180");
	multiply[2].setString("270");

	New_window.clear();
	New_window.draw(backgrnd);

	for (int i = 0; i < 3; i++)
	{
		multiply[i].setFillColor(sf::Color::Black);
		multiply[i].setFont(f);
		multiply[i].setCharacterSize(20);
		multiply[i].setPosition(i * 55, 15);
		New_window.draw(multiply[i]);
	}
	New_window.display();

	while (New_window.isOpen())
	{
		// Process events
		sf::Event event;
		while (New_window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				New_window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.x / 55 == 0)
					return 90;
				if (event.mouseButton.x / 55 == 1)
					return 180;
				if (event.mouseButton.x / 55 == 2)
					return 270;
			}
		}
	}

	return 0;
}

//returns last Event's pressed position x
int Input::GetXmousePos() const {
	return userEvent->mouseButton.x;
}

//returns last Event's pressed position y
int Input::GetYmousePos() const {
	return userEvent->mouseButton.y;
}

//the function returns the value of xpos and ypos when the mouse is dragged
//if the mouse is released  returns -1 for both x and y
void Input::GetMouseMove(int &x, int &y) const {
	while (true) {
		while (pWind->pollEvent(*userEvent))
		{
			if (userEvent->type == sf::Event::MouseMoved) {
				x = userEvent->mouseMove.x;
				y = userEvent->mouseMove.y;
				return;
			}
			if (userEvent->type == sf::Event::MouseButtonReleased) {
				if (userEvent->key.code == sf::Mouse::Left) {
					x = y = -1;
					return;
				}
			}
		}
	}
}

//the function returns the value of xpos and ypos when the mouse is moving
//if the mouse is released  returns -1 for both x and y
bool Input::GetMouseMoveNoHold(int &x, int &y) const
{
	while (true) {
		while (pWind->pollEvent(*userEvent))
		{
			if (userEvent->type == sf::Event::MouseMoved) {
				x = userEvent->mouseMove.x;
				y = userEvent->mouseMove.y;
				return false;
			}
			if (userEvent->type == sf::Event::MouseButtonPressed) {
				if (userEvent->key.code == sf::Mouse::Left) {
					x = userEvent->mouseButton.x;
					y = userEvent->mouseButton.y;
					return true;
				}
			}
		}
	}
}

//Added a function to return the type of pick game through creating a window
int Input::selectPickType()
{
	sf::RenderWindow New_window(sf::VideoMode(300, 600), "Pick ", sf::Style::Close);
	sf::RectangleShape backgrnd(sf::Vector2f(300, 600));		//background color
	backgrnd.setFillColor(UI.BkGrndColor);

	sf::Font f;
	f.loadFromFile("Resource Files\\Arial.ttf");

	sf::Texture image_types[4];
	sf::Sprite sprite_types[4];
	image_types[0].loadFromFile("images\\Play_By_Type.png");
	image_types[1].loadFromFile("images\\Play_By_Color.png");
	image_types[2].loadFromFile("images\\Play_By_TypeAndColor.png");
	image_types[3].loadFromFile("images\\Play_By_Area.png");

	sf::Text Pick[4];
	Pick[0].setString("By Type");
	Pick[1].setString("By Color");
	Pick[2].setString("By Type & Color");
	Pick[3].setString("By Area");

	New_window.clear();
	New_window.draw(backgrnd);

	for (int i = 0; i < 4; i++)
	{
		Pick[i].setFillColor(sf::Color::Black);
		Pick[i].setFont(f);
		Pick[i].setCharacterSize(20);
		Pick[i].setPosition(0, i * 150);
		sprite_types[i].setTexture(image_types[i]);
		sprite_types[i].setScale(0.5f, 0.5f);
		sprite_types[i].setPosition(0, i * 150 + 25);
		New_window.draw(Pick[i]);
		New_window.draw(sprite_types[i]);
	}
	New_window.display();

	while (New_window.isOpen())
	{
		// Process events
		sf::Event event;
		while (New_window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				New_window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.y / 150 == 0)
					return 1;
				if (event.mouseButton.y / 150 == 1)
					return 2;
				if (event.mouseButton.y / 150 == 2)
					return 3;
				if (event.mouseButton.y / 150 == 3)
					return 4;
			}
		}
	}

	return 0;
}

Input::~Input()
{
}
