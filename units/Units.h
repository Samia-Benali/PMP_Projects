#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>
#include <numeric>

namespace phy {

  /*
   * A unit defined in terms of the base units
   */
  template<int Metre, int Kilogram, int Second, int Ampere, int Kelvin, int Mole, int Candela>
  struct Unit {
    static constexpr int metre = Metre;
    static constexpr int kilogram = Kilogram;
    static constexpr int second = Second;
    static constexpr int ampere = Ampere;
    static constexpr int kelvin = Kelvin;
    static constexpr int mole = Mole;
    static constexpr int candela = Candela;
  };

  /*
   * Various type aliases
   */

  using Metre               = Unit<1,0,0,0,0,0,0>;
  using Kilogram            = Unit<0,1,0,0,0,0,0>;
  using Second              = Unit<0,0,1,0,0,0,0>;
  using Ampere              = Unit<0,0,0,1,0,0,0>;
  using Kelvin              = Unit<0,0,0,0,1,0,0>;
  using Mole                = Unit<0,0,0,0,0,1,0>;
  using Candela             = Unit<0,0,0,0,0,0,1>;
  using Radian              = Unit<0,0,0,0,0,0,0>;

  using Volt                = Unit<2,1,-3,-1,0,0,0>;
  using Ohm                 = Unit<2,1,-3,-2,0,0,0>;
  using Watt                = Unit<2,1,-3,0,0,0,0>;
  using Hertz               = Unit<0,0,-1,0,0,0,0>;
  using Pascal              = Unit<-1,1,-2,0,0,0,0>;
  using Speed               = Unit<1,0,-1,0,0,0,0>;
  using Newton              = Unit<1,1,-2,0,0,0,0>;

  namespace details {
    template<typename R1, typename R2>
    using CommonRatio = std::ratio<std::gcd(R1::num, R2::num), std::lcm(R1::den, R2::den)>;

    template <typename U1, typename U2>
    struct MultiplyFunction {
      using type = Unit<
        U1::metre + U2::metre,
        U1::kilogram + U2::kilogram,
        U1::second + U2::second,
        U1::ampere + U2::ampere,
        U1::kelvin + U2::kelvin,
        U1::mole + U2::mole,
        U1::candela + U2::candela
      >;
    };

    template <typename U1, typename U2>
    struct DivideFunction {
      using type = Unit<
        U1::metre - U2::metre,
        U1::kilogram - U2::kilogram,
        U1::second - U2::second,
        U1::ampere - U2::ampere,
        U1::kelvin - U2::kelvin,
        U1::mole - U2::mole,
        U1::candela - U2::candela
      >;
    };
  }

  /*
   * A quantity is a value associated with a unit and a ratio
   */
  template<class U, class R = std::ratio<1>>
  struct Qty {
    using Unit = U;
    using Ratio = R;

    intmax_t value;

    constexpr Qty() : value(0) {}
    constexpr Qty(intmax_t v) : value(v) {}

    template<typename ROther>
    constexpr Qty& operator+=(Qty<U, ROther> other);

    template<typename ROther>
    constexpr Qty& operator-=(Qty<U, ROther> other);
  };

  /*
   * Various quantities
   */

  using Length                = Qty<Metre>;
  using Mass                  = Qty<Kilogram>;
  using Time                  = Qty<Second>;
  using Current               = Qty<Ampere>;
  using Temperature           = Qty<Kelvin>;
  using Amount                = Qty<Mole>;
  using LuminousIntensity     = Qty<Candela>;

  using Frequency             = Qty<Hertz>;
  using Force                 = Qty<Newton>;
  using MeterSecond           = Qty<Speed>;
  using ElectricPotential     = Qty<Volt>;
  using ElectricalResistance  = Qty<Ohm>;
  using Power                 = Qty<Watt>;
  using Pressure              = Qty<Pascal>;

  /*
   * Some weird quantities
   */
  using Inch = Qty<Metre, std::ratio<254, 10000>>;
  using Foot = Qty<Metre, std::ratio<3048, 10000>>;
  using Yard = Qty<Metre, std::ratio<1143, 1250>>;
  using Mile = Qty<Metre, std::ratio<201168, 125>>;
  
  using Knot = Qty<MeterSecond, std::ratio<463, 900>>;

  /*
   * Cast function between two quantities
   */

  template<typename ResQty, typename U, typename R>
  constexpr ResQty qtyCast(Qty<U,R> q) {
    using Ratio = std::ratio_divide<R, typename ResQty::Ratio>;
    return ResQty((q.value * Ratio::num) / Ratio::den);
  }

  /*
   * Implementation class Qty
   */

  template<class U, class R>
  template<typename ROther>
  constexpr Qty<U, R>& Qty<U, R>::operator+=(Qty<U, ROther> other) {
    value += qtyCast<Qty<U, R>>(other).value;
    return *this;
  }

  template<class U, class R>
  template<typename ROther>
  constexpr Qty<U, R>& Qty<U, R>::operator-=(Qty<U, ROther> other) {
    value -= qtyCast<Qty<U, R>>(other).value;
    return *this;
  }

  /*
   * Comparison operators
   */

  template<typename U, typename R1, typename R2>
  constexpr bool operator==(Qty<U, R1> q1, Qty<U, R2> q2) {
    using Common = Qty<U, details::CommonRatio<R1, R2>>;
    return qtyCast<Common>(q1).value == qtyCast<Common>(q2).value;
  }

  template<typename U, typename R1, typename R2>
  constexpr bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2) {
    return !(q1 == q2);
  }

  template<typename U, typename R1, typename R2>
  constexpr bool operator<(Qty<U, R1> q1, Qty<U, R2> q2) {
    using CommonQ = Qty<U, details::CommonRatio<R1, R2>>;
    return qtyCast<CommonQ>(q1).value < qtyCast<CommonQ>(q2).value;
  }

  template<typename U, typename R1, typename R2>
  constexpr bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2) {
    return (q1 < q2) || (q1 == q2);
  }

  template<typename U, typename R1, typename R2>
  constexpr bool operator>(Qty<U, R1> q1, Qty<U, R2> q2) {
    return !(q1 <= q2);
  }

  template<typename U, typename R1, typename R2>
  constexpr bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2) {
    return !(q1 < q2);
  }

  /*
   * Arithmetic operators
   */

  template<typename U, typename R1, typename R2>
  constexpr auto operator+(Qty<U, R1> q1, Qty<U, R2> q2) {
    using ResRatio = details::CommonRatio<R1, R2>;
    using ResQty = Qty<U, ResRatio>;
    return ResQty(qtyCast<ResQty>(q1).value + qtyCast<ResQty>(q2).value);
  }

  template<typename U, typename R1, typename R2>
  constexpr auto operator-(Qty<U, R1> q1, Qty<U, R2> q2) {
    using ResRatio = details::CommonRatio<R1, R2>;
    using ResQty = Qty<U, ResRatio>;
    return ResQty(qtyCast<ResQty>(q1).value - qtyCast<ResQty>(q2).value);
  }

  template<typename U1, typename R1, typename U2, typename R2>
  constexpr auto operator*(Qty<U1, R1> q1, Qty<U2, R2> q2) {
    using ResU = typename details::MultiplyFunction<U1, U2>::type;
    using CommonR = typename details::CommonRatio<R1, R2>;
    
    auto v1 = qtyCast<Qty<U1, CommonR>>(q1).value;
    auto v2 = qtyCast<Qty<U2, CommonR>>(q2).value;
    using ResR = std::ratio_multiply<CommonR, CommonR>;
    
    return Qty<ResU, ResR>(v1 * v2);
  }

  template<typename U1, typename R1, typename U2, typename R2>
  constexpr auto operator/(Qty<U1, R1> q1, Qty<U2, R2> q2) {
    using ResU = typename details::DivideFunction<U1, U2>::type;
    using CommonR = typename details::CommonRatio<R1, R2>;
    auto v1 = qtyCast<Qty<U1, CommonR>>(q1).value;
    auto v2 = qtyCast<Qty<U2, CommonR>>(q2).value;
    using ResR = std::ratio_divide<R1, R2>;
    
    return Qty<ResU, ResR>(q1.value / q2.value);
  }

  // namespace literals {

  //   /*
  //    * Some user-defined literals
  //    */

  //   inline Length operator ""_metres(unsigned long long int val);
  //   inline Mass operator ""_kilograms(unsigned long long int val);
  //   inline Time operator ""_seconds(unsigned long long int val);
  //   inline Current operator ""_amperes(unsigned long long int val);
  //   inline Temperature operator ""_kelvins(unsigned long long int val);
  //   inline Amount operator ""_moles(unsigned long long int val);
  //   inline LuminousIntensity operator ""_candelas(unsigned long long int val);
  //   inline /* implementation defined */ operator ""_celsius(unsigned long long int val);

  // }

}

#endif // UNITS_H
