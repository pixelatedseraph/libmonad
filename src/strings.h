#pragma once
#define String string*
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct string 
{
    char*      data; // should be alloc'd in heap
    size_t     length;
    size_t     capacity;
    
}string;

typedef struct MatchRes MatchRes;

string* new_string(const char* str );
string* empty_string();
string* append_string(string* _str_obj,const char* );
string* sub_string(string* _str_obj , size_t start , size_t end);
string* rev_string (string* _str_obj);
string* trim(string *_str_obj);
string* trim_left(string *_str_obj);
string* trim_right(string *_str_obj);
string* to_upper(string* _str_obj);
string* to_lower(string* _str_obj);
string* clone(string* _str_obj);
size_t get_length(string* _str_obj);
void match(string* _str_obj,const char* pattern);
void replace(string* _str_obj, const char *_p1, const char *_p2);
bool string_equals(string *_str_obj1 , string *_str_obj2);
int compare_string(string *_str_obj1 , string  *_str_obj2);
char char_at (string* _str_obj, size_t idx);
void debug_str(string* _str_obj);
void displayln(const char* fmt,...);

