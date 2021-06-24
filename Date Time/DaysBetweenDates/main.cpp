#include <iostream>
#include <cassert>

using namespace std;

/*
  Number of days between two dates:
  Write a function that, given two dates, returns the
  number of days between the two dates. The function
  should work regardless of the order of the input dates.
*/
class Date
{
    int m_day;
    int m_month;
    int m_year;

public:
    Date(int mDay, int mMonth, int mYear) : m_day(mDay), m_month(mMonth), m_year(mYear)
    {
        assert(("Date needs to be between 1 -> 31", m_day <= 31 && m_day >= 1));
        assert(("Month needs to be between 1 -> 12", m_month <= 12 && m_month >= 1));
    }
    void operator-(const Date &other) const
    {
        cout << "Days difference: " << abs(m_day - other.m_day) << endl;
        cout << "Month difference: " << abs(m_month - other.m_month) << endl;
        cout << "Year difference: " << abs(m_year - other.m_year) << endl;
    }

    [[nodiscard]]
    int getMDay() const
    {
        return m_day;
    }
    [[nodiscard]]
    int getMMonth() const
    {
        return m_month;
    }
    [[nodiscard]]
    int getMYear() const
    {
        return m_year;
    }

    friend ostream &operator<<(ostream &os, const Date &time)
    {
        os << time.m_day << " / " << time.m_month << " / " << time.m_year;
        return os;
    }

};


int main()
{
    Date d1{1, 2, 2021};
    Date d2{2, 12, 2020};
    Date d3{31, 10, 2040};
    d1 - d2;
    cout << endl;
    d1 - d3;
    cout << endl;
    d3 - d2;

    return 0;
}
