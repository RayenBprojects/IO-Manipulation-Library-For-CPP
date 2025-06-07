#ifndef IOTOOLS_H //HEADER_FILE_IOTOOLS_H
#define IOTOOLS_H //HEADER_FILE_IOTOOLS_H

#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;


class IoTools{ // Common class for various projects
	
	public:

		void upLine(int jumps = 1){
			for (int i = 0 ; i < jumps ; i++){
				cout<<"\x1b[1F";
			}
		}

		void clearLine(){
			cout<<"\x1b[2K";
		}

		void lineTool(int size, char lineChar = '-', bool returnLine = false){
			for (int i = 0 ; i < size ; i++){
				cout<<lineChar;
			}
			if (returnLine){
				cout<<endl;
			}
		}

		void barTool(float nominator = 0 , float denominator = 1 , int barLength = 100 , bool percentDisplay = true, bool returnLine = false){
			float tempLengthFloat = (nominator/denominator)*((float)barLength);
			int tempLength = tempLengthFloat;
			if (tempLengthFloat - tempLength > 0.5){
				tempLength++;
			}
	
			cout<<'['; lineTool(tempLength, '|', false); lineTool(barLength - tempLength, '-', false) ; cout<<']';
	
			if (percentDisplay){
				float tempPercent = (nominator/denominator)*100;
				cout<<' '<<fixed<<setprecision(1)<<setw(5)<<tempPercent<<'%';
			}

			if (returnLine){
				cout<<endl;
			}
	} 

		void promptTool(char prompt[500] , char result[500] , char error[500],bool doError = false, bool isNumber = false){

			if (!doError){
				bool errorFlag;
				bool lengthFlag;
				do{
					errorFlag = false;
					lengthFlag = false;
			
					cout<<prompt;
					cin>>result;
			
					for (int i = 0 ; i < 500 ; i++){
						if (result[i] == '\0'){
							lengthFlag = true;
							break;
						}
				
						if (isNumber && (result[i] != '0') && (result[i] != '1') && (result[i] != '2') && (result[i] != '3') && (result[i] != '4') && (result[i] != '5') && (result[i] != '6') && (result[i] != '7') && (result[i] != '8') && (result[i] != '9')){
							errorFlag = true;
							break;
						}
					}
			
					if (!lengthFlag){
						errorFlag = true;
					}
			
					if (errorFlag){
						cout<<error;
				
						while(!kbhit()){}
						getch();
				
						cout<<"\x1b[2K"<<"\x1b[1F"<<"\x1b[2K";
				
					}
			
				} while(errorFlag);
			}
			else{
				cout<<error;
				getch();
				while(!kbhit){}
				getch();
				cout<<"\x1b[2K"<<"\x1b[1F"<<"\x1b[2K";
			}

		}

		void graphTool(char xName[20], char yName[20], float xMinMax[2], float yMinMax[2], int pointNum, float points[100][2], int xIncr = 10, int yIncr = 5){
			if (yMinMax[0] >= 0){
				// Sectioned off the code that prints the graph without points
				{
					cout<<"          "<<yName<<endl;
					for (int i = 0 ; i < yIncr*6+1 ; i++){
						if (i % 6 == 0){
							cout<<"         -|"<<endl;
						}
						else{
							cout<<"          |"<<endl;
						}
					}

					cout<<"          ";
					lineTool(xIncr*11,'=',false);
					cout<<"== "<<xName<<endl;

					cout<<"           ";
					for (int i =0 ; i < xIncr+1 ; i++){
						cout<<"|          ";
					}

					upLine(2 + 6*yIncr);

					for (int i = 0 ; i <= yIncr ; i++){
						cout<<setw(9)<<fixed<<setprecision(2)<<(yMinMax[1]-i*(yMinMax[1]-yMinMax[0])/yIncr)<<endl;
						if (i != yIncr ){
							for (int n =0 ; n < 5 ; n++){
								cout<<endl;
							}
						}
						else{
							cout<<endl<<endl;
						}
					}

					cout<<"      ";
					for (int i = 0 ; i <= xIncr ; i++){
						cout<<setw(9)<<fixed<<setprecision(2)<<(xMinMax[0]+i*(xMinMax[1]-xMinMax[0])/xIncr);
						if (i != xIncr ){
							cout<<"  ";
						}
					}
				}
				upLine(3+6*yIncr);

				for (int i = 0 ; i <= 6*yIncr ; i++){
					int displayCoords[100];
					int tempPointNum = 0;
					int travel = 0;
					cout<<"\x1b[11C";
					for (int n = 0 ; n < pointNum ; n++){
						if ((points[n][1] <= (yMinMax[1]-i*(yMinMax[1]/(6*yIncr)))) && (points[n][1] > (yMinMax[1]-(i+1)*(yMinMax[1]/(6*yIncr)))) && (points[n][0] <= xMinMax[1]) && (points[n][0] >= xMinMax[0])){
							if ((points[n][0])*(11*xIncr/xMinMax[1]) - (int)((points[n][0])*(11*xIncr/xMinMax[1])) >= 0.5){
								displayCoords[tempPointNum] = (int)((points[n][0])*(11*xIncr/xMinMax[1])) + 1;
							}
							else{
								displayCoords[tempPointNum] = (int)((points[n][0])*(11*xIncr/xMinMax[1]));
							}
							tempPointNum++;
						}
					}
					for (int n = 0 ; n < tempPointNum ; n++){
						for (int j = travel ; j <= displayCoords[n] ; j++){
							if (j == displayCoords[n]){
								cout<<'*';
								//cout<<n;
								travel = displayCoords[n]+1;
								break;
							}
							else{
								cout<<' ';
							}
						}
					}
					cout<<endl;
				}
				cout<<endl<<endl<<endl;
			}

		}
};

#endif