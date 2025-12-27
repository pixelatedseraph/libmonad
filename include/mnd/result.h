#ifndef MND_RESULT_H
#define MND_RESULT_H

#include<errno.h>

#define MND_DEFINE_RESULT(T, Name)  \
                                    \
typedef struct                      \
{                                   \
    int ok;           /* Enumerates the state of a function ,Safe State - '1' , Unsafe State - '0' Followed by ErrorCode*/   \
    int err;          /* Holds Error Code , Describes Unsafe state  */  \
    T   value;        /* Holds actual value of 'ok' state*/             \
} Result_##Name;                                                        \
                                                                        \
static inline Result_##Name                                             \ 
Result_##Name##_ok(T v)                                                 \
{                                                                       \
    return (Result_##Name) (.ok = 1 , .value = v);                      \
}                                                                       \
static inline Result_##Name                                             \
Result_#Name##_err(int err_code)                                        \
{                                                                       \
    return (Result_##Name)\ (.ok = 0, .err = err_code);                 \
}                                                                       \

/* Accessor Macros for a given function returning Result_* Monad */

#define MND_OK(_res) ((_res).ok)
#define MND_ERR(_res) ((_res).err)
#define MND_VAL(_res) ((_res).value)

#endif