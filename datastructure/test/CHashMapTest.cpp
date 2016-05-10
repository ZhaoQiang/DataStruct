/*
 * CHashMapTest.cpp
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#include "CHashMapTest.h"
#include "CHashMapTestObject.h"
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


CHashMapTest::CHashMapTest() :
    TestCase("CHashMapTest"),
	mp_hashTable(0),
	mp_objPool(0),
	mp_obj1(0),
	mp_obj2(0),
	mp_obj3(0)

{
	// TODO Auto-generated constructor stub

}

CHashMapTest::~CHashMapTest()
{
	// TODO Auto-generated destructor stub
}

void CHashMapTest::run()
{
	test_construction();
	test_insert();
	test_find();
	test_remove();
	test_destruction();
}

void CHashMapTest::test_construction()
{
	mp_hashTable = new CHashMap(HASH_TABLE_SIZE_FUNC);
	mp_objPool = new CStack(HASH_TABLE_SIZE_FUNC);

	for (uint32_t i=0; i<mp_objPool->getCapability(); i++)
	{
		CHashMapTestObject* lp_obj = new CHashMapTestObject;
		mp_objPool->push(lp_obj);
	}
}

void CHashMapTest::test_destruction()
{
	//TODO: release objects
    delete mp_hashTable;
    delete mp_objPool;
}

void CHashMapTest::test_insert()
{
	mp_obj1 = (CHashMapTestObject*)mp_objPool->pop();
	mp_obj2 = (CHashMapTestObject*)mp_objPool->pop();
	mp_obj3 = (CHashMapTestObject*)mp_objPool->pop();

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

void CHashMapTest::test_find()
{
	CHashMapTestObject findKeyObj;

	findKeyObj.setKey((uint8_t*)"obj2", 4);
	CHashMapTestObject* lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj2);

	findKeyObj.setKey((uint8_t*)"object3", 7);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj3);

	findKeyObj.setKey((uint8_t*)"obj1", 4);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj1);

	findKeyObj.setKey((uint8_t*)"object_not_exist", 16);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);


}

void CHashMapTest::test_remove()
{
	CHashMapTestObject findKeyObj;

	findKeyObj.setKey((uint8_t*)"obj2", 4);
	CHashMapTestObject* lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj2);

	CHashMapTestObject* lp_ret = (CHashMapTestObject*)mp_hashTable->remove(&findKeyObj);
	A7CTESTASS(lp_ret == mp_obj2);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	//A7CTESTASS(lp_find == NULL);

	findKeyObj.setKey((uint8_t*)"object3", 7);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj3);

	lp_ret = (CHashMapTestObject*)mp_hashTable->remove(&findKeyObj);
	A7CTESTASS(lp_ret == mp_obj3);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);


	findKeyObj.setKey((uint8_t*)"obj1", 4);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj1);

	lp_ret = (CHashMapTestObject*)mp_hashTable->remove(&findKeyObj);
	A7CTESTASS(lp_ret == mp_obj1);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);


	mp_hashTable->insert(mp_obj2);
	findKeyObj.setKey((uint8_t*)"obj2", 4);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == mp_obj2);

	findKeyObj.setKey((uint8_t*)"object_not_exist", 16);
	lp_find = (CHashMapTestObject*)mp_hashTable->find(&findKeyObj);
	A7CTESTASS(lp_find == NULL);

}



