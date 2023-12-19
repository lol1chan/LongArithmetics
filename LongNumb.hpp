#pragma once

#define LongNumb_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <array>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <random>
#define array_size 129


class LongNumb {
private:
    std::array<uint16_t, array_size> data;

private:
      std::string hexStringToUint16() const; 
    
public:
    std::string toBinaryString() const;
    std::string removeLeadingZeros(const std::string& binaryString) const;
    uint16_t hexDigitToUint16(char hexDigit);
    LongNumb(const std::string& hexStr);
    LongNumb();
    LongNumb(uint16_t someInt);
    LongNumb(std::array<uint16_t, array_size> data);
    LongNumb(const LongNumb& other);
    void LongShiftDigitsToHigh(int shiftCount);
    LongNumb multiplyByDigit(const uint16_t digit) const;
    int LongBitLength() const;
    LongNumb LongShiftBitsToHigh(int shiftCount) const;
    LongNumb LongPowerWindow(const LongNumb& A, const LongNumb& B);
    int DigitLength() const;
    void generateRandomHex(int length);
    std::string GenHex(int length);
   
    void appendChar(char hexDigit);

    LongNumb& operator = (const LongNumb& other);
    LongNumb operator + (const LongNumb& other);
    LongNumb operator - (const LongNumb& other) const;
    LongNumb operator * (const LongNumb& other);
    LongNumb operator / (const LongNumb& other);
    LongNumb operator % (const LongNumb& other);

    LongNumb operator << (const int shiftCount);
    LongNumb operator >> (const int shiftCount);


    bool operator == (const LongNumb& other) const;
    bool operator != (const LongNumb& other);
    bool operator < (const LongNumb& other) const;
    bool operator > (const LongNumb& other);
    bool operator <= (const LongNumb& other);
    bool operator >= (const LongNumb& other);
    
    void Print() const;

    LongNumb gcd(LongNumb& A, LongNumb& B);
    LongNumb lcm(LongNumb& A, LongNumb& B);
    LongNumb BarrettReduction(const LongNumb& A, const LongNumb& N, const LongNumb& M);
    LongNumb Mu(const LongNumb& N);
    LongNumb ModAdd(LongNumb& other, const LongNumb m);
    LongNumb ModSub(LongNumb& other, const LongNumb m);
    LongNumb ModMult(LongNumb& other, const LongNumb m);
    LongNumb ModPow(const LongNumb& A  ,const LongNumb& B, const LongNumb m);
    LongNumb ModSquare(LongNumb& A, const LongNumb m);
};