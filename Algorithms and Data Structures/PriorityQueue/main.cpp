#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  Priority queue:
  Write a data structure that represents a priority queue that
  provides constant time lookup for the largest element, but
  has logarithmic time complexity for adding and removing
  elements. A queue inserts new elements at the end and removes
  elements from the top. By default, the queue should use
  operator< to compare elements, but it should be possible
  for the user to provide a comparison function object that
  returns true if the first argument is less than the second.
  The implementation must provide at least the following operations:

  push() to add a new element
  pop() to remove the top element
  top() to provide access to the top element
  size() to indicate the number of elements in the queue
  empty() to indicate whether the queue is empty
*/
class priority_queue
{
    vector<int> m_vec;

    void sortVec()
    {
        sort(m_vec.begin(), m_vec.end(), [](int a, int b) { return a > b; });
    }

public:
    priority_queue(initializer_list<int> mVec) : m_vec(mVec)
    {
        sortVec();
    }
    friend ostream &operator<<(ostream &os, const priority_queue &queue)
    {
        os << "[ ";
        for_each(queue.m_vec.cbegin(), queue.m_vec.cend(), [&](const int &i) { os << i << " "; });
        os << "]" << endl;
        return os;
    }
    void push(int num)
    {
        m_vec.push_back(num);
        sortVec();
    }
    int pop()
    {
        int item = m_vec[0];
        m_vec.erase(m_vec.begin());
        return item;
    }
    int top()
    {
        return m_vec.front();
    }
    size_t size()
    {
        return m_vec.size();
    }
    bool empty()
    {
        return m_vec.empty();
    }
};

int main()
{
    cout << boolalpha << endl;
    priority_queue pq{1, 5, 4, 7, 2, 3, 0};
    pq.pop();
    cout << pq;
    pq.push(-1);
    cout << pq;
    cout << "Size: " << pq.size() << endl;
    cout << "Empty: " << pq.empty() << endl;

    return 0;
}
