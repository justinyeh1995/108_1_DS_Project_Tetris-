#include <iostream>
using namespace std;
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