#include <iostream>
#include <random>
#include <algorithm>
#include <future>
#include <vector>
#include <execution>
#include <iterator>
using namespace std;
/*
    Parallel min and max element algorithms using asynchronous functions:
    Implement general-purpose parallel algorithms that find the minimum
    value and, respectively, the maximum value in a given range. The
    parallelism should be implemented using asynchronous functions,
    although the number of concurrent functions is an implementation
    detail.
*/
enum class type_def
{
    MAX, MIN
};

template< typename iBegin, typename iEnd >
int getValue(iBegin begin, iEnd end, type_def t = type_def::MAX)
{
    vector<future<typename iterator_traits<iBegin>::value_type>> futures;

    auto size = distance(begin, end);
    auto threadCount = thread::hardware_concurrency();
    size /= threadCount;

    auto first = begin;
    auto last = begin;

    for (auto i{1}; i <= threadCount; i++)
    {
        first = last;
        if (i == threadCount)last = end;
        else advance(last, size);
        if (t == type_def::MIN) futures.emplace_back(async(launch::async, [first, last] { return *min_element(first, last); }));
        else futures.emplace_back(async(launch::async, [first, last] { return *max_element(first, last); }));
    }

    int val{-1};
    if (t == type_def::MIN)
        for_each(std::begin(futures), std::end(futures), [&val](auto &el) mutable {
            int res = el.get();
            if (val == -1) val = res;
            if (val > res) val = res;
        });
    else
        for_each(std::begin(futures), std::end(futures), [&val](auto &el) mutable {
            int res = el.get();
            if (val == -1) val = res;
            if (val < res) val = res;
        });
    return val;
};

int main()
{
    random_device rd;
    uniform_int_distribution dis(0, 1'000'000);

    auto genValues = [&rd, &dis]() {
        mt19937 gen(rd());
        return dis(gen);
    };

    vector<int> data(100'000);
    generate(begin(data), end(data), genValues);

    int res1 = getValue(begin(data), end(data));
    cout << "Max value: " << res1 << endl;

    int res2 = getValue(begin(data), end(data), type_def::MIN);
    cout << "Min value: " << res2 << endl;
    return 0;
}
