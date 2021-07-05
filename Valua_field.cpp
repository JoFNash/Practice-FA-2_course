#include <iostream>

typedef uint64_t byte;

class Polynom // is this class required?
{
    public:
        byte num;
        Polynom(){};

        ~Polynom(){};
        
};

class GaluaFieldPolynomes 
{
    private:
        byte add(byte poly1, byte poly2);
        byte multiply(byte poly1, byte poly2, byte modulo);
        byte inverse(byte poly, byte modulo); 
        bool check_irreducibility(byte poly);
}; 

byte GaluaFieldPolynomes::add(byte poly1, byte poly2)
{
    // через операцию - xor
    return poly1 ^ poly2; // (?)
}

byte GaluaFieldPolynomes::multiply(byte poly1, byte poly2, byte modulo)
{
    byte result = 0;
    
}

byte GaluaFieldPolynomes::inverse(byte poly, byte modulo)
{

}

bool GaluaFieldPolynomes::check_irreducibility(byte poly)
{

}

int main()
{
    GaluaFieldPolynomes GFpoly;
    
    byte k = 4;
    byte m = 5;
    std::cout << sizeof(k) << std::endl;

    return 0;
}