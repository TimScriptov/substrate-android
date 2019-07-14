#ifndef BIONIC_SYSTRACE_H
#define BIONIC_SYSTRACE_H
 
#include "bionic_macros.h"
 
// Tracing class for bionic. To begin a trace at a specified point:
//   ScopedTrace("Trace message");
// The trace will end when the contructor goes out of scope.
 
class __LIBC_HIDDEN__ ScopedTrace {
 public:
  explicit ScopedTrace(const char* message);
  ~ScopedTrace();
 
  void End();
 private:
  bool called_end_;
  DISALLOW_COPY_AND_ASSIGN(ScopedTrace);
};
 
void bionic_trace_begin(const char* message);
void bionic_trace_end();
 
#endif
 
