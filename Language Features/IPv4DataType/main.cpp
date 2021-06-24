#include <iostream>
#include "IPv4.h"
using namespace std;
/*
Write a class that represents an IPv4 address. Implement the
functions required to be able to read and write such
addresses from or to the console. The user should be
able to input values in dotted form, such as 127.0.0.1
or 168.192.0.100. This is also the form in which IPv4
\addresses should be formatted to an output stream.
 */

int main()
{
    IPv4 address{192, 168, 1, 1};
    cout << address;
    cout << "Unsigned long data: " << address.uLong() << endl;

    IPv4 a;
    cout << "Please enter an Ip address with the following syntax (###.###.###):\r\n";
    cin >> a;
    cout << a;
    cout << "Unsigned long data: " << a.uLong() << endl;
    return 0;
}
