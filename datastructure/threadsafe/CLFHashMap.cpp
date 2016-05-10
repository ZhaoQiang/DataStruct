/*
 * CLFHashMap.cpp
 *
 *  Created on: 2014.3.19
 *  Author: Zhao Qiang
 */

#include <string.h>
#include <stdint.h>

#include "CLFHashMap.h"
#include "IHashable.h"

using namespace std;

namespace NDataStructure
{

	CLFHashMap::CLFHashMap(size_t a_size) :
			m_capability(a_size),
			m_size(0),
			mp_table(0),
			m_bucketMask(a_size-1),
			debug(0)
	{
		// TODO Auto-generated constructor stub
		initialise();

	}

	CLFHashMap::~CLFHashMap()
	{
		// TODO Auto-generated destructor stub
	}

	void CLFHashMap::initialise()
	{
		mp_table = new IHashable*[m_capability];
		memset(mp_table, 0, sizeof(mp_table));

		mp_lockTable = new AtomicLock[m_capability];
		for(uint32_t i=0; i<m_capability; i++)
		{
			INIT_LOCK_UNLOCKED(mp_lockTable[i]);
		}
	}

	IHashable* CLFHashMap::insert(IHashable* ap_obj)
	{

		uint32_t index = (ap_obj->hash() & m_bucketMask);


		// lock the bucket
		LOCK(mp_lockTable[index]);

		IHashable* lp_node = mp_table[index];

		if (lp_node == 0)
		{
			mp_table[index] = ap_obj;
			UNLOCK(mp_lockTable[index]);
			return 0;
		}

		if (lp_node->equals(ap_obj))
		{
			mp_table[index] = ap_obj;
			ap_obj->mp_next = lp_node->mp_next;

			UNLOCK(mp_lockTable[index]);
			return lp_node;
		}

		for(;;)
		{
			if (lp_node->mp_next == 0)
			{
				lp_node->mp_next = ap_obj;
				UNLOCK(mp_lockTable[index]);
				return 0;
			}

			if (lp_node->mp_next->equals(ap_obj))
			{
				IHashable* ret = lp_node->mp_next;
				lp_node->mp_next = ap_obj;
				ap_obj->mp_next = ret->mp_next;
				UNLOCK(mp_lockTable[index]);
				return ret;
			}

			lp_node = lp_node->mp_next;

		}

		// never here.
		UNLOCK(mp_lockTable[index]);
		return 0;

	}

	IHashable* CLFHashMap::find(IHashable* ap_key)
	{
		uint32_t index = (ap_key->hash() & m_bucketMask);

		LOCK(mp_lockTable[index])
		IHashable* lp_node = mp_table[index];

		while (lp_node != 0)
		{

			if (lp_node->equals(ap_key))
			{
				UNLOCK(mp_lockTable[index]);
				return lp_node;
			}
			lp_node = lp_node->mp_next;
		}

		UNLOCK(mp_lockTable[index]);
		return 0;

	}

	IHashable* CLFHashMap::remove(IHashable* ap_key)
	{
		uint32_t index = (ap_key->hash() & m_bucketMask);

		LOCK(mp_lockTable[index])
		IHashable* lp_node = mp_table[index];

		if (lp_node == 0)
		{
			UNLOCK(mp_lockTable[index]);
			return 0;
		}
		if (lp_node->equals(ap_key))
		{
			mp_table[index]=lp_node->mp_next;
			UNLOCK(mp_lockTable[index]);
			return lp_node;
		}

		while (lp_node->mp_next != 0)
		{
			if (lp_node->mp_next->equals(ap_key))
			{
				IHashable* ret=lp_node->mp_next;
				lp_node->mp_next=lp_node->mp_next->mp_next;
				UNLOCK(mp_lockTable[index]);
				return ret;
			}
		}
		UNLOCK(mp_lockTable[index]);
		return 0;
	}

	size_t CLFHashMap::size()
	{

		size_t ret=0;
		for (uint32_t i=0; i<m_capability; i++)
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
};
