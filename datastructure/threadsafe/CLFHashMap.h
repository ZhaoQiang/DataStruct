/*
 * CLFHashMap.h
 *
 *  Created on: 2014��3��19��
 *      Author: zha55597
 */

#ifndef CLFHASHMAP_H_
#define CLFHASHMAP_H_

#include <stdlib.h>
#include <stdint.h>
#include "CAtomicLock.h"

class IHashable;

using namespace NSAtomicLock;

<<<<<<< HEAD
namespace NDataStructure
{

	class CLFHashMap
	{

		public:


			CLFHashMap(size_t a_size);
			virtual ~CLFHashMap();

			IHashable* insert(IHashable* ap_obj);

			IHashable* find(IHashable* ap_key);

			IHashable* remove(IHashable* ap_key);

			// slow operation
			size_t size();

			uint32_t debug;

		private:

			void initialise();

			IHashable** mp_table;
			AtomicLock* mp_lockTable;

			size_t m_capability;
			size_t m_size;
			size_t m_bucketMask;

	};
=======
class CLFHashMap
{

	public:


		CLFHashMap(size_t a_size);
		virtual ~CLFHashMap();

		IHashable* insert(IHashable* ap_obj);

		IHashable* find(IHashable* ap_key);

		IHashable* remove(IHashable* ap_key);

		// slow operation
		size_t size();

		uint32_t debug;

	private:

		void initialise();

		IHashable** mp_table;
		AtomicLock* mp_lockTable;

		size_t m_capability;
		size_t m_size;
		size_t m_bucketMask;

>>>>>>> remotes/origin/feature/MAA-131-support-3gpp-rel-11-for-the-st-decodes
};

#endif /* CLFHASHMAP_H_ */
