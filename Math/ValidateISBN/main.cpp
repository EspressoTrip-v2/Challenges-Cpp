#include <iostream>
#include <string>
#include "boost/lexical_cast.hpp"
using namespace std;
using namespace boost;


/*Write a program that validates that 10-digit values
entered by the user, as a string, represent valid ISBN-10 numbers.*/

// Sample = ISBN0-19-853453-1

string verify(string &ibn)
{

    string tempIBN;
    for (auto i{0}; i < ibn.size(); i++)
    {
        if (!isalpha(ibn[i]) && ibn[i] != '-')
        {
            tempIBN += ibn[i];
        }
    }
    int checkDigit = lexical_cast<int>(tempIBN[tempIBN.size() - 1]);
    tempIBN.pop_back();

    // Verification logic
    int modValue{};
    for (auto i{0}; i < tempIBN.size(); i++)
    {
        modValue += lexical_cast<int>(tempIBN[i]) * (i + 1);
    }
    return (modValue % 11 == checkDigit ? ibn + " : [ Verified ]" : ibn + " : [ Un-verified ]");
}

int main()
{
    string tInsert;
    while (true)
    {
        cout << "Enter ISBN-10 number:\r\n";
        getline(cin, tInsert);
        if (tInsert == "q" || tInsert == "Q")
            break;
        cout << "Processing number: " + tInsert << endl;
        cout << verify(tInsert) << endl;
    }

    return 0;
}
