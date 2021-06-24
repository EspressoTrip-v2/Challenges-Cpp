
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
const array<unsigned char, 4> &IPv4::getData() const
{
    return data;
}
void IPv4::getRange(const IPv4 &other) const
{
    auto addressOther = other.getData();
    int startRange = static_cast<int>(data[3]);
    int endRange = static_cast<int>(addressOther[3]);

    if (startRange > endRange)
    {
        int temp = endRange;
        endRange = startRange;
        startRange = temp;
    }

    for (auto i{0}; i < 3; i++)
    {
        if (data[i] != addressOther[i])
        {
            cout << "The IP addresses networks do not match: " <<
                 "Host address: " << static_cast<int>(data[0]) << "." << static_cast<int>(data[1]) << "." <<
                 static_cast<int>(data[2]) << ".---\\24" << endl;

            cout << "Supplied IP network: " << static_cast<int>(addressOther[0]) << "." << static_cast<int>
            (addressOther[1]) << "." << static_cast<int>(addressOther[2]) << ".---\\24" << endl;
            return;
        }
    }

    if (data[3] == addressOther[3])
    {
        cout << "The address supplied is equal to the starting address of host. Can not supply a range" << endl;
        return;
    }

    for (auto i{startRange}; i <= endRange; i++)
        cout << "#" << i << ": " << static_cast<int>(data[0]) << "." << static_cast<int>(data[1]) << "." <<
             static_cast<int>(data[2]) << "." << i << "\\24" << endl;

}


