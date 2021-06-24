#include <iostream>

using namespace std;

/*
 * Write a program that prints all Armstrong numbers with three digits.
 */

void calcArmstrong(int num)
{
    int total{};
    int original{num};
    // 1000
    int symbol1000 = (num - num % 1000) / 1000;
    num = num - (num - num % 1000) / 1000;
    total += (int) pow(symbol1000, 3);

    // 100
    int symbol100 = (num - num % 100) / 100;
    num = num - (num - num % 100);
    total += (int) pow(symbol100, 3);

    // 10
    int symbol10 = (num - num % 10) / 10;
    num = num - (num - num % 10);
    total += (int) pow(symbol10, 3);

    // 1
    int symbol1 = (num - num % 1) / 1;
    num = num - (num - num % 1);
    total += (int) pow(symbol1, 3);

    if (original == total)
        cout << "Armstrong number --> " << original << " : " << total << endl;

}

int main()
{
    for (auto i{0}; i < 9999; i++)
    {
        calcArmstrong(i);
    }


    return 0;
}
