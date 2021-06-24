#include <vector>
#include <array>
#include <list>
#include <cassert>
#include <algorithm>
using namespace std;
/*
 Write a set of general-purpose functions that enable checking whether any,
 all, or none of the specified arguments are present in a given container.
 These functions should make it possible to write code as follows:

 std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
 assert(contains_any(v, 0, 3, 30));

 std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
 assert(contains_all(a, 1, 3, 5, 6));

 std::list<int> l{ 1, 2, 3, 4, 5, 6 };
 assert(!contains_none(l, 0, 6));
 */
template<typename T1, typename... T2>
bool contains_any(T1 c, T2... el)
{
    auto compare = [c](const auto value) {
        return any_of(c.begin(), c.end(), [value](auto it) { return it == value; });
    };
    return (..., compare(el));
}


template<typename T1, typename... T2>
bool contains_all(T1 c, T2... el)
{
    int count{}, values{};
    auto compare = [&count, &values, c](const auto value) mutable {
        if (any_of(c.begin(), c.end(), [value](auto it) { return it == value; }))
        {
            count++;
            values++;
            return;
        }
        count++;
    };
    (..., compare(el));
    return count == values;
}
template<typename T1, typename... T2>
bool contains_none(T1 c, T2... el)
{
    int in{};
    auto compare = [&in, c](const auto value) mutable {
        if (any_of(c.begin(), c.end(), [value](auto it) { return it == value; }))
        {
            in++;
            return;
        }
    };
    (..., compare(el));
    return in == 0;
}
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    assert(contains_any(v, 0, 3, 30));

    std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
    assert(contains_all(a, 1, 3, 5, 6));

    std::list<int> l{1, 2, 3, 4, 5, 6};
    assert(!contains_none(l, 0, 6));
    return 0;
}
