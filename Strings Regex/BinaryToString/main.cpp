#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <bitset>
#include <iomanip>
using namespace std;

/*
  Write a function that, given a range of 8-bit integers (such as an array or vector),
  returns a string that contains a hexadecimal representation of the input data. The
  function should be able to produce both uppercase and lowercase content. Here are
  some input and output examples:

  Input: { 0xBA, 0xAD, 0xF0, 0x0D }, output: "BAADF00D" or "baadf00d"
  Input: { 1,2,3,4,5,6 }, output: "010203040506"
*/

template<typename C>
string convert(C &c, bool flag = false)
{
    ostringstream oss;
    if (flag) oss.setf(ios::uppercase);
    for (auto it{begin(c)}; it != end(c); it++)
    {
        oss << hex << setw(2) << setfill('0') << static_cast<int>(*it);
    }
    return oss.str();
}

int main()
{
    vector<int> vecA{0xBA, 0xAD, 0xF0, 0x0D};
    cout << convert(vecA, true) << endl;
    cout << convert(vecA) << endl;

    array<unsigned char, 6> vecB{{1, 2, 3, 4, 5, 6}};
    cout << convert(vecB, true) << endl;

    unsigned char vecC[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    cout << convert(vecC, true) << endl;


    return 0;
}
