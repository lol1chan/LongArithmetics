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


LongNumb generateRandomHexNumber(int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 15);

    LongNumb num;
    for (int i = 0; i < length-1; ++i) {
        int randomDigit = dis(gen);
        char digit = static_cast<char>(randomDigit < 10 ? '0' + randomDigit : 'a' + randomDigit - 10);
        num.appendChar(digit);
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

void runTestsMod(int length) {
    double ModAddTime = 0.0;
    double ModSubTime = 0.0;
    double ModMultTime = 0.0;
    double ModSquareTime = 0.0;
    double ModPowTime = 0.0;

    for (int i = 0; i < NUM_TESTS; i++) {
        LongNumb num1 = num1.GenHex(length);
        LongNumb num2 = num2.GenHex(length);
        LongNumb num3 = num3.GenHex(length);
        ModAddTime += measureTime([&] { LongNumb resultAdd = num1.ModAdd(num2, num3); });
        ModSubTime += measureTime([&] { LongNumb resultSub = num1.ModSub(num2, num3); });
        ModMultTime += measureTime([&] { LongNumb resultMult = num1.ModMult(num2, num3); });
        ModSquareTime += measureTime([&] { LongNumb resultSquare = resultSquare.ModSquare(num1, num3); });
        ModPowTime += measureTime([&] { LongNumb resultPow = num1.ModPow(num1, LongNumb(9), num3); });
    }

    double AverModAddTime = ModAddTime / NUM_TESTS;
    double AverModSubTime = ModSubTime / NUM_TESTS;
    double AverModMultTime = ModMultTime / NUM_TESTS;
    double AverModSquareTime = ModSquareTime / NUM_TESTS;
    double AverModPowTime = ModPowTime / NUM_TESTS;

    cout << "Length " << length << endl;
    cout << "Average ModAdd Time: " << AverModAddTime << " nanoseconds" << endl;
    cout << "Average ModSub Time: " << AverModSubTime << " nanoseconds" << endl;
    cout << "Average ModMult Time: " << AverModMultTime << " nanoseconds" << endl;
    cout << "Average ModSquare Time: " << AverModSquareTime << " nanoseconds" << endl;
    cout << "Average ModPow Time: " << AverModPowTime << " nanoseconds" << endl;
    cout << "\t" << endl;
}



int main() {

    //test operations

    /*LongNumb A("09AB3F8C67D2E051FA07D49A2B4B7E384AB30F3E5AEC853D01");
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
 

    vector<int> lengths = { 2, 50 };

    for (const auto& length : lengths) {
        runTests(length);
    }

    runTests(2);

    cout << "\t" << endl;
    cout << "\t" << endl;

    cout << "Test time:" << endl;

    return 0;*/

//
//LongNumb num1("23C0D0050AE991EF232C32AA88639EF38290F68434288F9C4BF429FE499B9220ABCA87E41472A1E15199B20E6CFDFE13CBB4E1F9358760F04A0FD9EA8A2B5A98E2CF08A5D0BFCC4C75B0F0A7F7BC57EFBDF2ACDC6CA08F63DA3B3A040CFA1AABC5F07A4B843282AD6E6FD1ECB9A00800F46446DCD357ACA4BE192CBF38282A9A");
//LongNumb num2("1604077CEA1866B49C76BA21B38F3F0DE1DA56A26E876A4C5236EA0EB2B4C9BE1CF0CAD51CD5310E778A3A464E252B7215F3BE74DCFAB0C09DEDE3FA462A06C");
//
//LongNumb sum = num1 + num2;
//cout << "num1 + num2 = ";
//sum.Print();
//
//LongNumb difference = num1 - num2;
//cout << "num1 - num2 = ";
//difference.Print();
//
//LongNumb product = num1 * num2;
//cout << "num1 * num2 = ";
//product.Print();
//
//LongNumb quotient = num1 / num2;
//cout << "num1 / num2 = ";
//quotient.Print();
//
//LongNumb remainder = num1 % num2;
//cout << "num1 mod num2 = ";
//remainder.Print();
//
//cout << "\t" << endl;
//
//LongNumb squared = num1.LongPowerWindow(num1, LongNumb(2));
//cout << "num1 ^ 2 = ";
//squared.Print();
//
//LongNumb power = num1.LongPowerWindow(num1, LongNumb(9));
//cout << "num1 ^ 9 = ";
//power.Print();



LongNumb A("0x3e3d9a7f43698b6057bf789e640c2b779a6990ca3b323b89fba7297f5e9c86e635ec6b5f859c1a6144066ed009e884d7db0c82d79c306fc3745240ff8a31240923c8db248f05a4003ec9ef8e579636c2ad9561f24d2328d0ffbe3b3c66bd003d8150fee34de21a037af10fa5cd66042294404c3fcd5eac9eee462611cf479df7");
LongNumb B("0x49e8fbc709682fd27b5374521000a9f7a84c1e31156eaf661db2cef3e738e9a05ed540487a805dd5098d19b5dd1eed610cff655279e2be39fb520c7713eb41258886210005a46e6de9311231b85da6d4f32c028847aa64bc04458861be442512db2056bae4a1d44d10d7013ddb5f8dcab1cc17f535d080974a219d4b0177fbf9");
LongNumb cB("0x49e8fbc709682fd27b5374521000a9f7a84c1e31156eaf661db2cef3e738e9a05ed540487a805dd5098d19b5dd1eed610cff655279e2be39fb520c7713eb41258886210005a46e6de9311231b85da6d4f32c028847aa64bc04458861be442512db2056bae4a1d44d10d7013ddb5f8dcab1cc17f535d080974a219d4b0177fbf9");
LongNumb N("0x1b37815d31c58266b4b80eec480567a24cc323e765f48e2b763918f434e108fa0699ac65a3340ebcb23dac90a4b750a70ed92018522c11e84d9b1190a35cc0a3db844ed8823e212bb50992a45692e8abc27f1d7e84f7217afe640b624dc4291d5c28536eebbf264b0b257ecb6b5dc77635dba985cb41db91b6c4a69a9b0aef83");
LongNumb C;
LongNumb result;
result = result.gcd(A, B);

result.Print();

C = C.lcm(A, B);
C.Print();

A=A.BarrettReduction(A, N, N);
B=B.BarrettReduction(B, N, N);


LongNumb resultAdd = A.ModAdd(B, N);
std::cout << "ModAdd result: ";
resultAdd.Print();


LongNumb resultSub = A.ModSub(B, N);
std::cout << "ModSub result: ";
resultSub.Print();

LongNumb resultMult = A.ModMult(B, N);
std::cout << "ModMult result: ";
resultMult.Print();

LongNumb resultSquare = resultSquare.ModSquare(A, N);
std::cout << "ModSquare result: ";
resultSquare.Print();

LongNumb resultPow = resultPow.ModPow(A, cB, N);
std::cout << "ModPow result: ";
resultPow.Print();


cout << "\t" << endl;
cout << "\t" << endl;


//runTestsMod(2);
//runTestsMod(50);

cout << "\t" << endl;
cout << "\t" << endl;

return 0;

}

