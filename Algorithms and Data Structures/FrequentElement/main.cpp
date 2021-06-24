#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <set>
#include <numeric>
#include <unordered_map>
using namespace std;

/*
   The most frequent element in a range:
   Write a function that, given a range, returns the
   most frequent element and the number of times it
   appears in the range. If more than one element
   appears the same maximum number of times then the
   function should return all the elements. For
   instance, for the range {1,1,3,5,8,13,3,5,8,8,5},
   it should return {5, 3} and {8, 3}.
 */
template< typename T >
vector<pair<T, int>> getElements(initializer_list<T> &&list)
{
    int high{0};
    set<T> s{list};
    unordered_map<T, int> count;
    vector<pair<T, int>> results;
    for (auto &i:s)
    {
        auto result = accumulate(list.begin(), list.end(), 0, [i](int a, T b) {
            return b == i ? a + 1 : a + 0;
        });
        if (result > high)
            high = result;
        count[i] = result;
    }
    for (auto &i: count)
    {
        if (i.second == high)
            results.push_back(pair<T, int>(i.first, i.second));
    }
    return move(results);
}
template< typename T >
void print(vector<T> &vec)
{
    for_each(vec.begin(), vec.end(), [](auto item) {
        cout << "{ " << item.first << " , " << item.second << " }" << endl;
    });
    cout << endl;
}
int main()
{
    auto r1 = getElements({11, 4, 3, 3, 5, 11, 11, 6, 3, 8, 9});
    auto r2 = getElements({1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5});
    print(r1);
    print(r2);
    return 0;
}
