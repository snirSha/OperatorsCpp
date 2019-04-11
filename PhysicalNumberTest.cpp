/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);
///////////////////////////////////////////////////////----------------->>>>first test
    PhysicalNumber e(0.2, Unit::KM);  //200 meter
    PhysicalNumber f(3000, Unit::M);  //3 km
    PhysicalNumber g(0.2, Unit::HOUR); //20 min
    PhysicalNumber h(65, Unit::M);   //1 hour & 5 min-->1.083333333
    PhysicalNumber i(90, Unit::MIN);   // 1.5 hour
    PhysicalNumber j(1000, Unit::CM); //10 meter
    PhysicalNumber k(3600, Unit::SEC); //1 hour
    PhysicalNumber l(500000, Unit::G); //0.1 ton
    PhysicalNumber m(0.6, Unit::KG);  // 600 gram
    PhysicalNumber n(0.02, Unit::TON); // 20 kg
//////////////////////////////////////////////////////////////////////////--->>end of 1st test

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT
    //basic output check
      .setname("testing our own")
      .CHECK_OUTPUT(e , "0.2[km]")
      .CHECK_OUTPUT(f, "3000[m]")
      .CHECK_OUTPUT(g, "0.2[hour]")
      .CHECK_OUTPUT(h, "65[m]")
      .CHECK_OUTPUT(i, "90[min]")
      .CHECK_OUTPUT(j, "1000[cm]")
      .CHECK_OUTPUT(k, "3600[sec]")
      .CHECK_OUTPUT(l, "500000[g]")
      .CHECK_OUTPUT(m, "0.6[kg]")
      .CHECK_OUTPUT(n, "0.02[ton]")
      .CHECK_OUTPUT(f-e, "2800[m]")
      .CHECK_OUTPUT(e-f, "-2.8[km]")
      .CHECK_OUTPUT(k-g, "2880[sec]")
      .CHECK_OUTPUT(m-n, "-19.4[kg]")
      .CHECK_OUTPUT(n-m, "0.0194[ton]")
      .CHECK_THROWS(g-e)
      .CHECK_OUTPUT(m++, "0.6[kg]")
      .CHECK_OUTPUT(m, "1.6[kg]")
      .CHECK_OUTPUT(--m, "0.6[kg]")
      .CHECK_OUTPUT((h+=f), "3065[m]")
      .CHECK_OUTPUT((i-=k), "30[min]")
      .CHECK_THROWS(i-f)
      .CHECK_OK(istringstream("2[g]") >> a)
      .CHECK_OUTPUT(+a, "2[g]")
      .CHECK_OUTPUT(-a, "-2[g]")
      .CHECK_EQUAL(f>e, true)
      .CHECK_EQUAL(i<g, false)
      .CHECK_OK(istringstream("0.5[hour]") >> b)
      .CHECK_EQUAL(i==b,true )
      .CHECK_EQUAL(i!=b,false )
      .CHECK_EQUAL(i>=b,true )
      .CHECK_EQUAL(i<=b,true )
      .CHECK_EQUAL(i>=k,false )
      .CHECK_THROWS(i-n)




      //check operators


      .setname("...")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
