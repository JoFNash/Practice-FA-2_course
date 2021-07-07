#include <iostream>
#include <vector>
#include <cmath>
#define MAX_DISH 64
#define IRRED_POLY 283
#define REVERSE_POW 254
typedef uint16_t byte;

class GaluaFieldPolynomes
{
private:
    std::vector<byte> irred_polynomes;

public:
    /* main methods */
    byte add(const byte& poly1, const byte& poly2);
    byte multiply(byte& poly1, const byte& poly2, const byte& modulo);
    byte inverse(byte& poly, const byte& modulo);

    /* bonus method */
    void get_all_irreducible_polynomes();

    /* additional methods */
    byte getRemainder(const byte& poly, const byte& modulo);
    bool check_irreducibility(const byte& poly);
    int get_degree(const byte& poly);
    bool odd_terms_in_polynomial(const byte& poly);
};

byte GaluaFieldPolynomes::add(const byte& poly1, const byte& poly2)
{
    return poly1 ^ poly2;
}

int GaluaFieldPolynomes::get_degree(const byte& poly)
{
    int degree = 0;
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

byte GaluaFieldPolynomes::getRemainder(const byte& poly, const byte& modulo)
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

byte GaluaFieldPolynomes::multiply(byte& poly1, const byte& poly2, const byte& modulo)
{
    byte result = 0;
    byte tmp_poly2 = poly2;

    for (int i = 0; i < 8; i++)
    {
        result ^= poly1 * (tmp_poly2 & (1 << i)); // мой вой был слышен в Америке 
    }

    if (get_degree(result) > 7) // это условие можно убрать в принципе
        result = getRemainder(result, modulo);
    return result;
}


byte GaluaFieldPolynomes::inverse(byte& poly, const byte& modulo)
{
    int degree_pow;
    byte bit;
    byte tmp_poly = poly;

    degree_pow = get_degree(REVERSE_POW); // 7
    bit = REVERSE_POW; // 254

    if (poly == 0)
        return 0;
    else if (poly == 1)
        return 1;

    for (int i = degree_pow; i >= 0; i--)
    {
        std::cout << "bit = " << bit << std::endl;
        std::cout << "poly = " << poly << std::endl;

        if (modulo & bit) // если 1
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
        return 1;
    else
        return 0;
}

void GaluaFieldPolynomes::get_all_irreducible_polynomes()
{
    int flag = 0;

    for (byte i = 256; i <= 511; i++)
    {
        if (odd_terms_in_polynomial(i))
        {
            for (byte j = 2; j < i; j++)
            {
                if (getRemainder(i, j) == 0)
                {
                    flag = 0;
                    break;
                }
                else
                {
                    flag++;
                }
            }
            if (flag == i - 2)
            {
                irred_polynomes.push_back(i);
                // std::cout << "Irred polynome = " << i << std::endl; // ахринеть, оно работает
                flag = 0;
            }

        }

    }
}

int main()
{
    GaluaFieldPolynomes GFpoly;

    byte k = 2;
    byte m = 7;

    // std::cout << GFpoly.add(k, m) << std::endl; 
    // std::cout << GFpoly.multiply(k, m, IRRED_POLY) << std::endl; 
    // std::cout << GFpoly.inverse(k, IRRED_POLY) << std::endl; 
    // std::cout << GFpoly.odd_terms_in_polynomial(2) << std::endl;
    // std::cout << GFpoly.odd_terms_in_polynomial(3) << std::endl;

    GFpoly.get_all_irreducible_polynomes();

    return 0;
}