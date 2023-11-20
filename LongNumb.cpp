﻿#include "LongNumb.hpp"

#define SYSTEM_SIZE 16
#define HEX_ALPH  "0123456789ABCDEF"

LongNumb::LongNumb(const std::string& hexStr) {
   
    data.fill(0);

    
    if (hexStr.length() > array_size * 4) {
        std::cerr << "Invalid length for hexadecimal number." << std::endl;
        return;
    }

    
    int hexIndex = hexStr.length() - 1;
    for (int i = 0; i<= array_size - 1 && hexIndex >= 0; i++) {
        
       
        char hexDigit3 = hexStr[hexIndex--];
        char hexDigit2 = hexIndex >= 0 ? hexStr[hexIndex--] : '0'; 
        char hexDigit1 = hexIndex >= 0 ? hexStr[hexIndex--] : '0';
        char hexDigit0 = hexIndex >= 0 ? hexStr[hexIndex--] : '0';


        uint16_t value =  hexDigitToUint16(hexDigit3);
        value = value | hexDigitToUint16(hexDigit2) << 4;
        value = value | hexDigitToUint16(hexDigit1) << 8;
        value = value | hexDigitToUint16(hexDigit0) << 12;
        data[i] = value;
    }
}



LongNumb::LongNumb() {
    data.fill(0);
}


LongNumb::LongNumb(uint16_t someInt) {
    data.fill(0);
    data[0] = someInt;
}


LongNumb::LongNumb(std::array<uint16_t, array_size> dataArray) {
    for (int i = 0; i < array_size; i++) {
        data[i] = dataArray[i];
    }
}

std::string LongNumb::hexStringToUint16() const { 
    std::string result;
    result.reserve(4 * array_size);

    for (int i = data.size() - 1; i >= 0; i--) {
        uint16_t value = data[i];

        for (int j = 3; j >= 0; j--) {
            char HexDigit = static_cast<char>((value >> (j * 4)) & 0xF);

            if (HexDigit < 10)
                result += '0' + HexDigit;
            else
                result += 'a' + (HexDigit - 10);
        }
    }

    return result;
}

std::string uint16ToHexString(uint16_t value) {
    std::stringstream ss;
    ss << std::hex << std::setw(4) << std::setfill('0') << value;
    return ss.str();
}

std::string stringToHexString(const std::string& input) {
    std::string hexStr;
    hexStr.reserve(input.length() * 2);

    for (char c : input) {
        hexStr += "0123456789ABCDEF"[(c & 0xF0) >> 4];
        hexStr += "0123456789ABCDEF"[c & 0x0F];
    }

    return hexStr;
}



LongNumb::LongNumb(const LongNumb& other) {
    data = other.data;
}

LongNumb& LongNumb::operator= (const LongNumb& other) {
    if (this != &other) { 
        data = other.data;
    }
    return *this;
}

bool LongNumb::operator == (const LongNumb& other) const {   

    for (int i = data.size() - 1; i >= 0; i--) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool LongNumb::operator != (const LongNumb& other) {
    return !(*this == other);
}

bool LongNumb::operator < (const LongNumb& other) {
    int i = array_size - 1;

    while (i >= 0 && data[i] == other.data[i]) {
        i--;
    }

    if (i == -1) {
        return false;
    }
    else {
        return data[i] < other.data[i];
    }
}

bool LongNumb::operator > (const LongNumb& other) {
    int i = array_size - 1;

    while (i >= 0 && data[i] == other.data[i]) {
        i--;
    }

    if (i == -1) {
        return false;
    }
    else {
        return data[i] > other.data[i];
    }
}

bool LongNumb::operator <= (const LongNumb& other) {
    int i = array_size - 1;

    while (i >= 0 && data[i] == other.data[i]) {
        i--;
    }

    if (i == -1) {
        return true;
    }
    else {
        return data[i] < other.data[i];
    }
}

bool LongNumb::operator >= (const LongNumb& other) {
    return !(*this < other);
}

LongNumb LongNumb::operator+ (const LongNumb& other)
{
    LongNumb sum;
    uint16_t carry = 0;

    for (int i = 0; i < array_size; i++)
    {
        uint32_t temp = static_cast<uint32_t>(data[i]) + other.data[i] + carry;
        sum.data[i] = static_cast<uint16_t>(temp & 0xFFFF); 
        carry = static_cast<uint16_t>(temp >> 16); 
    }

    return sum;
}

LongNumb LongNumb::operator- (const LongNumb& other)
{
    LongNumb result;
    int16_t borrow = 0;

    for (int i = 0; i < array_size; i++)
    {
        int32_t temp = static_cast<int32_t>(data[i]) - other.data[i] - borrow;
        if (temp < 0)
        {
            result.data[i] = static_cast<uint16_t>(temp + 0x10000); 
            borrow = 1;
        }
        else
        {
            result.data[i] = static_cast<uint16_t>(temp);
            borrow = 0;
        }
    }

   
    for (int i = 0; i < array_size; i++) {
        if (result.data[i] < 0) {
            result.data[i] = 0;
        }
    }

    return result;
}


LongNumb LongNumb::multiplyByDigit(const uint16_t digit) const {
    LongNumb res;
    uint32_t carry = 0;

    for (int i = 0; i < array_size; i++) {
        uint32_t temp = static_cast<uint32_t>(data[i]) * digit + carry;
        res.data[i] = static_cast<uint16_t>(temp & 0xFFFF);
        carry = temp >> 16;
    }

    res.data[array_size - 1] = static_cast<uint16_t>(carry);

    return res;
}

void LongNumb::LongShiftDigitsToHigh(int shiftCount) {
    if (shiftCount < 0 || shiftCount >= array_size) {
        
        return;
    }

    for (int i = array_size - 1; i >= shiftCount; i--) {
        data[i] = data[i - shiftCount];
    }

    for (int i = 0; i < shiftCount; i++) {
        data[i] = 0;
    }
}


LongNumb LongNumb::operator * (const LongNumb& other) {
    int n = array_size;
    LongNumb C;

    for (int i = 0; i < n; i++) {
        LongNumb temp = other.multiplyByDigit(data[i]);
        temp.LongShiftDigitsToHigh(i);
        C = C + temp;
    }

    return C;
}

LongNumb LongNumb::operator / (const LongNumb& other) {
    if (other == LongNumb(0)) {
        
        return LongNumb();
    }

   

    LongNumb A(*this);
    LongNumb B(other);
    LongNumb Q; 
    LongNumb R; 

    int k = B.LongBitLength();
    R = A;
    Q = LongNumb(0);

    while (R >= B) {
        int t = R.LongBitLength();
        LongNumb C = B.LongShiftBitsToHigh(t - k);

        if (R < C) {
            t = t - 1;
            C = B.LongShiftBitsToHigh(t - k);
        }

        R = R - C;

        Q = Q + (LongNumb(1) << (t - k));
        if (R == B)
        {
            return Q;
        }
    }

    return Q;
}

int LongNumb::LongBitLength() const {
    if (*this == LongNumb(0)) {
        return 0;
    }

    int i = DigitLength();
    i--;
    int length = i * 16;
    uint16_t temp = data[i];

    while (temp != 0) {
        temp = temp >> 1;
        length++;
    }

    return length;
}

int LongNumb::DigitLength() const {
    int length = array_size;

    while (data[length - 1] == 0) {
        length--;

        if (length == 0) {
            break;
        }
    }

    return length;
}

LongNumb LongNumb::LongShiftBitsToHigh(int shiftCount) const {
    if (shiftCount < 0 || shiftCount >= array_size * 16) {
        
        return LongNumb();
    }

    LongNumb result(*this);

    int shiftWords = shiftCount / 16;
    int shiftBits = shiftCount % 16;

    for (int i = array_size - 1; i >= shiftWords; i--) {
        result.data[i] = result.data[i - shiftWords];
    }

    for (int i = 0; i < shiftWords; i++) {
        result.data[i] = 0;
    }

    for (int i = array_size - 1; i >= 0; i--) {
        if (i >= 1) {
            result.data[i] = (result.data[i] << shiftBits) | (result.data[i - 1] >> (16 - shiftBits));
        }
        else {
            result.data[i] = (result.data[i] << shiftBits);
        }
    }

    return result;
}


LongNumb LongNumb::operator << (int shiftCount) {
    LongNumb result(*this); 
    int shiftWords = shiftCount / 16; 
    int shiftBits = shiftCount % 16; 

    
    for (int i = array_size - 1; i >= shiftWords; i--) {
        result.data[i] = result.data[i - shiftWords];
    }

    
    for (int i = 0; i < shiftWords; i++) {
        result.data[i] = 0;
    }

    
    for (int i = array_size - 1; i >= 0; i--) {
        if (i >= 1) {
            result.data[i] = (result.data[i] << shiftBits) | (result.data[i - 1] >> (16 - shiftBits));
        }
        else {
            result.data[i] = (result.data[i] << shiftBits);
        }
    }

    return result;
}

LongNumb LongNumb::operator >> (int shiftCount) {
    LongNumb result(*this);
    int shiftWords = shiftCount / 16;
    int shiftBits = shiftCount % 16;


    for (int i = 0; i < array_size - shiftWords; i++) {
        result.data[i] = result.data[i + shiftWords];
    }


    for (int i = array_size - shiftWords; i < array_size; i++) {
        result.data[i] = 0;
    }


    for (int i = 0; i < array_size; i++) {
        if (i < array_size - 1) {
            result.data[i] = (result.data[i] >> shiftBits) | (result.data[i + 1] << (16 - shiftBits));
        }
        else {
            result.data[i] = (result.data[i] >> shiftBits);
        }
    }

    return result;
}

LongNumb LongNumb::LongPowerWindow(const LongNumb& A, const LongNumb& B) {
    LongNumb C(1);

    LongNumb D[2 * array_size];
    D[0] = LongNumb(1);
    D[1] = A;

    for (int i = 2; i < 2 * array_size; i++) {
        D[i] = D[i - 1] * A;
    }

    int m = B.LongBitLength();
    for (int i = m - 1; i >= 0; i--) {
        C = C * D[B.data[i]];

        if (i != 0) {
            for (int k = 1; k <= 16; k++) {
                C = C * C;
            }
        }
    }

    return C;
}

LongNumb LongNumb::operator % (const LongNumb& other) {
    if (other == LongNumb(0)) {
        return LongNumb();
    }

    LongNumb A(*this);
    LongNumb B(other);

    LongNumb Q = A / B;
    LongNumb R = A - (Q * B);

    return R;


}

uint16_t LongNumb::hexDigitToUint16(char hexDigit) {
    if (hexDigit >= '0' && hexDigit <= '9') {
        return static_cast<uint16_t>(hexDigit - '0');
    }
    else if (hexDigit >= 'A' && hexDigit <= 'F') {
        return static_cast<uint16_t>(10 + (hexDigit - 'A'));
    }
    else if (hexDigit >= 'a' && hexDigit <= 'f') {
        return static_cast<uint16_t>(10 + (hexDigit - 'a'));
    }
    else {
        return 0;
    }
}


void LongNumb::generateRandomHex(int length) {
    srand(static_cast<unsigned int>(time(0)));

    const std::string hexChars = "0123456789ABCDEF";

    if (length < 1 || length > array_size * 4) {
        std::cerr << "Invalid length for random hexadecimal number." << std::endl;
        return;
    }

    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % hexChars.size();
        char hexDigit = hexChars[randomIndex];
        uint16_t value = hexDigitToUint16(hexDigit);
        data[i % array_size] = (data[i % array_size] << 4) | value;
    }
}
