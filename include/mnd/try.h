#ifndef MND_TRY_H
#define MND_TRY_H

/*
*   MND_UNWRAP : Unwraps Result_T -> T | Result_T (propogation)
*   invalid 'ok' causes the callee function to return and propogate the error upwards
*   valid 'ok' causes the unwraping of value stored in the Result_*
*   Returns 1.) T when ok ==1, 2.) Result_T when ok == 0
*/

#define MND_UNWRAP(Name,expr) \
({\
    Result_##Name _r = (expr);\
    if(!_r.ok) return _r; \
    _r.value;            \
 }) \

/*
*   MND_OR_ELSE : Unwraps Result_T -> Result_T(All cases)
*   invalid 'ok' proceeds with the fallback computation case while still being Result_T type
*   valid 'ok' proceeds with provided computation
*   Returns Result_T in all cases
*/

#define MND_OR_ELSE(NAME,expr,fallback) \
({  \
    Result_##Name _r = (expr);  \
    _r.ok ? _r : (default);   \
}) \

/*
*   MND_UNWRAP_OR_DEFAULT : Unwraps Result_T -> T | Default
*   invalid 'ok' returns default_value specified by callee
*   valid 'ok' proceeds with unwrapping Result_T
*   Returns 1.)T if valid 'ok' 2.) Default
*/

#define MND_UNWRAP_OR_DEFAULT(Name,expr, default_value) \
({      \
    Result_##Name _r = (expr); \
    _r.ok ? _r.value : (default_value); \
})    \

/*
*   MND_MAP : Unwraps Result_T -> fn(T) | Result_T
*   invalid 'ok' returns Result_T with errors propogating upwards
*   valid 'ok' proceeds with unwrapping Result_T and apply transformation fn to T
*   Returns 1.)fn(T) if valid 'ok' 2.) Result_T
*/

#define MND_MAP(Name,expr,fn) \
({\
    Result_##Name _r = (expr); \
    _r.ok ? fn(_r.value) : _r: \
})\


#endif
