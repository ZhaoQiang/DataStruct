/******************************************************************************
 * File         : LFFifo.h
 * Author       : brucema
 * Date Created : 26/2/2008
 * Contents     : Templated class for a mutex free fifo.
 *                This is a fairly standard concept..which is ONLY
 *                suitable for use with a single producer, single consumer 
 *                arrangement.
 *                Avoidance of mutex locks gives performance benefits.
 *
 *                Operation relies on the assignments to the
 *                r/w member variables being atomic.
 *                This code is non portable.
 *                The atomic macros are usable from user space in x86
 *                by virtue of the machine architecture. This is not the case
 *                for all architectures.
 ******************************************************************************
 * (C) COPYRIGHT AGILENT TECHNOLOGIES UK LTD 2008. ALL RIGHTS RESERVED.
 * NO PART OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT OF
 * AGILENT TECHNOLOGIES UK LTD.
 *****************************************************************************/

#ifndef _Maa_LFFifo_h_
#define _Maa_LFFifo_h_

#include <stdint.h>
#include <errno.h>

#include "branchPrediction.h"

#ifdef __GNUC__
    #if __GNUC__ < 4
        #include <asm/atomic.h>

namespace NDataStructure
{
    template < class T >
    class LFFifo
    {
    public:

        // Constructor
        LFFifo( uint32_t tSize ): size( tSize + 1 )
        {
            f = new T [ tSize + 1 ];
            atomic_set( &w, 0 );
            atomic_set( &r, 0 );
        }

        // Destructor
        virtual ~LFFifo()
        {
            delete [] f;
        }

        // Inserts a copy of rtItem onto the tail of the queue
        // return false if the queue is full 
        bool insert( const T &rtItem )
        {
            uint32_t nw;
            bool tRet = false;
            uint32_t ww = (uint32_t) atomic_read( &w );
            uint32_t rr = (uint32_t) atomic_read( &r );

            if( predict_true( ( ww + 1 ) < size ) )
                nw = ww + 1;
            else
                nw = 0;

            if( predict_true( nw != rr ) )
            {
                f[ ww ] = rtItem;
                atomic_set( &w, nw );
                tRet = true;
            }
            return tRet;
        }


        // Removes the from the head of the queue and copies 
        // it to rtItem
        // will return false if the fifo is empty.
        bool remove( T &rtItem )
        {
            bool tRet = false;
            uint32_t rr = (uint32_t) atomic_read( &r );
            uint32_t ww = (uint32_t) atomic_read( &w );

            if( predict_true( rr != ww ) )
            {
                rtItem = f[ rr ];
                if( predict_false( ( rr + 1 ) >= size ))
                    atomic_set( &r, 0 );
                else
                    atomic_inc( &r );

                tRet = true;
            }

            return tRet;
        }

        uint32_t capacity() { return size - 1;}
    protected:
        volatile T * f;
        atomic_t w;
        atomic_t r;

        uint32_t size;

        // No default constructor
        LFFifo();

        // No copy constructor
        LFFifo( const LFFifo & );

        // No assignment operator
        LFFifo &operator=( const LFFifo & );

    private:

    }; // class LFFifo

}; // namespace NDataStructure


    #else
namespace NDataStructure
{
    template < class T >
    class LFFifo
    {
    public:

        // Constructor
        LFFifo( uint32_t tSize ): size( tSize + 1 )
        {
            f = new T [ tSize + 1 ];
            __sync_val_compare_and_swap( &w, w, 0 );
            __sync_val_compare_and_swap( &r, r, 0 );
        }

        // Destructor
        virtual ~LFFifo()
        {
            delete [] f;
        }

        // Inserts a copy of rtItem onto the tail of the queue
        // return false if the queue is full 
        bool insert( const T &rtItem )
        {
            uint32_t nw;
            bool tRet = false;
            uint32_t ww = (uint32_t) __sync_fetch_and_add( &w, 0 );
            uint32_t rr = (uint32_t) __sync_fetch_and_add( &r, 0 );

            if( predict_true( ( ww + 1 ) < size ) )
                nw = ww + 1;
            else
                nw = 0;

            if( predict_true( nw != rr ) )
            {
                f[ ww ] = rtItem;
                __sync_val_compare_and_swap( &w, w, nw );
                tRet = true;
            }
            return tRet;
        }


        // Removes the from the head of the queue and copies 
        // it to rtItem
        // will return false if the fifo is empty.
        bool remove( T &rtItem )
        {
            bool tRet = false;
            uint32_t rr = (uint32_t) __sync_fetch_and_add( &r, 0 );
            uint32_t ww = (uint32_t) __sync_fetch_and_add( &w, 0 );

            if( predict_true( rr != ww ) )
            {
                rtItem = f[ rr ];
                if( predict_false( ( rr + 1 ) >= size ))
                    __sync_val_compare_and_swap( &r, r, 0 );
                else
                    __sync_fetch_and_add( &r, 1 );

                tRet = true;
            }

            return tRet;
        }

        uint32_t capacity() { return size - 1;}
    protected:
        volatile T * f;
        volatile int w;
        volatile int r;

        uint32_t size;

        // No default constructor
        LFFifo();

        // No copy constructor
        LFFifo( const LFFifo & );

        // No assignment operator
        LFFifo &operator=( const LFFifo & );

    private:

    }; // class LFFifo

}; // namespace NDataStructure
    #endif
#endif

#endif // _Maa_LFFifo_h_
