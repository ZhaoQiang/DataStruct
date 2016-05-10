/*
 * IHashable.cpp
 *
 *  Created on: 2014��3��21��
 *      Author: zha55597
 */
#include "IHashable.h"

#include <ctype.h>

IHashable::IHashable() :
    m_hashCode(0),
	mp_next(0)
{}

IHashable::~IHashable()
{}

bool IHashable::equals(IHashable* ap_right)
{
	return m_hashCode == ap_right->m_hashCode;
}

void IHashable::computeHashCode()
{
	m_hashCode = hash();
}

size_t IHashable::getHashCode()
{
	return m_hashCode;
}

void IHashable::reset()
{
	m_hashCode = 0;
}

size_t IHashable::string_alg1_case_sensitive(const char* ap_s)
{
    uint32_t l_hash = 0;
    int32_t l_c     = 0;

    while (0 != (l_c = *ap_s++))
    {
        l_hash = l_c + (l_hash << 6) + (l_hash << 16) - l_hash;
    }

    return size_t(l_hash);
}

size_t IHashable::string_alg1_case_insensitive(const char* ap_s)
{
    uint32_t l_hash = 0;
    int32_t l_c     = 0;

    while (0 != (l_c = *ap_s++))
    {
        l_hash = tolower(l_c) + (l_hash << 6) + (l_hash << 16) - l_hash;
    }

    return size_t(l_hash);
}

size_t IHashable::hash32bit(const uint32_t a_key)
{
    size_t l_retVal = a_key;

    l_retVal = ~l_retVal + (l_retVal << 15); // l_retVal = (l_retVal << 15) - l_retVal - 1;
    l_retVal = l_retVal ^ (l_retVal >> 12);
    l_retVal = l_retVal + (l_retVal << 2);
    l_retVal = l_retVal ^ (l_retVal >> 4);
    l_retVal = l_retVal * 2057; // l_retVal = (l_retVal + (l_retVal << 3)) + (l_retVal << 11);
    l_retVal = l_retVal ^ (l_retVal >> 16);

    return size_t(l_retVal);
}

uint64_t IHashable::hash64bit(const uint64_t a_key)
{
    uint64_t l_retVal = a_key;

    l_retVal = (~l_retVal) + (l_retVal << 21); // l_retVal = (l_retVal << 21) - l_retVal - 1;
    l_retVal = l_retVal ^ (l_retVal >> 24);
    l_retVal = (l_retVal + (l_retVal << 3)) + (l_retVal << 8); // l_retVal * 265
    l_retVal = l_retVal ^ (l_retVal >> 14);
    l_retVal = (l_retVal + (l_retVal << 2)) + (l_retVal << 4); // l_retVal * 21
    l_retVal = l_retVal ^ (l_retVal >> 28);
    l_retVal = l_retVal + (l_retVal << 31);

    return size_t(l_retVal);
}

size_t IHashable::hash64To32bit(const uint64_t a_key)
{
    uint64_t l_retVal = a_key;

    l_retVal = (~l_retVal) + (l_retVal << 18); // l_retVal = (l_retVal << 18) - l_retVal - 1;
    l_retVal = l_retVal ^ (l_retVal >> 31);
    l_retVal = l_retVal * 21; // l_retVal = (l_retVal + (l_retVal << 2)) + (l_retVal << 4);
    l_retVal = l_retVal ^ (l_retVal >> 11);
    l_retVal = l_retVal + (l_retVal << 6);
    l_retVal = l_retVal ^ (l_retVal >> 22);

    return size_t(l_retVal);
}

size_t IHashable::hashOctetString(const uint8_t* ap_s, const uint32_t a_byteLen)
{
    uint32_t l_hash = 0;

    for(uint32_t i = 0; i < a_byteLen; i++)
    {
        l_hash = ap_s[i] + (l_hash << 6) + (l_hash << 16) - l_hash;
    }

    return l_hash;
}




