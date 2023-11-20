#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "LongNumb.hpp"

using namespace std;
using namespace chrono;

constexpr int NUM_TESTS = 20;

template <typename Func>
double measureTime(Func&& func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

template <typename T>
LongNumb generateRandomHexNumber(T length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 15);

    LongNumb num;
    for (T i = 0; i < length; ++i) {
        int randomDigit = dis(gen);
        char digit = static_cast<char>(randomDigit < 10 ? '0' + randomDigit : 'a' + randomDigit - 10);
        num.appendChar(digit); \
    }
    return num;
}

template <typename T>
void runTests(T length) {
    double AdditionTime = 0.0;
    double SubtractionTime = 0.0;
    double MultiplicationTime = 0.0;
    double DivisionTime = 0.0;
    double ModTime = 0.0;
    double SquareTime = 0.0;
    double PowTime = 0.0;

    for (int i = 0; i < NUM_TESTS; i++) {
        LongNumb num1 = generateRandomHexNumber(length);
        LongNumb num2 = generateRandomHexNumber(length);

        AdditionTime += measureTime([&] { LongNumb resultAdd = num1 + num2; });
        SubtractionTime += measureTime([&] { LongNumb resultSub = num1 - num2; });
        MultiplicationTime += measureTime([&] { LongNumb resultMul = num1 * num2; });
        DivisionTime += measureTime([&] { LongNumb resultDiv = num1 / num2; });
        ModTime += measureTime([&] { LongNumb resultMod = num1 % num2; });
        SquareTime += measureTime([&] { LongNumb resultSquare = num1.LongPowerWindow(num1, LongNumb(2)); });
        PowTime += measureTime([&] { LongNumb resultPow = num1.LongPowerWindow(num1, LongNumb(9)); });
    }

    double AverAdditionTime = AdditionTime / NUM_TESTS;
    double AverSubtractionTime = SubtractionTime / NUM_TESTS;
    double AverMultiplicationTime = MultiplicationTime / NUM_TESTS;
    double AverDivisionTime = DivisionTime / NUM_TESTS;
    double AverModTime = ModTime / NUM_TESTS;
    double AverSquareTime = SquareTime / NUM_TESTS;
    double AverPowTime = PowTime / NUM_TESTS;

    cout << "Length " << length << endl;
    cout << "Average Addition Time: " << AverAdditionTime << " nanoseconds" << endl;
    cout << "Average Subtraction Time: " << AverSubtractionTime << " nanoseconds" << endl;
    cout << "Average Multiplication Time: " << AverMultiplicationTime << " nanoseconds" << endl;
    cout << "Average Division Time: " << AverDivisionTime << " nanoseconds" << endl;
    cout << "Average Mod Time: " << AverModTime << " nanoseconds" << endl;
    cout << "Average Square Time: " << AverSquareTime << " nanoseconds" << endl;
    cout << "Average Pow Time: " << AverPowTime << " nanoseconds" << endl;
    cout << "\t" << endl;
}

int main() {

    //test operations

    LongNumb A("09AB3F8C67D2E051FA07D49A2B4B7E384AB30F3E5AEC853D01");
    LongNumb B("05C1A9D8B42F670E29D6A53C8E910B684F2A45BCCD760FADE");
    LongNumb C("0382E9AF61B4D73C8958D46A270FCE5297D1C418AFCFA20232B");
    LongNumb D("4");
    LongNumb E("2B");

    LongNumb result1 = (A + B) * C;
    LongNumb result2 = C * (A + B);
    LongNumb result3 = A * C + B * C;

    if (result1 == result2 && result2 == result3) {
        cout << "Test 1: (A + B) * C = C * (A + B) = A * C + B * C is passed.\n";
    }
    else {
        cout << "Test 1: (A + B) * C = C * (A + B) = A * C + B * C is failed.\n";
    }

    int n = 100;
    LongNumb res1 = A * n;
    LongNumb res2("0");
    for (int i = 0; i < n; i++) {
        res2 = res2 + A;
    }
    if (res1 == res2) {
        cout << "Test 2: n * A = A + A + ... + A (n times) is passed.\n";
    }
    else {
        cout << "Test 2: n * A = A + A + ... + A (n times) is failed.\n";
    }

    LongNumb Add = A + B;
    LongNumb expectedAdd("a075a29f315d6c2dca53eedf4348eeecfa5b39a27c3e637df");
    if (Add == expectedAdd) {
        cout << "Test 3: Add (A + B) works correctly.\n";
    }
    else {
        cout << "Test 3: Addition (A + B) test failed.\n";
    }

    LongNumb Sub = A - B;
    LongNumb expectedSub("94f24eedc8fe9e1176a6a4662626d81c5c06ae28e15244223");
    if (Sub == expectedSub) {
        cout << "Test 4: Sub (A - B) works correctly.\n";
    }
    else {
        cout << "Test 4: Sub (A - B) test failed.\n";
    }

    LongNumb Mult = A * B;
    LongNumb expectedMult("37a8c2e320e6625afddfbf0b265ac0f39de73b4f86aa60f541bed9208b81600c9f4b3a56dfb1a5ccbc6596dd1f07de0de");
    if (Mult == expectedMult) {
        cout << "Test 5: Multiplication (A * B) works correctly.\n";
    }
    else {
        cout << "Test 5: Multiplication (A * B) test failed.\n";
    }

    LongNumb Div = C / B;
    LongNumb expectedDiv("9c");
    if (Div == expectedDiv) {
        cout << "Test 6: Division (B / C) works correctly.\n";
    }
    else {
        cout << "Test 6: Division (B / C) test failed.\n";
    }

    LongNumb Mod = C % A;
    LongNumb expectedMod("7d65d38142f122eb3661f9f98836e10079cf553365b85f226");
    if (Mod == expectedMod) {
        cout << "Test 7: Mod (C % A) works correctly.\n";
    }
    else {
        cout << "Test 7: Mod (C % A) test failed.\n";
    }

    LongNumb Power = E.LongPowerWindow(E, D);
    LongNumb expectedPower("342ab1");
    if (Power == expectedPower) {
        cout << "Test 8: ToPower (E^D) works correctly.\n";
    }
    else {
        cout << "Test 8: ToPower (E^D) test failed.\n";
    }

    //time tests

    vector<int> lengths = { 2, 50 };

    for (const auto& length : lengths) {
        runTests(length);
    }

    cout << "\t" << endl;
    cout << "\t" << endl;

    cout << "Test time:" << endl;

    return 0;
}

