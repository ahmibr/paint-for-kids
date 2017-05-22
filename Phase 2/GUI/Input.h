#ifndef INPUT_H
#define INPUT_H

#include "UI_Info.h" 

#include<SFML\Graphics.hpp>
#include<iostream>
#include "../DEFS.h"

using namespace std;

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	sf::RenderWindow *pWind;	//Pointer to the Graphics Window
	sf::RectangleShape *Nbar;						//

	sf::Event *userEvent;
public:
	Input(sf::RenderWindow *pW);		//Consturctor
	void GetPointClicked(int &x, int &y) const;
	//Get coordinate where user clicks
	string GetSrting(Output* pO) const;	 //Returns a string entered by the user

	float Resize_wind();//Added a function to return size of shape through creating a window
	bool confirmAction(string editable)const;//Added a function to return exit confirmation
	//Added a function to return size of shape through creating a window
	float Rotate_wind();//Added a function to return rotation of shape through creating a window
	int GetXmousePos() const;//returns last Event's pressed position x
	int GetYmousePos() const;//returns last Event's pressed position y
	void GetMouseMove(int &x, int &y) const;//the function returns the value of xpos and ypos when the mouse is dragged
	bool GetMouseMoveNoHold(int & x, int & y) const;//the function returns the value of xpos and ypos when the mouse is moving

	int selectPickType();//Added a function to return the type of pick game through creating a window

	ActionType GetUserAction() const; //Read the user click and map to an action
	void BackgrndColor();
	void GraphicsInfo(GfxInfo &choice);		//added to return graphics

	~Input();
};

#endif