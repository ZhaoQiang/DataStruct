/*
 * CHashMapTestObject.h
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#ifndef CHASHMAPTESTOBJECT_H_
#define CHASHMAPTESTOBJECT_H_

#include <stdint.h>
#include <stdlib.h>
#include "IHashable.h"

#define MAX_KEY_LEN 16
#define MAX_VALUE_LEN 32

class CHashMapTestObject: public IHashable
{
	public:
		CHashMapTestObject();
		virtual ~CHashMapTestObject();

		size_t hash();

		void setKey(uint8_t* ap_key, uint32_t a_keyLen);
		void setValue(uint8_t* ap_value, uint32_t a_valueLen);

	public:
		uint8_t mp_key[MAX_KEY_LEN];
		uint32_t m_keyLen;

		uint8_t mp_value[MAX_VALUE_LEN];
		uint32_t m_valueLen;
};

#endif /* CHASHMAPTESTOBJECT_H_ */
