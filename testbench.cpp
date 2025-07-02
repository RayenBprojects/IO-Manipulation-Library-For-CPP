#include <iostream>
#include <conio.h>
using namespace std;

#include "iotools.h"

/*
Programmer Note: Current version works splendidly, this is safe for a merge
*/

int main(){ // Test Scenarios cannot be confirmed automatically, behavior must be observed and recorded by programmer

    IoTools::PageTool page1;

    page1.addText("Test Begin");
    page1.addLine(100);
    page1.addReturnLine();

    char prompt[500] = "Enter a positive integer please -> ";
    char result[500];
    char error[500] = "Oops, seems you made a mistake!";
    page1.addPrompt(prompt, result, error, false, true);

    page1.showPage();

    page1.addReturnLine();
    page1.addText(result);
    page1.showPage();

    float testPoints[2][2] = {{0,0},{5,5}};
    char xAxis[] = "X-Axis";
    char yAxis[] = "Y-Axis";
    float xMinMax[2] = {0,10};
    float yMinMax[2] = {0,10};
    page1.addGraph(xAxis,yAxis,xMinMax,yMinMax,2,testPoints,3,3);
    page1.showPage();

    while(!kbhit()){}
    return 0;
}