#include <iostream>
#include "Thread.h"
#include "LFFifo.h"

#include "tsdTrace.h"
#include "main.h"

using namespace std;

typedef Tsd::LFFifo< uint32_t * > TestQ;

class ProducerThread: public Tsd::Thread
{
public:
   ProducerThread( uint32_t tId, 
                   TestQ *ptQ, 
                   uint32_t tCount,
                   uint32_t tSleep = 1000 /*ns*/) :
      mId( tId ),
      mQ( ptQ ),
      mCount( tCount ),
      mSleep( tSleep )
   {
   }
   
protected:   
   virtual void run()
   {
     tsdTrace( eQuietVolume,
	       cout << "ProducerThread( " << mId << " ) starts" << endl; );

      uint32_t i = 0;
      
      while(  i < mCount )
	{
	  uint32_t *ptTemp = new uint32_t;
	  *ptTemp = 1000 + i;
	
	  tsdTrace( eQuietVolume,
		    cout << "ProducerThread( " << mId << " ) produces item " 
		    << hex << ptTemp << dec << " = " << *ptTemp << endl; );

	  //spin until we succeed inserting the item.
	  while( ! mQ -> insert( ptTemp ) )
	    {
	      sleep( 0, mSleep );
	    }

	  i++;
	}
      
      cout << "ProducerThread( " << mId << " ) done" << endl;
   }
   
private:
   uint32_t mId;
   TestQ *mQ;
   uint32_t mCount;
   uint32_t mSleep;
};


class ConsumerThread: public Tsd::Thread
{
public:
   ConsumerThread( uint32_t tId, 
                   TestQ *ptQ, 
                   uint32_t tCount,
                   uint32_t tSleep=10000 /*ns*/ ) :
      mId( tId ),
      mQ( ptQ ),
      mCount( tCount ),
      mSleep( tSleep )
   {
   }
   
protected:   
   virtual void run()
   {
     tsdTrace( eQuietVolume,
	       cout << "ConsumerThread( " << mId << " ) starts" << endl;);

      uint32_t i=0;
      uint32_t val=1000;
      uint32_t tErrs = 0;
    
      while( i < mCount )
      {
	uint32_t *ptTemp;
	
	if( mQ -> remove( ptTemp ) )
	  {
	    if( ! ptTemp )
	      {
		tErrs++;
		i++;
		continue;
	      }

	    tsdTrace( eQuietVolume,
		      cout << "ConsumerThread( " << mId 
		      << " ) consumes an item " 
		      << hex << ptTemp << dec << " = " << *ptTemp << endl; );
	    
	    if( *ptTemp != val )
	      {
		tErrs ++;
	      }

	    delete ptTemp;
	    i++;
	    val++;
	    sleep( 0, mSleep );
	  }
      }

      cout << "Consumer Thread(" << mId << "): " 
	   << tErrs << " errors " << endl;

      tsdTrace( eQuietVolume,
		cout << "ConsumerThread( " << mId << " ) done" << endl; );

   }
   
private:
   uint32_t mId;
   TestQ *mQ;
   uint32_t mCount;
   uint32_t mSleep;
};


// thread consumes on inQ and produces on outQ
class RelayThread: public Tsd::Thread
{
public:
   RelayThread( uint32_t tId, 
		TestQ *ptInQ, 
		TestQ *ptOutQ,
		uint32_t tCount,
		uint32_t tSleep=10000 /*ns*/ ) :
      mId( tId ),
      mInQ( ptInQ ),
      mOutQ( ptOutQ ),
      mCount( tCount ),
      mSleep( tSleep )
   {
   }
   
protected:   
   virtual void run()
   {
     tsdTrace( eQuietVolume,
	       cout << "RelayThread( " << mId << " ) starts" << endl;);

      uint32_t i=0;
      uint32_t val=1000;
      uint32_t tErrs = 0;
    
      while( i < mCount )
      {
	uint32_t *ptTemp;
	
	
	if( mInQ -> remove( ptTemp ) )
	  {
	    if( ! ptTemp )
	      {
		tErrs++;
		i++;
		continue;
	      }

	    tsdTrace( eQuietVolume,
		      cout << "RelayThread( " << mId 
		      << " ) consumes an item " 
		      << hex << ptTemp << dec << " = " << *ptTemp << endl; );
	    
	    if( *ptTemp != val )
	      {
		tErrs ++;
	      }

	    i++;
	    val++;

	    sleep( 0, mSleep );

	    // stick the item in the output Q.
	    while( !mOutQ -> insert( ptTemp ) );

	  }
      }

      cout << "Relay Thread(" << mId << "): " << tErrs << " errors " << endl;

      tsdTrace( eQuietVolume,
		cout << "RelayThread( " << mId << " ) done" << endl; );

   }
   
private:
   uint32_t mId;
   TestQ *mInQ;
   TestQ *mOutQ;
   uint32_t mCount;
   uint32_t mSleep;
};


void test0()
{
  uint32_t i;
  cout << "TEST 0 - Start" << endl;

  Tsd::LFFifo< uint32_t > tQ(100);

  tsdTrace( eQuietVolume,  cout << "Filling Q" << endl;);
  for( i = 0; i < 100; i++ )
    {
      tsdTrace( eQuietVolume,  cout << i << ":";);
      TEST_FOR( tQ.insert( i ) );
    }
  
  tsdTrace( eQuietVolume,  cout << "Test Overfill" << endl;);
  for( i = 100; i < 200; i++ )
    {
      tsdTrace( eQuietVolume,  cout << i << ":";);
      TEST_FOR( !tQ.insert(i) );
    }
    
  tsdTrace( eQuietVolume,  cout << "Test Removal" << endl;);
  for( i = 0; i < 100; i++ )
    {
      tsdTrace( eQuietVolume,  cout << i << ":";);
      uint32_t tItem=101;
      TEST_FOR(  tQ.remove( tItem ) );
      TEST_FOR( tItem == i );
    }

  tsdTrace( eQuietVolume,  cout << "Test Underflow" << endl;);
  for( i = 100; i < 200; i++ )
    {
      tsdTrace( eQuietVolume,  cout << i << ":";);
      uint32_t tItem;
      TEST_FOR( !tQ.remove( tItem ) );
    }

   cout << "TEST 0 - End" << endl;
}

void test1()
{
   cout << "TEST 1 - Start" << endl;
   const uint32_t tNQ = 10;
   const uint32_t tQSz = 100;
   TestQ * ptQs[tNQ];
   uint32_t tId = 1;

   //create queues
   for( uint32_t i = 0; i < tNQ; i++ )
     ptQs[i] = new TestQ( tQSz );


   // create producers/consumers
   ProducerThread tTP( tId++ , ptQs[ 0 ], 5000 );

   RelayThread * ptRelays[ tNQ - 1 ];

   for( uint32_t i=0; i < tNQ - 1; i++ )
     {
       ptRelays[i] = new RelayThread( tId++, ptQs[ i ], ptQs[ i + 1 ], 5000 );
     }

   ConsumerThread tTC( tId, ptQs[ tNQ - 1 ], 5000 );

   
   // start consumer thread
   TEST_FOR( tTC.start() );

   // start relay threads
   for( uint32_t i=0; i < tNQ - 1; i++ )
     {
       TEST_FOR( ptRelays[ i ] -> start() );
     }

   // start producer thread
   TEST_FOR( tTP.start() );

   tTC.join();

   for( uint32_t i=0; i < tNQ - 1; i++ )
     {
       ptRelays[ i ] -> join();
     }

   tTP.join();

   // delete the relay threads.
   for( uint32_t i=0; i < tNQ - 1; i++ )
     {
       delete ptRelays[ i ];
     }

   // delete the queues
   for( uint32_t i = 0; i < tNQ; i++ )
     delete ptQs[ i ];

   cout << "TEST 1 - End" << endl << endl;
}

