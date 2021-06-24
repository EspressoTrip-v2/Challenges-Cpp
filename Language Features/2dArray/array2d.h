//
// Created by Juan on 5/16/2021.
//


#ifndef INC_2DARRAY_ARRAY2D_H
#define INC_2DARRAY_ARRAY2D_H

#include <ostream>
#include <string>
#include <stdexcept>
#include <cassert>
using namespace std;

template<typename T>
class Iterator
{
    T *_point;
public:
    explicit Iterator(T *point) : _point(point)
    {}

    // Operators
    bool operator<(const Iterator<T> &other) const
    {
        return _point < other._point;
    }

    bool operator==(const Iterator<T> &other) const
    {
        return _point == other._point;
    }

    bool operator!=(const Iterator<T> &other) const
    {
        return _point != other._point;
    }

    Iterator<T> operator++()
    {
        _point++;
        return *this;
    }

    Iterator<T> operator++(int)
    {
        _point++;
        return *this;
    }


    T &operator*()
    {
        return *_point;
    }

    T *operator->()
    {
        return _point;
    }

    // Pointer arithmetic
    Iterator<T> operator-(int value)
    {
        _point -= 1;
        return *this;
    }
    Iterator<T> operator+(int value)
    {
        _point += 1;
        return *this;
    }

};


template<typename T = unsigned int, size_t _column_dim = 2, size_t _row_dim = 2>
class array2d
{
private:
    friend std::ostream &operator<<(std::ostream &os, const array2d &d)
    {
        os << "[ ";
        for (auto i{0}; i < (d._size); i++)
        {
            os << d._array[i] << " ";
        }

        os << "]" << endl;
        return os;
    }
    size_t _col;
    size_t _row;
    size_t _size;
    T _array[_column_dim + _row_dim];

public:
    array2d(std::initializer_list<T> row_1, std::initializer_list<T> row_2) :
            _col{_column_dim}, _row{_row_dim}, _size{_column_dim + _row_dim}, _array{}
    {
        assert(("Column size can not be zero", _col != 0));
        assert(("Row size can not be zero", _row != 0));

        auto row_1Begin = row_1.begin();
        auto row_2Begin = row_2.begin();

        for (auto i{0}; i < _size; i++)
        {
            if (row_1Begin != row_1.end())
            {
                _array[i] = *row_1Begin;
                row_1Begin++;
            } else
            {
                if (row_2Begin != row_2.end())
                {
                    _array[i] = *row_2Begin;
                    row_2Begin++;
                } else
                {
                    break;
                }
            }
        }
    }

    pair<size_t, size_t> size()
    {
        return {_row, _col};
    }

    T at(int row, int col)
    {
        int index{};
        if (row == 0) index = col;
        if (row == 1) index = _row + col - 1;
        if (index > _size || row >= 2 || col > _col)
        {
            cerr << "Request out of range" << endl;
            throw out_of_range("Request out of range");
        }
        return _array[index];
    }

    T *data()
    {
        return _array;
    }

    Iterator<T> begin()
    {
        return Iterator<T>{_array};
    }

    Iterator<T> end()
    {
        return Iterator<T>{(_array + _size)};
    }

};

#endif //INC_2DARRAY_ARRAY2D_H
