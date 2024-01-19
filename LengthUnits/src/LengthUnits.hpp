#pragma once
#include <iostream>
#include <limits>
#include <numeric>
#include <ratio>
#include <stdexcept>

namespace LengthUnits {

// float epsilon for doubles
static constexpr double EPS = std::numeric_limits<float>::epsilon ();

template <class ratio>
class Distance;

template <class _To, class ratio1>
constexpr _To distance_cast (const Distance<ratio1> &_Dur) noexcept;

template <class ratio = std::ratio<1>>
class Distance {
  private:
    double amount;

  public:
    using ratioType = typename ratio::type;

    Distance (double amount = 1.) : amount (amount){};
    Distance (const Distance &other) : amount (other.amount) {}

    template <class ratio2>
    Distance (const Distance<ratio2> &right) noexcept {
        using _CF = std::ratio_divide<ratio2, ratioType>;

        constexpr bool _Num_is_one = _CF::num == 1;
        constexpr bool _Den_is_one = _CF::den == 1;

        if (_Den_is_one) {
            if (_Num_is_one) {
                amount = (right.Count ());
            } else {
                amount = (right.Count () * static_cast<double> (_CF::num));
            }
        } else {
            if (_Num_is_one) {
                amount = (right.Count () / static_cast<double> (_CF::den));
            } else {
                amount = (right.Count () * static_cast<double> (_CF::num) / static_cast<double> (_CF::den));
            }
        }
    }

    double Count () const {
        return amount;
    }

    Distance &operator++ () {
        ++amount;
        return *this;
    }

    Distance &operator-- () {
        --amount;
        return *this;
    }

    Distance &operator+= (const Distance &right) {
        amount += right.amount;
        return *this;
    }

    Distance operator* (double const val) {
        return Distance (amount * val);
    }

    Distance &operator*= (double const val) {
        amount *= val;
        return *this;
    }

    Distance operator/ (double const val) {
        if (val == 0.)
            throw std::overflow_error ("division by zero");
        return Distance (amount / val);
    }

    Distance &operator/= (double const val) {
        if (val == 0.)
            throw std::overflow_error ("division by zero");
        amount /= val;
        return *this;
    }

    double operator% (double const val) {
        if (val == 0.)
            throw std::overflow_error ("division by zero");

        return amount - floor (amount / val) * val;
    }
};

template <class ratio1, class ratio2>
struct common_distance;

template <class ratio1, class ratio2>
struct common_distance<Distance<ratio1>, Distance<ratio2>> {
    using type = Distance<std::ratio<std::gcd (ratio1::num, ratio2::num), std::lcm (ratio1::den, ratio2::den)>>;
};

template <class ratio1, class ratio2>
constexpr typename common_distance<Distance<ratio1>, Distance<ratio2>>::type
operator+ (const Distance<ratio1> &left, const Distance<ratio2> &right) {
    using _CR = typename common_distance<Distance<ratio1>, Distance<ratio2>>::type;

    return _CR (_CR (left).Count () + _CR (right).Count ());
}

template <class ratio1, class ratio2>
constexpr bool operator== (const Distance<ratio1> &left, const Distance<ratio2> &right) {
    using _CR = typename common_distance<Distance<ratio1>, Distance<ratio2>>::type;

    return std::abs (_CR (left).Count () - _CR (right).Count ()) < EPS;
}

template <class ratio1, class ratio2>
constexpr bool operator!= (const Distance<ratio1> &left, const Distance<ratio2> &right) {
    return !(left == right);
}

using NanoMeters = Distance<std::nano>;
using MicroMeters = Distance<std::micro>;
using MilliMeters = Distance<std::milli>;
using CentiMeters = Distance<std::centi>;
using DeciMeters = Distance<std::deci>;
using Meters = Distance<std::ratio<1>>;
using KiloMeters = Distance<std::kilo>;

using Inches = Distance<std::ratio<254, 10000>>;
using Feet = Distance<std::ratio<3048, 10000>>;
using Miles = Distance<std::ratio<1609344, 1000>>;

namespace literals {
NanoMeters operator""_nanoM (long double val) noexcept {
    return NanoMeters (val);
}
MicroMeters operator""_microM (long double val) noexcept {
    return MicroMeters (val);
}
MilliMeters operator""_milliM (long double val) noexcept {
    return MilliMeters (val);
}
CentiMeters operator""_centiM (long double val) noexcept {
    return CentiMeters (val);
}
DeciMeters operator""_deciM (long double val) noexcept {
    return DeciMeters (val);
}
Meters operator""_M (long double val) noexcept {
    return Meters (val);
}
KiloMeters operator""_kiloM (long double val) noexcept {
    return KiloMeters (val);
}
Inches operator""_In (long double val) noexcept {
    return Inches (val);
}
Feet operator""_Ft (long double val) noexcept {
    return Feet (val);
}
Miles operator""_Mi (long double val) noexcept {
    return Miles (val);
}
} // namespace literals

} // namespace LengthUnits
