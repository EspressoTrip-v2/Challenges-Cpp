#include <iostream>
#include <cmath>
#include "conversion_types.h"

using namespace std;
using namespace conversions;

/*
  Write a small library that enables expressing temperatures in
  the three most used scales, Celsius, Fahrenheit, and Kelvin,
  and converting between them. The library must enable you to
  write temperature literals in all these scales, such as
  36.5_deg for Celsius, 97.7_f for Fahrenheit, and 309.65_K for
  Kelvin; perform operations with these values; and convert between them.
*/

bool equal_temps(const double a, const double b, double error_factor = 0.001)
{
    return fabs(a - b) < error_factor;
}

// Custom literals
constexpr quantity<scale::CELSIUS> operator "" _C(long double value)
{
    return quantity<scale::CELSIUS>(static_cast<double>(value));
}
constexpr quantity<scale::FAHRENHEIT> operator "" _F(long double value)
{
    return quantity<scale::FAHRENHEIT>(static_cast<double>(value));
}
constexpr quantity<scale::KELVIN> operator "" _K(long double value)
{
    return quantity<scale::KELVIN>(static_cast<double>(value));
}

// Operators
template<scale T>
bool operator<(const quantity<T> &lhs, const quantity<T> &rhs)
{
    return static_cast<double>(lhs) < static_cast<double>(rhs);
}
template<scale T>
bool operator>(const quantity<T> &lhs, const quantity<T> &rhs)
{
    return static_cast<double>(lhs) > static_cast<double>(rhs);
}
template<scale T>
bool operator==(const quantity<T> &lhs, const quantity<T> &rhs)
{
    return equal_temps(static_cast<double>(lhs), static_cast<double>(rhs));
}

template<scale T>
bool operator!=(const quantity<T> &lhs, const quantity<T> &rhs)
{
    return !equal_temps(static_cast<double>(lhs), static_cast<double>(rhs));
}

template<scale T>
quantity<T> operator+(const quantity<T> &lhs, const quantity<T> &rhs)
{
    return quantity<T>{static_cast<double>(lhs) + static_cast<double>(rhs)};
}
template<scale T>
quantity<T> operator-(const quantity<T> &lhs, const quantity<T> &rhs)
{
    return quantity<T>{static_cast<double>(lhs) - static_cast<double>(rhs)};
}

int main()
{

    auto t1 = 35.0_C;
    auto t2 = 35.0_F;
    auto t3 = 35.75_K;
    auto t4 = 35.0_C;
    auto t5 = 100.6_K;


    cout << "*** Conversion ***\n";
    cout << "Celsius to Fahrenheit: " << t1 << " : " << conversion_type<scale::CELSIUS,
            scale::FAHRENHEIT>::convert(t1) << endl;
    cout << "Celsius to Kelvin: " << t1 << " : " << conversion_type<scale::CELSIUS,
            scale::KELVIN>::convert(t1) << endl;
    cout << "---\n";
    cout << "Fahrenheit to Celsius: " << t2 << " : " << conversion_type<scale::FAHRENHEIT,
            scale::CELSIUS>::convert(t2) << endl;
    cout << "Fahrenheit to Kelvin: " << t2 << " : " << conversion_type<scale::FAHRENHEIT,
            scale::KELVIN>::convert(t2) << endl;

    cout << "---\n";
    cout << "Kelvin to Fahrenheit: " << t3 << " : " << conversion_type<scale::KELVIN,
            scale::FAHRENHEIT>::convert(t3) << endl;
    cout << "Kelvin to Celsius: " << t3 << " : " << conversion_type<scale::KELVIN,
            scale::CELSIUS>::convert(t3) << endl;


    cout << "\n";
    cout << "*** Arithmetic ***\n";
    cout << "Adding: " << t1 << " + " << t4 << " = " << t1 + t4 << endl;
    cout << "Subtraction: " << t3 << " - " << t5 << " = " << t3 - t5 << endl;

    return 0;
}
