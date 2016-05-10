/*
 * CStack.h
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#ifndef CSTACK_H_
#define CSTACK_H_

#include <stdlib.h>
#include <stdint.h>

class CStack
{
	public:
		CStack(uint32_t a_capability);
		virtual ~CStack();

		bool push(void* ap_element);
		void* pop();
		void* get(uint32_t a_index);

		inline uint32_t getCapability()
		{
			return m_capability;
		}
		inline uint32_t getSize()
		{
			return m_top;
		}

	private:
		uint32_t m_capability;

		void** mp_stack;

		uint32_t m_top;
};

#endif /* CSTACK_H_ */
