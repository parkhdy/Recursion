/*****************************************************************************
 *  FILE: randgen.cpp                                                        *
 *  Random number generator class --- wrapper for rand48                     *
 *                                                                           *
 *  LIBRARIES: cstdlib --- for Xrand48()                                     *
 *             cassert --- for assert()                                      *
 *             unistd.h --- for read()                                       *
 *             fcntl.h --- for open() and O_RDONLY                           *
 *             sys/time.h --- for timeval                                    * 
 *****************************************************************************/
#include "randgen.h"
#include <cassert>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

using namespace std;

randgen::randgen( ) 
{ 
  // Seed from kernel random source, if possible
  int krand = open( "/dev/urandom", O_RDONLY);
  if ( krand != -1 )
    {
      read( krand, Xi, 6);
      close( krand );
    }
  else
    {
      // no kernel random source, init from time
      // Beware of this, multiple instances are in danger of being
      //  seeded identically
      struct timeval t;
      gettimeofday( &t, NULL );
      Xi[0] = t.tv_usec & 0xffff;
      Xi[1] = ( t.tv_usec >> 16 ) & 0xffff;
      Xi[2] =  t.tv_sec & 0xffff;
    }
}

randgen::randgen( long int seed ) 
{
  // Bi-endian? little-endian? Does it matter?
  Xi[0] = ( seed >> 16 ) & 0xffff;
  Xi[1] = seed & 0xffff;
  Xi[2] = 0x330E;
}

// random long int uniformly distributed over [beg..end)
// PRECONDITION: beg < end
long int randgen::randInt( long int beg, long int end )
{
  assert( beg < end );
  return (static_cast<long int>( (end - beg)*erand48( Xi ) + beg) );
}
  
// random double uniformly distributed over [beg..end)
// PRECONDITION: beg < end
double randgen::randDbl( double beg, double end )
{
  assert( beg < end );
  return ( (end - beg)*erand48( Xi ) + beg );
}


