#include "Block.h"
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
        //block = {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0};
        for(int i = 0; i < 3; i++){
           block[2][i] = 1;
        }
        block[3][1] = 1;
        break;
    case 1:
        //block = {{0,0,0,0},{0,1,0,0},{1,1,0,0},{0,1,0,0}};
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