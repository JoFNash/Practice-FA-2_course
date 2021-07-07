#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <fstream>
#include <limits>

#define MAX_DISH 16
#define IRRED_POLY 283
#define REVERSE_POW 254

typedef uint16_t byte;

class GaluaFieldPolynomes
{
private:
    std::vector<byte> irred_polynomes;

public:

    ~GaluaFieldPolynomes() = default;

    /* main methods */
    byte add(const byte& poly1, const byte& poly2);
    byte multiply(const byte& poly1, const byte& poly2, const byte& modulo);
    byte& inverse(byte& poly, const byte& modulo);

    /* bonus method */
    int get_all_irreducible_polynomes();

    /* additional methods */
    byte get_remainder(const byte& poly, const byte& modulo);
    bool check_irreducibility(const byte& poly);
    int get_degree(const byte& poly);
    bool odd_terms_in_polynomial(const byte& poly);
    int print_irred_polynomes(const std::vector<byte>& vect);
};

byte GaluaFieldPolynomes::add(const byte& poly1, const byte& poly2)
{
    return poly1 ^ poly2;
}

int GaluaFieldPolynomes::get_degree(const byte& poly)
{
    int degree = 0;
    byte bit = 1;
    for (int i = 0; i < MAX_DISH; i++)
    {
        if (poly & bit)
        {
            degree = i;
        }
        bit <<= 1;
    }
    return degree;
}

byte GaluaFieldPolynomes::get_remainder(const byte& poly, const byte& modulo)
{
    int degree_modulo;
    int degree_poly;
    int difference;
    byte tmp_poly = poly;

    degree_modulo = get_degree(modulo);

    while ((difference = (degree_poly = get_degree(tmp_poly)) - degree_modulo) >= 0)
    {
        tmp_poly ^= (modulo << difference);
    }
    return tmp_poly;
}

byte GaluaFieldPolynomes::multiply(const byte& poly1, const byte& poly2, const byte& modulo)
{
    byte result = 0;
    byte tmp_poly2 = poly2;

    for (int i = 0; i < 8; i++)
    {
        result ^= poly1 * (tmp_poly2 & (1 << i)); 
    }
    result = get_remainder(result, modulo);    
    return result;
}

byte& GaluaFieldPolynomes::inverse(byte& poly, const byte& modulo)
{
    int degree_pow;
    byte bit;
    byte tmp_poly;

    tmp_poly = poly;
    degree_pow = get_degree(REVERSE_POW); 
    bit = REVERSE_POW;

    for (int i = degree_pow; i >= 0; i--)
    {
        if (modulo & bit) // если 1
        {
            poly = multiply(poly, poly, modulo);
            poly = multiply(poly, tmp_poly, modulo);
        }
        else              // если 0
        {
            poly = multiply(poly, poly, modulo);
        }
        bit >>= 1;
    }
    return poly;
}

/* check for zero or odd number of monomials */
bool GaluaFieldPolynomes::odd_terms_in_polynomial(const byte& poly)
{
    int counter_one = 0;
    byte bit = 1;
    int degree_poly = get_degree(poly);

    for (int i = 0; i <= degree_poly; i++)
    {
        if (bit & poly)
        {
            counter_one++;
        }
        bit <<= 1;
    }

    if (counter_one % 2)
        return true;
    else
        return false;
}

/* get 30 irreducible polynomials */
int GaluaFieldPolynomes::get_all_irreducible_polynomes()
{
    int non_zero_remainders = 0; // число ненулевых остатков
    byte min_poly_with_degree_8 = 256;
    byte max_poly_with_degree_8 = 511;
    byte j;

    for (byte i = min_poly_with_degree_8; i <= max_poly_with_degree_8; i++)
    {
        if (odd_terms_in_polynomial(i))
        {
            for (j = 2; j < i; j++)
            {
                if (get_remainder(i, j) == 0)
                {
                    non_zero_remainders = 0;
                    break;
                }
                else
                    non_zero_remainders++;
            }

            if (non_zero_remainders == i - 2)
            {
                irred_polynomes.push_back(i);
                non_zero_remainders = 0;
            }
        }
    }
    if (print_irred_polynomes(irred_polynomes) == 0)
        return 0;
    else
        return 1;
}

int GaluaFieldPolynomes::print_irred_polynomes(const std::vector<byte>& Vect)
{
    std::ofstream file;
    byte bit;
    std::vector<byte>::const_iterator iter;

    file.open("file.txt");

    if(!file.is_open())
        return 0;
    else
    {
        file << "30 Irreducible polynomes:\n" << std::endl;
        for (iter = Vect.cbegin(); iter != Vect.cend(); iter++)
        {
            bit = 256;
            file << *iter << " = ";

            for (byte k = get_degree(*iter); k > 0; k--)
            {
                if (bit & (*iter))
                {
                    file << "x^" << k << " + "; 
                }
                bit >>= 1;
            }
            file << "1" << std::endl;
        }
        file.close();
        return 1;
    }
}

int main()
{
    GaluaFieldPolynomes GFpoly;

    byte k = 3;
    byte m = 7;

    std::cout << GFpoly.add(k, m) << std::endl; 
    std::cout << GFpoly.multiply(k, m, IRRED_POLY) << std::endl; 
    std::cout << GFpoly.inverse(k, IRRED_POLY) << std::endl; 

    if(GFpoly.get_all_irreducible_polynomes() == 0)
        std::cout << "Error: can't open file!" << std::endl;

    return 0;
}