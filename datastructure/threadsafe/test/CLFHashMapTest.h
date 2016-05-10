/*
 * CLFHashMapTest.h
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#ifndef CLFHASHMAPTEST_H_
#define CLFHASHMAPTEST_H_

#include "CLFHashMap.h"
#include "CLFStack.h"
#include "CLFHashMapTestObject.h"
#include <iostream>

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




#define A7CTESTASS(_exp) \
	if (_exp) \
	{ \
		cout<<"PASS: "<<#_exp<<endl; \
	} \
	else \
	{ \
		cout<<"FAIL: "<<#_exp<<endl; \
	}

class CLFHashMapTest
{
	public:
		CLFHashMapTest();
		virtual ~CLFHashMapTest();

		void run();

		void test_construction();

		void test_insert();
		void test_find();
		void test_remove();

		void test_concurrency();

		void test_destruction();


		CLFHashMap* mp_hashTable;
		static CLFHashMap* mp_sharedTable;

		static CLFHashMap* getSharedTable()
		{
			return mp_sharedTable;
		}

		CLFStack* mp_objPool;
		//static std::atomic<uint32_t> findFailed;

	private:
		CLFHashMapTestObject *mp_obj1, *mp_obj2, *mp_obj3;

};

#endif /* CLFHASHMAPTEST_H_ */
