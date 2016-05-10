/*
 * CStack.cpp
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#include "CStack.h"

CStack::CStack(uint32_t a_capability) :
	m_capability(a_capability),
	mp_stack(0),
	m_top(0)
{
	// TODO Auto-generated constructor stub
	mp_stack = new void*[a_capability];
}

CStack::~CStack()
{
	// TODO Auto-generated destructor stub
}

bool CStack::push(void* ap_elemenet)
{
	if (m_top == m_capability)
	{
		return false;
	}

	mp_stack[m_top++] = ap_elemenet;
	return true;
}

void* CStack::pop()
{
	if (m_top == 0)
	{
		return 0;
	}

	return mp_stack[--m_top];
}

void* CStack::get(uint32_t a_index)
{
	if (a_index<m_top)
	{
		return mp_stack[a_index];
	}
	return 0;
}

