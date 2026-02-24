#include "Units.h"
#include <iostream>
#include <gtest/gtest.h>


// TODO : Test Nombre négatifs et cas limites

TEST(UnitsTests, TestAliasBase){
  EXPECT_TRUE((std::is_same_v<phy::Metre, phy::Unit<1,0,0,0,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Kilogram, phy::Unit<0,1,0,0,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Second, phy::Unit<0,0,1,0,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Ampere, phy::Unit<0,0,0,1,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Kelvin, phy::Unit<0,0,0,0,1,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Mole, phy::Unit<0,0,0,0,0,1,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Candela, phy::Unit<0,0,0,0,0,0,1>>));
}

TEST(UnitsTests, TestAliasDerived){
  EXPECT_TRUE((std::is_same_v<phy::Volt, phy::Unit<2,1,-3,-1,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Ohm, phy::Unit<2,1,-3,-2,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Watt, phy::Unit<2,1,-3,0,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Hertz, phy::Unit<0,0,-1,0,0,0,0>>));
  EXPECT_TRUE((std::is_same_v<phy::Pascal, phy::Unit<-1,1,-2,0,0,0,0>>));
}

TEST(UnitsTests, TestAliasQuantities){
  EXPECT_TRUE((std::is_same_v<phy::Length, phy::Qty<phy::Metre>>));
  EXPECT_TRUE((std::is_same_v<phy::Mass, phy::Qty<phy::Kilogram>>));
  EXPECT_TRUE((std::is_same_v<phy::Time, phy::Qty<phy::Second>>));
  EXPECT_TRUE((std::is_same_v<phy::Current, phy::Qty<phy::Ampere>>));
  EXPECT_TRUE((std::is_same_v<phy::Temperature, phy::Qty<phy::Kelvin>>));
  EXPECT_TRUE((std::is_same_v<phy::Amount, phy::Qty<phy::Mole>>));
  EXPECT_TRUE((std::is_same_v<phy::LuminousIntensity, phy::Qty<phy::Candela>>));
}

TEST(UnitsTests, TestAliasQuantitiesDerived){
  EXPECT_TRUE((std::is_same_v<phy::Frequency, phy::Qty<phy::Hertz>>));
  EXPECT_TRUE((std::is_same_v<phy::Force, phy::Qty<phy::Newton>>));
  EXPECT_TRUE((std::is_same_v<phy::MeterSecond, phy::Qty<phy::Speed>>));
  EXPECT_TRUE((std::is_same_v<phy::ElectricPotential, phy::Qty<phy::Volt>>));
  EXPECT_TRUE((std::is_same_v<phy::ElectricalResistance, phy::Qty<phy::Ohm>>));
  EXPECT_TRUE((std::is_same_v<phy::Power, phy::Qty<phy::Watt>>));
  EXPECT_TRUE((std::is_same_v<phy::Pressure, phy::Qty<phy::Pascal>>));
}

TEST(UnitsTests, TestOperatorsPlusEquals){
  phy::Qty<phy::Metre, std::ratio<1>> m(1);
  phy::Qty<phy::Metre, std::ratio<1, 1000>> mm(2);
  m += mm;
  EXPECT_EQ(m.value, 1);
  mm += m;
  EXPECT_EQ(mm.value, 1002);
}

TEST(UnitsTests, TestOperatorsMinusEqual){
  phy::Qty<phy::Volt, std::ratio<1>> v(1);
  phy::Qty<phy::Volt, std::ratio<1, 1000>> vv(2);
  v -= vv;
  EXPECT_EQ(v.value, 1);
  vv -= v;
  EXPECT_EQ(vv.value, -998);
}

TEST(UnitsTests, TestOperatorsEqualEqual){
  phy::Qty<phy::Length, std::ratio<1>> m(1);
  phy::Qty<phy::Length, std::ratio<1, 1000>> mm(1000);
  phy::Qty<phy::Length, std::ratio<1, 100>> mmm(1000);
  EXPECT_TRUE(m == mm);
  EXPECT_FALSE(m == mmm);
  EXPECT_FALSE(mm == mmm);
}

// TEST(UnitsTests, TestOperatorsEqualEqualMILEYARD){
//   phy::Mile m(1);
//   phy::Yard y(1760);
//   EXPECT_TRUE(m == y);

// }
TEST(UnitsTests, TestOperatorsEqualEqualMinus){
  phy::Qty<phy::Speed, std::ratio<1>> m(-1);
  phy::Qty<phy::Speed, std::ratio<1, 1000>> mm(-1000);
  phy::Qty<phy::Speed, std::ratio<1, 100>> mmm(-1000);
  EXPECT_TRUE(m==mm);
  EXPECT_FALSE(m == mmm);
  EXPECT_FALSE(mm == mmm);
}

TEST(UnitsTests, TestOperatorsDifferentEqual){
  phy::Qty<phy::Newton, std::ratio<1>> m(1);
  phy::Qty<phy::Newton, std::ratio<1, 1000>> mm(1000);
  phy::Qty<phy::Newton, std::ratio<1, 1000>> mmm(-1000);
  EXPECT_FALSE(m!=mm);
  EXPECT_TRUE(m != mmm);
  EXPECT_TRUE(mm != mmm);
}

TEST(UnitsTests, TestOperatorsLTAndGT){
  phy::Qty<phy::Power, std::ratio<1>> m(6);
  phy::Qty<phy::Power, std::ratio<1, 1000>> mm(1000);
  phy::Qty<phy::Power, std::ratio<1, 1000>> mmm(-1000);
  EXPECT_FALSE(m < mm);
  EXPECT_TRUE(m > mm);
  EXPECT_TRUE(mm > mmm);
  EXPECT_FALSE(mm < mmm);
  EXPECT_FALSE(m < mmm);
  EXPECT_TRUE(m > mmm);

}


TEST(UnitsTests, TestOperatorsLEAndGE){
  phy::Qty<phy::Pressure, std::ratio<1>> m(6);
  phy::Qty<phy::Pressure, std::ratio<1>> m1(1);
  phy::Qty<phy::Pressure, std::ratio<1, 1000>> mm(1000);
  phy::Qty<phy::Pressure, std::ratio<1, 1000>> mmm(-1000);
  EXPECT_FALSE(m <= m1);
  EXPECT_TRUE(m1 <= m);
  EXPECT_TRUE(m1 <= mm);
  EXPECT_TRUE(mm <= m1);
  EXPECT_FALSE(m <= mm);
  EXPECT_TRUE(m >= mm);
  EXPECT_TRUE(mm >= mmm);
  EXPECT_FALSE(mm <= mmm);
  EXPECT_FALSE(m <= mmm);
  EXPECT_TRUE(m >= mmm);

}

TEST(UnitsTests, TESTArithmeticsOperatorsPlus){
    phy::Qty<phy::ElectricalResistance, std::ratio<1>> i(600);
    phy::Qty<phy::ElectricalResistance, std::ratio<1, 1000>> y(18);
    auto val = i + y;
    fprintf(stdout, "val : %ld\n", val.value);
    EXPECT_EQ(val.value, 600018);

}

TEST(UnitsTests, TESTArithmeticsOperatorsMinus){
    phy::Qty<phy::Frequency, std::ratio<1>> i(12);
    phy::Qty<phy::Frequency, std::ratio<1, 1000>> y(-60);
    auto val = i - y;
    fprintf(stdout, "val : %ld\n", val.value);
    EXPECT_EQ(val.value, 12060);

}


TEST(UnitsTests, TESTArithmeticsOperatorsMultiply){
    phy::Qty<phy::Metre, std::ratio<1>> m(9);
    phy::Qty<phy::Metre, std::ratio<1>> m2(-6);
    auto val = m * m2;
    fprintf(stdout, "val : %ld\n", val.value);
    EXPECT_EQ(val.value, -54);

}

TEST(UnitsTests, TESTArithmeticsOperatorsMILEYARD){
    phy::Mile m(1);
    phy::Yard y(1);
    auto val = m + y;
    fprintf(stdout, "val : %ld\n", val.value);
    EXPECT_EQ(val.value, 2);

}



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
