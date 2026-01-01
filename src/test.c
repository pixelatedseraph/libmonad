#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strings.h"
#include "../include/mnd/prelude.h"

typedef struct Student{
    String name;
    int age;
}Student;

#define MALLOC_EXCEPTION 1

MND_DEFINE_RESULT(int,INT)
MND_DEFINE_RESULT(Student*,p_Student)

String ec_to_str(int ec){
    switch (ec)
    {
    case MALLOC_EXECPTION:
        return new_string("Malloc has failed allocating memory ");
        break;
    default:
        return new_string("Unknown Exception");
        break;
    }
}

/* leaf layer  */
Result_p_Student CreateStudentEntry(){
    Student* s = malloc(sizeof(Student));
    if (!s) {
        return Result_p_Student_err(MALLOC_EXECPTION);
    }
    return Result_p_Student_ok(s);
}

/* logic layer */
Result_p_Student InsertStudentEntry(Result_p_Student s,char* name, int age){
    Student* S = MND_UNWRAP(p_Student,s); // if true , S is initalized with pointer to 'Student struct' else it returns the error
    S->name = new_string(name);
    S->age  = age;
    return Result_p_Student_ok(S);
}

/* boundary layer */
int main(void){
    Result_p_Student r = CreateStudentEntry();
    if (!MND_OK(r)) {
        fprintf(stderr,"[ERROR] %s \n",(ec_to_str(MND_ERR(r)))->data);
        return -1;
    }
    r = InsertStudentEntry(r,"Mazeed",19);
    if(!MND_OK(r)) {
        fprintf(stderr,"[ERROR] %s \n",(ec_to_str(MND_ERR(r)))->data);
        return -1;
    }
    printf("Name : %s Age : %d\n",MND_VAL(r)->name->data,MND_VAL(r)->age);
    free(MND_VAL(r));
    return 0;
}
