#include "Stack.h"
#include <iostream>
class Board{
	private:
		int row, col;
        stack* Stack; 
        int** GameBoard; 
	public:
		Board(){};
		Board(int m , int n ):row(m+4),col(n){
			GameBoard = new int*[row];
			for(int i = 0; i < row; i++){
				 GameBoard[i] = new int[col];
			}
            Stack = new stack[col];
		}
		int getStackSize(int col){
			return Stack[col].size();
		}
		int getRow(){return this->row;}
		int getCol(){return this->col;}
		void Initialization();
		int getPostionY(int col);
		void UpdateStack(int posy);
		void UpdateBoard(int** block, int posx);
		bool CheckCollision(int** block,int posx,int posy);
		bool IsOverlap(int** block,int posx,int posy);
		void DeleteLine_Naive(int row_to_delete);
		void DeleteAnyLine();
		bool Terminate(){
            for(int i = 0; i < this->col; i++){
				if(Stack[i].top() < 4){
					return true;
				}
			}
			return false;
		};
		void PrintBoard();
		void PrintStack();
		friend class Block;
};