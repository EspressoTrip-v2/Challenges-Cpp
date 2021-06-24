#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <algorithm>
using namespace std;

/*
   Circular buffer
   Create a data structure that represents a circular buffer of a fixed size.
   A circular buffer overwrites existing elements when the buffer is being filled
   beyond its fixed size. The class you must write should:

   Prohibit default construction
   Support the creation of objects with a specified size
   Allow checking of the buffer capacity and status (empty(), full(), size(), capacity())
   Add a new element, an operation that could potentially overwrite the oldest element in the buffer
   Remove the oldest element from the buffer
   Support iteration through its elements
 */

// Forward declaration
template< typename T >
class circular_iterator;

template< typename T, size_t S >
class CBuffer
{
    friend class circular_iterator<T>;

    friend ostream &operator<<(ostream &os, const CBuffer<T, S> &buffer)
    {
        os << "[ ";
        for (auto &i:buffer.m_buf)
        {
            os << i << " ";
        }
        os << "]" << endl;
        return os;
    };

    vector<T> m_buf;
    size_t m_size;
    size_t m_fill;
    int m_pos;

    using iterator = circular_iterator<T>;

public:
    CBuffer() = delete;
    explicit CBuffer(initializer_list<T> &&list) : m_buf{list}, m_size{list.size()}, m_fill{list.size()}, m_pos{0}
    {
        assert(("Suggested size does not match size of data received", S == m_size));
    }
    [[nodiscard]]
    size_t capacity() const
    {
        return m_buf.capacity();
    }
    [[nodiscard]]
    bool empty() const
    {
        return m_buf.empty();
    }
    [[nodiscard]]
    bool full() const
    {
        return m_buf.size() == m_size;
    }
    [[nodiscard]]
    size_t size() const
    {
        return m_buf.size();
    }
    iterator begin()
    {
        return circular_iterator<T>(m_buf.data(), m_pos);
    }
    iterator end()
    {
        return circular_iterator<T>(m_buf.data() + m_size, m_pos);
    }
    void push(T &&elm)
    {
        if (m_buf.empty() || m_buf.size() < m_size)
        {
            m_buf.push_back(elm);
            return;
        }
        if (m_pos == m_size)
        {
            m_pos = 0;
            m_buf[m_pos] = elm;
            m_pos++;
            return;
        }
        m_buf[m_pos] = elm;
        m_pos++;
    }
    void pop()
    {
        m_buf.pop_back();
    }

    void sortBuf(string &&direction = "forward")
    {
        if (direction == "forward")
        {
            sort(m_buf.begin(), m_buf.end());
            return;
        } else if (direction == "reverse")
        {
            sort(m_buf.begin(), m_buf.end(), [](T a, T b) { return a > b; });
        }
    }

};

template< typename T >
class circular_iterator
{
    T *m_pointer;
    size_t m_pos;
public:
    // Iterator Traits
    using iterator_category = forward_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T *;
    using reference = T &;

    // Constructors and methods
    circular_iterator(T *mPointer, size_t mPos) : m_pointer(mPointer), m_pos(mPos)
    {}
    circular_iterator(const circular_iterator<T> &iter) : m_pointer(iter.m_pointer), m_pos(iter.m_pos)
    {}
    T &operator*()
    {
        return *m_pointer;
    }

    T *operator->()
    {
        return m_pointer;
    }

    circular_iterator<T> &operator=(const circular_iterator<T> &iter)
    {
        if (iter == *this) return *this;
        m_pointer = iter.m_pointer;
        m_pos = iter.m_pos;
        return *this;
    }

    bool operator==(const circular_iterator<T> &iter) const
    {
        return m_pointer == iter.m_pointer;
    }

    circular_iterator<T> &operator++()
    {
        m_pointer++;
        return *this;
    }
    circular_iterator<T> operator++(int)
    {
        circular_iterator<T> old = *this;
        operator++();
        return old;
    }
    bool operator!=(const circular_iterator<T> &iter) const
    {
        return m_pointer != iter.m_pointer;
    }
};


int main()
{
    cout << boolalpha << endl;
    CBuffer<string, 4> buf1{"1", "2", "3", "4"};
    cout << buf1;
    buf1.pop();
    buf1.pop();
    buf1.pop();
    buf1.pop();
    cout << "Is empty: " << buf1.empty() << ", Size: " << buf1.size() << endl;
    cout << "Is full: " << buf1.full() << endl;
    buf1.push("20");
    buf1.push("10");
    buf1.push("99");
    buf1.push("Juan");
    cout << buf1;
    buf1.push("1");
    buf1.push("2");
    buf1.push("3");
    buf1.push("4");
    cout << buf1;
    cout << "Is empty: " << buf1.empty() << endl;
    cout << "Is full: " << buf1.full() << ", Size: " << buf1.size() << endl;


    return 0;
}
