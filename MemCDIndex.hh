#ifndef MEMCD_INDEX_HH
#define MEMCD_INDEX_HH 1
// $Id$
// MemCDIndex.hh -- Exercise performance of memcached interface as lookup table.
//
// 20151023  Michael Kelsey

#include "IndexTester.hh"
#include <sys/types.h>

class memcached_st;


class MemCDIndex : public IndexTester {
public:
  MemCDIndex(int verbose=0);
  virtual ~MemCDIndex();

protected:
  virtual void create(unsigned long long asize);
  virtual int value(unsigned long long index);

  bool launchServer(unsigned long long asize);
  bool launchClient(unsigned long long asize);

  void killServer();
  void killClient();

private:
  pid_t mcdsv;			// Process ID of server, for killing
  memcached_st* memcd;		// State of memcached client
};

#endif	/* MEMCD_INDEX_HH */
