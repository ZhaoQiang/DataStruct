/*
 * CHashMap.h
 *
 *  Created on: 2014��3��19��
 *      Author: zha55597
 */

#ifndef CHASHMAP_H_
#define CHASHMAP_H_

#include <stdlib.h>
#include <stdint.h>

class IHashable;


class CHashMap
{

	public:


		CHashMap(size_t a_size);
		virtual ~CHashMap();

		IHashable* insert(IHashable* ap_obj);

		IHashable* find(IHashable* ap_key);

		IHashable* remove(IHashable* ap_key);

		// slow operation
		size_t size();

	private:

		void initialise();

		IHashable** mp_table;

		size_t m_capability;
		size_t m_size;
		size_t m_bucketMask;
};

#endif /* CHASHMAP_H_ */
