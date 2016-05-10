/*
 * CLFStack.h
 *
 *  Created on: 2014��3��20��
 *      Author: zha55597
 */

#ifndef CLFSTACK_H_
#define CLFSTACK_H_

#include <stdlib.h>
#include <stdint.h>

class CLFStack
{
	public:
		CLFStack(uint32_t a_capability);
		virtual ~CLFStack();

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

#endif /* CLFSTACK_H_ */
