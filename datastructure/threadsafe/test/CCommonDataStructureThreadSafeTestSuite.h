#if !defined(maa_ccommondatastructurethreadsafetestsuite_h)
#define maa_ccommondatastructurethreadsafetestsuite_h

/**
 * Concrete class for common thread-safe unit test suite
 *
 * Author:       Mark Phaneuf
 * Date Created: 28th May 2014
 *
 * (C) COPYRIGHT JDS UNIPHASE 2014. ALL RIGHTS RESERVED. NO PART
 * OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT
 * OF JDS UNIPHASE.
 */

// External Includes
#include <a7c_test.h>

namespace NDataStructure {

class CCommonDataStructureThreadSafeTestSuite : public a7common::TestSuite
{
public:

    /**
     * Test Suite constructor
     */
    CCommonDataStructureThreadSafeTestSuite();

    /**
     * Setup the test to run
     */
    void setUp ();
};

} // namespace NDataStructure

#endif // maa_ccommondatastructurethreadsafetestsuite_h
