#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <fstream>
#include <limits>

#define MAX_DISH 16
#define IRRED_POLY 283
#define REVERSE_POW 254

typedef uint8_t byte;

class GaluaFieldPolynomes
{
private:
    std::vector<uint16_t> irred_polynomes;
    
    int push_irred_polynomes_to_vector();

public:

    /* main methods */
    byte add(byte poly1, byte poly2) const;
    byte multiply(byte poly1, byte poly2, uint16_t modulo) const;
    byte inverse(byte poly, uint16_t modulo) const;

    /* bonus method */
    std::vector<uint16_t> get_irred_polynomes() const; // for further work with irred_polynomes

    /* additional methods */
    byte get_remainder(uint16_t poly, uint16_t modulo) const;
    bool check_irreducibility(byte poly) const;
    int get_degree(uint16_t poly) const;
    bool odd_terms_in_polynomial(uint16_t poly) const;
    int print_irred_polynomes(std::vector<uint16_t> vect) const;
};

byte GaluaFieldPolynomes::add(byte poly1, byte poly2) const
{
    return poly1 ^ poly2;
}

int GaluaFieldPolynomes::get_degree(uint16_t poly) const
{
    int degree = 0;
    uint16_t bit = 1;
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

byte GaluaFieldPolynomes::get_remainder(uint16_t poly, uint16_t modulo) const
{
    int degree_modulo;
    int degree_poly;
    int difference;
    uint16_t tmp_poly = poly;

    degree_modulo = get_degree(modulo);

    while ((difference = (degree_poly = get_degree(tmp_poly)) - degree_modulo) >= 0)
    {
        tmp_poly ^= (modulo << difference);
    }
    return tmp_poly;
}

byte GaluaFieldPolynomes::multiply(byte poly1, byte poly2, uint16_t modulo) const
{
    uint16_t result = 0; // 2 bytes
    byte tmp_poly2 = poly2;

    for (int i = 0; i < 8; i++)
    {
        result ^= poly1 * (tmp_poly2 & (1 << i));
    }
    result = get_remainder(result, modulo);
    return result;
}

byte GaluaFieldPolynomes::inverse(byte poly, uint16_t modulo) const
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
bool GaluaFieldPolynomes::odd_terms_in_polynomial(uint16_t poly) const
{
    int counter_one = 0;
    uint16_t bit = 1;
    int degree_poly = get_degree(poly);

    for (int i = 0; i <= degree_poly; i++)
    {
        if (bit & poly)
        {
            counter_one++;
        }
        bit <<= 1;
    }

    if ((counter_one % 2) !=0 && counter_one != 1)
        return true;
    else
        return false;
}

/* get 30 irreducible polynomials */
int GaluaFieldPolynomes::push_irred_polynomes_to_vector()
{
    int non_zero_remainders = 0;
    uint16_t min_poly_with_degree_8 = 282; // 256
    uint16_t max_poly_with_degree_8 = 511;
    uint16_t j;

    for (uint16_t i = min_poly_with_degree_8; i <= max_poly_with_degree_8; i++)
    {
        if (odd_terms_in_polynomial(i))
        {
            for (j = 2; j < 32; j++) // check all polynomes 1, 2, 3, 4 degree
            {
                if (get_remainder(i, j) == 0)
                {
                    non_zero_remainders = 0;
                    break;
                }
                else
                    non_zero_remainders++;
            }

            if (non_zero_remainders == 30)
            {
                irred_polynomes.push_back(i);
                // std::cout << i << std::endl;
                non_zero_remainders = 0;
            }
        }
    }
    if (print_irred_polynomes(irred_polynomes) == 0)
        return 0;
    else
        return 1;
}

std::vector<uint16_t> GaluaFieldPolynomes::get_irred_polynomes() const
{
    get_irred_polynomes();
    return irred_polynomes;
}

int GaluaFieldPolynomes::print_irred_polynomes(std::vector<uint16_t> Vect) const
{
    std::ofstream file;
    uint16_t bit;
    std::vector<uint16_t>::const_iterator iter;

    file.open("file.txt");

    if (!file.is_open())
        return 0;
    else
    {
        file << "30 Irreducible polynomes:\n" << std::endl;
        for (iter = Vect.cbegin(); iter != Vect.cend(); iter++)
        {
            bit = 256;
            file << *iter << " = ";

            for (uint16_t k = get_degree(*iter); k > 0; k--)
            {
                if (bit & (*iter))
                {
                    file << "x^" << (unsigned)k << " + ";
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

    std::cout << (unsigned)GFpoly.add(k, m) << std::endl;
    std::cout << (unsigned)GFpoly.multiply(k, m, IRRED_POLY) << std::endl;
    std::cout << (unsigned)GFpoly.inverse(k, IRRED_POLY) << std::endl;

    GFpoly.get_irred_polynomes();


    return 0;
}