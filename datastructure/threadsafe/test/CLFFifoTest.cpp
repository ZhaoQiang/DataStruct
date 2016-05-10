#include "CLFFifoTest.h"

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

// External includes - Logging
#include <log4cxx/logger.h>

namespace NDataStructure
{
    //----------------------------------------------------------------------------//

    CLFFifoTest::CLFFifoTest() :
        TestCase("Unit Test Case For CLFFifoTest"),
        m_maxQueueSize(10),
        mp_test(0),
        mp_deleteOnlyOnce(0),
        mp_logger(0)
    {
        mp_logger = log4cxx::Logger::getLogger("CLFFifoTest");
    }  

    //----------------------------------------------------------------------------//

    CLFFifoTest::~CLFFifoTest()
    {
    }

    //----------------------------------------------------------------------------//

    void CLFFifoTest::run()
    {
        test_construction();

        test_initialisation();

        test_getterSetter();

        test_destruction();
    }

    //----------------------------------------------------------------------------//

    void CLFFifoTest::test_construction()
    {
        A7CTESTDESC("Test construction of CLFFifo");

        mp_test = new NDataStructure::CLFFifo<uint64_t*>(100);
        A7CTESTASS(0 != mp_test);
        A7CTESTASS(0 == mp_test->size());
    }    

    //----------------------------------------------------------------------------//

    void CLFFifoTest::test_initialisation()
    {
        A7CTESTDESC("Test initialisation of CLFFifo");   
    }    

    //----------------------------------------------------------------------------//

    void CLFFifoTest::test_getterSetter()
    {
        A7CTESTDESC("Test Getters/Setters of CLFFifo");

        bool l_return(false);
        uint64_t* lp_ptr(0);
        uint64_t* l_list[m_maxQueueSize];

        for (uint32_t i = 0; i < m_maxQueueSize >> 1; i++)
        {
            lp_ptr = new uint64_t;
            l_list[i] = lp_ptr;
            
            A7CTESTASS(true == mp_test->insert(lp_ptr));
        }

        A7CTESTASS((m_maxQueueSize >> 1) == mp_test->size());

        lp_ptr = 0;
        A7CTESTASS(true == mp_test->remove(lp_ptr));
        A7CTESTANNOTATE("Removed: " << (long long) lp_ptr);

        A7CTESTANNOTATE("Inserting: " << (long long) lp_ptr);
        A7CTESTASS(true == mp_test->insert(lp_ptr));

        // Save key to delete once
        A7CTESTANNOTATE("Inserting again: " << (long long) lp_ptr);

        mp_deleteOnlyOnce = lp_ptr;
        l_return = mp_test->insert(lp_ptr);

#if defined(OBJPOOL_DEBUG)
        A7CTESTASS(false == l_return);
#else
        // Double insert allowed without debug
        A7CTESTASS(true == l_return);
#endif
    }

    //----------------------------------------------------------------------------//

    void CLFFifoTest::test_destruction()
    {
        bool l_deleted(false);

        for (uint32_t i = 0; i < m_maxQueueSize; i++)
        {
            uint64_t* lp_ptr(0);

            // Remove contents
            if (true == mp_test->remove(lp_ptr))
            {
                if (lp_ptr == mp_deleteOnlyOnce)
                {
                    if (false == l_deleted)
                    {
                        delete lp_ptr;
                        lp_ptr = 0;
                        l_deleted = true;  // prevent double delete
                    }
                    else
                    {
                        // Already deleted this key
                    }
                }
                else
                {
                    delete lp_ptr;
                    lp_ptr = 0;
                }
            }
            else
            {
                break;
            }
        }

        delete mp_test;
        mp_test = NULL;
    }

} // namespace NDataStructure
