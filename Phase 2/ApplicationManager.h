#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "DataManager.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure ** selectedList; //List of selected Figures
	DataManager* pData; //pointer to data manager to clean up
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	void fixFigList(); //utility function to rearrange figurelist after deleting items
public:
	ApplicationManager();
	~ApplicationManager();

	bool ChangeSelectedColor(GfxInfo selectedColor);

	void SelectAllFigures();
	void DeSelectAllFigures();
	void ShowAllFigures();
	void HideAllFigures();
	void ToLeftHalf();
	void RandomizePositionsRight(CFigure ** figures);
	void RestoreFromHalf();
	void deleteFigureArray(CFigure ** figures);//delete figure array
	CFigure ** createCopyOfFigures();//Create a copy of the figure array and return it
	CFigure * getRandomFigure();//returns a random visible figure and select it

	void UpdateInterface(CFigure ** figures) const;

	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); //Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	void removeFigure(int ID); //Remove figure by it's ID
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	int GetFigureCount() const; //Search for a figure given a point inside the figure
	CFigure *GetFigure(int index) const;
	CFigure * GetFigure(int x, int y, CFigure ** figures) const;
	CFigure ** getSelectedList(int &size);
	int getSelectedCount()const;
	//Search for a figure given index of figure
	void restartApp(); //delete figures before loading new graph
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif