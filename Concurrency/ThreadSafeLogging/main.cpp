#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
using namespace std;

/*
    Thread-safe logging to the console:
    Write a class that enables components running in different
    threads to safely print log messages to the console by
    synchronizing access to the standard output stream to
    guarantee the integrity of the output. This logging
    component should have a method called log() with a string
    argument representing the message to be printed to the console.
*/


class logger
{
    static mutex m_mutex;
    template< typename T >
    static void print(T &&s)
    {
        lock_guard<mutex> lck(m_mutex);
        cout << "Thread #" << s << endl;
    };
public:
    template< typename T >
    static void log(T &&s)
    {
        print(s);

    };
};

// instantiate static mutex
mutex logger::m_mutex;

int main()
{
    vector<thread> threads;
    auto size = thread::hardware_concurrency();
    for (auto i{0}; i < size; i++)
    {
        threads.emplace_back(thread([i]() { logger::log(i); }));
    }

    for (auto &i:threads)
        i.join();

    return 0;
}
