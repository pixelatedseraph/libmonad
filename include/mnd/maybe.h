#ifndef MAYBE_H
#define MAYBE_H

#define MND_DEFINE_MAYBE(T, Name)       \
typedef struct                          \
{                                       \
    int exists;                         \
    T   value;                          \
}MAYBE_##Name;                          \
                                        \
static inline MAYBE_##Name              \
Maybe_##Name##_some(T v)                \
{                                       \
    return (MAYBE_##Name) {.exists = 1 , .value = v }; \
}                                                       \
                                         \
static inline MAYBE_##Name               \
Maybe_##Name##_none(void)                \
{                                        \
    return (MAYBE_##Name) {.exists = 0}; \
} \

/* Accessor Macros for Maybe_T */

#define MND_HAS(_res) ((_res).exists)
#define MND_UNBOX(_res) ((_res).value)

#endif 