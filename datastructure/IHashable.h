/*
 * IHashable.h
 *
 *  Created on: 2014��3��19��
 *      Author: zha55597
 */

#ifndef IHASHABLE_H_
#define IHASHABLE_H_

#include <stdlib.h>
#include <stdint.h>


class IHashable
{
	public:
        /** Constructor */
        IHashable();

		virtual ~IHashable();

		virtual size_t hash() = 0;

		virtual bool equals(IHashable* ap_right);

		void computeHashCode();

		virtual void reset();

		virtual size_t getHashCode();

        /**
         * Compute a hash code for a string
         *
         * @param ap_s - The string to checksum
         *
         * @return size_t - The computed hash code
         */
         static size_t string_alg1_case_sensitive(const char* ap_s);

        /**
         * Compute a hash code for a string
         *
         * @param ap_s - The string to checksum
         *
         * @return size_t - The computed hash code
         */
         static size_t string_alg1_case_insensitive(const char* ap_s);

        /**
         * Compute a hash code for a 32-bit number
         *
         * @param a_key - The integer to hash
         *
         * @return size_t - The computed hash code
         */
         static size_t hash32bit(const uint32_t a_key);

        /**
         * Copy a hash code for a 64-bit number.  Note, this is not
         * suitable for an STL hash map since STL requires a 32-bit
         * hashcode.
         *
         * @param a_key - The long integer to hash
         *
         * @return uint64_t - The computed hash code
         */
         static uint64_t hash64bit(const uint64_t a_key);

        /**
         * Compute a 32-bit hash code for a 64-bit number.
         *
         * @param a_key - The long integer to hash
         *
         * @return size_t - the computed hash code
         */
         static size_t hash64To32bit(const uint64_t a_key);

        /**
         * Compute a hash code for a octet string
         *
         * @param ap_s - The octet string to hash, uint8_t*
         *
         * @param a_byteLen - The uint8_t* array size
         *
         * @return size_t - The computed hash code
         */
         static size_t hashOctetString(const uint8_t* ap_s, const uint32_t a_byteLen);

    private:


        /**
         * Copy constructor
         * @param ar_right
         */
        IHashable(const IHashable &ar_right);

        /**
         * Operator=
         *
         * @param ar_right
         *
         * @return CThread&
         */
        IHashable& operator=(const IHashable &ar_right);


	private:
		size_t m_hashCode;

        IHashable* mp_next;

        friend class CHashMap;
		friend class CLFHashMap;


};

#endif /* IHASHABLE_H_ */
