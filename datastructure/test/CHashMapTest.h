/*
 * CHashMapTest.h
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#ifndef CHASHMAPTEST_H_
#define CHASHMAPTEST_H_

#include "CHashMap.h"
#include "CStack.h"
#include "CHashMapTestObject.h"
#include <iostream>
#include "a7c_test.h"

#define START_TIMER gettimeofday(&tBegin, NULL)
#define STOP_TIMER gettimeofday(&tEnd, NULL)

#define PRINT_INTERVAL \
    if(tEnd.tv_usec<tBegin.tv_usec) \
    { \
        tEnd.tv_usec += 1000000; \
        tEnd.tv_sec --; \
    } \
    if (tEnd.tv_sec < tBegin.tv_sec) \
    { \
        cout<<"ERROR"<<endl; \
    } \
    else \
    { \
        cout<<tEnd.tv_sec - tBegin.tv_sec<<":"<<tEnd.tv_usec - tBegin.tv_usec << endl; \
    }

#define STOP_TIMER_PRINT \
    STOP_TIMER; \
    PRINT_INTERVAL


#define TEST_TIMECOST(statement) \
    START_TIMER; \
    for (uint32_t i=0; i<loopTimes; i++) \
    { \
        statement; \
    } \
    STOP_TIMER_PRINT




class CHashMapTest : public a7common::TestCase
{
	public:
		CHashMapTest();
		virtual ~CHashMapTest();

		void run();

		void test_construction();

		void test_insert();
		void test_find();
		void test_remove();

		void test_destruction();


		CHashMap* mp_hashTable;


		CStack* mp_objPool;
		//static std::atomic<uint32_t> findFailed;

	private:
		CHashMapTestObject *mp_obj1, *mp_obj2, *mp_obj3;

};

#endif /* CHASHMAPTEST_H_ */
