#include "Board.h"
#include <iostream>
using namespace std;
void Board::Initialization(){
	for(int i = 0; i < this->row; i++){
		for(int j = 0; j < this->col; j++){
			GameBoard[i][j] = 0;
		}
	}
	for(int j = 0; j < this->col; j++){
		Stack[j].push(getRow()-1);// starting from the lowest layer
	}
}

int Board::getPostionY(int col){
	int posy = Stack[col-1].top();//0 indexing
	//check from top to bottom : Dummy Protection 
	for(int i = 1; i <= 3; i++){
		if( col-1+i > getCol()-1)break;
		if(posy > Stack[col-1+i].top()){
			posy = Stack[col-1+i].top();
		}
	} 
	return posy;
}

void Board::PrintBoard(){
	for(int i = 0; i < this->row; i++){
		for(int j = 0; j < this->col; j++){
			cout<< GameBoard[i][j]<<" ";
		}
		cout<<endl;
	}
}

void Board::PrintStack(){
	for(int j = 0; j < this->col; j++){
		cout<<Stack[j].top()<<" ";
	}
	cout<<endl;
}
 
bool Board::CheckCollision(int** block,int posx, int posy){
	for(int i = 0; i < 4; i++){
		if((posy - i)>=0){
			for(int j = 0; j < 4; j++){
				// Search every layer
				if(GameBoard[posy - i][posx-1 + j] == 1 && block[3-i][j] == 1 && posx-1 + j <= col-1) {
					return true;
				}
			}
		}
	}
	return false;
}

void Board::UpdateBoard(int** block, int posx){
	int posy = getPostionY(posx);
	int k = posx-1;
	/*
	Move down till collide
	*/
	while(posy<getRow()-1){	
		posy++;
	 	if(CheckCollision(block,posx,posy))break;
	}
	/*
	if it's now collide, move up till it's not!
	*/
	while(CheckCollision(block,posx,posy)){
		--posy;
	}
	/*
	Update GameBoard & Stack
	*/
	for(int i = 0; i < 4; i++){
		if((posy - i)>=0){
			for(int j = 0; j < 4; j++){
				if( posx-1 + j <= col-1){
					//Update the cell that are 1 in block 
					if(block[3-i][j] == 1){
						GameBoard[posy - i][posx-1 + j] = block[3-i][j];
					}
					//Update each stack 
					if(GameBoard[posy - i][posx-1 + j] == 1 ){
						//UpdateStack(posy);
						Stack[posx-1 + j].push(posy - i-1);
					}	
				}
			}
		}
	}
	DeleteAnyLine();
}
//Naive Delete
void Board::DeleteLine_Naive (int pY){
    // Moves all the upper lines one row down
  	for (int i = pY; i > 0; i--){
        for (int j = 0; j < this->col; j++)
        {
          GameBoard[i][j] = GameBoard[i-1][j];
        }
    }
	// Update each Stack
	for (int j = 0; j < this->col; j++){
		if(!Stack[j].isEmpty()){
		    int tmp = Stack[j].top();
			tmp++;
			Stack[j].push(tmp);
		}	
	}
	// Update the top row 
	for(int i = 0; i < this->col; i++){
		GameBoard[0][i] = 0;
	}   
}

void Board::DeleteAnyLine(){
	for(int i = 0; i < this->row; i++){
		int fill = 0;
		while(fill < this->col){
			if(GameBoard[i][fill] == 0){
				break;
			}
			++fill;
		}
		if(fill == this->col){
			DeleteLine_Naive(i);
		}
	}
}