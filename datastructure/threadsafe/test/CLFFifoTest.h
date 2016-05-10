#if !defined(maa_clffifotest_h)
#define maa_clffifotest_h

/**
 * Concrete class for CLF Fifo Test
 *
 * Author:       Mark Phaneuf
 * Date Created: 28th May 2014
 *
 * (C) COPYRIGHT JDS UNIPHASE 2014. ALL RIGHTS RESERVED. NO PART
 * OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT
 * OF JDS UNIPHASE.
 */

// External Includes - A7CUnitTest
#include <a7c_test.h>
#include <inttypes.h>

// External Includes - Logger
#include <log4cxx/logger.h>

// Internal Includes
#include "CLFFifo.h"

namespace NDataStructure
{

    class CLFFifoTest : public a7common::TestCase
    {
    public:

        /**
         * Default Constructor
         */    
        CLFFifoTest();

        /**
         * Destructor
         */    
        virtual ~CLFFifoTest();

        /**
         * Run the unit test
         */    
        void run();

    private:

        /**
         * Test object creation
         */    
        void test_construction();

        /**
         * Test object creation
         */    
        void test_initialisation();

        /**
         * Test getters/Setters
         */    
        void test_getterSetter();

        /**
         * Test object destruction
         */
        void test_destruction();

    private:

        // lock free queue type
        typedef NDataStructure::CLFFifo<uint64_t*> tBufferQ;

        // Lock-free queue size
        const uint32_t m_maxQueueSize;

        // lock-free queue
        tBufferQ* mp_test;

        // Duplicate key, only want to delete once
        uint64_t* mp_deleteOnlyOnce;

        // Logger
        log4cxx::LoggerPtr mp_logger;
    };

} // namespace NDataStructure

#endif // maa_clffifotest_h
