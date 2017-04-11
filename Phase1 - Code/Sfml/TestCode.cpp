#include "Input.h"
#include "Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	int x, y;

	//Create Input and Output objects to test
	Output *pOut = new Output();
	Input *pIn = pOut->CreateInput();

	//Starting the test
	pOut->PrintMessage("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x, y);	//Wait for any click


								///////////////////////////////////////////////////////////////////////////////////
								// TEST 1:	
								//			Create The FULL Tool bar, the drawing area and the status bar	
								//			This has already been done through the constrcutor of class Output
								///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click


								///////////////////////////////////////////////////////////////////////////////////
								// TEST 2:	
								//			Drawing all the Figures with all possible states: 
								//			Non-filled, Filled, and highlighted in both cases			
								///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST2: Now we will show that Output class can draw any figure in any state, Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	GfxInfo gfxInfo;//to be used with draw function of the class Ouput
	Point P1, P2, P3;

	/// 2.1- Rectangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Rectangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	// 2.1.1 - Drawing non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);


	gfxInfo.BorderWdth = 3;
	gfxInfo.DrawClr = sf::Color::Black;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled

	pOut->DrawRect(P1, P2, gfxInfo, false);

	// 2.1.2 - Drawing highlighted non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->DrawRect(P1, P2, gfxInfo, true);


	// 2.1.3 - Drawing a filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);


	pIn->GraphicsInfo(gfxInfo);
	pOut->DrawRect(P1, P2, gfxInfo, false);


	// 2.1.4 - Drawing a highlighted filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);



	pOut->PrintMessage("Drawing a Rectangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();


	/// 2.2- Line Test ///
	/// ============== 
	pOut->PrintMessage("Drawing a Line, normal and Highlighted, Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->PrintMessage("Press 2 points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	pOut->DrawLine(P1, P2, gfxInfo, false);

	pOut->PrintMessage("Drawing a Line Test ,  Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->DrawLine(P1, P2, gfxInfo, true);


	pOut->PrintMessage("Drawing a Line Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();




	/// 2.3- Triangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Triangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

								// 2.1.1 Drawing non-filled traingle
	pOut->PrintMessage("Drawing a Triangle ==> non-filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);
	gfxInfo.BorderWdth = 3;

	//gfxInfo.DrawClr = sf::Color::Black;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled

	pOut->DrawTriangle(P1, P2, P3, gfxInfo, false);
	///TODO: Add code to draw Triangle in all possible states
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, true);


	// 2.1.1 Drawing filled traingle
	pOut->PrintMessage("Drawing a Triangle ==> filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);

	pIn->GraphicsInfo(gfxInfo);

	pOut->DrawTriangle(P1, P2, P3, gfxInfo, false);
	///TODO: Add code to draw Triangle in all possible states
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, true);


	pOut->PrintMessage("Drawing a Triangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.4- Circle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Circle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->PrintMessage("Drawing a Circle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);	//Wait for any click
	pIn->GetPointClicked(P2.x, P2.y);	//Wait for any click

	gfxInfo.BorderWdth = 3;	///TODO: Add code to draw Circle in all possible states

	gfxInfo.DrawClr = sf::Color::Black;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawCirc(P1, P2, gfxInfo, false);

	pOut->PrintMessage("Now click to highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawCirc(P1, P2, gfxInfo, true);

	pOut->PrintMessage("Drawing a Circle, filled and Highlighted filled,  Click to continue");
	pIn->GetPointClicked(P1.x, P1.y);	//Wait for any click

	pOut->PrintMessage("Drawing a Circle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);	//Wait for any click
	pIn->GetPointClicked(P2.x, P2.y);	//Wait for any click
	pIn->GraphicsInfo(gfxInfo);
	gfxInfo.isFilled = true;
	pOut->DrawCirc(P1, P2, gfxInfo, false);

	pOut->PrintMessage("Now click to highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawCirc(P1, P2, gfxInfo, true);

	pOut->PrintMessage("Drawing a Circle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: 
	//			Input Class: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->PrintMessage("Testing Input ability to read strings. Press Enter when you finish");

	string textEntered = pIn->GetSrting(pOut);

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar
	// 2- After reading the stirng clear the status bar
	// 3- print on the status bar "You Entered" then print the string

	pOut->PrintMessage("You Entered : " + textEntered + " ,Click to continue");

	pIn->GetPointClicked(x, y);

	pOut->PrintMessage("Read string test is done, Click anywhere to continue");

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: 
	//			Input Class : Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;
	float test2;

	///TODO:  
	//You must add a case for each action (both Draw mode and Play mode actions)
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case DRAW_RECT:
			pOut->PrintMessage("Action: Draw a Rectangle , Click anywhere");
			break;

		case DRAW_LINE:
			pOut->PrintMessage("Action: Draw a Line , Click anywhere");
			break;

		case DRAW_CIRC:
			pOut->PrintMessage("Action: Draw a Circle , Click anywhere");
			break;

		case DRAW_TRI:
			pOut->PrintMessage("Action: Draw a Triangle , Click anywhere");
			break;

		case CHNG_BK_CLR:
			pOut->PrintMessage("Action: Change Background color , Click anywhere");
			pIn->BackgrndColor();
			pOut->ClearDrawArea();
			break;

		case ZOOM_IN:
			pOut->PrintMessage("Action: Zoom In, Click anywhere");
			break;

		case ZOOM_OUT:
			pOut->PrintMessage("Action: Zoom Out, Click anywhere");
			break;

		case RESIZE:
			pOut->PrintMessage("Action: Resize, Click anywhere");
			test2 = pIn->Resize_wind();
			pOut->PrintMessage("Resize is " + to_string(test2));
			break;

		case ROTATE:
			pOut->PrintMessage("Action: Rotate, Click anywhere");
			test2 = pIn->Rotate_wind();
			pOut->PrintMessage("Rotate is " + to_string(test2));
			break;

		case SAVE:
			pOut->PrintMessage("Action: Save, Click anywhere");
			break;

		case LOAD:
			pOut->PrintMessage("Action: Load, Click anywhere");
			break;

		case DEL:
			pOut->PrintMessage("Action: Delete shape , Click anywhere");
			break;


		case CUT:
			pOut->PrintMessage("Action: Cut , Click anywhere");
			break;

		case COPY:
			pOut->PrintMessage("Action: Copy , Click anywhere");
			break;

		case PASTE:
			pOut->PrintMessage("Action: Paste , Click anywhere");
			break;

		case UNDO:
			pOut->PrintMessage("Action: Undo , Click anywhere");
			break;

		case REDO:
			pOut->PrintMessage("Action: Redo , Click anywhere");
			break;

		case CHNG_DRAW_CLR:
			pOut->PrintMessage("Action: Change color , Click anywhere");
			pIn->GraphicsInfo(gfxInfo);
			break;

		case BRNG_FRNT:
			pOut->PrintMessage("Action: Bring to front , Click anywhere");
			break;

		case SEND_BACK:
			pOut->PrintMessage("Action: Send to back , Click anywhere");
			break;

		case STATUS:
			pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
			break;

		case DRAWING_AREA:
			pOut->PrintMessage("Action: a click on the Drawing Area, Click anywhere");
			break;

		case EMPTY:
			pOut->PrintMessage("Action: a click on empty area in the Design Tool Bar, Click anywhere");
			break;

		case TO_PLAY:
			pOut->PrintMessage("Action: Switch to Play Mode, creating Design tool bar");
			pOut->CreatePlayToolBar();
			break;

		case TO_DRAW:
			pOut->PrintMessage("Action: Switch to Draw Mode, creating simualtion tool bar");
			pOut->CreateDrawToolBar();
			break;

		case PICK:
			pOut->PrintMessage("Action: PICK, Click anywhere");
			break;

		case FIND:
			pOut->PrintMessage("Action: Find, Click anywhere");
			break;


		case EXIT:
			break;
		}
	} while (ActType != EXIT);


	/// Exiting
	pOut->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x, y);


	delete pIn;
	delete pOut;
	return 0;
}
