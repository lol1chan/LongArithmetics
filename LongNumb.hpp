#pragma once

#define LongNumb_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <array>
#include <ostream>
#include <cstdlib>
#include <ctime>
#define array_size 256


class LongNumb {
private:
    std::array<uint16_t, array_size> data;

private:
      std::string hexStringToUint16() const; 
    
public:
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

    LongNumb& operator = (const LongNumb& other);
    LongNumb operator + (const LongNumb& other);
    LongNumb operator - (const LongNumb& other);
    LongNumb operator * (const LongNumb& other);
    LongNumb operator / (const LongNumb& other);
    LongNumb operator % (const LongNumb& other);

    LongNumb operator << (const int shiftCount);
    LongNumb operator >> (const int shiftCount);

    bool operator == (const LongNumb& other) const;
    bool operator != (const LongNumb& other);
    bool operator < (const LongNumb& other);
    bool operator > (const LongNumb& other);
    bool operator <= (const LongNumb& other);
    bool operator >= (const LongNumb& other);
    
    void Print() const {
        int mostSignificantDigit = array_size - 1;

        
        while (mostSignificantDigit >= 0 && data[mostSignificantDigit] == 0) {
            mostSignificantDigit--;
        }

        if (mostSignificantDigit < 0) {
            
            std::cout << "0";
        }
        else {
            
            for (int i = mostSignificantDigit; i >= 0; i--) {
                std::cout << std::hex << std::setw(4) << std::setfill('0') << data[i];
            }
        }

        std::cout << std::endl;
    }

};