#include "LengthUnits.hpp"
#include "gtest/gtest.h"

using namespace LengthUnits;

TEST (LengthUnitsBase, Ctor) {
    auto nano = NanoMeters ();
    auto micro = MicroMeters ();
    auto milli = MilliMeters ();
    auto centi100 = CentiMeters (100);
    auto deci = DeciMeters ();
    auto meter = Meters ();
    auto km = KiloMeters ();
    auto inch = Inches ();
    auto feet = Feet ();
    auto miles = Miles ();

    EXPECT_EQ (meter.Count (), 1.);
    EXPECT_EQ (inch.Count (), 1.);
    EXPECT_EQ (meter, centi100);
    EXPECT_NE (nano, micro);
}

TEST (LengthUnitsBase, Literals) {
    using namespace LengthUnits::literals;

    EXPECT_EQ (NanoMeters (2), 2._nanoM);
    EXPECT_EQ (MicroMeters (), 1._microM);
    EXPECT_EQ (MilliMeters (), 1._milliM);
    EXPECT_EQ (CentiMeters (), 1._centiM);
    EXPECT_EQ (DeciMeters (), 1._deciM);
    EXPECT_EQ (Meters (44), 44._M);
    EXPECT_EQ (KiloMeters (), 1._kiloM);
    EXPECT_EQ (Inches (234.234), 234.234_In);
    EXPECT_EQ (Feet (), 1._Ft);
    EXPECT_EQ (Miles (0.0123), 0.0123_Mi);
}

TEST (LengthUnitsBase, CopyCtor) {
    auto dis = Meters (1);
    auto disInNano = NanoMeters (dis);
    auto disInKM = KiloMeters (dis);

    EXPECT_EQ (1e+9, disInNano.Count ());
    EXPECT_EQ (.001, disInKM.Count ());
    EXPECT_EQ (disInNano, disInKM);
}

TEST (LengthUnitsBase, MetricRatio) {
    EXPECT_EQ (NanoMeters (1000), MicroMeters (1));
    EXPECT_EQ (MicroMeters (1000), MilliMeters (1));
    EXPECT_EQ (MilliMeters (10), CentiMeters (1));
    EXPECT_EQ (CentiMeters (10), DeciMeters (1));
    EXPECT_EQ (DeciMeters (10), Meters (1));
    EXPECT_EQ (Meters (1000), KiloMeters (1));

    EXPECT_EQ (Meters (.01), CentiMeters (1));

    EXPECT_NE (NanoMeters (), KiloMeters ());
}

TEST (LengthUnitsBase, ImperialRatio) {

    EXPECT_EQ (Meters (381), Feet (1250));

    EXPECT_EQ (Feet (1), Inches (12));
    EXPECT_EQ (Miles (1), Feet (5280));
}

TEST (LengthUnitsBase, Increment) {
    Meters m = Meters ();
    ++m;
    EXPECT_EQ (m.Count (), 2.);
    EXPECT_EQ ((++m).Count (), 3.);

    double const originalVal = 234.234;
    auto miles = Miles (originalVal);

    EXPECT_EQ ((++miles).Count (), originalVal + 1.);
}

TEST (LengthUnitsBase, Decrement) {
    Meters m = Meters ();
    --m;
    EXPECT_EQ (m.Count (), 0.);
    EXPECT_EQ ((--m).Count (), -1.);

    double const originalVal = 234.234;
    auto miles = Miles (originalVal);

    EXPECT_EQ ((--miles).Count (), originalVal - 1.);
}

TEST (LengthUnitsBase, Addition) {
    Meters m = Meters ();

    EXPECT_EQ (m + m, Meters(2));
    EXPECT_EQ ((Meters (2.3) + Meters(8.5)).Count (), 2.3 + 8.5);

    EXPECT_EQ (Inches(4) + Inches(8), Feet());
    EXPECT_EQ (CentiMeters(123.34) + KiloMeters(8), DeciMeters(80012.334));
}

TEST (LengthUnitsBase, Subtraction) {
    Meters m = Meters ();

    EXPECT_EQ (m - m, Meters(0));
    EXPECT_EQ ((Meters (10.3) - Meters(2.1)).Count (), 10.3-2.1);

    EXPECT_EQ (Miles(4) - Feet(5280. * 1.5), Miles(2.5));
    EXPECT_EQ (KiloMeters(8) - CentiMeters(123), DeciMeters(79987.7));
}

TEST (LengthUnitsBase, Multiplication) {
    Meters m = Meters ();

    EXPECT_EQ (m * 1, m);
    EXPECT_EQ ((Meters (2.3) * .5).Count (), 2.3 * .5);

    m *= 3.;

    EXPECT_EQ (m.Count (), 3.);
}

TEST (LengthUnitsBase, Division) {
    Meters m = Meters ();
    EXPECT_EQ (m / 1, m);
    EXPECT_EQ ((Meters (2.3) / .5).Count (), 2.3 / .5);

    m /= 3;

    EXPECT_EQ (m.Count (), 1. / 3.);

    EXPECT_THROW ({ m / 0; }, std::overflow_error);
    EXPECT_THROW ({ m /= 0; }, std::overflow_error);
}

TEST (LengthUnitsBase, Modulo) {
    Meters m = Meters ();

    EXPECT_EQ (m % 1, 0);
    EXPECT_NEAR (Meters (2.3) % .5, .3, 0.00001);
    EXPECT_NEAR (Meters (-2.3) % .5, .2, 0.00001);
}