#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    Filtering a list of phone numbers:
    Write a function that, given a list of phone numbers, returns only the
    numbers that are from a specified country. The country is indicated by
    its phone country code, such as 44 for Great Britain. Phone numbers may
    start with the country code, a + followed by the country code, or have
    no country code. The ones from this last category must be ignored.
 */
vector<string> sortPhone(vector<string> &numbers, string_view &&areaCode)
{
    vector<string> toVec(100);
    copy_if(numbers.begin(), numbers.end(), toVec.begin(), [&](string &item) {
        return item.starts_with(areaCode) || item.starts_with("+" + string(areaCode));
    });
    return toVec;
}

void print(vector<string> &v)
{
    for (auto &item:v)
    {
        if (!item.empty())
            cout << item << endl;
    }
}

int main()
{
    vector<string> numbers{
            "+40744909080",
            "44 7520 112233",
            "+44 7555 123456",
            "40 7200 123456",
            "7555 123456"};

    auto result = sortPhone(numbers, "44");
    print(result);
    return 0;
}
