#include <iostream>
#include "IPv4.h"
using namespace std;
/*
 Write a program that allows the user to input two IPv4 addresses representing a
 range and list all the addresses in that range. Extend the structure defined
 for the previous problem to implement the requested functionality.
 */

int main()
{
    IPv4 addressA{192, 168, 1, 0};
    IPv4 addressB{192, 168, 1, 25};

    addressA.getRange(addressB);

    return 0;
}
