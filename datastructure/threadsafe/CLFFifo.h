/******************************************************************************
 * File         : CLFFifo.h
 * Author       : brucema
 * Date Created : 10/10/2008
 * Contents     : CLFFifo sub-classes LFFifo to maintain a count of how many 
 *                items are in the fifo.
 *                The count is useful for telemetry/debugging
 *                An underflow indication is available for use in raising 
 *                alarms for e.g. buffer exhaustion.
 *                The counter & sub-classing will result in a small performance
 *                overhead.
 *                As with LFFifo, there may be only one reader and one writer 
 *                thread.
 ******************************************************************************
 * (C) COPYRIGHT AGILENT TECHNOLOGIES UK LTD 2008. ALL RIGHTS RESERVED.
 * NO PART OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT OF
 * AGILENT TECHNOLOGIES UK LTD.
 *****************************************************************************/

#ifndef _Maa_CLFFifo_h_
#define _Maa_CLFFifo_h_

// The debug code makes assumptions about what can be placed in a LFFifo 
// Specifically it expects them to be pointers rather than objects
// The Subscriber and Session record features now use the LFFifo to copy
// objects. This causes DEBUG=1 builds to fail.
// Neuter this DEBUG code for now by explicitly undef OBJPOOL_DEBUG

#undef OBJPOOL_DEBUG

#include "LFFifo.h"
#include "ASDAtomicBitOps.h"

#if defined(OBJPOOL_DEBUG)
    #include <iostream>
    #include <assert.h>
    #include <set>
#endif

#ifdef __GNUC__
    #if __GNUC__ < 4
        #include <asm/atomic.h>

namespace NDataStructure
{
    template < class T >
    class CLFFifo:public LFFifo<T>
    {
    public:
        // Constructor
        CLFFifo( uint32_t tSize ): LFFifo<T>( tSize )
        {
            atomic_set( &n, 0 );
        }

        // Destructor
        virtual ~CLFFifo()
        {
        }

        // Inserts a copy of rtItem onto the tail of the queue
        // return false if the queue is full 
        // Only the writer thread may call this method.
        bool insert( const T &rtItem )
        {
            bool tRet = LFFifo<T>::insert( rtItem );
            if( tRet ) atomic_inc( &n );
            return tRet;
        }

        // Removes item from the head of the queue and copies 
        // it to rtItem
        // will return false if the fifo is empty.
        // Only the reader thread may call this methos
        bool remove( T &rtItem )
        {
            bool tRet = LFFifo<T>::remove( rtItem );
            if( tRet )
            {
                if( atomic_dec_and_test( &n ) )
                {
                    // the fifo has emptied, set underflow indication
                    u.set( eUnderflowBit );
                }
            }
            return tRet;
        }

        // return the current number of items in the fifo.
        // Any thread may call this method.
        uint32_t size() { return atomic_read( &n );}

        // atomically test and clear the underflow indication.
        // return true if an underflow has occured since last clear
        // Multiple threads may call this method, but only one of them will 
        // 'consume' the alarm if there is one. 
        bool tac_underflow() { return u.tac( eUnderflowBit );}

        // return the underflow indication without clearing it.
        bool test_underflow() { return u.test( eUnderflowBit );}

    protected:
        enum
        {
            eUnderflowBit = 0
        };
        atomic_t n;    // number of items currently in fifo.
        Tsd::ABW u;    // underflow indication

        // No default constructor
        CLFFifo();

        // No copy constructor
        CLFFifo( const CLFFifo & );

        // No assignment operator
        CLFFifo &operator=( const CLFFifo & );

    private:

    }; // class CLFFifo

}; // namespace NDataStructure

    #else

namespace NDataStructure
{
    template < class T >
    class CLFFifo:public LFFifo<T>
    {
    public:
        // Constructor
        CLFFifo( uint32_t tSize ): LFFifo<T>( tSize )
        {

#if defined(OBJPOOL_DEBUG)
            if( pthread_mutexattr_init( &m_mutexAttr ) != 0 )
            {
                std::cout << "CLFFifo::CLFFifo().  Failed to create mutex attr." << std::endl;
                assert(0);
            }

            if(pthread_mutex_init(&m_newDelMutex, &m_mutexAttr) != 0)
            {
                std::cout << "CLFFifo::CLFFifo(). Failed to create mutex." << std::endl;
                assert(0);
            }

            m_mutexInitialised = true;
#endif

            __sync_val_compare_and_swap( &n, n, 0 );
        }

        // Destructor
        virtual ~CLFFifo()
        {
#if defined(OBJPOOL_DEBUG)
            if( m_mutexInitialised )
            {
                pthread_mutexattr_destroy(&m_mutexAttr);
                pthread_mutex_destroy(&m_newDelMutex);   
            }
#endif
        }

        // Inserts a copy of rtItem onto the tail of the queue
        // return false if the queue is full 
        // Only the writer thread may call this method.
        bool insert( const T &rtItem )
        {
            bool tRet = false;
#if defined(OBJPOOL_DEBUG)
            if( !m_mutexInitialised || NULL == rtItem)
            {
                return false;
            }

            bool l_lockRetVal = pthread_mutex_lock(&m_newDelMutex);
            assert(0 == l_lockRetVal);

            std::set<unsigned long long>::iterator i = m_freeAddressMap.find(reinterpret_cast<unsigned long long>(rtItem));
            if(m_freeAddressMap.end() != i)
            {
#if defined(OBJPOOL_DEBUG_DISABLE_ASSERT)
                std::cout << "CLFFifo::insert().  Attempting to return an object which is already in the pool: " << std::endl;
                l_lockRetVal = pthread_mutex_unlock(&m_newDelMutex);
                assert(0 == l_lockRetVal);
                return false;
                
#else
                assert(0);
#endif
            }
            else
            {
#endif

                tRet = LFFifo<T>::insert( rtItem );
                if( tRet ) __sync_fetch_and_add( &n, 1 );

#if defined(OBJPOOL_DEBUG)
                if( tRet )
                {
                    m_freeAddressMap.insert(reinterpret_cast<unsigned long long>(rtItem));
                }
            }

            l_lockRetVal = pthread_mutex_unlock(&m_newDelMutex);
            assert(0 == l_lockRetVal);
#endif

            return tRet;
        }


        // Removes item from the head of the queue and copies 
        // it to rtItem
        // will return false if the fifo is empty.
        // Only the reader thread may call this methods
        bool remove( T &rtItem )
        {
            bool tRet = LFFifo<T>::remove( rtItem );
            if( tRet )
            {
                if( !__sync_sub_and_fetch( &n, 1 ) )
                {
                    // the fifo has emptied, set underflow indication
                    u.set( eUnderflowBit );
                }

#if defined(OBJPOOL_DEBUG)
                if( !m_mutexInitialised)
                {
                    std::cout << "mutex not initialized" << std::endl;
                    return false;
                }

                bool l_lockRetVal = pthread_mutex_lock(&m_newDelMutex);
                assert(0 == l_lockRetVal);

                std::set<unsigned long long>::iterator i = m_freeAddressMap.find(reinterpret_cast<unsigned long long>(rtItem));
                if(m_freeAddressMap.end() != i)
                {
                    m_freeAddressMap.erase ( i );
                }

                l_lockRetVal = pthread_mutex_unlock(&m_newDelMutex);
                assert(0 == l_lockRetVal);
#endif
            }
            return tRet;
        }

        // return the current number of items in the fifo.
        // Any thread may call this method.
        uint32_t size() { return __sync_fetch_and_add( &n, 0 );}


        // atomically test and clear the underflow indication.
        // return true if an underflow has occured since last clear
        // Multiple threads may call this method, but only one of them will 
        // 'consume' the alarm if there is one. 
        bool tac_underflow() { return u.tac( eUnderflowBit );}

        // return the underflow indication without clearing it.
        bool test_underflow() { return u.test( eUnderflowBit );}

    protected:
        enum
        {
            eUnderflowBit = 0
        };
        volatile int n;    // number of items currently in fifo.
        Tsd::ABW u;    // underflow indication

#if defined(OBJPOOL_DEBUG)
        bool m_mutexInitialised;
        pthread_mutex_t m_newDelMutex;
        pthread_mutexattr_t m_mutexAttr;
        std::set<unsigned long long> m_freeAddressMap;
#endif

        // No default constructor
        CLFFifo();

        // No copy constructor
        CLFFifo( const CLFFifo & );

        // No assignment operator
        CLFFifo &operator=( const CLFFifo & );

    private:

    }; // class CLFFifo

}; // namespace NDataStructure

    #endif
#endif

#endif // _Maa_CLFFifo_h_
