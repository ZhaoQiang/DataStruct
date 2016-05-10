#if !defined(maa_commondatastructuretestsuite_h)
#define maa_commondatastructuretestsuite_h

/**
 * Concrete class for common Unit Test Suite
 *
 * Author:       Mark Phaneuf
 * Date Created: 19th February 2014
 *
 * (C) COPYRIGHT JDS UNIPHASE 2014. ALL RIGHTS RESERVED. NO PART
 * OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT
 * OF JDS UNIPHASE.
 */

// External Includes
#include <a7c_test.h>

namespace maa_common {

class CCommonDataStructureTestSuite : public a7common::TestSuite
{
public:

    /**
     * Test Suite constructor
     */
    CCommonDataStructureTestSuite();

    /**
     * Setup the test to run
     */
    void setUp ();
};

} // namespace maa_common

#endif // maa_commondatastructuretestsuite_h
