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
    PhysicalNumber km2a(2, Unit::KM);
    PhysicalNumber kg2a(2, Unit::KG);
    PhysicalNumber m300b(300, Unit::M);
    PhysicalNumber hr2c(2, Unit::HOUR);
    PhysicalNumber min30d(30, Unit::MIN);

    // Or Avital https://github.com/oravital7/PhysicalNumber
    PhysicalNumber gram30(30, Unit::G);
    PhysicalNumber cm30(30, Unit::CM);
    PhysicalNumber km30(30, Unit::KM);
    PhysicalNumber m200(200, Unit::M);    


    // Ofek Bader and Snir Yefet https://github.com/neyney10/Ariel-University-CPP-Assignment-3
    //DISTANCE
    PhysicalNumber km2(2, Unit::KM);
    PhysicalNumber mtr2000(2000, Unit::M);
    PhysicalNumber cm200000(200000, Unit::CM);
    PhysicalNumber km05(0.5, Unit::KM);


    //Netanel Davidov and Maxim Mermer: https://github.com/netanel208/PhysicalNumber-cpp
    PhysicalNumber cm2a(2, Unit::CM);
    PhysicalNumber km3a(3, Unit::KM);
    PhysicalNumber m4a(4, Unit::M);
    PhysicalNumber km01a(0.1, Unit::KM);

    PhysicalNumber sec2b(2, Unit::SEC);
    PhysicalNumber min3b(3, Unit::MIN);
    PhysicalNumber hr4b(4, Unit::HOUR);
    PhysicalNumber hr01b(0.1, Unit::HOUR);

    PhysicalNumber g2c(2, Unit::G);
    PhysicalNumber kg3c(3, Unit::KG);
    PhysicalNumber ton4c(4, Unit::TON);
    PhysicalNumber ton01c(0.1, Unit::TON);

    PhysicalNumber g100x(100, Unit::G);
    PhysicalNumber hr2y(2, Unit::HOUR);
    PhysicalNumber m10z(10, Unit::M);

    //TIME
    PhysicalNumber hr2(2, Unit::HOUR);
    PhysicalNumber min120(120, Unit::MIN);
    PhysicalNumber sec7200(7200, Unit::SEC);
    PhysicalNumber min60(60, Unit::MIN);

    //MASS
    PhysicalNumber ton2(2, Unit::TON);
    PhysicalNumber kg2000(2000, Unit::KG);
    PhysicalNumber g2000000(2000000, Unit::G);
    PhysicalNumber ton1(1, Unit::TON);
    PhysicalNumber kg500(500, Unit::KG);
    PhysicalNumber g1000(1000, Unit::G);

    //ANY (for input)
    PhysicalNumber inputPN(999, Unit::G);


    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(km2a, "2[km]")
    .CHECK_OUTPUT(m300b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(m300b+km2a, "2300[m]")
    .CHECK_OUTPUT((km2a+=m300b), "2.3[km]")
    .CHECK_OUTPUT(km2a, "2.3[km]")
    .CHECK_OUTPUT(km2a+km2a, "4.6[km]")
    .CHECK_OUTPUT(m300b-m300b, "0[m]")
    .CHECK_OUTPUT(hr2c, "2[hour]")
    .CHECK_OUTPUT(min30d, "30[min]")
    .CHECK_OUTPUT(min30d+hr2c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(km2a+hr2c)
    .CHECK_THROWS(km2a+min30d)
    .CHECK_THROWS(m300b+hr2c)
    .CHECK_THROWS(m300b+min30d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> km2a)
    .CHECK_OUTPUT((km2a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // Or Avital https://github.com/oravital7/PhysicalNumber
      .setname("mORe incompatible dimensions")
      .CHECK_THROWS(gram30+cm30)
      .CHECK_THROWS(cm30+gram30)
      .CHECK_THROWS(gram30+=cm30)
      .CHECK_THROWS(cm30+=gram30)
      .CHECK_THROWS(cm30-=gram30)
      .CHECK_THROWS(gram30-=cm30)
      .CHECK_THROWS(cm30-gram30)
      .CHECK_THROWS(gram30-cm30)
      .CHECK_THROWS(m300b += gram30)
      .CHECK_THROWS(km2a -= min30d)
      .CHECK_THROWS(hr2c += m200)
      .CHECK_THROWS(hr2c -= m200)
      .CHECK_THROWS(m200 -= hr2c)
      .CHECK_THROWS(m200 += hr2c)

      .setname("Illegal input")
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("200[g") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("0.2[]") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("200g]") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("0.2[kgg]") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("122.2kg") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("1332.2[to n]") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")
      .CHECK_OK(istringstream("[ton]1332.2") >> inputPN)
      .CHECK_OUTPUT(inputPN, "999[g]")

      .setname("mORe compatible dimensions")
      .CHECK_OUTPUT(++gram30, "31[g]")
      .CHECK_OUTPUT(--gram30, "30[g]")
      .CHECK_OUTPUT(--cm30, "29[cm]")
      .CHECK_OUTPUT(++cm30, "30[cm]")
      .CHECK_OUTPUT((gram30+=gram30), "60[g]")
      .CHECK_OUTPUT((cm30+=cm30), "60[cm]")
      .CHECK_OUTPUT((-gram30),"-60[g]")
      .CHECK_OUTPUT(+gram30,"60[g]")
      .CHECK_OUTPUT((km30+=m200) , "30.2[km]")
      .CHECK_OK(cm30-=cm30)  // after this, cm30==0
      .CHECK_OUTPUT((cm30+=m200),"20000[cm]")  // after this, cm30==200m
      .CHECK_OUTPUT((m200+=cm30) , "400[m]")   // after this, m200==400m
      .CHECK_OUTPUT((++m200) , "401[m]")
      .CHECK_OUTPUT((--m200) , "400[m]")
      .CHECK_OUTPUT((-m200) , "-400[m]")
      .CHECK_OUTPUT((+m200) , "400[m]")
      .CHECK_OUTPUT(gram30++, "60[g]")
      .CHECK_OUTPUT(gram30, "61[g]")
      .CHECK_OUTPUT(gram30--, "61[g]")
      .CHECK_OUTPUT(gram30, "60[g]")

      .setname("Comparison operators")
      .CHECK_EQUAL(cm30 < km30, true)
      .CHECK_EQUAL(cm30 > km30, false)
      .CHECK_EQUAL(cm30 != km30, true)
      .CHECK_EQUAL(cm30 == km30, false)
      .CHECK_EQUAL(cm30 == cm30, true)
      .CHECK_EQUAL(m200 > cm30, true)
      .CHECK_EQUAL(m200 != cm30, true)
      .CHECK_EQUAL(m200 > cm30, true)
      .CHECK_EQUAL(m200 >= cm30, true)
      .CHECK_OK(istringstream("200[m]") >> m200)
      .CHECK_OUTPUT(m200, "200[m]")
      .CHECK_EQUAL(m200 == cm30, true)
      .CHECK_OK(istringstream("2000[g]") >> gram30)
      .CHECK_OK(istringstream("2[kg]") >> kg2a)
      .CHECK_OUTPUT(kg2a, "2[kg]")
      .CHECK_EQUAL(gram30 == kg2a, true)
      .CHECK_EQUAL(gram30 != kg2a, false)
      .CHECK_OUTPUT((--gram30), "1999[g]")
      .CHECK_EQUAL(gram30 != kg2a, true)
      .CHECK_EQUAL(gram30 == kg2a, false)
      .CHECK_OK(istringstream("200[g]") >> gram30)
      .CHECK_OK(istringstream("0.2[kg]") >> kg2a)
      .CHECK_OUTPUT(gram30 , "200[g]")
      .CHECK_OUTPUT(kg2a , "0.2[kg]")
      .CHECK_EQUAL(gram30 != kg2a, false)
      .CHECK_EQUAL(gram30 == kg2a, true)

      .CHECK_OK(istringstream("30[min]") >> m300b)
      .CHECK_OK(istringstream("0.5[hour]") >> hr2c)
      .CHECK_OUTPUT(m300b , "30[min]")
      .CHECK_OUTPUT(hr2c , "0.5[hour]")
      .CHECK_EQUAL(m300b != hr2c, false)
      .CHECK_EQUAL(m300b == hr2c, true)

      .CHECK_OK(istringstream("1[ton]") >> m300b)
      .CHECK_OK(istringstream("1000[kg]") >> hr2c)
      .CHECK_OUTPUT(m300b , "1[ton]")
      .CHECK_OUTPUT(hr2c , "1000[kg]")
      .CHECK_EQUAL(m300b != hr2c, false)
      .CHECK_EQUAL(m300b == hr2c, true)

      .CHECK_OK(istringstream("0.5[km]") >> m300b)
      .CHECK_OK(istringstream("500[m]") >> hr2c)
      .CHECK_OUTPUT(m300b , "0.5[km]")
      .CHECK_OUTPUT(hr2c , "500[m]")
      .CHECK_EQUAL(m300b != hr2c, false)
      .CHECK_EQUAL(m300b == hr2c, true)

      .CHECK_OUTPUT((m300b+m300b+hr2c), "1.5[km]")
      .CHECK_OUTPUT((hr2c+m300b+m300b), "1500[m]")
      .CHECK_OUTPUT((hr2c+m300b-m300b), "500[m]")
      .CHECK_OUTPUT((m300b-hr2c-hr2c+m300b), "0[km]")
      .CHECK_EQUAL((m300b+hr2c > m300b), true)
      .CHECK_EQUAL((m300b-hr2c < m300b), true)
      .CHECK_OUTPUT((m300b+=hr2c+=m300b), "1.5[km]")
      .CHECK_OUTPUT(m300b, "1.5[km]")
      .CHECK_OK(istringstream("300[m]") >> m300b)
      .CHECK_OUTPUT(m300b, "300[m]")
      .CHECK_OUTPUT(hr2c, "1000[m]")

      .setname("(gram30++)-gram30")
      .CHECK_OUTPUT((gram30++)-gram30,"-1[g]")
      .setname("(gram30--)-gram30")
      .CHECK_OUTPUT((gram30--)-gram30,"1[g]")

      ////// AUTHORS : OFEK BADER AND SNIR YEFET /////
      ///////////// DISTANCE UNITS ///////////////////
      .setname("TEST DISTANCE UNITS CONSTRUCTOR and output (Ctor)")
      .CHECK_OUTPUT(km2, "2[km]")
      .CHECK_OUTPUT(mtr2000, "2000[m]")
      .CHECK_OUTPUT(cm200000, "200000[cm]")
      .CHECK_OUTPUT(km05, "0.5[km]")

      .setname("TEST DISTANCE UNITS COMPARISON (=)")
      .CHECK_EQUAL(mtr2000, km2) // Should Return True (V)
      .CHECK_EQUAL(cm200000, km2) // Should Return True (V)
      .CHECK_EQUAL(cm200000, mtr2000) // Should Return True (V)

      .setname("TEST DISTANCE UNITS COMPARISON (NOT) (!=)")
      .CHECK_EQUAL((km05 != km05), false) //suppose to return true
      .CHECK_EQUAL((km05 != km2), true) //suppose to return true
      .CHECK_EQUAL((mtr2000 != km2), false) //suppose to return false (actual=false ,expected=true)
      //.CHECK_THROWS(km05 != hr2)

      .setname("TEST DISTANCE UNITS GREATER (>)")
      .CHECK_EQUAL((km05 > km2), false)
      .CHECK_EQUAL((km2 > km05), true)
      .CHECK_EQUAL((km05 > km05), false)
      .CHECK_EQUAL((m300b > km05), false) 
      //.CHECK_THROWS(km05 > hr2)

      .setname("TEST DISTANCE UNITS LESSER (<)")
      .CHECK_EQUAL((km05 < km2), true) //suppose to return true
      .CHECK_EQUAL((km2 < km05), false) // supose to return true
      .CHECK_EQUAL((km05 < km05), false) //suppose to return true
      .CHECK_EQUAL((m300b < km05), true) //suppose to return true (m300b = 300 meter)
      //.CHECK_THROWS(km05 < hr2)

      .setname("TEST DISTANCE UNITS COMPARISON GREATER (>=)")
      .CHECK_EQUAL((km05 >= km2), false)
      .CHECK_EQUAL((km2 >= km05), true)
      .CHECK_EQUAL((km05 >= km05), true) //suppose to return true
      .CHECK_EQUAL((m300b >= km05), false) //suppose to return false (m300b = 300 meter)
      //.CHECK_THROWS(km05 >= hr2)

      .setname("TEST DISTANCE UNITS COMPARISON LESSER (<=)")
      .CHECK_EQUAL((km05 <= km2), true) //suppose to return true
      .CHECK_EQUAL((km2 <= km05), false) // supose to return false
      .CHECK_EQUAL((km05 <= km05), true) //suppose to return true
      .CHECK_EQUAL((m300b <= km05), true) //suppose to return true (m300b = 300 meter)
      //.CHECK_THROWS(km05 <= hr2)

      .setname("TEST DISTANCE UNITS ADDITION OP (+)")
      .CHECK_EQUAL((km05 + PhysicalNumber(1.5, Unit::KM)), km2) // Should Return True (V)
      .CHECK_EQUAL((km05 + PhysicalNumber(1500, Unit::M)), km2) // Should Return True (V)
      .CHECK_EQUAL((cm200000 + PhysicalNumber(1.2, Unit::KM)), +PhysicalNumber(3.2, Unit::KM)) // Should Return True (V)
      .CHECK_EQUAL((km05 + PhysicalNumber(250, Unit::M)), PhysicalNumber(750, Unit::M)) //should return true
      .CHECK_THROWS(km05 + hr2)

      .setname("TEST DISTANCE UNITS ADDTIONEQ OP (+=)")
      .CHECK_OUTPUT((cm200000 += km2), "400000[cm]") //suppose to return true (cm200000 = 400000cm)
      .CHECK_OUTPUT((km05 += PhysicalNumber(500, Unit::M)), "1[km]") // (km05 = 1km)
      //.CHECK_OUTPUT((km05+=0),"0.5[km]") //suppose to return true (ALERT MIGHT CAUSE PROBLEM SINCE WE A DECIMAL POINT??)
      .CHECK_OUTPUT((km05 += PhysicalNumber(0.5, Unit::KM)), "1.5[km]") // (km05 = 1.5km)
      .CHECK_THROWS(km05 += hr2) // should throw exception DISTANCE != TIME.

      .setname("TEST DISTANCE UNITS SUBSCTRACTION OP (-)")
      .CHECK_OUTPUT(PhysicalNumber(1.5, Unit::KM) - km05, "0[km]") //
      .CHECK_OUTPUT(cm200000 - PhysicalNumber(1.3, Unit::KM), "270000[cm]") // suppose to return true
      .CHECK_THROWS(km05 -= hr2)

      .setname("TEST DISTANCE UNTIS SUBSCTRACTIONEQ OP (-=)")
      .CHECK_OUTPUT((cm200000 -= km2), "200000[cm]")
      .CHECK_OUTPUT((km05 -= PhysicalNumber(400, Unit::M)), "1.1[km]")

      .CHECK_THROWS(km05 -= hr2) // should throw an exception

      .setname("TEST DISTANCE UNTIS POSTFIX INCREMENT (..++)")
      .CHECK_OUTPUT(km2++, "2[km]") // (km3 = 3km)
      .CHECK_OUTPUT(km2, "3[km]")   // (km2 = 3km)
      .CHECK_OUTPUT(cm200000++, "200000[cm]") // (cm200000 = 270000)
      .CHECK_OUTPUT(cm200000, "200001[cm]")   // (cm200000 = 270000)

      .setname("TEST DISTANCE UNTIS PREFIX INCREMENT (++..)")
      .CHECK_OUTPUT(++km2, "4[km]") //suppose to return true
      .CHECK_OUTPUT(km2, "4[km]")   //suppose to return true
      .CHECK_OUTPUT(++cm200000, "200002[cm]") //suppose to return true
      .CHECK_OUTPUT(cm200000, "200002[cm]")   //suppose to return true

      ///////////// TIME UNITS ///////////////////  D=30MIN
      .setname("TEST TIME UNITS CONSTRUCTOR and output (Ctor)")
      .CHECK_OUTPUT(hr2, "2[hour]")
      .CHECK_OUTPUT(min120, "120[min]")
      .CHECK_OUTPUT(sec7200, "7200[sec]")
      .CHECK_OUTPUT(min60, "60[min]")
      .CHECK_OUTPUT(PhysicalNumber(14.212, Unit::MIN), "14.212[min]")

      .setname("TEST TIME UNITS COMPARISON (=)")
      .CHECK_EQUAL(hr2, min120) // suppose to return true
      .CHECK_EQUAL(sec7200, min120) //suppose to return true
      .CHECK_EQUAL(sec7200, hr2) //suppose to return true

      .setname("TEST TIME UNITS COMPARISON (NOT) (!=)")
      .CHECK_EQUAL(sec7200 != min60, true) //suppose to return true
      .CHECK_EQUAL(sec7200 != min120, false) // suppose to return true
      .CHECK_EQUAL(min120 != hr2, false) //suppose to return true
      .CHECK_EQUAL(hr2 != sec7200, false) // suppose to return true
      //.CHECK_THROWS(hr2 != km2a)

      .setname("TEST TIME UNITS GREATER (>)")
      .CHECK_EQUAL(PhysicalNumber(121, Unit::MIN) > hr2, true) // suppose to return true to all
      .CHECK_EQUAL(hr2 > hr2, false) //
      .CHECK_EQUAL(min60 > min30d, true) //
      .CHECK_EQUAL(min60 > hr2, false) //
      //.CHECK_THROWS(min30d > km2a)

      .setname("TEST TIME UNITS LESSER (<)")
      .CHECK_OK(istringstream("2[hour]") >> hr2c)
      .CHECK_OK(istringstream("2[hour]") >> hr2)
      .CHECK_OK(istringstream("30[min]") >> min30d)
      .CHECK_OK(istringstream("60[min]") >> min60)
      .CHECK_OK(istringstream("7200[sec]") >> sec7200)
      .CHECK_EQUAL(hr2c < hr2, false) //both equals 2 hours
      .CHECK_EQUAL(min30d < hr2c, true) //min30d =30min , hr2c = 2hr
      .CHECK_EQUAL(min60 < hr2, true)
      .CHECK_EQUAL(sec7200 < hr2, false) 
      //.CHECK_THROWS(km2a < min30d)

      .setname("TEST TIME UNITS COMPARISON GREATER (>=)")
      .CHECK_EQUAL(hr2c >= hr2, true) //both equals
      .CHECK_EQUAL(min60 >= min30d, true) //min30d is 30min
      .CHECK_EQUAL(sec7200 >= hr2, true) //suppose to return true
      .CHECK_EQUAL(min120 >= min60, true)
      //.CHECK_THROWS(hr2 >= km2)

      .setname("TEST TIME UNITS COMPARISON LESSER (<=)")
      .CHECK_EQUAL(hr2c <= hr2, true) //both equals
      .CHECK_EQUAL(min60 <= min30d, false) //min30d is 30min
      .CHECK_EQUAL(sec7200 <= hr2, true) //suppose to return true
      .CHECK_EQUAL(min120 <= min60, false)
      //.CHECK_THROWS(hr2 <= km2)

      .setname("TEST TIME UNITS ADDITION OP (+)")
      .CHECK_EQUAL(hr2 + hr2, PhysicalNumber(4, Unit::HOUR)) //suppose to return true
      .CHECK_EQUAL(hr2 + min60, PhysicalNumber(3, Unit::HOUR))
      .CHECK_EQUAL(hr2 + min30d, PhysicalNumber(2.5, Unit::HOUR))
      .CHECK_EQUAL(min120 + sec7200, PhysicalNumber(240, Unit::MIN))
      .CHECK_THROWS(hr2 + km05)
      .CHECK_THROWS(min120 + PhysicalNumber(3, Unit::KM))
      .setname("TEST TIME UNITS ADDTIONEQ OP (+=)")
      .CHECK_OUTPUT((hr2 += hr2), "4[hour]")
      .CHECK_OUTPUT((sec7200 += PhysicalNumber(120, Unit::MIN)), "14400[sec]") //NOTICE: not sure about the string syntax "[sec]""
      .CHECK_OUTPUT((min60 += PhysicalNumber(30, Unit::MIN)), "90[min]")       // (min60 = 90)
      .CHECK_OUTPUT((min120 += hr2), "360[min]")                               // (min120 = 360min)
      .CHECK_THROWS(min120 += km05)
      .CHECK_THROWS(hr2 += km05)
      .setname("TEST TIME UNTIS SUBSCTRACTION OP (-)")
      .CHECK_OUTPUT((hr2 - PhysicalNumber(30, Unit::MIN)), "3.5[hour]")
      .CHECK_OUTPUT((hr2 - hr2), "0[hour]")
      .CHECK_OUTPUT((sec7200 - PhysicalNumber(60, Unit::MIN)), "10800[sec]")
      .CHECK_OUTPUT((min120 - PhysicalNumber(30, Unit::MIN)), "330[min]")
      .CHECK_THROWS(min120 - km05)
      .CHECK_THROWS(sec7200 - km05)
      .setname("TEST TIME UNTIS SUBSCTRACTIONEQ OP (-=)")
      .CHECK_OUTPUT((hr2 -= PhysicalNumber(30, Unit::MIN)), "3.5[hour]") // hr2 = 3.5hour
      .CHECK_OUTPUT((hr2 -= hr2), "0[hour]")
      .CHECK_OUTPUT((sec7200 -= PhysicalNumber(60, Unit::MIN)), "10800[sec]")
      .CHECK_EQUAL(sec7200, PhysicalNumber(10800, Unit::SEC))
      .CHECK_OUTPUT((min120 -= PhysicalNumber(30, Unit::MIN)), "330[min]")
      .CHECK_THROWS(min120 -= km05)
      .CHECK_THROWS(sec7200 -= km05)
      .setname("TEST TIME UNTIS SUBSCTRACTION UNARY OP (-..)")
      // .CHECK_OUTPUT((),"[]")
      // .CHECK_OUTPUT((),"[]")
      // .CHECK_OUTPUT((),"[]")
      // .CHECK_OUTPUT((),"[]")
      //  .CHECK_THROWS()
      .setname("TEST TIME UNTIS POSTFIX INCREMENT (..++)")
      .CHECK_OUTPUT((hr2++), "0[hour]")
      .CHECK_OUTPUT((hr2), "1[hour]")
      .CHECK_OUTPUT((sec7200++), "10800[sec]")
      .CHECK_OUTPUT((sec7200), "10801[sec]")
      .CHECK_OUTPUT((min60++), "90[min]")
      .CHECK_OUTPUT((min60), "91[min]")
      .setname("TEST TIME UNTIS PREFIX INCREMENT (++..)")
      .CHECK_OUTPUT((++hr2), "2[hour]")
      .CHECK_OUTPUT((hr2), "2[hour]")
      .CHECK_OUTPUT(++(++sec7200), "10803[sec]")
      .CHECK_OUTPUT(sec7200, "10803[sec]")
      .CHECK_OUTPUT((++min60), "92[min]")
      .CHECK_OUTPUT((min60), "92[min]")

        .setname("///////////// MASS UNITS ///////////////////")

        //TON2 , TON1 , KG2000 , KG500 ,G2000000 , G1000
        // TEST MASS UNITS COMPARISON (=)
        .CHECK_EQUAL(ton2 == ton1, false)
        .CHECK_EQUAL(ton2 == kg2000, true)
        .CHECK_EQUAL(g2000000 == kg2000, true)
        .CHECK_EQUAL(g1000 == ton1, false)
        .CHECK_THROWS(ton1 == hr2)

        // TEST MASS UNITS COMPARISON (NOT) (!=)
        .CHECK_EQUAL(ton2 != ton1, true)
        .CHECK_EQUAL(ton2 != kg2000, false)
        .CHECK_EQUAL(g2000000 != kg2000, false)
        .CHECK_EQUAL(g1000 != ton1, true)
        .CHECK_THROWS(ton1 != hr2)
        // TEST MASS UNITS GREATER (>)
        .CHECK_EQUAL(kg500 > ton2, false)
        .CHECK_EQUAL(ton2 > ton2, false)
        .CHECK_EQUAL(ton1 > g1000, true)
        .CHECK_EQUAL(kg2000 > kg500, true)
        .CHECK_THROWS(g2000000 > min30d)
        // TEST MASS UNITS LESSER (<)
        .CHECK_EQUAL(kg500 < ton2, true)
        .CHECK_EQUAL(ton2 < ton2, false)
        .CHECK_EQUAL(ton1 < g1000, false)
        .CHECK_EQUAL(kg2000 < kg500, false)
        .CHECK_THROWS(kg2000 < min30d)
        // TEST MASS UNITS COMPARISON GREATER (>=)
        .CHECK_EQUAL(g1000 >= kg2000, false)
        .CHECK_EQUAL(ton1 >= ton1, true)
        .CHECK_EQUAL(kg500 >= g1000, true)
        .CHECK_EQUAL(ton2 >= g2000000, true)
        .CHECK_THROWS(ton2 >= hr2)
        // TEST MASS UNITS COMPARISON LESSER (<=)
        .CHECK_EQUAL(g1000 <= kg2000, true)
        .CHECK_EQUAL(ton1 <= ton1, true)
        .CHECK_EQUAL(kg500 <= g1000, false)
        .CHECK_EQUAL(ton2 <= g2000000, true)
        .CHECK_THROWS(ton2 <= hr2)
        // TEST MASS UNITS ADDITION OP (+)
        .CHECK_OUTPUT(ton1 + ton1, "2[ton]")
        .CHECK_OUTPUT(kg2000 + ton1, "3000[kg]")
        .CHECK_OUTPUT(ton2 + g1000, "2.001[ton]")
        .CHECK_OUTPUT(kg500 + ton1, "1500[kg]")
        .CHECK_THROWS(kg500 + min30d)
        // TEST MASS UNITS ADDTIONEQ OP (+=)
        .CHECK_OUTPUT((ton1 += ton1), "2[ton]")
        .CHECK_OUTPUT((kg2000 += ton1), "4000[kg]")
        .CHECK_OUTPUT((g1000 += PhysicalNumber(150, Unit::G)), "1150[g]")
        .CHECK_OUTPUT((kg500 += ton1), "2500[kg]")
        .CHECK_THROWS(kg500 += hr2)
        // TEST MASS UNTIS ADDITION UNARY OP (+..)
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_THROWS()

        //<name> = <actual value>
        //ton1 = 2ton , ton2=ton2 ,kg2000= 4000kg , kg500= 2500kg , g1000=2001000  ,g2000000
        // TEST MASS UNTIS SUBSCTRACTION OP (-)
        .CHECK_OUTPUT(ton1 - ton2, "0[ton]")
        .CHECK_OUTPUT(g2000000 - PhysicalNumber(1998850, Unit::G), "1150[g]")
        .CHECK_OUTPUT(kg2000 - ton2, "2000[kg]")
        .CHECK_OUTPUT(kg2000 - PhysicalNumber(1000, Unit::G), "3999[kg]")
        .CHECK_THROWS(ton2 - hr2)

        //<name> = <actual value>
        //ton1 = 2ton , ton2=ton 2 ,kg2000= 4000kg , kg500= 2500kg , g1000=2001000  ,g2000000 = 2000000
        // TEST MASS UNTIS SUBSCTRACTIONEQ OP (-=)
        .CHECK_OUTPUT((ton2 -= ton1), "0[ton]")
        .CHECK_OUTPUT((g2000000 -= PhysicalNumber(1998850, Unit::G)), "1150[g]")
        .CHECK_OUTPUT((kg2000 -= ton2), "4000[kg]")
        .CHECK_OUTPUT((kg2000 -= PhysicalNumber(1000, Unit::G)), "3999[kg]")
        .CHECK_THROWS(ton2 -= hr2)

        //<name> = <actual value>
        //ton2= 0 ton , ton1 = 2 ton, kg2000 = 3000 ,kg500 =2500 , g200000=2000000, g1000=1000
        // TEST MASS UNTIS SUBSCTRACTION UNARY OP (-..)
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_OUTPUT(,"[]")
        // .CHECK_THROWS()

        //<name>=<actual value>
        ////ton2= 0 ton , ton1 = 2 ton, kg2000 = 3000 ,kg500 =2500 , g200000=2000000, g1000=1000
        // TEST MASS UNTIS POSTFIX INCREMENT (..++)
        .CHECK_OUTPUT(kg2000++, "3999[kg]")
        .CHECK_OUTPUT(kg2000, "4000[kg]")
        .CHECK_OUTPUT(ton1++, "2[ton]")
        .CHECK_OUTPUT(ton1, "3[ton]")
        .CHECK_OUTPUT(g1000++, "1150[g]")
        .CHECK_OUTPUT(g1000, "1151[g]")
        //.CHECK_OUTPUT(kg500++++++++,"2500[kg]")
        //.CHECK_OUTPUT(ton2++++++++++,"0[ton]")

        //<name> = <actual value>
        //ton2 = 5 ton , ton1 =3 ton ,kg2000= 3001 kg ,kg500 = 2504 kg , g1000= 1001 g ,g2000000=2000000
        // TEST MASS UNTIS PREFIX INCREMENT (++..)
        .CHECK_OUTPUT(++kg2000, "4001[kg]")
        .CHECK_OUTPUT(kg2000, "4001[kg]")
        .CHECK_OUTPUT(++ton1, "4[ton]")
        .CHECK_OUTPUT(++g1000, "1152[g]")
        //.CHECK_OUTPUT(++++++++kg500,"2508[kg]")
        //.CHECK_OUTPUT(++++++++++ton2,"10[ton]")

        // Netanel Davidov and Maxim Mermer: https://github.com/netanel208/PhysicalNumber-cpp
    .setname("Operator '+' binary - Compatible dimensions")
    .CHECK_OUTPUT(cm2a+km3a, "300002[cm]")                             //2[cm] + 3[km]
    .CHECK_OUTPUT(cm2a+m4a, "402[cm]")                                //2[cm] + 4[m]
    .CHECK_OUTPUT(cm2a+km01a, "10002[cm]")                              //2[cm] + 0.1[km]
    .CHECK_OUTPUT(km3a+cm2a, "3.00002[km]")                            //3[km] + 2[cm]
    .CHECK_OUTPUT(sec2b+min3b, "182[sec]")                               //2[sec] + 3[min]
    .CHECK_OUTPUT(sec2b+hr4b, "14402[sec]")                             //2[sec] + 4[hour]
    .CHECK_OUTPUT(sec2b+hr01b, "362[sec]")                               //2[sec] + 0.1[hour]
    .CHECK_OUTPUT(hr4b+min3b, "4.05[hour]")                             //4[hour] + 3[min]
    .CHECK_OUTPUT(g2c+kg3c, "3002[g]")                                //2[g] + 3[kg]
    .CHECK_OUTPUT(g2c+ton4c, "4e+06[g]")                             //2[g] + 4[ton]
    .CHECK_OUTPUT(g2c+ton01c, "100002[g]")                              //2[g] + 0.1[ton]
    .CHECK_OUTPUT(kg3c+g2c, "3.002[kg]")                              //3[kg] + 2[g]


    .setname("Operator '+' binary - Incompatible dimensions")
    .CHECK_THROWS(cm2a+sec2b)
    .CHECK_THROWS(sec2b+g2c)
    .CHECK_THROWS(g2c+cm2a)
    .CHECK_THROWS(km3a+kg3c)


    .setname("Operator '-' binary - Compatible dimensions")
    .CHECK_OUTPUT(km3a-cm2a, "2.99998[km]")
    .CHECK_OUTPUT(m4a-cm2a, "3.98[m]")                                //4[m] - 2[cm]
    .CHECK_OUTPUT(km01a-cm2a, "0.09998[km]")                            //0.1[km] - 2[cm]
    .CHECK_OUTPUT(cm2a-km3a, "-299998[cm]")                            //2[cm] - 3[km]
    .CHECK_OUTPUT(min3b-sec2b, "2.96667[min]")                      //3[min] - 2[sec]
    .CHECK_OUTPUT(hr4b-sec2b, "3.99944[hour]")                     //4[hour] - 2[sec]
    .CHECK_OUTPUT(hr01b-sec2b, "0.0994444[hour]")                     //0.1[hour] - 2[sec]
    .CHECK_OUTPUT(hr4b-min3b, "3.95[hour]")                             //4[hour] - 3[min]


    .setname("Operator '-' binary - Incompatible dimensions")
    .CHECK_THROWS(cm2a-sec2b)
    .CHECK_THROWS(sec2b-g2c)
    .CHECK_THROWS(g2c-cm2a)
    .CHECK_THROWS(km3a-kg3c)


    .setname("Operator '+=' binary - Compatible dimensions")
    .CHECK_OUTPUT((cm2a+=km3a), "300002[cm]")                             //cm2a = 2[cm] + 3[km]
    .CHECK_OUTPUT((sec2b+=hr4b), "14402[sec]")                             //sec2b = 2[sec] + 4[hour]
    .CHECK_OUTPUT((hr4b+=min3b), "4.05[hour]")                             //hr4b = 4[hour] + 3[min]
    .CHECK_OUTPUT((g2c+=ton01c), "100002[g]")                              //g2c = 2[g] + 0.1[ton]
    .CHECK_OUTPUT((kg3c+=kg3c), "6[kg]")                                  //kg3c = 3[kg] + 3[kg]


    .setname("Operator '+=' binary - Incompatible dimensions")
    .CHECK_THROWS(cm2a+=sec2b)
    .CHECK_THROWS(sec2b+=g2c)
    .CHECK_THROWS(g2c+=cm2a)
    .CHECK_THROWS(km3a+=kg3c)


    .setname("Operator '-=' binary - Compatible dimensions")
    .CHECK_OUTPUT((cm2a-=km3a), "2[cm]")                                  //cm2a = 300002[cm] - 300000[cm]
    .CHECK_OUTPUT((sec2b-=hr4b), "-178[sec]")                                 //sec2b = 4[hour] + 2[sec] - 4[hour] - 3[min]
    .CHECK_OUTPUT((hr4b-=min3b), "4[hour]")                                //hr4b = 4.05[hour] - 3[min]
    .CHECK_OUTPUT((g2c-=ton01c), "2[g]")                                   //g2c = 100002[g] - 0.1[ton]
    .CHECK_OUTPUT((kg3c-=kg3c), "0[kg]")                                  //kg3c = 6[kg] - 6[kg]


    .setname("Operator '-=' binary - Incompatible dimensions")
    .CHECK_THROWS(cm2a-=sec2b)
    .CHECK_THROWS(sec2b-=g2c)
    .CHECK_THROWS(g2c-=cm2a)
    .CHECK_THROWS(km3a-=kg3c)


    .CHECK_OUTPUT((kg3c=PhysicalNumber(3,Unit::KG)), "3[kg]")           //return kg3c to previous value


    .setname("Operator '==' binary - Compatible dimensions")
    .CHECK_EQUAL(cm2a==cm2a,true)                                         
    .CHECK_EQUAL(km3a==PhysicalNumber(3000,Unit::M),true)               //3[km] == 3000[m]                                      
    .CHECK_EQUAL(m4a==PhysicalNumber(0.004,Unit::KM),true)             //4[m] == 0.004[km]                            
    .CHECK_EQUAL(sec2b==sec2b,true)
    .CHECK_EQUAL(min3b==PhysicalNumber(180,Unit::SEC),true)              //3[min] == 180[sec]
    .CHECK_EQUAL(min3b==PhysicalNumber(0.05,Unit::HOUR),true)            //3[min] == 0.05[hour]


    .setname("Operator '!=' binary - Compatible dimensions")
    .CHECK_EQUAL(cm2a!=km3a,true)                                         //2[cm] != 3[km]                                         
    .CHECK_EQUAL(m4a!=PhysicalNumber(3000,Unit::M),true)               //4[m] != 3000[m]                                      
    .CHECK_EQUAL(km01a!=PhysicalNumber(0.004,Unit::KM),true)             //0.1[km] != 0.004[km]                            
    .CHECK_EQUAL(sec2b!=min3b,true)                                         //2[sec] != 3[min]
    .CHECK_EQUAL(hr4b!=PhysicalNumber(180,Unit::SEC),true)              //4[hour] != 180[sec]
    .CHECK_EQUAL(hr01b!=PhysicalNumber(0.05,Unit::HOUR),true)            //0.1[hour] != 0.05[hour]


    .setname("Operator '==','!=' binary - Incompatible dimensions")
    .CHECK_THROWS(cm2a==sec2b)
    .CHECK_THROWS(sec2b==g2c)
    .CHECK_THROWS(g2c!=cm2a)
    .CHECK_THROWS(km3a!=kg3c)


    .setname("Operator '<=' binary - Compatible dimensions")
    .CHECK_EQUAL(cm2a<=cm2a,true)                                         //2[cm] <= 2[cm]
    .CHECK_EQUAL(cm2a<=km3a,true)                                         //2[cm] <= 3[km]                                         
    .CHECK_EQUAL(km01a<=km3a,true)                                         //0.1[km] <= 3[km]
    .CHECK_EQUAL(hr01b<=hr4b,true)                                         //0.1[hour] <= 4[hour]
    .CHECK_EQUAL(hr01b<=PhysicalNumber(10,Unit::MIN),true)               //0.1[hour] <= 10[min]
    .CHECK_EQUAL(kg3c<=ton4c,true)                                         //3[kg] <= 4[ton]
    .CHECK_EQUAL(g2c<=ton01c,true)                                         //2[g] <= 0.1[ton]
    

    .setname("Operator '>=' binary - Compatible dimensions")
    .CHECK_EQUAL(cm2a>=cm2a,true)                                         //2[cm] >= 2[cm]
    .CHECK_EQUAL(km3a>=cm2a,true)                                         //3[km]  >= 2[cm]                                        
    .CHECK_EQUAL(km3a>=km01a,true)                                         //3[km] >= 0.1[km]
    .CHECK_EQUAL(hr4b>=hr01b,true)                                         //4[hour] >= 0.1[hour]
    .CHECK_EQUAL(PhysicalNumber(10,Unit::MIN)>=hr01b,true)               //10[min] >= 0.1[hour]
    .CHECK_EQUAL(ton4c>=kg3c,true)                                         //4[ton] >= 3[kg]
    .CHECK_EQUAL(ton01c>=g2c,true)                                         //0.1[ton] >= 2[g]


    .setname("Operator '<=','>=' binary - Incompatible dimensions")
    .CHECK_THROWS(cm2a<=sec2b)
    .CHECK_THROWS(sec2b>=g2c)
    .CHECK_THROWS(g2c>=cm2a)
    .CHECK_THROWS(km3a<=kg3c)


    .setname("Operator '<' binary - Compatible dimensions")
    .CHECK_EQUAL(cm2a<cm2a,false)                                         //2[cm] !< 2[cm]
    .CHECK_EQUAL(cm2a<km3a,true)                                          //2[cm] < 3[km]                                         
    .CHECK_EQUAL(km01a<km3a,true)                                          //0.1[km] < 3[km]
    .CHECK_EQUAL(hr01b<hr4b,true)                                          //0.1[hour] < 4[hour]
    .CHECK_EQUAL(hr01b<PhysicalNumber(10,Unit::MIN),true)                //0.1[hour] < 10[min]
    .CHECK_EQUAL(kg3c<ton4c,true)                                          //3[kg] < 4[ton]
    .CHECK_EQUAL(g2c<ton01c,true)                                          //2[g] < 0.1[ton]


    .setname("Operator '>' binary - Compatible dimensions")
    .CHECK_EQUAL(cm2a>cm2a,false)                                         //2[cm] !> 2[cm]
    .CHECK_EQUAL(km3a>cm2a,true)                                          //3[km] > 2[cm]                                        
    .CHECK_EQUAL(km3a>km01a,true)                                          //3[km] > 0.1[km]
    .CHECK_EQUAL(hr4b>hr01b,true)                                          //4[hour] > 0.1[hour]
    .CHECK_EQUAL(PhysicalNumber(10,Unit::MIN)>hr01b,true)                //10[min] > 0.1[hour]
    .CHECK_EQUAL(ton4c>kg3c,true)                                          //4[ton] > 3[kg]
    .CHECK_EQUAL(ton01c>g2c,true)                                          //0.1[ton] > 2[g]


    .setname("Operator '++(postfix)' unary - Compatible dimensions")
    .CHECK_OUTPUT(cm2a++,"2[cm]")                                       //2[cm]++ = 3[cm]
    .CHECK_OUTPUT(km3a++,"3[km]")                                       //3[km]++ = 4[cm]
    .CHECK_OUTPUT(m4a++,"4[m]")                                        //4[m]++ = 5[m]
    .CHECK_OUTPUT(km01a++,"0.1[km]")                                     //0.1[km]++ = 1.1[km]

    
    .setname("Operator '--(postfix)' unary - Compatible dimensions")
    .CHECK_OUTPUT(cm2a--,"3[cm]")                                       //3[cm]-- = 2[cm]
    .CHECK_OUTPUT(km3a--,"4[km]")                                       //4[km]-- = 3[cm]
    .CHECK_OUTPUT(m4a--,"5[m]")                                        //5[m]-- = 4[m]
    .CHECK_OUTPUT(km01a--,"1.1[km]")                                     //1.1[km]-- = 0.1[km]


    .setname("Operator '(prefix)++' unary - Compatible dimensions")
    .CHECK_OUTPUT(++cm2a,"3[cm]")                                       //++2[cm] = 3[cm]
    .CHECK_OUTPUT(++km3a,"4[km]")                                       //++3[km] = 4[cm]
    .CHECK_OUTPUT(++m4a,"5[m]")                                        //++4[m] = 5[m]
    .CHECK_OUTPUT(++km01a,"1.1[km]")                                     //++0.1[km] = 1.1[km]


    .setname("Operator '(prefix)--' unary - Compatible dimensions")
    .CHECK_OUTPUT(--cm2a,"2[cm]")                                       //--3[cm] = 2[cm]
    .CHECK_OUTPUT(--km3a,"3[km]")                                       //--4[km] = 3[cm]
    .CHECK_OUTPUT(--m4a,"4[m]")                                        //--5[m] = 4[m]
    .CHECK_OUTPUT(--km01a,"0.1[km]")                                     //--1.1[km] = 0.1[km]


    .setname("Operator '+' unary - Compatible dimensions")
    .CHECK_EQUAL(+cm2a,PhysicalNumber(2,Unit::CM))                           //+2[cm] = 2[cm]
    // .CHECK_EQUAL(+PhysicalNumber(-2,Unit::CM),PhysicalNumber(2,Unit::CM))  //+(-2)[cm] = 2[cm]
    .CHECK_EQUAL(+PhysicalNumber(0,Unit::MIN),PhysicalNumber(0,Unit::MIN)) //+0[cm] = 0[cm]


    .setname("Operator '-' unary - Compatible dimensions")
    .CHECK_EQUAL(-PhysicalNumber(1,Unit::MIN),PhysicalNumber(-1,Unit::MIN))//-1[min] = -1[min]
    .CHECK_EQUAL(-kg3c,PhysicalNumber(-3,Unit::KG))                          //-3[kg] = -3[kg]
    .CHECK_OUTPUT(-km01a,"-0.1[km]")                        //-0.1[km] = -0.1[km]


    .setname("Input - Compatible dimensions")
    .CHECK_OK(istringstream("700[kg]") >> g100x)
    .CHECK_OUTPUT(g100x,"700[kg]")
    .CHECK_OK(istringstream("20[hour]") >> hr2y)
    .CHECK_OUTPUT(hr2y,"20[hour]")
    .CHECK_OK(istringstream("5[m]") >> m10z)
    .CHECK_OUTPUT(m10z,"5[m]")
    .CHECK_OK(istringstream("700[kg]") >> hr2y)
    .CHECK_OUTPUT(hr2y,"700[kg]")
    .CHECK_OK(istringstream("700[kg]") >> m10z)
    .CHECK_OUTPUT(m10z,"700[kg]")
    .CHECK_OK(istringstream("5[m]") >> hr2y)
    .CHECK_OUTPUT(hr2y,"5[m]")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  grade << " " << "bayHogkjxySS7cqMI54xjKiuF4l2_5" << endl;
    return 0;
}
