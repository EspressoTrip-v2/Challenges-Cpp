//
// Created by Juan on 5/18/2021.
//
#include <iostream>
using namespace std;
#ifndef TEMPERATURELITERALS_CONVERSION_TYPES_H
#define TEMPERATURELITERALS_CONVERSION_TYPES_H
namespace conversions
{
    enum class scale
    {
        CELSIUS, FAHRENHEIT, KELVIN
    };

    // Temperature value storage
    template<scale S>
    class quantity
    {
        double amount;
    public:
        scale type = S;
        constexpr explicit quantity(double amount) : amount(amount)
        {}
        explicit operator double() const // user defines cast
        {
            return amount;
        }

        friend ostream &operator<<(ostream &os, const quantity &quantity)
        {
            os << quantity.amount << (quantity.type == scale::CELSIUS ? " C" :
                                      quantity.type == scale::KELVIN ? " K" : " F");
            return os;
        }
    };


// Temperature Conversions
    template<scale F, scale T>
    struct conversion_type
    {
        constexpr static quantity<T> convert(const quantity<F> &value) = delete;
    };

    template<>
    struct conversion_type<scale::CELSIUS, scale::FAHRENHEIT>
    {
        constexpr static quantity<scale::FAHRENHEIT> convert(const quantity<scale::CELSIUS> &value)
        {
            return quantity<scale::FAHRENHEIT>{(static_cast<double>(value) * 9 / 5) + 32};
        }
    };

    template<>
    struct conversion_type<scale::FAHRENHEIT, scale::CELSIUS>
    {
        constexpr static quantity<scale::CELSIUS> convert(const quantity<scale::FAHRENHEIT> &value)
        {
            return quantity<scale::CELSIUS>{(static_cast<double>(value) - 32) * 9 / 5};
        }
    };

    template<>
    struct conversion_type<scale::FAHRENHEIT, scale::KELVIN>
    {
        constexpr static quantity<scale::KELVIN> convert(const quantity<scale::FAHRENHEIT> &value)
        {
            return quantity<scale::KELVIN>{(static_cast<double>(value) - 32) * 9 / 5 + 273.15};
        }
    };

    template<>
    struct conversion_type<scale::KELVIN, scale::FAHRENHEIT>
    {
        constexpr static quantity<scale::FAHRENHEIT> convert(const quantity<scale::KELVIN> &value)
        {
            return quantity<scale::FAHRENHEIT>{(static_cast<double>(value) - 273.15) * 9 / 5 + 32};
        }
    };

    template<>
    struct conversion_type<scale::CELSIUS, scale::KELVIN>
    {
        constexpr static quantity<scale::KELVIN> convert(const quantity<scale::CELSIUS> &value)
        {
            return quantity<scale::KELVIN>{static_cast<double>(value) + 273.15};
        }
    };

    template<>
    struct conversion_type<scale::KELVIN, scale::CELSIUS>
    {
        constexpr static quantity<scale::CELSIUS> convert(const quantity<scale::KELVIN> &value)
        {
            return quantity<scale::CELSIUS>{static_cast<double>(value) - 273.15};
        }
    };
}

#endif //TEMPERATURELITERALS_CONVERSION_TYPES_H
