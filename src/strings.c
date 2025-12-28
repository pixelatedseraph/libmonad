#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"strings.h"
#include<ctype.h>
#include<stdbool.h>

static string** registry;
static size_t   reg_count = 0;
static size_t   reg_cap = 0;     

static void register_string(string* _str_obj){
    if (reg_count == reg_cap){
        reg_cap = reg_cap ? reg_cap * 2 : 4;
        registry = realloc(registry,sizeof(string*) * reg_cap );
        if (!registry) {exit(1);}
    }
    registry[reg_count++] = _str_obj;
}

/**
 * method to generate string_objects on heap
 * @param  sequence of characters
 * @return string_object(deep copy)
 */

string* new_string(const char* str ){
    if (!str) { exit(1);}
    string* _str_obj = malloc(sizeof(string));
    if (!_str_obj)  { exit(1);}
    size_t _ln_str = strlen(str);
    size_t cap = _ln_str * 2 + 1;
    _str_obj -> data  = malloc(cap);
    if (!_str_obj -> data) {exit(1);}
    memcpy(_str_obj->data , str , _ln_str);
    _str_obj->data [_ln_str] = '\0';
    _str_obj -> length = _ln_str;
    _str_obj -> capacity = cap;
    register_string(_str_obj);
    return _str_obj;
}

/**
 * method for generate a empty string
 * @param  void 
 * @return string_object(deep copy)
 */

string* empty_string(){
    string* _str_obj = malloc(sizeof(string));
    if (!_str_obj)  { exit(1);}
    size_t len = 0;
    size_t cap = len * 2 + 1;
    _str_obj -> data  = malloc(cap);
    if (!_str_obj -> data) {exit(1);}
    _str_obj -> data [0] = '\0';
    _str_obj -> length = len;
    _str_obj -> capacity = cap;
    register_string(_str_obj);
    return _str_obj;
}

/**
 * method for adding more characters to an existing string
 * @param  string_object , sequence of chars 
 * @return string_object(deep copy)
 */

string* append_string(string* _str_obj,const char* new){
    if (!new) {exit(0);}
    if (!_str_obj ) {exit(0);}
    if (!_str_obj ->data) {exit(0);}
    size_t _ln_new = strlen(new);
    size_t _ln_old = strlen(_str_obj->data);
    size_t _cap = _str_obj->capacity;
    size_t needed = _str_obj ->length + _ln_new + 1;
    int reg_idx = -1;
    for  (size_t i = 0 ; i < reg_count ; ++i){
    if (registry[i] == _str_obj ) {
        reg_idx = i;
        break;
        } 
    }
    size_t new_cap = _str_obj->capacity;
    if (needed > _str_obj->capacity) {
        while (needed > new_cap){
            new_cap = new_cap * 2 + 1;
        }
        _str_obj ->data = realloc(_str_obj->data,new_cap);
        if (!_str_obj->data) exit(1);
        registry[reg_idx] = _str_obj;
    }
    memcpy((_str_obj->data)+ _ln_old , new, _ln_new );
    _str_obj->data[_ln_old + _ln_new] = '\0';
    _str_obj->length += _ln_new;
    _str_obj->capacity = new_cap;
    return _str_obj;
}


/**
 * method to extract a sub-string from a string 
 * @param string_object , starting index , ending index
 * @return string_object ,(deep copy)
 */

string* sub_string(string* _str_obj , size_t start , size_t end){
    if (!_str_obj) exit(1);
    if (!_str_obj ->data) exit(1);
    if(start > end) exit(1);
    if (start == end) { fprintf(stderr,"call 'char_at()' instead\n"); exit(1); }
    if (end  > _str_obj -> length) { exit(1); }
    string* _str_buff = empty_string();
    char buff [8192]; // 8 kb stack alloc'd buffer
    size_t idx_test = 0;
    for (size_t itr = start ; itr <= end ; ++itr){
        buff[idx_test++] = _str_obj->data[itr];
    }
    buff[idx_test] = '\0';
    return _str_buff = append_string(_str_buff,buff);
 /*    size_t idx = 0;
    for (size_t itr = start ; itr <= end ; ++itr ){
        _str_buff->data[idx++]  = _str_obj->data[itr];
    }
    return _str_buff; */
}

/**
 * utility method for enquiring arbitrary character of valid bounds within a string 
 * @param string_object , index at which character is required
 * @return character at index provided
 */

char char_at(string *_str_obj,size_t idx){
    if (!_str_obj) exit(1);
    if (_str_obj->length <= idx) exit(1);
    return _str_obj->data[idx];
}

/**
 * utility method for enquiring length of string 
 * @param string_object  
 * @return length of string
 */

size_t get_length(string *_str_obj){
    if (!_str_obj || !_str_obj ->data) exit(1);
    return _str_obj -> length;
}

/**
 * utility method for comparing two string_objects 
 * @param string_object , string_object
 * @return 0 if both are same , 1 if s1 > s2 , -1 if s2 > s1
 */

int compare_string(string *_str_obj1 , string  *_str_obj2){
    if (!_str_obj1 || !_str_obj2) exit(1);
    if (!_str_obj1 ->data || !_str_obj2 -> data ) exit(1);
    int res =  strcmp(_str_obj1->data , _str_obj2->data);
    return res;
}

/**
 * utility method for checking if two strings are equal 
 * @param string_object , string_object 
 * @return boolean , true if same 
 */

bool string_equals(string *_str_obj1 , string *_str_obj2){
    if (!_str_obj1 || !_str_obj2) exit(1);
    if (!_str_obj1 ->data || !_str_obj2 -> data ) exit(1);
    return strcmp(_str_obj1->data,_str_obj2->data) ? false : true;
}

/**
 * utility method for removing white space in strings from both sides(doesnt elimante  space in between of string object)
 * @param string_object 
 * @return string_object (deep copy)
 */

string* trim(string *_str_obj){
    if (!_str_obj) exit(1);
    if (!_str_obj->data) exit(1);
    size_t start = -1;
    size_t end = -1; 
    for (size_t i = 0 ; i < _str_obj -> length ; ++i){
        if (_str_obj->data[i] == ' ') continue;
        start = i;
        break;
    }
    for (size_t i = _str_obj ->length - 1; i > start ; --i){
        if (_str_obj->data[i] == ' ') continue;
        end = i;
        break;
    }
    return sub_string(_str_obj,start,end); // <- deep copy 
}


/**
 * utility method for removing white space from left side only
 * @param string_object 
 * @return string_object (deep copy)
 */

string* trim_left(string *_str_obj){
    if (!_str_obj) exit(1);
    if (!_str_obj->data) exit(1);
    size_t start = -1;
    size_t end = _str_obj->length -1;
    for (size_t itr = 0 ; itr < _str_obj ->length ; ++itr ){
        if(_str_obj->data[itr] == ' ') continue;
        start = itr;
        break;
    }
    return sub_string(_str_obj,start,end); // <- deep copy
}

/**
 * utility method for removing white space in strings from right side only
 * @param string_object 
 * @return string_object (deep copy)
 */

string* trim_right(string *_str_obj){
    if (!_str_obj) exit(1);
    if (!_str_obj->data) exit(1);
    size_t start = 0;
    size_t end =  -1;
    for (size_t itr = _str_obj->length -1 ; itr > start ; --itr ){
        if(_str_obj->data[itr] == ' ') continue;
        end = itr;
        break;
    }
    return sub_string(_str_obj,start,end); // <- deep copy
}


/**
 * utility method to mutate to uppercase  
 * @param string_object  
 * @return string object , modifies in place
 */

string* to_upper(string* _str_obj){
    if (!_str_obj) exit(1);
    if (!_str_obj->data) exit(1);
    for (size_t i = 0 ; i < _str_obj->length ; ++i){
        char ch = _str_obj->data[i];
        if (ch >=97 && ch <= 122){
            _str_obj->data[i] = ch - 32;
        } 
    }
    return _str_obj;
}


/**
 * utility method to mutate to lowercase
 * @param string_object  
 * @return string object, modifies in place
 */

string* to_lower(string* _str_obj){
    if (!_str_obj) exit(1);
    if (!_str_obj->data) exit(1);
    for (size_t i = 0 ; i < _str_obj -> length ; ++i){
        char ch = _str_obj->data[i];
        if (ch >= 65 && ch <= 90){
            _str_obj->data[i] = ch + 32;
        }
    }
    return _str_obj;
}

/**
 * utility method to deep copy a string 
 * @param string_object  
 * @return string object, clones the param and allocates space 
 */

string* clone(string* _str_obj){
    if (!_str_obj) exit(1);
    if (!_str_obj->data) exit(1);
    int start = 0;
    int end = _str_obj->length -1 ;
    return sub_string(_str_obj,start,end);
}

/**
 * utility method to search for a pattern in a given string object
 * @param string_object , pattern
 * @return print statement with highlighted word,this fucntion will match for the pattern only once and terminates , will write fully functional grep-like system later 
 */

void match(string* _str_obj,const char* pattern){
    if(!_str_obj) exit(1);
    if(!_str_obj->data) exit(1);
    size_t _ln_p = strlen(pattern);
    size_t _ln_t = _str_obj->length;
    if (_ln_p > _ln_t) exit(1);
    for (size_t m = 0 ; m < _ln_t ; ++m){
        if (_str_obj->data[m] == pattern[0]) {
            int matched = 1;
            for (size_t i = 1; i < _ln_p ; ++i){
                if(!(_str_obj->data[m+i] == pattern[0+i])){
                    matched = 0;
                    break;
                }
            }
            if(matched){
                //white text
                if (m>0){
                for (int i = 0; i < m ; ++i){
                    char ch = _str_obj->data[i];
                    printf("%c",ch);
                }
                //colored text
                for (int i = m ; i < m+_ln_p ; ++i){
                    char ch = _str_obj->data[i];
                    printf("\033[31m%c\033[0m",ch);
                }
                //rest of the text
                for (int i = m+_ln_p ; i < _ln_t ; ++i){
                    char ch = _str_obj->data[i];
                    printf("%c",ch);
                }
                printf("\n");
            }
            else{
                //color
                for (int i = m ; i < m+_ln_p ; ++i){
                char ch = _str_obj-> data[i];
                printf("\033[31m%c\033[0m",ch);
                }
                // white
                for (int i = m +_ln_p  ; i < _ln_t ; ++i){
                    char ch = _str_obj->data[i];
                    printf("%c",ch);
                }
                printf("\n");
                }
            }
        }
    }
}


/**
 * static method to search for a pattern in a given string objects 
 * @param string_object , pattern
 * @return print statement with highlighted word and MatchRes struct optional for caller, which prvides starting index and offset
 */

typedef struct MatchRes
{
    size_t start;
    size_t offset;

} MatchRes;
/* private function */
static MatchRes _match(string* _str_obj,const char* pattern){
    if(!_str_obj) exit(1);
    if(!_str_obj->data) exit(1);
    size_t _ln_p = strlen(pattern);
    size_t _ln_t = _str_obj->length;
    if (_ln_p > _ln_t) exit(1);
    for (size_t m = 0 ; m < _ln_t ; ++m){
        if (_str_obj->data[m] == pattern[0]) {
            int matched = 1;
            for (size_t i = 1; i < _ln_p ; ++i){
                if(!(_str_obj->data[m+i] == pattern[0+i])){
                    matched = 0;
                    break;
                }
            }
            if(matched){
                //white text
                if (m>0){
                /* for (int i = 0; i < m ; ++i){
                    char ch = _str_obj->data[i];
                    printf("%c",ch);
                }
                //colored text
                for (int i = m ; i < m+_ln_p ; ++i){
                    char ch = _str_obj->data[i];
                    printf("\033[31m%c\033[0m",ch);
                }
                //rest of the text 
                for (int i = m+_ln_p ; i < _ln_t ; ++i){
                    char ch = _str_obj->data[i];
                    printf("%c",ch);
                }
                printf("\n"); */
                return (MatchRes){m,_ln_p} ;
            }
            else{
                //color
              /*   for (int i = m ; i < m+_ln_p ; ++i){
                char ch = _str_obj->data[i];
                printf("\033[31m%c\033[0m",ch);
                }
                // white
                for (int i = m +_ln_p ; i < _ln_t ; ++i){
                    char ch = _str_obj->data[i];
                    printf("%c",ch);
                }
                printf("\n"); */
                return (MatchRes){m,_ln_p};
                }
            }
        }
    }
    return (MatchRes){-1,-1};
}



/**
 * utility method to replace a slice of string with something else 
 * @param string_object, old pattern , new pattern
 * @return print statement with a highlighted replaced word
 */

void replace(string* _str_obj, const char *_p1, const char *_p2){
    if(!_str_obj) exit(1);
    if(!_str_obj->data) exit(1);
    if(!_p1) exit(1);
    if(!_p2) exit(1);
    size_t _ln_p1 = strlen(_p1);
    size_t _ln_p2 = strlen(_p2);
    if (_ln_p1 == _ln_p2){
        MatchRes _m_res = _match(_str_obj , _p1);
        for (int itr = _m_res.start,idx = 0 ; 
            itr <= _m_res.start + _m_res.offset && idx < _ln_p2 ; 
            ++itr, ++idx)
        {    
            _str_obj->data[itr] = _p2[idx];
        }
    }
    else if (_ln_p1 > _ln_p2){
        MatchRes _m_res = _match(_str_obj , _p1);
        int itr , idx;
        for (itr = _m_res.start, idx = 0 ; 
        itr <= _m_res.start + _m_res.offset && idx < _ln_p2 ; 
        ++itr, ++idx)
        {    
            _str_obj->data[itr] = _p2[idx];
        }
       _str_obj->data[itr] = '\0';
       size_t _offset = _ln_p1 - _ln_p2;
       _str_obj->length -= _offset;
    }

    else{
        MatchRes _m_res = _match(_str_obj , _p1);
        size_t _ln_mod = _str_obj->length - (_m_res.start + _m_res.offset);
        size_t _need = _ln_mod + strlen(_p1);
        if (_need < _str_obj->capacity){
            int itr , idx;
            char buff [8192] = {0};
            memcpy(buff,_p1,_ln_p1); 
            for (itr = _m_res.start, idx = 0 ; 
            itr < _m_res.start + _m_res.offset && idx < _ln_p2 ; 
            ++itr, ++idx)
            {    
            _str_obj->data[itr] = _p2[idx];
            }  
            size_t _new_len = _m_res.start + _ln_p2;
            _str_obj->length = _new_len;
        }
    }
}

/**
 * utility method for reversing strings 
 * @param string_object  
 * @return string object (shallow copy)
 */



string* rev_string (string* _str_obj){
    if (!_str_obj) {exit(1);}
    size_t _ln_str =  strlen(_str_obj->data);
    size_t _first = 0;
    size_t _last = _ln_str - 1;
    while(_first < _last){
        char tmp = _str_obj->data[_first];
        _str_obj->data[_first] = _str_obj->data[_last];
        _str_obj->data[_last] = tmp;
        _first ++; _last--;        
    }
    return _str_obj;
}

/**
 * wrapper api over printf - auto derefs the strings object  
 * @param  formatted_string with '%S' 
 * @return void 
 */

void displayln(const char* fmt,...){
    va_list args;
    va_start(args, fmt);
    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1) == 'S') {
            string *s = va_arg(args, string*);
            printf("%s", s->data);
            fmt += 2;
            continue;
        }
        if (*fmt == '%') {
            char spec[32];
            int i = 0;
            spec[i++] = *fmt++;   // copy '%'
            while (strchr("+-0 #", *fmt) || isdigit(*fmt) || *fmt == '.' || *fmt == 'l' || *fmt == 'h') {
                spec[i++] = *fmt++;
            }
            spec[i++] = *fmt++;
            spec[i] = '\0';
            vprintf(spec, args);
            continue;
        }
        putchar(*fmt++);
    }
    putchar('\n');
    va_end(args);
}

/**
 * prints string information - quite helpful if something goes wrong  
 * @param string_object
 * @return void 
 */

void debug_str(string* _str_obj){
    if (!_str_obj){
        fprintf(stderr,"NUll Pointer !!!\n");
        exit(1);
    }
    printf("string : %s \n Length: %zu \n Capacity : %zu \n",_str_obj->data,_str_obj->length,_str_obj->capacity);
}

/**
 * automatic dealloctes strings - raii like api  
 * @param void
 * @return void 
 */

__attribute__((destructor))
static void destroy_all_strings(void){
    if ( reg_count == 0 ) goto nop;
    for (size_t i =0 ; i < reg_count ; ++i){
        free(registry[i] -> data);
        free(registry[i]);
    }
    free(registry);
    nop: 
    ;
}


/**
 * manually frees strings , deprecated 
 * @param string_object 
 * @return void 
 */

static void free_str(string* _str_obj){
    if (!_str_obj) {exit(0);}
    free(_str_obj->data);
    _str_obj->data = NULL;
    free(_str_obj);
    _str_obj = NULL;
}

/* int main(){
    string* s1 = new_string("Fuck");
    s1 = append_string(s1," World");
    printf("%s \n",s1->data);
    s1 = rev_string(s1);
    printf("%s \n",s1->data);
    free_str(s1);  
}
 */

