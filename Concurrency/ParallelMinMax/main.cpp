#include <iostream>
#include <random>
#include <thread>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

/*
    Parallel min and max element algorithms using threads:
    Implement general-purpose parallel algorithms that find
    the minimum value and, respectively, the maximum value
    in a given range. The parallelism should be implemented
    using threads, although the number of concurrent threads
    is an implementation detail.
*/
constexpr int MAX_SIZE{100'000};

enum class min_max
{
    MAX,
    MIN
};
template< typename iBegin, typename iEnd >
int parallel(iBegin b, iEnd e, min_max t = min_max::MAX)
{
    vector<int> results;
    vector<thread> threads;

    auto size = distance(b, e);
    auto threadCount = thread::hardware_concurrency();
    size /= threadCount;

    auto first = e;
    auto last = first;
    if (size < MAX_SIZE && t == min_max::MAX) return *max_element(b, e);
    if (size < MAX_SIZE && t == min_max::MIN) return *min_element(b, e);
    if (t == min_max::MIN)
    {
        for (auto i{1}; i <= threadCount; i++)
        {
            if (i == 1)first = last;
            if (i == threadCount) last = e;
            else advance(last, size);
            threads.emplace_back([&results, first, last, i]() {
                results.push_back(*min_element(first, last));
            });
        }
    } else
    {
        for (auto i{1}; i <= threadCount; i++)
        {
            if (i == 1)first = last;
            if (i == threadCount) last = e;
            else advance(last, size);
            threads.emplace_back([&results, first, last, i]() {
                results.push_back(*max_element(first, last));
            });
        }
    }

    if (results.size() > 1) parallel(begin(results), end(results), t);

    for (auto &i: threads) i.join();

    return results[0];
}
int main()
{
    random_device rd;

    auto gen = [&rd]() {
        mt19937 g(rd());
        uniform_int_distribution dis(0, 1'000'000);
        return dis(g);
    };

    vector<int> r(1'000'000);
    generate(begin(r), end(r), gen);
    auto min = parallel(begin(r), end(r), min_max::MIN);
    auto max = parallel(begin(r), end(r));

    cout << "Max value: " << max << endl;
    cout << "Min value: " << min << endl;
    return 0;
}
