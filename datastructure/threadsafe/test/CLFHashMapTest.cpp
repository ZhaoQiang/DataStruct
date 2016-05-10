/*
 * CLFHashMapTest.cpp
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#include "CLFHashMapTest.h"
#include "CLFHashMapTestObject.h"
#include "stdlib.h"
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <sys/time.h>


#define HASH_TABLE_SIZE_FUNC 1024
#define HASH_TABLE_SIZE_PERF 1048576 //2^20

using namespace std;

CLFHashMap* CLFHashMapTest::mp_sharedTable = NULL;
//std::atomic<uint32_t> CLFHashMapTest::findFailed = 0;

CLFHashMapTest::CLFHashMapTest() :
	mp_hashTable(0),
	mp_objPool(0),
	mp_obj1(0),
	mp_obj2(0),
	mp_obj3(0)

{
	// TODO Auto-generated constructor stub

}

CLFHashMapTest::~CLFHashMapTest()
{
	// TODO Auto-generated destructor stub
}

void CLFHashMapTest::run()
{
	test_construction();
	test_insert();
	test_find();
	test_remove();
	test_destruction();
}

void CLFHashMapTest::test_construction()
{
	mp_hashTable = new CLFHashMap(HASH_TABLE_SIZE_FUNC);
	mp_objPool = new CLFStack(HASH_TABLE_SIZE_FUNC);

	for (uint32_t i=0; i<mp_objPool->getCapability(); i++)
	{
		CLFHashMapTestObject* lp_obj = new CLFHashMapTestObject;
		mp_objPool->push(lp_obj);
	}
}

void CLFHashMapTest::test_destruction()
{
	//TODO: release objects
}

void CLFHashMapTest::test_insert()
{
	mp_obj1 = (CLFHashMapTestObject*)mp_objPool->pop();
	mp_obj2 = (CLFHashMapTestObject*)mp_objPool->pop();
	mp_obj3 = (CLFHashMapTestObject*)mp_objPool->pop();

	mp_obj1->setKey((uint8_t*)"obj1", 4);
	mp_obj2->setKey((uint8_t*)"obj2", 4);
	mp_obj3->setKey((uint8_t*)"object3", 7);

	mp_obj1->setValue((uint8_t*)"val1", 4);
	mp_obj2->setValue((uint8_t*)"val2", 4);
	mp_obj3->setValue((uint8_t*)"value3", 6);


	mp_hashTable->insert(mp_obj1);
	mp_hashTable->insert(mp_obj2);
	mp_hashTable->insert(mp_obj3);
}

void CLFHashMapTest::test_find()
{
	CLFHashMapTestObject findKeyObj;

	findKeyObj.setKey((uint8_t*)"obj2", 4);
	CLFHashMapTestObject* lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj2);

	findKeyObj.setKey((uint8_t*)"object3", 7);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj3);

	findKeyObj.setKey((uint8_t*)"obj1", 4);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj1);

	findKeyObj.setKey((uint8_t*)"object_not_exist", 16);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);


}

void CLFHashMapTest::test_remove()
{
	CLFHashMapTestObject findKeyObj;

	findKeyObj.setKey((uint8_t*)"obj2", 4);
	CLFHashMapTestObject* lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj2);

	CLFHashMapTestObject* lp_ret = (CLFHashMapTestObject*)mp_hashTable->remove(&findKeyObj);
	A7CTESTASS(lp_ret == mp_obj2);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);

	findKeyObj.setKey((uint8_t*)"object3", 7);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj3);

	lp_ret = (CLFHashMapTestObject*)mp_hashTable->remove(&findKeyObj);
	A7CTESTASS(lp_ret == mp_obj3);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);


	findKeyObj.setKey((uint8_t*)"obj1", 4);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj1);

	lp_ret = (CLFHashMapTestObject*)mp_hashTable->remove(&findKeyObj);
	A7CTESTASS(lp_ret == mp_obj1);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);


	mp_hashTable->insert(mp_obj2);
	findKeyObj.setKey((uint8_t*)"obj2", 4);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj2);

	findKeyObj.setKey((uint8_t*)"object_not_exist", 16);
	lp_find = (CLFHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);

}

void* insertThreadFun(void* arg)
{
	IHashable* lp_obj=NULL;
	CLFStack* lp_pool = (CLFStack*)arg;
	CLFHashMap* lp_sharedTable = CLFHashMapTest::getSharedTable();
	uint32_t index=0;
	while(lp_obj = (IHashable*)lp_pool->get(index++))
	{
		lp_sharedTable->insert(lp_obj);
	}
}

/*
void* findThreadFun(void* arg)
{
	IHashable* lp_obj=NULL, *lp_find = NULL;
	CLFStack* lp_pool = (CLFStack*)arg;
	CLFHashMap* lp_sharedTable = CLFHashMapTest::getSharedTable();
	uint32_t index=0;
	while(lp_obj = (IHashable*)lp_pool->get(index++))
	{
		lp_find = lp_sharedTable->find(lp_obj);
		if (lp_find != lp_obj)
		{
			CLFHashMapTest::findFailed.fetch_add(1);
		}
	}
}
*/

void CLFHashMapTest::test_concurrency()
{

	timeval tBegin, tEnd;
	uint32_t threadNum = 10;
	uint32_t objInsert = 100000;

	uint32_t hashSize = 2097152;

	CLFHashMapTest::mp_sharedTable = new CLFHashMap(hashSize);

	CLFStack **lp_objPools = new CLFStack*[10];

	cout<<"generating inserting data..."<<endl;
	for (uint32_t i=0; i<threadNum; i++)
	{
		lp_objPools[i]=new CLFStack(objInsert);
		for (uint32_t j=0; j<objInsert; j++)
		{
			CLFHashMapTestObject* lp_obj = new CLFHashMapTestObject;
			char tmp[10];
			sprintf(tmp, "%d", threadNum*j+i);

			lp_obj->setKey((uint8_t*)tmp, strlen(tmp));
			lp_obj->setValue((uint8_t*)tmp, strlen(tmp));
			lp_objPools[i]->push(lp_obj);
		}

	}

	cout<<"starting insert thread.."<<endl;
	pthread_t insert_ths[10];

	START_TIMER;
	for (uint32_t i=0; i<threadNum; i++)
	{
		pthread_t th;
		pthread_create(&insert_ths[i], NULL, insertThreadFun, lp_objPools[i]);

	}

	for (uint32_t i=0; i<threadNum; i++)
	{
		pthread_join(insert_ths[i], NULL);
	}
	STOP_TIMER;



	//cout<<"waiting 1s"<<endl;
	//sleep(1);

	cout<<"final hashtable size: "<<mp_sharedTable->size()<<endl;

	cout<<"Time cost ";
	PRINT_INTERVAL;

	cout<<"checking element inserted...";

	CLFHashMapTestObject findKeyObj, *lp_find=NULL;
	uint32_t failed=0;
	for (uint32_t i=0; i<threadNum*objInsert; i++)
	{
		char tmp[10];
		sprintf(tmp, "%d", i);

		findKeyObj.setKey((uint8_t*)tmp, strlen(tmp));
		lp_find = (CLFHashMapTestObject*)mp_sharedTable->find(&findKeyObj);
		if (lp_find == NULL)
		{
			failed++;
		}
	}
	if (failed==0)
	{
		cout<<"passed"<<endl;
	}
	else
	{
		cout<<"failed: "<<failed<<endl;
	}

/*
	cout<<"starting find thread.."<<endl;
	pthread_t find_ths[10];
	for (uint32_t i=0; i<threadNum; i++)
	{
		pthread_t th;
		pthread_create(&find_ths[i], NULL, findThreadFun, lp_objPools[i]);

	}

	for (uint32_t i=0; i<threadNum; i++)
	{
		pthread_join(find_ths[i], NULL);
	}
*/

}

int main()
{
	CLFHashMapTest test;
	test.run();
	test.test_concurrency();
	return 0;
}
