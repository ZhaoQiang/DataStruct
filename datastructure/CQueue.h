/*
 * CQueue.h
 *
 *  Created on: 2014年4月3日
 *      Author: zha55597
 */

#ifndef CQUEUE_h
#define CQUEUE_h

namespace NDataStructure
{

	class CQueue
	{
		public:
			CQueue(uint32_t a_capability);
			virtual ~CQueue();

			bool put(void* ap_item);
			bool get(void*& arp_item);

			bool putNonBlock(void* ap_item);
			bool getNonBlock(void*& arp_item);

		protected:
			uint32_t m_capability;
	};

} /* namespace NDataStructure */

#endif /* CQUEUE_H_ */
