// 
// File:   stp7TestSuite.h
// Author: erik
//
// Created on 28. April 2007, 16:07
//

#ifndef _stp7TestSuite_H
#define	_stp7TestSuite_H

#include "stp7.h"
#include <cxxtest/TestSuite.h>

class Stp7TestSuite: public CxxTest::TestSuite {
public:
    void testBasics( void ) {
        Stp7 stp;
        TS_ASSERT_DIFFERS(stp.toString(), "");
        TS_ASSERT_THROWS_NOTHING(stp.planFastestProfile(0, 30, 0, 6, 0, 4, 2));
        TS_ASSERT_DIFFERS(stp.toString(), "");
        TS_ASSERT_DELTA(stp.getDuration(), 8.46,0.01);
        TS_ASSERT_DELTA(stp.pos(8.46),30,0.05);
        TS_ASSERT_DELTA(stp.vel(8.46),0,0.1);
        TS_ASSERT_DELTA(stp.acc(8.46),0,0.1);
    };
    
    void testCruiseProfilesStandard(void) {
        Stp7 stp;
        // TT profile
        stp.planFastestProfile(-5,5,0,3,0,2,2);
        TS_ASSERT_DELTA(stp.getDuration(),5.8333,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TT);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // TW profile
        stp.planFastestProfile(-5,6,-1,3,1.5,2,1.25);
        TS_ASSERT_DELTA(stp.getDuration(),6.6834,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),6,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // WT profile
        stp.planFastestProfile(-5,5,2,3,0,2,2);
        TS_ASSERT_DELTA(stp.getDuration(),4.8190,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WT);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // WW profile
        stp.planFastestProfile(-4,4,0,2,0,2,1);
        TS_ASSERT_DELTA(stp.getDuration(),6.8284,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
    }
    
    void testCruiseProfilesSpecial(void) {
        Stp7 stp;
        // a0>amax, double deceleration, TT
        stp.planFastestProfile(-3,3,-2,2,3,1.5,2);
        TS_ASSERT_DELTA(stp.getDuration(),6.0990,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),3,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TT);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
        
        // a(1.5)>amax, double deceleration, WW
        stp.planFastestProfile(-4,4,1.5,2,1.5,2,1.5);
        TS_ASSERT_DELTA(stp.getDuration(),5.1037,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
        
        // a0>amax, double deceleration, WW
        stp.planFastestProfile(-4,4,1,2,2.5,2,2);
        TS_ASSERT_DELTA(stp.getDuration(),4.8248,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
    }
    
    void testNoCruiseProfilesStandard(void) {
        Stp7 stp;
        
        // WW profile
        stp.planFastestProfile(4,-4,0,3,0,2,1);
        TS_ASSERT_DELTA(stp.getDuration(),6.3496,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),-4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // TW profile
        stp.planFastestProfile(0,10,15,12,-5,8,4);
        TS_ASSERT_DELTA(stp.getDuration(),5.291,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),10,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // TT profile
        stp.planFastestProfile(-4,4,0,4,0,3,4);
        // calc7st(4,4,3,4,0,0,-4,true);
        TS_ASSERT_DELTA(stp.getDuration(),4.1010,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TT);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // WT profile
        stp.planFastestProfile(-10,4,4.5,5,0.2,2,1);
        TS_ASSERT_DELTA(stp.getDuration(),5.1591,0.0001);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WT);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
    }
    
    void testNoCruiseProfileDoubleDec(void) {
        Stp7 stp;
        
        // WW profile
        // calc7st(4.228053, 0.857550, 1.727873, 3.105438, -0.2, 5, -10.239185,true);
        stp.planFastestProfile(-10.239185,4.228053,5,3.105438,-0.2,1.727873,0.857550);
        TS_ASSERT_DELTA(stp.getDuration(),5.7485,1e-4);
        TS_ASSERT_DELTA(stp.pos(100),4.228053,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
        
        // TW profile
        // calc7st(4, 3,2,1, 4,0.5, -3, true);
        stp.planFastestProfile(-3,4,0.5,1,4,2,3);
        TS_ASSERT_DELTA(stp.getDuration(),3.9662,1e-4);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
                
        // WT profile
        // calc7st(4.228053, 0.857550, 1.727873, 3.105438, 0.2, 5, -10.239185,true)
        stp.planFastestProfile(-10.239185,4.228053,5,3.105438,0.2,1.727873, 0.857550);
        TS_ASSERT_DELTA(stp.getDuration(),5.42855,1e-4);
        TS_ASSERT_DELTA(stp.pos(100),4.228053,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WT);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
        
        // TT profile
        // calc7st(3.7, 3,2,1, 4,0.5, -3, true);
        stp.planFastestProfile(-3,3.7,0.5,1,4,2,3);
        TS_ASSERT_DELTA(stp.getDuration(),3.6613,1e-4);
        TS_ASSERT_DELTA(stp.pos(100),3.7,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TT);
        TS_ASSERT(!stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
    }
    
    void testCruiseProfileStretched(void) {
        Stp7 stp;
        
        // TcT ==> TcT
        //[t,j] = calc7st(5,2,2,3,0,0,-5);
        //stretch7st(t,j,6.5,5,2,2,3,0,0,-5,true);
        stp.planFastestProfile(-5,5,0,3,0,2,2);
        stp.scaleToDuration(6.5);
        TS_ASSERT_DELTA(stp.getDuration(),6.5,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TT);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
   
        // TcT ==> WcW
        //[t,j] = calc7st(5,2,2,3,0,0,-5);
        //stretch7st(t,j,10,5,2,2,3,0,0,-5,true);
        stp.planFastestProfile(-5,5,0,3,0,2,2);
        stp.scaleToDuration(10);
        TS_ASSERT_DELTA(stp.getDuration(),10,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // TcT, a0 ==> TcW, a0
        //[t,j] = calc7st(3,2,1.5,2,3,-2,-3);
        //stretch7st(t,j,10,3,2,1.5,2,3,-2,-3,true); 
        stp.planFastestProfile(-3,3,-2,2,3,1.5,2);
        stp.scaleToDuration(10);
        TS_ASSERT_DELTA(stp.getDuration(),10,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),3,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // WcT ==> WcT
        //[t,j] = calc7st(5,2,2,3,0,2,-5);
        //stretch7st(t,j,5,5,2,2,3,0,2,-5,true);
        stp.planFastestProfile(-5,5,2,3,0,2,2);
        stp.scaleToDuration(5);
        TS_ASSERT_DELTA(stp.getDuration(),5,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WT);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
    }

    void testDoubleDecProfileStretched() {
        Stp7 stp;
   
        // WcW, ddec ==> WcW, ddec
        //[t,j] = calc7st(4,2,2,2,2.5,1,-4);
        //stretch7st(t,j,5,4,2,2,2,2.5,1,-4, true);
        stp.planFastestProfile(-4,4,1,2,2.5,2,2);
        stp.scaleToDuration(5);
        TS_ASSERT_DELTA(stp.getDuration(),5,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());

        // WcT ==> WcW ddec
        //[t,j] = calc7st(5,2,2,3,0,2,-5);
        //stretch7st(t,j,6.5,5,2,2,3,0,2,-5,bPlot);
        stp.planFastestProfile(-5,5,2,3,0,2,2);
        stp.scaleToDuration(6.5);
        TS_ASSERT_DELTA(stp.getDuration(),6.5,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile()); 
        
        // TcT, a0 ==> ddec WcW
        //[t,j] = calc7st(3,2,1.5,2,3,-2,-3);
        //stretch7st(t,j,30,3,2,1.5,2,3,-2,-3,bPlot);
        stp.planFastestProfile(-3,3,-2,2,3,1.5,2);
        stp.scaleToDuration(30);
        TS_ASSERT_DELTA(stp.getDuration(),30,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),3,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
        
        // WcW, ddec ==> TcW, ddec
        //[t,j] = calc7st(4,2,2,2,2.5,1,-4);
        //stretch7st(t,j,10,4,2,2,2,2.5,1,-4, bPlot);
        stp.planFastestProfile(-4,4,1,2,2.5,2,2);
        stp.scaleToDuration(10);
        TS_ASSERT_DELTA(stp.getDuration(),10,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());     
    }
    
    void testNoCruiseProfileStretched() {
        Stp7 stp;
        
        // WW ==> WcW
        //[t,j] = calc7st(4,1,2,3,0,0,-4);
        //stretch7st(t,j,7,4,1,2,3,0,0,-4,true);
        stp.planFastestProfile(-4,4,0,3,0,2,1);
        stp.scaleToDuration(7);
        TS_ASSERT_DELTA(stp.getDuration(),7,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
        
        // TW, v0 ==> TcW, v0
        //[t,j] = calc7st(10, 4, 8, 12, -5, 15, 0, true);
        //stretch7st(t, j, 5.5, 10, 4, 8, 12, -5, 15, 0, true);
        stp.planFastestProfile(0,10,15,12,-5,8,4);
        stp.scaleToDuration(5.5);
        TS_ASSERT_DELTA(stp.getDuration(),5.5,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),10,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());        
        
        // TT ==> WcW
        //[t,j] = calc7st(4,4,3,4,0,0,-4);
        //stretch7st(t,j,6,4,4,3,4,0,0,-4,bPlot);
        stp.planFastestProfile(-4,4,0,4,0,3,4);
        stp.scaleToDuration(6);
        TS_ASSERT_DELTA(stp.getDuration(),6,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),4,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(!stp.isDoubleDecProfile());
    }
    
    void _testProblemCasesStretched() {
        Stp7 stp;
        
        TS_WARN("Only tests whether the right TYPE of profile was found.");
        
        // WT ddec ==> TcW ddec
        // PROBLEM: results in WcW breaking the amax limit
        //[t,j] = calc7st(4.5, 0.8, 1.7, 3, 0.2, 5, -10);
        //stretch7st(t,j,6,4.5, 0.8, 1.7, 3, 0.2, 5, -10, bPlot);
        stp.planFastestProfile(-10,4.5,5,3,0.2,1.7,0.8);
        stp.scaleToDuration(6);
        TS_ASSERT_DELTA(stp.getDuration(),6,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),4.5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
        
        // WT ddec ==> WcT ddec
        // PROBLEM: results in WcW breaking the amax limit
        //[t,j] = calc7st(4.5, 0.8, 1.7, 3, 0.2, 5, -10);
        //stretch7st(t,j,5.5,4.5, 0.8, 1.7, 3, 0.2, 5, -10, bPlot);
        stp.planFastestProfile(-10,4.5,5,3,0.2,1.7,0.8);
        stp.scaleToDuration(5.5);
        TS_ASSERT_DELTA(stp.getDuration(),5.5,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),4.5,1e-6);
        TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_WT);
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile()); 
        
        // TT, ddec ==> ???
        // PROBLEM: finds no solution
        //[t,j] = calc7st(10, 0.8, 1.5, 3, -0.1, 6.5, -10);
        //stretch7st(t,j,7,10, 0.8, 1.5, 3, -0.1, 6.5, -10, bPlot);
        stp.planFastestProfile(-10,10,6.5,3,-0.1,1.5,0.8);
        stp.scaleToDuration(7);
        TS_ASSERT_DELTA(stp.getDuration(),7,1e-6);
        TS_ASSERT_DELTA(stp.pos(100),10,1e-6);
        //???????????????
        //?? TS_ASSERT_EQUALS(stp.getProfileType(), Stp7::PROFILE_TW);
        //???????????????
        TS_ASSERT(stp.hasCruisingPhase());
        TS_ASSERT(stp.isDoubleDecProfile());
    }
};

#endif	/* _stp7TestSuite_H */

