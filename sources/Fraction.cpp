#include "Fraction.hpp"
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
namespace ariel 
{
    Fraction::Fraction(): numerator(0), denominator(1) {}
    Fraction::Fraction(int numerator, int denominator):numerator(numerator), denominator(denominator){
        if (denominator == 0) 
            throw invalid_argument("The denominator cannot be 0");
        
        if (denominator < 0){
            numerator = -numerator;
            denominator = -denominator;
        }
        reduce();
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
    
    void Fraction:: reduce(){
        int gcd = abs( this -> __gcd(numerator, denominator) );
        numerator /= gcd;
        denominator /= gcd;
    }
    

    int Fraction:: __gcd(int a, int b) const { 
        return ( b == 0 ) ? a : __gcd(b, a % b); 
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
        int a = overflow_multiplicat(numerator, other.denominator);
        int b = overflow_multiplicat(other.numerator, denominator);
        
        int num = overflow_addit(a, b);
        int deno = overflow_multiplicat(denominator, other.denominator);

        return Fraction(num, deno);
    }
    const Fraction operator+(const float& number1, const Fraction& number2) {
        return Fraction(number1) + number2;
    }
    const Fraction operator+(const Fraction& number1, const float& number2) {
        return number1 + Fraction(number2);
    }
    
    /// (-)
    const Fraction Fraction::operator-(const Fraction& other) const {
        int a = overflow_multiplicat(numerator, other.denominator);
        int b = overflow_multiplicat(other.numerator, denominator);
        
        int num = overflow_subtract(a, b);
        int deno = overflow_multiplicat(denominator, other.denominator);

        return Fraction(num, deno);
    }

    const Fraction Fraction::operator-(const float& other) const  {
        return *this - Fraction(other);
    }

    const Fraction operator-(const float& number1, const Fraction& number2) {
        return Fraction(number1) - number2;
    }

    /// (/) 
    const Fraction Fraction::operator/(const Fraction& other) const {
        if (other.numerator == 0)
            throw runtime_error("Cannot divide by zero");

        int num = overflow_multiplicat(numerator, other.denominator);
        int deno = overflow_multiplicat(denominator, other.numerator);

        return Fraction(num, deno);
    }

    const Fraction Fraction:: operator/(const float& number1){
        if (number1 == 0.0)
            throw runtime_error("Can't divide by zero");

        return *this / Fraction(number1);
    }

    const Fraction operator/(const float& number1, const Fraction& number2){
        if (number2.numerator == 0)
            throw runtime_error("Can't divide by zero");

        return Fraction(number1) / number2;
    }

    // (*) -- done
    const Fraction Fraction::operator*(const Fraction& other) const {
        int numerator = overflow_multiplicat(numerator, other.numerator);
        int denominator = overflow_multiplicat(denominator, other.denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator*(const float& number1){
        return *this * Fraction(number1);
    }
    const Fraction operator*(const float& number1, const Fraction& number2) {
        return Fraction(number1) * number2;
    }

    
    // postfix -- done
    Fraction Fraction:: operator++(int number){
        Fraction temp = *this;
        ++(*this);
        return temp;
    }
    Fraction Fraction:: operator--(int number){
        Fraction temp = *this;
        --(*this);
        return temp;
    }
    
    // prefix -- done
    Fraction Fraction:: operator--(){
        this->numerator -= this->denominator;
        reduce();
        return *this;
    }
    
    Fraction Fraction:: operator++(){
        this->numerator += this->denominator;
        reduce();
        return *this;
    }
    
    // (>) -- done
    bool Fraction::operator>(const Fraction& other) const {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }
    bool operator>(const float& number1, const Fraction& number2) {
        return Fraction(number1) > number2;
    }
    bool operator>(const Fraction& number1, float number2) {
        return number1 > Fraction(number2);
    }

    // (<) -- done
    bool Fraction::operator<(const Fraction& other) const {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }
    bool operator<(const float& number1, const Fraction& number2) {
        return Fraction(number1) < number2;
    }
    bool operator<(const Fraction& number1, float number2) {
        return number1 < Fraction(number2);
    }

    // (>=) -- done
    bool Fraction:: operator>=(const Fraction& number1) const{
        return !(*this < number1);
    }
    bool operator>= (const float& number1, const Fraction& number2) {
        return !( Fraction(number1) < number2 );
    }
    bool operator>= (const Fraction& number1, float number2) {
        return !( number1 < Fraction(number2) );
    }

    // (<=) -- done
    bool Fraction:: operator<=(const Fraction& number1) const{
        return !(*this > number1);
    }
    bool operator<= (const float& number1, const Fraction& number2) {
        return !( Fraction(number1) > number2 );
    }
    bool operator<= (const Fraction& number1, float number2) {
        return !( number1 > Fraction(number2) );
    }
    

    // (==) -- done
    bool Fraction:: operator==(const Fraction& number1) const{
        return (numerator == number1.numerator) && (denominator == number1.denominator);
    }
    bool operator==( const Fraction &number1,  const float number2){
        return number1 == Fraction(number2);
    }
    bool operator==( const float number1,  const Fraction &number2){
        return Fraction(number1) == number2;

    }
    // for unequality -- done

    bool Fraction:: operator!=(const Fraction& number1) const{
        return !((numerator == number1.numerator) && (denominator == number1.denominator));
    }
    bool operator!=( const Fraction &number1,  const float number2){
        return !(number1 == Fraction(number2));
    }
    bool operator!=( const float number1,  const Fraction &number2){
        return !(Fraction(number1) == number2);

    }
    
    // (>>) -- done
    istream& operator>> (istream& input, Fraction& frac){
        int num ,deno;
        input >> num >> deno;

        if(input.fail()) 
            throw runtime_error("Needed *two* numbers\n");
        if(deno == 0)
            throw runtime_error("The denominator cannot be 0\n");

        frac = Fraction(num, deno);
        
        return input;
    }
    
    //(<<) -- done
    ostream& operator<< (ostream& output, Fraction const& frac){
        return output << frac.getNumerator() << '/' << frac.getDenominator();
    }
    
    Fraction& Fraction::operator=(const Fraction& other) {
        if (this == &other)
            return *this;
        
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }
    

    

    
};
