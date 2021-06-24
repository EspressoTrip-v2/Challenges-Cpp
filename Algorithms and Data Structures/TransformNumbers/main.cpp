#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <regex>
#include <iomanip>
using namespace std;
/*
    Transforming a list of phone numbers:
    Write a function that, given a list of phone numbers, transforms them so
    they all start with a specified phone country code, preceded by the + sign.
    Any whitespaces from a phone number should also be removed. The following
    is a list of input and output examples:

    07555 123456    => +447555123456
    07555123456     => +447555123456
    +44 7555 123456 => +447555123456
    44 7555 123456  => +447555123456
    7555 123456     => +447555123456
*/
vector<string> transformNumbers(vector<string> &numbers, string_view &&areaCode)
{
    cout << setw(20) << "Conversion" << endl;
    cout << setfill('-') << setw(33) << " " << endl;
    cout << setfill(' ') << "";
    regex pattern(" ");
    vector<string> toVec(numbers.size());

    transform(numbers.begin(), numbers.end(), toVec.begin(), [&](string &item) {
        string old = item;
        if (regex_search(item, pattern))
        {
            item = regex_replace(item, pattern, "");
        }
        if (item.starts_with("0"))
            item = item.substr(1);
        if (item.starts_with("+"))
            item = item.substr(3);
        if (item.starts_with(areaCode))
            item = item.substr(2);
        cout << left << setw(15) << old << " => " << "+" << areaCode << item << endl;
        return "+" + string(areaCode) + item;
    });

    cout << right << setfill('-') << setw(33) << " " << endl;
    cout << setfill(' ') << "";
    return toVec;
}


int main()
{

    vector<string> numbers{
            "07555 123456",
            "07555123456",
            "+44 7555 123456",
            "44 7555 123456",
            "7555 123456"
    };
    auto edited = transformNumbers(numbers, "44");
    return 0;
}
