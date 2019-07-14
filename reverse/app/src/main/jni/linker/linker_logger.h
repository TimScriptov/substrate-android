#pragma once
 
#include <stdlib.h>
#include <limits.h>
#include "private/bionic_macros.h"
#include "private/bionic_systrace.h"
 
#define LD_LOG(type, x...) \
  { \
    g_linker_logger.Log(type, x); \
  }
 
constexpr const uint32_t kLogErrors = 1 << 0;
constexpr const uint32_t kLogDlopen = 1 << 1;
constexpr const uint32_t kLogDlsym  = 1 << 2;
 
class LinkerLogger {
 public:
  LinkerLogger() : flags_(0) { }
 
  void ResetState();
  void Log(uint32_t type, const char* format, ...);
 private:
  uint32_t flags_;
 
  DISALLOW_COPY_AND_ASSIGN(LinkerLogger);
};
 
extern LinkerLogger g_linker_logger;
extern char** g_argv;
 
// If the system property debug.ld.greylist_disabled is true, we'll not use the greylist
// regardless of API level.
extern bool g_greylist_disabled;
 
