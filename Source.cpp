#include "LongNumb.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {


    LongNumb A("09AB3F8C67D2E051FA07D49A2B4B7E384AB30F3E5AEC853D01");
    LongNumb B("05C1A9D8B42F670E29D6A53C8E910B684F2A45BCCD760FADE");
    LongNumb C("0382E9AF61B4D73C8958D46A270FCE5297D1C418AFCFA20232B");

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
    LongNumb expected1("a075a29f315d6c2dca53eedf4348eeecfa5b39a27c3e637df");
    if (Add == expected1) {
        cout << "Test 3: Add (A + B) works correctly.\n";
    }
    else {
        cout << "Test 3: Addition (A + B) test failed.\n";
    }

    LongNumb Sub = A - B;
    LongNumb expected2("94f24eedc8fe9e1176a6a4662626d81c5c06ae28e15244223");
    if (Sub == expected2) {
        cout << "Test 4: Sub (A - B) works correctly.\n";
    }
    else {
        cout << "Test 4: Sub (A - B) test failed.\n";
    }

    LongNumb Mult = A * B;
    LongNumb expected3("37a8c2e320e6625afddfbf0b265ac0f39de73b4f86aa60f541bed9208b81600c9f4b3a56dfb1a5ccbc6596dd1f07de0de");
    if (Mult == expected3) {
        cout << "Test 5: Multiplication (A * B) works correctly.\n";
    }
    else {
        cout << "Test 5: Multiplication (A * B) test failed.\n";
    }

    LongNumb Div = C / B;
    LongNumb expected4("9c");
    if (Div == expected4) {
        cout << "Test 6: Division (B / C) works correctly.\n";
    }
    else {
        cout << "Test 6: Division (B / C) test failed.\n";
    }

    LongNumb result = C % A;
    LongNumb expected5("7d65d38142f122eb3661f9f98836e10079cf553365b85f226");
    if (result == expected5) {
        cout << "Test 7: Mod (C % A) works correctly.\n";
    }
    else {
        cout << "Test 7: Mod (C % A) test failed.\n";
    }



    array<int, 2> lengths = { 2, 50 };

    for (const auto length : lengths) {
        double AdditionTime = 0.0;
        double SubtractionTime = 0.0;
        double MultiplicationTime = 0.0;
        double DivisionTime = 0.0;
        double ModTime = 0.0;
        double SquareTime = 0.0;
        double PowTime = 0.0;

        for (int i = 0; i < 20; i++) {
            LongNumb num1;
            LongNumb num2;
            num1.generateRandomHex(length);
            num2.generateRandomHex(length);

            auto AdditionStartTime = high_resolution_clock::now();
            LongNumb resultAdd = num1 + num2;
            auto AdditionEndTime = high_resolution_clock::now();
            AdditionTime += duration_cast<nanoseconds>(AdditionEndTime - AdditionStartTime).count();

            auto SubtractionStartTime = high_resolution_clock::now();
            LongNumb resultSub = num1 - num2;
            auto SubtractionEndTime = high_resolution_clock::now();
            SubtractionTime += duration_cast<nanoseconds>(SubtractionEndTime - SubtractionStartTime).count();

            auto MultiplicationStartTime = high_resolution_clock::now();
            LongNumb resultMul = num1 * num2;
            auto MultiplicationEndTime = high_resolution_clock::now();
            MultiplicationTime += duration_cast<nanoseconds>(MultiplicationEndTime - MultiplicationStartTime).count();

            auto DivisionStartTime = high_resolution_clock::now();
            LongNumb resultDiv = num1 / num2;
            auto DivisionEndTime = high_resolution_clock::now();
            DivisionTime += duration_cast<nanoseconds>(DivisionEndTime - DivisionStartTime).count();

            auto ModStartTime = high_resolution_clock::now();
            LongNumb resultMod = num1 % num2;
            auto ModEndTime = high_resolution_clock::now();
            ModTime += duration_cast<nanoseconds>(ModEndTime - ModStartTime).count();

            auto SquareStartTime = high_resolution_clock::now();
            LongNumb resultSquare = num1.LongPowerWindow(num1, LongNumb(2));
            auto SquareEndTime = high_resolution_clock::now();
            SquareTime += duration_cast<nanoseconds>(SquareEndTime - SquareStartTime).count();

            auto PowStartTime = high_resolution_clock::now();
            LongNumb resultPow = num1.LongPowerWindow(num1, LongNumb(9));
            auto PowEndTime = high_resolution_clock::now();
            PowTime += duration_cast<nanoseconds>(PowEndTime - PowStartTime).count();
        }

        double AverAdditionTime = AdditionTime / 20.0;
        double AverSubtractionTime = SubtractionTime / 20.0;
        double AverMultiplicationTime = MultiplicationTime / 20.0;
        double AverDivisionTime = DivisionTime / 20.0;
        double AverModTime = ModTime / 20.0;
        double AverSquareTime = SquareTime / 20.0;
        double AverPowTime = PowTime / 20.0;

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

    cout << "\t" << endl;
    cout << "\t" << endl;

    cout << "Test time:" << endl;
    

    return 0;
}
