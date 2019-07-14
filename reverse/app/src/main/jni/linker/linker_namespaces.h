#pragma once
 
#include "linker_common_types.h"
 
#include <string>
#include <vector>
#include <unordered_set>
 
struct android_namespace_t;
 
struct android_namespace_link_t {
 public:
  android_namespace_link_t(android_namespace_t* linked_namespace,
                           const std::unordered_set<std::string>& shared_lib_sonames,
                           bool allow_all_shared_libs)
      : linked_namespace_(linked_namespace), shared_lib_sonames_(shared_lib_sonames),
        allow_all_shared_libs_(allow_all_shared_libs)
  {}
 
  android_namespace_t* linked_namespace() const {
    return linked_namespace_;
  }
 
  const std::unordered_set<std::string>& shared_lib_sonames() const {
    return shared_lib_sonames_;
  }
 
  bool is_accessible(const char* soname) const {
    if (soname == nullptr) {
      return false;
    }
    return allow_all_shared_libs_ || shared_lib_sonames_.find(soname) != shared_lib_sonames_.end();
  }
 
  bool allow_all_shared_libs() const {
    return allow_all_shared_libs_;
  }
 
 private:
  android_namespace_t* const linked_namespace_;
  const std::unordered_set<std::string> shared_lib_sonames_;
  bool allow_all_shared_libs_;
};
 
struct android_namespace_t {
 public:
  android_namespace_t() : name_(nullptr), is_isolated_(false), is_greylist_enabled_(false) {}
 
  const char* get_name() const { return name_; }
  void set_name(const char* name) { name_ = name; }
 
  bool is_isolated() const { return is_isolated_; }
  void set_isolated(bool isolated) { is_isolated_ = isolated; }
 
  bool is_greylist_enabled() const { return is_greylist_enabled_; }
  void set_greylist_enabled(bool enabled) { is_greylist_enabled_ = enabled; }
 
  const std::vector<std::string>& get_ld_library_paths() const {
    return ld_library_paths_;
  }
  void set_ld_library_paths(std::vector<std::string>&& library_paths) {
    ld_library_paths_ = library_paths;
  }
 
  const std::vector<std::string>& get_default_library_paths() const {
    return default_library_paths_;
  }
  void set_default_library_paths(std::vector<std::string>&& library_paths) {
    default_library_paths_ = library_paths;
  }
  void set_default_library_paths(const std::vector<std::string>& library_paths) {
    default_library_paths_ = library_paths;
  }
 
  const std::vector<std::string>& get_permitted_paths() const {
    return permitted_paths_;
  }
  void set_permitted_paths(std::vector<std::string>&& permitted_paths) {
    permitted_paths_ = permitted_paths;
  }
  void set_permitted_paths(const std::vector<std::string>& permitted_paths) {
    permitted_paths_ = permitted_paths;
  }
 
  const std::vector<android_namespace_link_t>& linked_namespaces() const {
    return linked_namespaces_;
  }
  void add_linked_namespace(android_namespace_t* linked_namespace,
                            const std::unordered_set<std::string>& shared_lib_sonames,
                            bool allow_all_shared_libs) {
    linked_namespaces_.push_back(
        android_namespace_link_t(linked_namespace, shared_lib_sonames, allow_all_shared_libs));
  }
 
  void add_soinfo(soinfo* si) {
    soinfo_list_.push_back(si);
  }
 
  void add_soinfos(const soinfo_list_t& soinfos) {
    for (auto si : soinfos) {
      add_soinfo(si);
    }
  }
 
  void remove_soinfo(soinfo* si) {
    soinfo_list_.remove_if([&](soinfo* candidate) {
      return si == candidate;
    });
  }
 
  const soinfo_list_t& soinfo_list() const { return soinfo_list_; }
 
  // For isolated namespaces - checks if the file is on the search path;
  // always returns true for not isolated namespace.
  bool is_accessible(const std::string& path);
 
  // Returns true if si is accessible from this namespace. A soinfo
  // is considered accessible when it belongs to this namespace
  // or one of it's parent soinfos belongs to this namespace.
  bool is_accessible(soinfo* si);
 
  soinfo_list_t get_global_group();
  soinfo_list_t get_shared_group();
 
 private:
  const char* name_;
  bool is_isolated_;
  bool is_greylist_enabled_;
  std::vector<std::string> ld_library_paths_;
  std::vector<std::string> default_library_paths_;
  std::vector<std::string> permitted_paths_;
  // Loader looks into linked namespace if it was not able
  // to find a library in this namespace. Note that library
  // lookup in linked namespaces are limited by the list of
  // shared sonames.
  std::vector<android_namespace_link_t> linked_namespaces_;
  soinfo_list_t soinfo_list_;
 
  DISALLOW_COPY_AND_ASSIGN(android_namespace_t);
};
 
