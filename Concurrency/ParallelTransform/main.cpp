#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
/*
    Parallel transform algorithm
    Write a general-purpose algorithm that applies a given unary
    function to transform the elements of a range in parallel.
    The unary operation used to transform the range must not
    invalidate range iterators or modify the elements of the
    range. The level of parallelism, that is, the number of
    execution threads and the way it is achieved, is an
    implementation detail.
*/
template< typename T >
vector<int> parallel(vector<T> &data)
{
    // Iterators
    auto first = begin(data);
    auto last = first;
    // Thread container
    vector<thread> threadContainer;
    // descriptors
    auto size = distance(begin(data), end(data));
    auto threads = thread::hardware_concurrency();
    cout << "Threads: " << threads << ", Size data: " << size << ", Partition per thread: " << size / threads << endl;
    size /= threads;
    // Split work into threads
    for (auto i{1}; i <= threads; i++)
    {
        if (i != 1) first = last;
        if (i == threads) last = end(data);
        else advance(last, size);
        threadContainer.emplace_back([first, last, i]() {
            transform(first, last, first, [&](auto e) {
                return i;
            });
        });
    }
//     Join threads
    for (auto &i: threadContainer)
    {
        i.join();
    }
    return data;
}

int main()
{
    std::vector<int> data(100000);
    auto result = parallel(data);
    for (auto &i : result)
        cout << i << " ";
    return 0;
}
