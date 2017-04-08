#ifndef INPUT_H
#define INPUT_H

#include "UI_Info.h" 

#include<SFML\Graphics.hpp>
#include<iostream>
#include "DEFS.h"

using namespace std;

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	sf::RenderWindow *pWind;	//Pointer to the Graphics Window

	sf::Event *userEvent;
public:
	Input(sf::RenderWindow *pW);		//Consturctor
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting(Output* pO) const;	 //Returns a string entered by the user

	ActionType GetUserAction() const; //Read the user click and map to an action

	GfxInfo Input::GraphicsInfo();		//added to return graphics

	~Input();
};

#endif