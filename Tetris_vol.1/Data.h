#include <iostream>
#include <fstream>
using namespace std;
class Data{
    private:
        int r, c;
        string Type;
        int posx;
    public:
        Data(string T = "",int x = 1):Type(T),posx(x){}
        string getType(){return this->Type;}
        int getX(){return this->posx;}  
        void setString(string Type){this->Type = Type;}
        void setPosX(int posx){this->posx = posx;}
        string getString(){return this->Type;}
        int getPosX(){return this->posx;}
		
		void setR(int r){this->r = r;}
        void setC(int c){this->c = c;}
        int getR(){return this->r;}
        int getC(){return this->c;}
};