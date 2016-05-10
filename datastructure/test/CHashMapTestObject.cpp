/*
 * CHashMapTestObject.cpp
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#include "CHashMapTestObject.h"
#include <string.h>


CHashMapTestObject::CHashMapTestObject() :
	m_keyLen(0),
	m_valueLen(0)
{
	// TODO Auto-generated constructor stub

}

CHashMapTestObject::~CHashMapTestObject()
{
	// TODO Auto-generated destructor stub
}

void CHashMapTestObject::setKey(uint8_t* ap_key, uint32_t a_keyLen)
{
	m_keyLen = a_keyLen > MAX_KEY_LEN ? MAX_KEY_LEN : a_keyLen;
	memcpy(mp_key, ap_key, m_keyLen);
	computeHashCode();
}

void CHashMapTestObject::setValue(uint8_t* ap_value, uint32_t a_valueLen)
{
	m_valueLen = a_valueLen > MAX_VALUE_LEN ? MAX_VALUE_LEN : a_valueLen;
	memcpy(mp_value, ap_value, m_valueLen);
}

size_t CHashMapTestObject::hash()
{
	return hashOctetString(mp_key, m_keyLen);
}

