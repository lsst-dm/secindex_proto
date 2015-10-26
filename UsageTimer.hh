#ifndef USAGE_TIMER_HH
#define USAGE_TIMER_HH 1
// $Id$
// UsageTimer.hh -- Utility to wrap getrusage() for collecting data within
// a program.
//
// 20151023  Michael Kelsey
// 20151026  Add access to memory usage (multiply by ticks)

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <iosfwd>

// Global operators to do timeval arithmetic, used by UsageTimer

struct timeval operator+(const struct timeval& tva, const struct timeval& tvb);
struct timeval operator-(const struct timeval& tva, const struct timeval& tvb);
struct timeval& operator+=(struct timeval& tva, const struct timeval& tvb);
struct timeval& operator-=(struct timeval& tva, const struct timeval& tvb);

// Global operators to do rusage arithmetic, used by UsageTimer
 
struct rusage operator+(const struct rusage& rua, const struct rusage& rub);
struct rusage operator-(const struct rusage& rua, const struct rusage& rub);
struct rusage& operator+=(struct rusage& rua, const struct rusage& rub);
struct rusage& operator-=(struct rusage& rua, const struct rusage& rub);

// Class to do incremental timing

class UsageTimer {
public:
  UsageTimer() { zero(); }
  ~UsageTimer() {;}

  void zero(); 			// Reset total count
  void start();			// Begin recording
  void end();			// Finish recording
  void report(std::ostream& os) const; 		// Print results, like |time|

  double userTime() const { return uTotal.ru_utime.tv_sec+uTotal.ru_utime.tv_usec/1e6; }
  double sysTime() const { return uTotal.ru_stime.tv_sec+uTotal.ru_stime.tv_usec/1e6; }
  double elapsed() const { return (double)tTotal/CLOCKS_PER_SEC; }
  double cpuEff() const { return (userTime()+sysTime())/elapsed(); }
  long maxMemory() const { return uTotal.ru_maxrss; }
  double memoryText() const { return (double)uTotal.ru_ixrss/tTotal; }
  double memoryData() const { return (double)uTotal.ru_idrss/tTotal; }
  double memoryStack() const { return (double)uTotal.ru_isrss/tTotal; }
  long pageFaults() const { return uTotal.ru_majflt; }
  long swaps() const { return uTotal.ru_nswap; }
  long ioInput() const { return uTotal.ru_inblock; }
  long ioOutput() const { return uTotal.ru_oublock; }

private:
  struct rusage uStart;	// Collects usage information for report
  struct rusage uEnd;
  struct rusage uTotal;

  clock_t tStart;		// Collects simple elapsed time, for report
  clock_t tEnd;
  clock_t tTotal;

  static const struct rusage uZero;
};


// Allow direct output of "report()" format

inline std::ostream& operator<<(std::ostream& os, const UsageTimer& usage) {
  usage.report(os);
  return os;
}


#endif	/* USAGE_TIMER_HH */
