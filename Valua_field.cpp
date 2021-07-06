#include <iostream>
#define MAX_DISH 32
typedef uint16_t byte; 

class Polynom // is this class required?
{
    public:
        byte num;
        Polynom(){};
        ~Polynom(){};
        
};

class GaluaFieldPolynomes 
{
    public:
        byte add(byte poly1, byte poly2);
        byte multiply(byte poly1, byte poly2, byte modulo);
        byte inverse(byte poly, byte modulo); 
        byte getRemainder(byte poly, byte modulo);
        bool check_irreducibility(byte poly);
        int get_degree(byte poly);
}; 

byte GaluaFieldPolynomes::add(byte poly1, byte poly2)
{
    return poly1 ^ poly2;
}

int GaluaFieldPolynomes::get_degree(byte poly)
{
    int degree;
    int place = 1;
    for (int i = 0; i < MAX_DISH; i++)
    {
        if (poly & place)
        {
            degree = i;
        }
        place <<= 1;
    }
    return degree;
}

byte GaluaFieldPolynomes::getRemainder(byte poly, byte modulo)
{
    int degree_modulo;
    int degree_poly;
    int difference;

    degree_modulo = get_degree(modulo);
    while((difference = (degree_poly = get_degree(poly)) - degree_modulo) >= 0)
    {
        poly = (modulo << difference) ^ poly;
    }
    return poly;
}

byte GaluaFieldPolynomes::multiply(byte poly1, byte poly2, byte modulo)
{
    byte result = 0;
    for(int i = 0; i < 8; i++)
    { 
        result ^= poly1 * poly2 & (1 << i);
    }
    
    result = getRemainder(result, modulo);
    
    return result;
}


byte GaluaFieldPolynomes::inverse(byte poly, byte modulo)
{
    // pass
}

bool GaluaFieldPolynomes::check_irreducibility(byte poly)
{
    // pass
}

int main()
{
    GaluaFieldPolynomes GFpoly;
    
    byte k = 3;
    byte m = 7;
    byte modulo = 283;

    //std::cout << GFpoly.add(k, m) << std::endl;
    //std::cout << sizeof(k) << std::endl; // 2 bytes
    std::cout << GFpoly.multiply(k, m, modulo) << std::endl; // works for like normal polynomes
    return 0;
}