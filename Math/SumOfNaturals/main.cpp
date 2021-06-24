#include <iostream>
#include <cstdlib>


using namespace std;
/*
 * Write a program that calculates and prints the sum of all the natural
 * numbers divisible by either 3 or 5, up to a given limit entered by the user.
 */
long long calculate(int sNumber, int divisor)
{
    long long sum{};
    for (auto i{1}; i <= sNumber; i++)
    {
        if (i % divisor == 0)
            sum += i;
    }
    return sum;
}
int main()
{
    while (true)
    {
        int input;
        cout << "Please enter a limit for calculations or 0 to quit:\r\n ";
        cin >> input;
        if (cin.fail())
        {
            cout << "Not a number" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (input == 0) break;
        long long sum3 = calculate(input, 3);
        long long sum5 = calculate(input, 5);
        cout << "Sum of natural numbers divisible by 3" << " = " << sum3 << endl;
        cout << "Sum of natural numbers divisible by 5" << " = " << sum5 << endl;
    }
    return 0;
}
