#include <iostream>
using namespace std;
/*
 * Write a program that, given two positive integers,
 * will calculate and print the greatest common divisor of the two.
 */
int main()
{
    int num1{125};
    int num2{100};
    int cDivisor{};
    if (num1 > num2)
    {
        for (auto i{1}; i <= num2; i++)
        {
            if (num1 % i == 0 && num2 % i == 0)
                cDivisor = i;
        }
    } else
    {
        for (auto i{1}; i <= num1; i++)
        {
            if (num1 % i == 0 && num2 % i == 0)
                cDivisor = i;
        }
    }

    cout << "Common divisor: " << cDivisor << endl;
    return 0;
}
