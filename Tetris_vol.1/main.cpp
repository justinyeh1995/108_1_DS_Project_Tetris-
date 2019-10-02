#include <iostream>
#include <fstream>
#include "Data.h"
#include "Block.h"
#include "Board.h"
int main(){
	/* File I/O */
	Data darray[1000];
	ifstream file("tetris.data");
	// address row and col initialization
	int r, c;
	file >> r;
	darray[0].setR(r);
	file >> c;
	darray[0].setC(c);
	/* Declare Board object b */ 
	Board b(darray[0].getR(),darray[0].getC());
	//board initialization
	b.Initialization();
	/* Declare Block object block */
	Block block("");
	/* Read (Type, posx) */
    string type;
    int x = 0;
    int idx = 1;
    while (!file.eof()) {
    file >> type;
    if(type == "End")break;
    darray[idx].setString(type);
    file >> x;
    darray[idx].setPosX(x);
    b.UpdateBoard(block.getBlock(darray[idx].getString()), darray[idx].getPosX());
    idx++;
    }
    file.close();
    /* Print output */
	cout<<endl;
	b.PrintBoard();
	cout<<endl;
	// b.PrintStack();
	// cout<<endl;
	/* Output file "tetris.final" */
    ofstream outFile("tetris.final", ios::out);
	int** board = b.getBoard();
	for(int row = 0; row < b.getRow()-4; row++)
	{
		for (int col = 0; col < c; col++)
		{
			outFile << board[row][col];
		}
		outFile << endl;
	}
	outFile.close();

	return 0;
}