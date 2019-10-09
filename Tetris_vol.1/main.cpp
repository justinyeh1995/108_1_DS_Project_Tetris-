#include <iostream>
#include <fstream>
#include "Block.h"
#include "Board.h"
int main(){
	/* File I/O */
	ifstream file("tetris.data");
	// address row and col initialization
	int r, c;
	file >> r;
	file >> c;
	/* Declare Board object b */ 
    Board b(r,c);
	//board initialization
	b.Initialization();
	/* Declare Block object block */
	Block block("");
	/* Read (Type, posx) */
    string type;
    int x = 0;
    while (!file.eof() && !b.Terminate()) {
    file >> type;
    if(type == "End")break;
    file >> x;
    b.UpdateBoard(block.getBlock(type),x);
    }
    file.close();
    /* Print output */
	cout<<endl;
	b.PrintBoard();
	cout<<endl;
	b.PrintStack();
	cout<<endl;
	/* Output file "tetris.final" */
    ofstream outFile("tetris.output", ios::out);
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