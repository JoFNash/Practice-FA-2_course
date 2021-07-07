#include <iostream>
#define MAX_DISH 64
#define IRRED_POLY 283
#define REVERSE_POW 254
typedef uint16_t byte; 

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
        poly ^= (modulo << difference);
    }
    return poly;
}

byte GaluaFieldPolynomes::multiply(byte poly1, byte poly2, byte modulo)
{
    byte result = 0;
    byte tmp_poly2 = poly2;

    for(int i = 0; i < 8; i++)
    { 
        result ^= poly1 * (tmp_poly2 & (1 << i)); // мой вой был слышен в Америке 
    }
    
    result = getRemainder(result, modulo);
    return result;
}


byte GaluaFieldPolynomes::inverse(byte poly, byte modulo)
{
    int degree_pow;
    int bit;
    byte tmp_poly = poly;
    
    degree_pow = get_degree(REVERSE_POW);
    bit = get_degree(REVERSE_POW);

    for (int i = degree_pow; i > 0; i--)
    {
        if(modulo & bit)
        {
            poly = multiply(poly, poly, modulo);
            poly = multiply(poly, tmp_poly, modulo);
        }
        else 
        {
            poly = multiply(poly, poly, modulo);
        }
        bit >>= 1;
    }
    return poly;
}

bool GaluaFieldPolynomes::check_irreducibility(byte poly)
{
    // pass
}

int main()
{
    GaluaFieldPolynomes GFpoly;
    
    byte k = 2;
    byte m = 150;

    // std::cout << GFpoly.multiply(k, m, IRRED_POLY) << std::endl; 
    std::cout << GFpoly.inverse(k, IRRED_POLY) << std::endl; 
    return 0;
}