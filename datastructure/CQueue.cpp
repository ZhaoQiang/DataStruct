/*
 * CQueue.cpp
 *
 *  Created on: 2014年4月3日
 *      Author: zha55597
 */

#include "CQueue.h"

namespace NDataStructure
{

	CQueue::CQueue(uint32_t a_capability) :
			m_capability(a_capability)
	{
		// TODO Auto-generated constructor stub

	}

	CQueue::~CQueue()
	{
		// TODO Auto-generated destructor stub
	}

	bool put(void* ap_item)
	{
		return false;
	}
	bool get(void*& arp_item)
	{
		return false;

	}

	bool putNonBlock(void* ap_item)
	{
		return false;

	}

	bool getNonBlock(void*& arp_item)
	{
		return false;

	}

} /* namespace NStateMachine */
