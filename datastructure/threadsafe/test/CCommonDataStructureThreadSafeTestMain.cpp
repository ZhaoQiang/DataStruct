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
// Internal Includes
#include "CCommonDataStructureThreadSafeTestSuite.h"

using namespace NDataStructure;

//----------------------------------------------------------------------------//

int main(int argc, char* argv[])
{
    CCommonDataStructureThreadSafeTestSuite testSuite;
    return testSuite.runTest();
}
