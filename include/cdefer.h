#pragma once

#include <stddef.h>

#ifdef __cplusplus
#  error "cdefer.h is a C-only header"
#endif

// tool for generating unique names
#define DEFER_CONCAT(a, b) DEFER_CONCAT_INNER(a, b)
#define DEFER_CONCAT_INNER(a, b) a##b
#define DEFER_UNIQUE_NAME(base) DEFER_CONCAT(base, __COUNTER__)

// defer implementation
#if defined(__GNUC__) && !defined(__clang__)
// if gcc
// has cleanup attribute and nested functions
#  if !defined(__has_attribute)
#    error "defer requires __has_attribute support"
#  else

#    if !__has_attribute(cleanup)
#      error "defer requires cleanup attribute support"
#    else

#      define DEFER_IMPL(fname, phname, ...)                                   \
        void fname(int**)                                                      \
        {                                                                      \
          __VA_ARGS__                                                          \
        }                                                                      \
        int* phname __attribute__((cleanup(fname), unused)) = NULL
#      define DEFER(...)                                                       \
        DEFER_IMPL(DEFER_UNIQUE_NAME(defer_block),                             \
                   DEFER_UNIQUE_NAME(defer_block_ph),                          \
                   __VA_ARGS__)
#      define DEFER_IF(cond, ...) DEFER(if (cond){ __VA_ARGS__ })

#    endif
#  endif
#elif defined(__clang__)
// if clang
#  if (!defined(__has_feature) || !defined(__has_attribute))
#    error "defer requires __has_feature and __has_attribute support"
#  else

#    if (!__has_feature(blocks) || !__has_attribute(cleanup))
#      error "defer requires blocks and cleanup attribute support"
#    else

void
defer_block_cleanup(void (^*block)(void))
{
  if (*block) {
    (*block)();
  }
}

#      define DEFER(...)                                                       \
        void (^DEFER_UNIQUE_NAME(defer_block))(void)                           \
          __attribute__((cleanup(defer_block_cleanup), unused)) = (^{          \
            __VA_ARGS__ })
#      define DEFER_IF(cond, ...) DEFER(if (cond){ __VA_ARGS__ })

#    endif
#  endif
#else
#  error "defer is not supported on this platform"
#endif
