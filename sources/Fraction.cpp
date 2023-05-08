#include "Fraction.hpp"
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

using namespace std;
namespace ariel 
{
    Fraction::Fraction(): numerator(0), denominator(1) {}
    Fraction::Fraction(const Fraction& other): numerator(other.numerator), denominator(other.denominator) {}
    Fraction::Fraction(Fraction&& other) noexcept: numerator(other.numerator), denominator(other.denominator) {}
    Fraction::Fraction(int numerator, int denominator):numerator(numerator), denominator(denominator){
        if (denominator == 0) 
            throw invalid_argument("The denominator cannot be 0");
        reduce();

        if(this->numerator < 0 && this->denominator < 0){
            this->numerator *= -1;
            this->denominator *= -1;
        }
        if(this->numerator >= 0 && this->denominator < 0){
            this->numerator *= -1;
            this->denominator *= -1;
        }
    }

    Fraction::Fraction(float num){
        if (num == 0){
            this->numerator = 0;
            this->denominator = 1;
        }
        this->numerator = (int)(num * 1000);
        this->denominator = 1000;
        reduce();
    }
    
    Fraction& Fraction::operator=(const Fraction& other) {
        if (this == &other)
            return *this;
        
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }
    
    Fraction& Fraction::operator=(Fraction&& other) noexcept {
        if (this == &other)
            return *this;

        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }
    
    void Fraction:: reduce(){
        int gcd = std:: gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    int Fraction::getNumerator() const { 
        return numerator; 
    }
    int Fraction::getDenominator() const {
         return denominator; 
    }
    void Fraction::setNumerator(int numerator) {
         this->numerator = numerator; 
    }
    void Fraction::setDenominator(int denominator) { 
        if( denominator == 0 )
            throw invalid_argument("The denominator cannot be 0");
    
        this->denominator = denominator;
    }
    /// (+)
    const Fraction Fraction::operator+(const Fraction& other) const {
        long long numerator1 = static_cast<long long>(this->numerator) * static_cast<long long>(other.denominator);
        long long numerator2 = static_cast<long long>(other.numerator) * static_cast<long long>(this->denominator);
        long long rs_deno = static_cast<long long>(this->denominator) * static_cast<long long>(other.denominator);
        long long rs_num = numerator1 + numerator2;

        // check for overflow
        if ((rs_num > numeric_limits<int>::max()) || (rs_deno > numeric_limits<int>::max()) ||
            (rs_num < numeric_limits<int>::min()) ||(rs_deno < numeric_limits<int>::min()))
           
            throw overflow_error("Fraction addition overflowed");
        
        return Fraction (rs_num, rs_deno);
    }
    const Fraction Fraction::operator+(const float &number) const {
        return *this + Fraction(number);
    }
    const Fraction operator+(const float& number1, const Fraction& number2) {
        return Fraction(number1) + number2;
    }
    
    
    // (-) -- done //
    const Fraction Fraction::operator-(const Fraction& other) const {
         if((*this > 0) && (other.getNumerator() == numeric_limits<int>::min()))
            throw overflow_error("Fraction subtraction overflowed");
    
        Fraction n_number = other * -1;
        return Fraction (*this + n_number);
    }
    const Fraction Fraction::operator-(const float& number) const  {
        return *this - Fraction(number);
    }
    const Fraction operator-(const float& number1, const Fraction& number2) {
        return Fraction(number1) - number2;
    }

    // (/) -- done //
    const Fraction Fraction::operator/(const Fraction& other) const {
        if (other.numerator == 0) 
            throw runtime_error("Cannot divided by zero");
            
        Fraction temp = Fraction(other.denominator, other.numerator);
        return Fraction( *this * temp) ;
    }

    const Fraction Fraction:: operator/(const float& number1) const{
        if (number1 == 0.0)
            throw runtime_error("Cannot divided by zero");

        return *this / Fraction(number1);
    }

    const Fraction operator/(const float& number1, const Fraction& number2){
        if (number2.numerator == 0)
            throw runtime_error("Cannot divide by zero");

        return Fraction(number1) / number2;
    }

    // (*) -- done //
    const Fraction Fraction::operator*(const Fraction& other) const {
        // check for overflow
        if ((long long)numerator * other.numerator > numeric_limits<int>::max()
            || (long long)denominator * other.denominator > numeric_limits<int>::max()) {
            throw overflow_error("Multiplication overflow");
        }
        int num = numerator * other.numerator;
        int deno = denominator * other.denominator;
        
        return Fraction(num, deno);
    }
    const Fraction Fraction::operator*(const float& number1) const{
        return *this * Fraction(number1);
    }
    const Fraction operator*(const float& number1, const Fraction& number2) {
        return Fraction(number1) * number2;
    }

    
    
    // (>) -- done //
    bool Fraction::operator>(const Fraction& other) const {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }
    bool Fraction::operator>(const float& number1) const {
        return *this > Fraction(number1);
    }
    bool operator>( const float& number1, const Fraction& number2) {
        return Fraction(number1) > number2;
    }
    

    // (<) -- done //
    bool Fraction::operator<(const Fraction& other) const {
        return !(*this > other || *this == other);
    }
    bool Fraction::operator<(const float& number1) const {
        return *this < Fraction(number1);
    }
    bool operator<(const float& number1, const Fraction& number2)  {
        return Fraction(number1) < number2;
    }
    
    

    // (>=) -- done //
    bool Fraction:: operator>=(const Fraction& other) const{
        return (numerator * other.denominator) >= (denominator * other.numerator);
    }
    bool Fraction:: operator>=(const float& number1) const {
        return !(*this < Fraction(number1));
    }
    bool operator>=(const float& number1, const Fraction& number2) {
        return !( Fraction(number1) < number2 );
    }

    // (<=) -- done //
    bool Fraction:: operator<=(const Fraction& other) const{
        return (numerator * other.denominator) <= (denominator * other.numerator);
    }
    bool Fraction:: operator<=(const float& number1) const {
        return !(*this > Fraction(number1));
    }
    bool operator<= (const float& number1, const Fraction& number2) {
        return !( Fraction(number1) > number2 );
    }
    
    
    // (==) -- done //
    bool Fraction:: operator==(const Fraction& number1) const{
        return (numerator == number1.numerator) && (denominator == number1.denominator);
    }
    bool Fraction::operator==(const float& other) const {
        return *this == Fraction(other);
    }
    bool operator==( const float& number1,  const Fraction &number2) {
        return Fraction(number1) == number2;
    }


    // (!=) -- done //
    bool Fraction:: operator!=(const Fraction& other) const{
        return !((numerator == other.numerator) && (denominator == other.denominator));
    }
    bool Fraction::operator!=(const float& other) const {
        return !(*this == Fraction(other));
    }
    bool operator!=( const float& number1, const Fraction &number2) {
        return !(Fraction(number1) == number2);
    }
    
    
    // (>>) -- done //
    istream& operator>> (istream& input, Fraction& frac){
        int num ,deno;
        input >> num >> deno;

        if(input.fail()) 
            throw runtime_error("Needed *two* numbers\n");
        if(deno == 0)
            throw runtime_error("The denominator cannot be 0\n");
        else if (deno < 0){
            num = -num;
            deno = -deno;
        }

        frac.numerator = num;
        frac.denominator = deno;
        frac.reduce();
        
        return input;
    }
    
    // (<<) -- done //
    ostream& operator<< (ostream& output, Fraction const& frac){
        return output << frac.getNumerator() << '/' << frac.getDenominator();
    }
       
};
