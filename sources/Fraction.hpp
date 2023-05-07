#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <climits>
#include <typeinfo>
using namespace std;

namespace ariel {
    class Fraction{

    private:
        int numerator;
        int denominator;

//////////////////////// - overflow - //////////////////////////////////////////////////

        static int overflow_addit(int number1, int number2) {
            if ((number2 > 0 && number1 > (INT_MAX - number2)) || (number2 < 0 && number1 < (INT_MIN - number2)))
                throw std::overflow_error("Addition overflow");
            
            return (number1 + number2);
        }
        static int overflow_subtract(int number1, int number2) {
            if ((number2 < 0 && number1 > INT_MAX + number2) || (number2 > 0 && number1 < INT_MIN + number2))
                throw overflow_error("Subtract overflow");
                    
            return (number1 - number2);
        }
        static int overflow_divide(int number1, int number2) {
            if (number2 == 0 || (number1 == INT_MIN && number2 == -1))
                throw overflow_error("Divide overflow");

            return (number1 / number2);
        }
        static int overflow_multiplicat(int number1, int number2) {
            if ((number2 > 0 && number1 > INT_MAX / number2) || (number2 < 0 && number1 < INT_MIN / number2))
                throw overflow_error("Multiplicat overflow");
                    
            return (number1 * number2);
        }

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(float);
        int __gcd(int a, int b) const;
        void reduce();

        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int numerator);
        void setDenominator(int denominator);
        
        const Fraction operator+(const Fraction& number1) const;
        friend const Fraction operator+(const float& number1, const Fraction& number2);
        friend const Fraction operator+(const Fraction& number1, const float& number2);
        
        const Fraction operator-(const Fraction& number1) const;
        const Fraction operator-(const float& number1) const;
        friend const Fraction operator-(const float& number1, const Fraction& number2);

        
        const Fraction operator/(const Fraction& number1) const;
        const Fraction operator/(const float& number1);
        friend const Fraction operator/(const float& number1, const Fraction& number2);


        const Fraction operator*(const Fraction& number1) const;
        const Fraction operator*(const float& number1);
        friend const Fraction operator*(const float& number1,const Fraction& number2);


        Fraction operator++(int number);
        Fraction operator--(int number);

        Fraction operator++();
        Fraction operator--();
        
        bool operator>(const Fraction& number1) const;
        friend bool operator>(const float& number1, const Fraction& number2);
        friend bool operator>(const Fraction& number1, float number2);

        bool operator<(const Fraction& number1) const;
        friend bool operator<(const float& number1, const Fraction& number2);
        friend bool operator<(const Fraction& number1, float number2);

        bool operator>=(const Fraction& number1) const;
        friend bool operator>= (const float& number1, const Fraction& number2);
        friend bool operator<= (const Fraction& number1, float number2);

        bool operator<=(const Fraction& number1) const;
        friend bool operator<= (const float& number1, const Fraction& number2);
        friend bool operator<= (const Fraction& number1, float number2);

        bool operator==(const Fraction& number1) const;
        friend bool operator==( const Fraction &number1,  const float number2) ;
        friend bool operator==( const float number1,  const Fraction &number2);
        
        bool operator!=(const Fraction& number1) const;
        friend bool operator!=( const Fraction &number1,  const float number2) ;
        friend bool operator!=( const float number1,  const Fraction &number2);
        
        friend ostream& operator<< (ostream& output, Fraction const& frac);
        friend istream& operator>> (istream& input, Fraction& frac);
        
        Fraction& operator=(const Fraction& other) ;

        
    };

}

