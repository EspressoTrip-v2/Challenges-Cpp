#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

/*
* Write a program that prints the list of all pairs of amicable numbers smaller than 1,000,000.
*/


int abundant(int number)
{
    int sum{};
    for (auto i{1}; i <= number; i++)
    {
        if (number % i == 0 && i != number)
        {
            sum += i;
        }
    }
    return sum;
}

void printAmicable(unordered_map<int, int> &mapA, unordered_map<int, int> &mapB)
{

    for (auto &p: mapA)
    {
        if (mapB.count(p.second) > 0 && mapB.at(p.second) == p.first && p.first != p.second)
        {
            cout << p.first << " : " << p.second << endl;
        }
    }

}

void amicableNumber()
{
    unordered_map<int, int> nDivisorsSumsA, nDivisorsSumsB;
    for (auto num{1}; num < 100000; num++)
    {
        int temp = abundant(num);
        if (temp > 200)
        {
            nDivisorsSumsA[num] = temp;
            nDivisorsSumsB[num] = temp;
        }
    }

    printAmicable(nDivisorsSumsA, nDivisorsSumsB);
}

int main()
{
    amicableNumber();
    return 0;
}
