#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <climits>
#include <typeinfo>
#include <limits>

using namespace std;

namespace ariel {
    class Fraction{

    private:
        int numerator;
        int denominator;

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(const Fraction& other);
        Fraction(Fraction&& other) noexcept;
        Fraction(float);
        ~Fraction() = default;

        Fraction& operator=(const Fraction& other) ;
        Fraction& operator=(Fraction&& other) noexcept;

        void reduce();

        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int numerator);
        void setDenominator(int denominator);
        
        const Fraction operator+(const Fraction& number1) const;
        const Fraction operator+(const float &number) const;
        friend const Fraction operator+(const float& number1, const Fraction& number2);
        
        const Fraction operator-(const Fraction& number1) const;
        const Fraction operator-(const float& number1) const;
        friend const Fraction operator-(const float& number1, const Fraction& number2);

        
        const Fraction operator/(const Fraction& number1) const;
        const Fraction operator/(const float& number1)const;
        friend const Fraction operator/(const float& number1, const Fraction& number2);


        const Fraction operator*(const Fraction& number1) const;
        const Fraction operator*(const float& number1)const;
        friend const Fraction operator*(const float& number1,const Fraction& number2);
        
        bool operator>(const Fraction& number1) const;
        bool operator>(const float& other) const;
        friend bool operator>( const float& number1, const Fraction& number2);

        bool operator<(const Fraction& number1) const;
        bool operator<(const float& other) const;
        friend bool operator<(const float& number1, const Fraction& number2);

        bool operator>=(const Fraction& number1) const;
        bool operator>=(const float& other) const;
        friend bool operator>= (const float& number1, const Fraction& number2);

        bool operator<=(const Fraction& number1) const;
        bool operator<=(const float& other) const;
        friend bool operator<= (const float& number1, const Fraction& number2);

        bool operator==(const Fraction& number1) const;
        bool operator==(const float& other) const ;
        friend bool operator==( const float& number1,  const Fraction &number2);

        bool operator!=(const Fraction& number1) const;
        bool operator!=(const float& other) const;
        friend bool operator!=( const float& number1,  const Fraction &number2);

        friend ostream& operator<< (ostream& output, Fraction const& frac);
        friend istream& operator>> (istream& input, Fraction& frac);
        
        //prefix
        Fraction& operator++(){
            numerator += denominator;
            return *this;
        }
        Fraction& operator--(){
            numerator -= denominator;
            return *this;
        }

        //postfix
        Fraction operator++(int number){
            Fraction temp = *this;
            numerator += denominator;
            return temp;
        }
        Fraction operator--(int number){
            Fraction temp = *this;
            numerator -= denominator;
            return temp;
        }
   
    };

}

