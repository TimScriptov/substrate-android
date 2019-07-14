#pragma once
 
#include <android/dlext.h>
#include "linked_list.h"
 
// TODO(dimitry): move this to linker_defines.h? Unless it is removed by
// consequent refactoring steps.
 
// Android uses RELA for aarch64 and x86_64. mips64 still uses REL.
#if defined(__aarch64__) || defined(__x86_64__)
#define USE_RELA 1
#endif
 
 
struct soinfo;
 
class SoinfoListAllocator {
 public:
  static LinkedListEntry<soinfo>* alloc();
  static void free(LinkedListEntry<soinfo>* entry);
 
 private:
  // unconstructable
  DISALLOW_IMPLICIT_CONSTRUCTORS(SoinfoListAllocator);
};
 
class NamespaceListAllocator {
 public:
  static LinkedListEntry<android_namespace_t>* alloc();
  static void free(LinkedListEntry<android_namespace_t>* entry);
 
 private:
  // unconstructable
  DISALLOW_IMPLICIT_CONSTRUCTORS(NamespaceListAllocator);
};
 
typedef LinkedList<soinfo, SoinfoListAllocator> soinfo_list_t;
typedef LinkedList<android_namespace_t, NamespaceListAllocator> android_namespace_list_t;
 
