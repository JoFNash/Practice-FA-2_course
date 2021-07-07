#include <iostream>
#include <vector>
#define MAX_DISH 64
#define IRRED_POLY 283
#define REVERSE_POW 254
typedef uint16_t byte; 

class GaluaFieldPolynomes 
{
    private:
        std::vector<byte> irred_polynomes;

    public:
        byte add(const byte& poly1, const byte& poly2);
        byte multiply(const byte& poly1, const byte& poly2, const byte& modulo);
        byte inverse(byte& poly, const byte& modulo); 
        byte getRemainder(byte& poly, const byte& modulo);
        bool check_irreducibility(const byte& poly);
        void get_all_irreducible_polynomes();
        int get_degree(const byte& poly);
}; 

byte GaluaFieldPolynomes::add(const byte& poly1, const byte& poly2)
{
    return poly1 ^ poly2;
}

int GaluaFieldPolynomes::get_degree(const byte& poly)
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

byte GaluaFieldPolynomes::getRemainder(byte& poly, const byte& modulo)
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

byte GaluaFieldPolynomes::multiply(const byte& poly1, const byte& poly2, const byte& modulo)
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


byte GaluaFieldPolynomes::inverse(byte& poly, const byte& modulo)
{
    int degree_pow;
    int bit;
    byte tmp_poly = poly;
    
    degree_pow = get_degree(REVERSE_POW); // 7
    bit = get_degree(REVERSE_POW); // 7

    for (int i = 0; i <= degree_pow; i++)
    {
        if(modulo & bit) // если 1
        {
            poly = multiply(poly, poly, modulo);
            poly = multiply(poly, tmp_poly, modulo);
        }
        else             // если 0
        {
            poly = multiply(poly, poly, modulo);
        }
        bit >>= 1;
    }
    return poly;
}

bool GaluaFieldPolynomes::check_irreducibility(const byte& poly)
{
    // pass
}

void GaluaFieldPolynomes::get_all_irreducible_polynomes()
{
    
}

int main()
{
    GaluaFieldPolynomes GFpoly;
    
    byte k = 3;
    byte m = 7;

    // std::cout << GFpoly.add(k, m) << std::endl; 
    // std::cout << GFpoly.multiply(k, m, IRRED_POLY) << std::endl; 
    std::cout << GFpoly.inverse(k, IRRED_POLY) << std::endl; 

    return 0;
}