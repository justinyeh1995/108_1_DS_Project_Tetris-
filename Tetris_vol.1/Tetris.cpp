#include <iostream>
#include <fstream>
#include "Stack.h"
using namespace std;
/* Class Board */
class Board{
	private:
		int row, col;
        stack* Stack; 
        int** GameBoard; 
	public:
		Board(){};
		Board(int m , int n ):row(m+4),col(n){
			//row + 4 
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
				if(Stack[i].top() < 3){
					return true;
				}
			}
			return false;
		};
        int** getBoard();
		void PrintBoard();
		void PrintStack();
		friend class Block;
};

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
	for(int i = 4; i < this->row; i++){
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
	for(int i = 4; i < this->row; i++){
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
    /*
    address case 
    1 2
    O 1 
    */
    for(int i = 4; i < this->row; i++){
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

int** Board::getBoard(){
	int r = row-4;
	int** Board =new int*[r];
	for (int i = 0; i < r; i++)
	{
		Board[i] =new int[col];
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Board[i][j] = GameBoard[i+4][j];
			cout<<Board[i][j];
		}	
		cout<<endl;
	}
	return Board;	
}

/* Class Block */
class Block{
    private:
        string Type;
        string Type_array[19];
        int** block;
    public:
        Block(string input_type = ""):Type(input_type){
            Type_array[0] = "T1";
            Type_array[1] = "T2";
            Type_array[2] = "T3";
            Type_array[3] = "T4";
            Type_array[4] = "L1";
            Type_array[5] = "L2";
            Type_array[6] = "L3";
            Type_array[7] = "L4";
            Type_array[8] = "J1";
            Type_array[9] = "J2";
            Type_array[10] = "J3";
            Type_array[11] = "J4";
            Type_array[12] = "S1";
            Type_array[13] = "S2";
            Type_array[14] = "Z1";
            Type_array[15] = "Z2";
            Type_array[16] = "I1";
            Type_array[17] = "I2";
            Type_array[18] = "O";
            getBlock(Type);
            //PrintBlock();
        }
        void InitializeBlock(int** block);
        int** getBlock(string Type);
        int getElementIndex(string Type);
        void PrintBlock();
				friend class Board;
};

void Block::InitializeBlock(int** block){
		for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            block[i][j] = 0;
        }
    }
}

int Block::getElementIndex(string Type){
    int idx = 0;
    int length = 19;
    while(idx < 19){
        if( Type == Type_array[idx])break;
        ++idx;
    }
    return idx;
}

int** Block::getBlock(string Type){
		block = new int*[4];
		for(int i = 0; i < 4; i++){
			block[i] = new int[4];
		}
		InitializeBlock(block);
		int idx = getElementIndex(Type);
    //Type_array.find(Type);
    switch (idx){
    case 0:
        for(int i = 0; i < 3; i++){
           block[2][i] = 1;
        }
        block[3][1] = 1;
        break;
    case 1:
        block[1][1] = 1;
        for(int i = 0; i < 2; i++){
           block[2][i] = 1;
        }
        block[3][1] = 1;
        break;
    case 2:
        block[2][1] = 1;
        for(int i = 0; i < 3; i++){
           block[3][i] = 1; 
        }
        break;
    case 3:
        for(int i = 1; i < 4; i++){
           block[i][0] = 1; 
        }
        block[2][1] = 1;
        break;
    case 4:
        for(int i = 1; i < 4; i++){
           block[i][0] = 1; 
        }
        block[3][1] = 1;
        break;
    case 5:
        for(int i = 0; i < 3; i++){
           block[2][i] = 1;
        }
        block[3][0] = 1;
        break;
    case 6:
        block[1][0] = 1;
        for(int i = 1; i < 4; i++){
           block[i][1] = 1;
        }
        break;
    case 7:
        block[2][2] = 1;
        for(int i = 0; i < 3; i++){
           block[3][i] = 1; 
        }
        break;
    case 8:
        block[3][0] = 1;
        for(int i = 1; i < 4; i++){
           block[i][1] = 1;
        }
        break;
    case 9:
        block[2][0] = 1;
        for(int i = 0; i < 3; i++){
           block[3][i] = 1; 
        }
        break;
    case 10:
        for(int i = 1; i < 4; i++){
           block[i][0] = 1; 
        }
        block[1][1] = 1;
        break;
    case 11:
        for(int i = 0; i < 3; i++){
           block[2][i] = 1;
        }
        block[3][2] = 1;
        break;
    case 12:
        for(int i = 0; i < 2; i++){
           block[2][i+1] = 1;
           block[3][i] = 1;
        }
        break;
    case 13:
        for(int i = 0; i < 2; i++){
           block[i+1][0] = 1;
           block[i+2][1] = 1;
        }
        break;
    case 14:
        for(int i = 0; i < 2; i++){
           block[2][i] = 1;
           block[3][i+1] = 1;
        }
        break;
    case 15:
        for(int i = 0; i < 2; i++){
           block[i+2][0] = 1;
           block[i+1][1] = 1;
        }
        break;
    case 16:
        for(int i = 0; i < 4; i++){
           block[i][0] = 1;
        }
        break;
    case 17:
        for(int i = 0; i < 4; i++){
           block[3][i] = 1;
        }
        break;
    case 18:
        for(int i = 0; i < 2; i++){
           block[2][i] = 1;
           block[3][i] = 1;
        }
        break;

    default:
        break;
    }
	return block;
}

void Block::PrintBlock(){
    for(int i = 0; i < 4; i++){
	    for(int j = 0; j < 4; j++){
		    cout<<block[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
};

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