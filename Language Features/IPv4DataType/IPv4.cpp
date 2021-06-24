
#include "IPv4.h"
IPv4::IPv4() : data{0}
{}
IPv4::IPv4(unsigned char a, unsigned char b,
           unsigned char c, unsigned char d) : data{a, b, c, d}
{}
std::istream &operator>>(std::istream &is, IPv4 &pv4)
{
    int b1, b2, b3, b4;
    char d1, d2, d3;
    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    if (d1 == '.' && d2 == '.' && d3 == '.')
    {
        pv4 = {static_cast<unsigned char>(b1), static_cast<unsigned char>(b2), static_cast<unsigned char>(b3),
               static_cast<unsigned char>(b4)};
    } else
    {
        is.setstate(ios_base::failbit);
    }

    return is;
}
ostream &operator<<(ostream &os, const IPv4 &pv4)
{
    os << static_cast<int>(pv4.data[0]) << "." << static_cast<int>(pv4.data[1]) <<
       "." << static_cast<int>(pv4.data[2]) << "." << static_cast<int>(pv4.data[3]) << endl;
    return os;
}
unsigned long IPv4::uLong()
{
    auto aL = static_cast<unsigned long>(data[0]) << 24;
    auto bL = static_cast<unsigned long>(data[1]) << 16;
    auto cL = static_cast<unsigned long>(data[2]) << 8;
    auto dL = static_cast<unsigned long>(data[0]);
    return (aL | bL | cL | dL);
}

