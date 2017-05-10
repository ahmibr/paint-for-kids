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
	bool GetMouseMoveNoHold(int & x, int & y) const;
	//Get coordinate where user clicks
	string GetSrting(Output* pO) const;	 //Returns a string entered by the user
	float Input::Resize_wind();
	float Input::Rotate_wind();
	int GetXmousePos() const;
	int GetYmousePos() const;
	void Input::GetMouseMove(int &x, int &y) const;
	int selectPickType();
	ActionType GetUserAction() const; //Read the user click and map to an action
	void BackgrndColor();
	void GraphicsInfo(GfxInfo &choice);		//added to return graphics

	~Input();
};

#endif