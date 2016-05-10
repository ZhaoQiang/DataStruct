/*----------------------------------------------------------------------------
  File         : main.cpp
  Author       : brucema
  Date Created : April 15th 2008
  Contents     : Test harness for filterEngine
  ----------------------------------------------------------------------------
  (C) COPYRIGHT AGILENT TECHNOLOGIES COMPANY 2008. ALL RIGHTS RESERVED.
  NO PART OF THIS PROGRAM MAY BE PHOTOCOPIED REPRODUCED OR TRANSLATED
  TO ANOTHER PROGRAM LANGUAGE WITHOUT THE PRIOR WRITTEN CONSENT OF
  AGILENT TECHNOLOGIES COMPANY.
  ---------------------------------------------------------------------------*/
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#include "main.h"
#include "tsdTrace.h"

#include "log4cxx/logger.h"

using namespace std;
using namespace log4cxx;

log4cxx::LoggerPtr p_logger = Logger::getLogger("main");

TsdTraceVolume tTheTraceVolume = eNoVolume;
uint32_t tTestsPerformed = 0;
uint32_t tTestsPassed    = 0;
uint32_t tTestsFailed    = 0;

static const char * cptUsage =
  "flags: [-v][-h]\n"
  "-v              Be verbose \n"
  "-h              Show this message and exit\n";

/*
 *
 */
static inline void usage()
{
  LOG4CXX_ERROR(p_logger, cptUsage);
}

/* 
 * parse the command line arguments 
 */
static int get_args ( int argc, char * argv[] )
{
  int c;
  opterr = 0;
  while( (c = getopt( argc, argv, "hv"))!= EOF)
    {
      switch( c )
	{
	case 'h':
	  usage();
	  exit(1);
	  break;

	case 'v':
	  tTheTraceVolume = eExtraLoudVolume;
	  break;

	case '?':
	  if (isprint (optopt))
	    {
	      LOG4CXX_ERROR(p_logger, "ERROR: unrecognised option " << optopt);
	      exit(1);
	    }
	  break;

	default:
	  {
	    LOG4CXX_ERROR(p_logger, "ERROR: unrecognised command line option");
	    exit(1);
	  }
	  break; 
	}
    }

  return 0;	
}


/*
 *
 */
bool testFor( bool tTestResult, const char *ptFileName, uint32_t tLineNumber )
{
  tTestsPerformed++;

  if ( tTestResult )
  {
    tTestsPassed++;
    cout << ptFileName << "(line " << tLineNumber << "): PASS" << endl;
  }
  else
  {
    tTestsFailed++;
    cout << ptFileName << "(line " << tLineNumber << "): FAIL" << endl;
  }
  return tTestResult;
}

static void preamble()
{
  cout << "#### UnitTest testLFF ####" << endl;
}


/*
 *
 */
static void summary()
{
  if ( tTestsFailed == 0 )
    {
      cout << "PASSED unit tests. " 
	   << tTestsPerformed 
	   << " tests performed." << endl;
    }
  else
    {
      cout << "FAILED unit tests. "
	   << tTestsPerformed
	   << " tests performed, failed "
	   << tTestsFailed << "." << endl;
    }

  cout << "#### end ####" << endl;
}

int main( int argc, char ** argv )
{
  int tRet = 0;

  get_args( argc, argv );

  preamble();
    
   try
   {
     test0();
     test1();
     test2();
     test3();
   }
   catch( std::string &tExp )
   {
      cout << "Exception: \"" << tExp << "\"" << endl;
   }
   catch( ... )
   {
      cout << "Exception: caught unknown exception" << endl;
   }
   
   summary();

  if( tTestsFailed > 0 ) tRet = 1;
  return tRet;
}
