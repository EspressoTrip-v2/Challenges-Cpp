#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
using namespace std;
/*
    Zip algorithm:
    Write a function that, given two ranges, returns a new range
    with pairs of elements from the two ranges. Should the two
    ranges have different sizes, the result must contain as many
    elements as the smallest of the input ranges. For example, if
    the input ranges were { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } and
    { 1, 1, 3, 5, 8, 13, 21 }, the result should be
    {{1,1}, {2,1}, {3,3}, {4,5}, {5,8}, {6,13}, {7,21}}.
*/
template< typename T, typename S >
vector<pair<T, S>> zipThis(vector<T> &a, vector<S> &b)
{
    vector<pair<T, S>> res;
    if (a.size() <= b.size())
        accumulate(a.begin(), a.end(), 0, [&](int acc, T val) {
            res.push_back({val, b[acc]});
            return ++acc;
        });

    if (a.size() > b.size())
        accumulate(b.begin(), b.end(), 0, [&](int acc, T val) {
            res.push_back({a[acc], val});
            return ++acc;
        });
    return res;
}

template< typename T, typename S >
void print(vector<pair<T, S>> &v)
{
    cout << "{ ";
    for (auto &i:v)
    {
        cout << "{ " << i.first << ", " << i.second << " } ";
    }
    cout << "}" << endl;
}

int main()
{
    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v2{1, 1, 3, 5, 8, 13, 21};

    vector<int> v3{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v4{1, 1, 3, 5, 8, 13, 21, 111, 234, 8};

    auto result1 = zipThis(v1, v2);
    auto result2 = zipThis(v3, v4);
    print(result1);
    print(result2);


    return 0;
}
