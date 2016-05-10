/*----------------------------------------------------------------------------
  File         : main.h
  Author       : brucema
  Date Created : Oct 10th 2008
  Contents     : 
  ----------------------------------------------------------------------------
  (C) COPYRIGHT AGILENT TECHNOLOGIES COMPANY 2008. ALL RIGHTS RESERVED.
  NO PART OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
  TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT OF
  AGILENT TECHNOLOGIES COMPANY.
  ---------------------------------------------------------------------------*/
#ifndef __ASD_TEST_MAIN_H__
#define __ASD_TEST_MAIN_H__

#include <string>

#define TEST_FOR( XXX ) testFor( XXX, __FILE__, __LINE__ )
bool testFor( bool tTestResult, const char *ptFileName, uint32_t tLineNumber );
void test0();
void test1();
void test2();
void test3();
#endif
