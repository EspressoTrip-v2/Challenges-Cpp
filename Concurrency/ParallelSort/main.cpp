#include <iostream>
#include <vector>
#include <random>
#include <future>

using namespace std;
/*
    Parallel sort algorithm:
    Write a parallel version of the sort algorithm as defined
    for problem 53. Sort Algorithm, in Chapter 6, Algorithms
    and Data Structures, which, given a pair of random access
    iterators to define its lower and upper bounds, sorts the
    elements of the range using the quicksort algorithm. The
    function should use the comparison operators for comparing
    the elements of the range. The level of parallelism and the
    way to achieve it is an implementation detail.
*/
template< typename T >
void print(const vector<T> &v)
{
    cout << "{ ";
    for (auto &i: v)
        cout << i << " ";
    cout << "}" << endl;
}
template< typename iBegin, typename iEnd >
iBegin partition(iBegin begin, iEnd end)
{
    auto pivot = begin;
    auto i = begin + 1;
    auto j = end - 1;
    while (i <= j)
    {
        while (i <= j && *i <= *pivot) i++;
        while (i <= j && *j > *pivot) j--;
        if (i < j) swap(*i, *j);
    }
    swap(*pivot, *j);
    return j;
}

template< typename iBegin, typename iEnd >
void quickSort(iBegin start, iEnd last)
{
    if (start < last)
    {
        auto index = partition(start, last);

        // Async is a bit glitch
//        auto a = async(launch::async, [start, index]() { quickSort(start, index); });
//        a.wait();
//        auto b = async(launch::async, [index, last]() { quickSort(index + 1, last); });
//        b.wait();

        thread a([start, index]() { quickSort(start, index); });
        thread b([index, last]() { quickSort(index + 1, last); });

        a.join();
        b.join();
    }
}

int main()
{
    random_device rd;
    uniform_int_distribution dis(0, 100);

    vector<int> data(1000);
    auto numGen = [&rd, &dis]() {
        mt19937 generator(rd());
        return dis(generator);
    };
    generate(begin(data), end(data), numGen);

    quickSort(begin(data), end(data));
    print(data);
    return 0;
}
