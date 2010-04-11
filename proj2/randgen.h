/*****************************************************************************
 *  FILE: randgen.h                                                          *
 *  Random number generator class --- wrapper for rand48                     *
 *  Constructors:                                                            *
 *    randgen( long int seed ) provides random sequence starting from seed   *
 *    randgen( ) provides random sequence seeded from one of two sources:    *
 *     on systems with a kernel random source (/dev/urandom) it will be      *
 *      seeded from it (this is reasonably robust)                           *
 *     on systems without /dev/urandom, it will be seeded from system        *
 *      time, which means randgens declared in proximity are highly          *
 *      likely to be seeded with the same value.  Don't do this (see USAGE). *
 *                                                                           *
 *  Access methods:                                                          *
 *    drand48( ) returns doubles uniformly distributed over [0.0..1.0)       *
 *    lrand48( ) returns long ints uniformly distributed over [0.0..2^31)    *
 *    mrand48( ) returns long ints uniformly distributed over (-2^31..2^31)  *
 *    randInt( long int beg, long int end )                                  *
 *        returns long ints uniformly distributed over [beg..end)            *
 *    randDbl( double beg, double end )                                      *
 *        returns doubles uniformly distributed over [beg..end)              *
 *                                                                           *
 *  USAGE: It is best to think of these objects as returning a stream of     *
 *    random numbers rather than individual numbers.  Each instance of       *
 *    the class provides its own stream.  The generator is initialized       *
 *    when the instance is declared.  Thus the lifetime of the instance must *
 *    span all uses of the numbers from that stream.  This usually implies   *
 *    that instances should not be local to functions unless each invocation *
 *    uses the entire stream.  Also, in the case that these cannot be seeded *
 *    from /dev/urandom instances that are constructed in close proximity    *
 *    in time (on the order of < 1 millisecond) will be seeded identically.  *
 *    Instead of local instances a single instance should be declared at a   *
 *    level that encompasses all uses of the stream, which can then be       *
 *    passed _by_reference_ to each function that uses it.                   *
 *                                                                           *
 *  LIBRARIES: cstdlib --- for Xrand48()                                     *
 *****************************************************************************/
#ifndef Randgen_H
#define Randgen_H

#include<cstdlib>

class randgen
{
 public:
  randgen( );
  randgen( long int seed );

  // random double uniformly distributed over [0.0..1.0)
  double drand48(void) {return erand48( Xi );}

  // random long int uniformly distributed over [0.0..2^31)
  long int lrand48(void) {return nrand48( Xi ); }
  
  // random long int uniformly distributed over (-2^31..2^31)
  long int mrand48(void) {return jrand48( Xi ); }

  // random long int uniformly distributed over [beg..end)
  // PRECONDITION: beg < end
  long int randInt( long int beg, long int end );
  
  // random double uniformly distributed over [beg..end)
  // PRECONDITION: beg < end
  double randDbl( double beg, double end );

 private:
  unsigned short int Xi[3];  // Current state

};
#endif
