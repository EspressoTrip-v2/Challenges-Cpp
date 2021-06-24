#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;

/*
  Double buffer:
  Write a class that represents a buffer that could be
  written and read at the same time without the two
  operations colliding. A read operation must provide
  access to the old data while a write operation is in
  progress. Newly written data must be available for
  reading upon completion of the write operation.
 */
template< typename T >
class double_buffer
{
    vector<T> m_old;
    vector<T> m_update;
    mutex m_mutex;

public:
    double_buffer(initializer_list<T> &&list) : m_update(list), m_old(list)
    {}

    void read()
    {
        unique_lock<mutex> lck(m_mutex);
        cout << "[ ";
        for_each(m_old.begin(), m_old.end(), [](T item) { cout << item << " "; });
        cout << "]" << endl;
    }

    void write(initializer_list<T> &&list)
    {
        unique_lock<mutex> lck(m_mutex);
        m_update = list;
        m_old = m_update;
    };

};

template< typename T >
void read(double_buffer<T> &db)
{
    this_thread::sleep_for(10ms);
    db.read();
}

template< typename T >
void write(double_buffer<T> &db, initializer_list<T> &&list)
{
    this_thread::sleep_for(30ms);
    db.write(move(list));
}
int main()
{
    double_buffer<int> db{1, 2, 3};

    for (auto i{0}; i < 1000; i++)
    {
        thread temp1(read<int>, ref(db));
        thread temp2(write<int>, ref(db), forward<initializer_list<int>>({i + 1, i + 2, i + 3}));

        temp1.join();
        temp2.join();
    }

    return 0;
}
