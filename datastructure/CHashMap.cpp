/*
 * CHashMap.cpp
 *
 *  Created on: 2014.3.19
 *      Author: Zhao Qiang
 */

#include <string.h>
#include <stdint.h>

#include "CHashMap.h"
#include "IHashable.h"


CHashMap::CHashMap(size_t a_size) :
	mp_table(0),
	m_capability(a_size),
	m_size(0),
	m_bucketMask(0)
{
	// TODO Auto-generated constructor stub
	initialise();

}

CHashMap::~CHashMap()
{
	// TODO Auto-generated destructor stub
}

void CHashMap::initialise()
{
    uint64_t optimizedCapability = 1;
    while(optimizedCapability<m_capability && optimizedCapability != 0)
    {
        optimizedCapability<<=1;
    }
    m_capability = optimizedCapability - 1;
    m_bucketMask = m_capability - 1;


	mp_table = new IHashable*[m_capability];
	memset(mp_table, 0, m_capability * sizeof(*mp_table));

}

IHashable* CHashMap::insert(IHashable* ap_obj)
{

	uint32_t index = (ap_obj->hash() & m_bucketMask);


	IHashable* lp_node = mp_table[index];

	if (lp_node == 0)
	{
		mp_table[index] = ap_obj;
		return 0;
	}

	if (lp_node->equals(ap_obj))
	{
		mp_table[index] = ap_obj;
		ap_obj->mp_next = lp_node->mp_next;
		return lp_node;
	}

	for(;;)
	{
		if (lp_node->mp_next == 0)
		{
			lp_node->mp_next = ap_obj;
			return 0;
		}

		if (lp_node->mp_next == ap_obj)
		{
			return 0;
		}

		if (lp_node->mp_next->equals(ap_obj))
		{
			IHashable* ret = lp_node->mp_next;
			lp_node->mp_next = ap_obj;
			ap_obj->mp_next = ret->mp_next;
			return ret;
		}

		lp_node = lp_node->mp_next;

	}

	// never here.
	return 0;

}

IHashable* CHashMap::find(IHashable* ap_key)
{
	uint32_t index = (ap_key->hash() & m_bucketMask);

	IHashable* lp_node = mp_table[index];

	while (lp_node != 0)
	{

		if (lp_node->equals(ap_key))
		{
			return lp_node;
		}
		lp_node = lp_node->mp_next;
	}

	return 0;

}

IHashable* CHashMap::remove(IHashable* ap_key)
{
	uint32_t index = (ap_key->hash() & m_bucketMask);

	IHashable* lp_node = mp_table[index];

	if (lp_node == 0)
	{
		return 0;
	}
	if (lp_node->equals(ap_key))
	{
		mp_table[index]=lp_node->mp_next;
		return lp_node;
	}

	while (lp_node->mp_next != 0)
	{
		if (lp_node->mp_next->equals(ap_key))
		{
			IHashable* ret=lp_node->mp_next;
			lp_node=lp_node->mp_next;
			return ret;
		}
	}
	return 0;
}

size_t CHashMap::size()
{

	size_t ret=0;
	for (uint32_t i=0; i < m_capability; i++)
	{
		IHashable* lp_node = mp_table[i];
		while(lp_node != 0)
		{
			++ret;
			lp_node = lp_node->mp_next;
		}
	}
	return ret;
}
