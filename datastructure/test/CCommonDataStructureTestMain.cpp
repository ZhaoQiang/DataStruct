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

// Internal Includes
#include "CCommonDataStructureTestSuite.h"

using namespace maa_common;

//----------------------------------------------------------------------------//

int main(int argc, char* argv[])
{
    CCommonDataStructureTestSuite testSuite;
    return testSuite.runTest();
}
