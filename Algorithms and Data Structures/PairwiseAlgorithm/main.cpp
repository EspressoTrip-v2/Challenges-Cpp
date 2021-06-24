#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
/*
    Pairwise algorithm:
    Write a general-purpose function that, given a range, returns a
    new range with pairs of consecutive elements from the input range.
    Should the input range have an odd number of elements, the last
    one must be ignored. For example, if the input range was
    {1, 1, 3, 5, 8, 13, 21}, the result must be { {1, 1}, {3, 5}, {8, 13}}.
 */
template< typename T >
vector<pair<T, T>> pairWise(vector<T> &v)
{
    vector<pair<T, T>> temp;
    if (v.size() % 2 != 0)v.pop_back();
    for (auto i{0}; i < v.size() - 1; i++)
    {
        if (i == 0)
        {
            temp.push_back({v[0], v[0 + 1]});
        } else if (i % 2 == 0)
        {
            temp.push_back({v[i], v[i + 1]});
        }
    }
    return temp;
}
template< typename T >
void print(vector<pair<T, T>> &p)
{
    cout << "Pairs: { ";
    for (auto &i : p)
    {
        cout << "{ " << i.first << ", " << i.second << " } ";
    }
    cout << "}" << endl;
    cout << endl;
}

int main()
{
    vector<int> v{1, 1, 3, 5, 8, 13, 21, 150};
    vector<int> v2{1, 1, 3, 5, 8, 13, 21, 100, 19, 30, 111};
    auto res1 = pairWise(v);
    auto res2 = pairWise(v2);

    print(res1);
    print(res2);

    return 0;
}
