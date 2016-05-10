/*
 * CLinkedList.h
 *
 *  Created on: 2014年4月4日
 *      Author: zha55597
 */

#ifndef CLINKEDLIST_H_
#define CLINKEDLIST_H_

namespace NSessionFollower
{

	class ILinkedListItem
	{
		public:
			ILinkedListItem();
			virtual ~ILinkedListItem();

			virtual bool compare(ILinkedListItem& ar_right) = 0;

		protected:
			void* mp_data;

			ILinkedListItem* mp_prev;
			ILinkedListItem* mp_next;


	};

	class CLinkedList
	{
		public:
			CLinkedList();
			virtual ~CLinkedList();

			void addTail(ILinkedListItem* ap_item);
			void addHead(ILinkedListItem* ap_item);
			void find(ILinkedListItem* ap_compare);

			void insertBehind(ILinkedListItem* ap_compare, ILinkedListItem* ap_insert);
			void insertBefore(ILinkedListItem* ap_compare, ILinkedListItem* ap_insert);

			void removeRaw(ILinkedListItem* ap_item);
			void remove(ILinkedListItem* ap_compare);

		private:
			ILinkedListItem* mp_head;
			ILinkedListItem* mp_tail;

	};

} /* namespace NStateMachine */

#endif /* CLINKEDLIST_H_ */
