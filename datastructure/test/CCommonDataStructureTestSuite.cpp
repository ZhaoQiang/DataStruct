#include "CCommonDataStructureTestSuite.h"

/**
 * Concrete class for common Unit Test Suite
 *
 * Author:       Mark Phaneuf
 * Date Created: 6th March 2014
 *
 * (C) COPYRIGHT JDS UNIPHASE 2014. ALL RIGHTS RESERVED. NO PART
 * OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
 * TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT
 * OF JDS UNIPHASE.
 */

// External Includes
#include <a7c_test.h>

// Internal Includes
#include "CHashMapTest.h"

namespace maa_common {

//----------------------------------------------------------------------------//

CCommonDataStructureTestSuite::CCommonDataStructureTestSuite() :
    TestSuite("Common Data Structures Test Suite")
{
}

//----------------------------------------------------------------------------//

void CCommonDataStructureTestSuite::setUp ()
{
    addTest(new CHashMapTest());
}

} // namespace maa_breakout
