#include <iostream>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;

/*
 * Write a program that prints all abundant numbers and their abundance,
 * up to a number entered by the user.
 */
void abundant(int number)
{
    set<int> numbers;
    int sum{};
    for (auto i{1}; i <= number; i++)
    {
        if (number % i == 0 && !numbers.count(i) && i != number)
        {
            numbers.emplace(i);
            sum += i;
        }
    }

    if (sum > number)
    {
        cout << "Number: " << number << ", Abundant value: " << sum << endl;
        cout << "[ ";
        for (auto &i: numbers)
        {
            cout << i << " ";
        }
        cout << "]" << endl;
    } else
    {
        cout << "Number not an abundant." << endl;
    }

}

int main()
{
    bool flag{false};

    do
    {
        int input{};
        cout << "Please select a number range ( 0 to quit ):\r\n";
        cin >> input;
        if (input == 0)
            flag = true;
        abundant(input);

    } while (!flag);
    return 0;
}
