
#include <array>
#include <iostream>
using namespace std;
#ifndef IPV4DATATYPE_IPV4_H
#define IPV4DATATYPE_IPV4_H


class IPv4
{
    array<unsigned char, 4> data;
    friend std::istream &operator>>(std::istream &os, IPv4 &pv4);
    friend ostream &operator<<(ostream &os, const IPv4 &pv4);
public:
    IPv4();
    IPv4(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
    unsigned long uLong();
};


#endif //IPV4DATATYPE_IPV4_H
