#include "CCommonDataStructureThreadSafeTestSuite.h"

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

// Internal Includes
#include "CLFFifoTest.h"

namespace NDataStructure {

//----------------------------------------------------------------------------//

CCommonDataStructureThreadSafeTestSuite::CCommonDataStructureThreadSafeTestSuite() :
    TestSuite("Common Data Strucutre Thread-safe Suite")
{
}

//----------------------------------------------------------------------------//

void CCommonDataStructureThreadSafeTestSuite::setUp ()
{
    addTest(new CLFFifoTest());
}

} // namespace NDataStructure
