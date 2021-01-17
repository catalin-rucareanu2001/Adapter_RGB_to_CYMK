#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CYMK
{
protected:
    double Cyan;
    double Yellow;
    double Magenta;
    double Black;

public:
    CYMK() {}; // needed for AdaptFormat constructor?
    CYMK(int Cyan, int Yellow, int Magenta, int Black);
    void AfisareA()
    {
        cout << "\nCyan=" << this->Cyan << "\nYellow=" << this->Yellow << "\nMagenta=" << this->Magenta << "\nBlack=" << this->Black << "\n";
    }

};

CYMK::CYMK(int Cyan, int Yellow, int Magenta, int Black)
{
    this->Cyan = Cyan;
    this->Yellow = Yellow;
    this->Magenta = Magenta;
    this->Black = Black;
}


class RGB
{
private:
    int Blue;
    int Red;
    int Green;

public:
    RGB(int Red, int Blue, int Green);
    void AfisareP()
    {
        cout << "\nRed=" << this->Red << "\nGreen=" << this->Green << "\nBlue=" << this->Blue << "\n";
    }

    friend class AdaptFormat;
};

RGB::RGB(int Red, int Blue, int Green)
{
    this->Blue = Blue;
    this->Red = Red;
    this->Green = Green;
}



class AdaptFormat : public CYMK
{
private:
    RGB* to_adapt; // pointer to avoid = overloading

public:
    AdaptFormat(RGB new_format);
    ~AdaptFormat();

    void AfisareAa()
    {
        double r, g, b;
        r = to_adapt->Red / 255.0;
        g = to_adapt->Green / 255.0;
        b = to_adapt->Blue/ 255.0;
        if (b >= r) 
        {
            if (b >= g)
            {
                this->Black = 1 - b;
            }  
            else
            {
                this->Black = 1 - g;
            }
                
        }
        else {
            if (r >= g)
            {
                this->Black = 1 - r;
            }
            else
            {
                this->Black = 1 - g;
            }
        }
        cout << "\nK=" << Black;
        if (Black!=1)
        {
            Cyan = (1 - r - Black) / (1 - Black);
            Yellow = (1 - b - Black) / (1 - Black);
            Magenta = (1 - g - Black) / (1 - Black);
        }
        else
        {
            Cyan = 0;
            Yellow = 0;
            Magenta = 0;
        }
        
        cout << "\nCyan=" << (int)(this->Cyan*100) << "\nYellow=" << (int)(this->Yellow*100) << "\nMagenta=" << (int)(this->Magenta*100) << "\nBlack=" << (int)(this->Black*100) << "\n";
    }

};

AdaptFormat::AdaptFormat(RGB new_format) : CYMK{}
{
    this->to_adapt = new RGB(new_format.Red, new_format.Blue, new_format.Green);
}

AdaptFormat::~AdaptFormat()
{
    delete this->to_adapt;
}



int main(void)
{
    int C = 30, Y = 12, M = 24, K = 2;
    int Rr= 255, Gg= 212, Bb= 90;

    CYMK ended(C, Y, M, K);
    RGB started(Rr, Gg, Bb);
    AdaptFormat adapted(started);

    cout << "From an end product: ";
    ended.AfisareA();

    cout << "\nFrom starting class: ";
    started.AfisareP();

    cout << "\nFrom adapted starting class: ";
    adapted.AfisareAa();

    return 0;
}