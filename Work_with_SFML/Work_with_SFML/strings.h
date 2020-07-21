#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define END_OF_STRING(symb) (symb == '\0' || symb == '\n')

#pragma warning (disable: 4996 4090)

typedef struct
{
	char* line_ptr;
	size_t len;
} Strings;





enum Params_of_the_text
{
	MAX_FILE_NAME = 30,
};

//! The function for input any text
//! @param[in] in[] - input data stream
//! @param[in] type[] - type of input data
//! @param[out] - out put data stream
//! The fucntion return result of input

int Input(const char* type, char* text);


//! The fucntion for reading file to buffer
//! @param[in] name_of_file[] - name of original text
//! @param[in] file_size - pointer to the byte size of file (returning from fread)
//! The function return buffer

char* Create_Buffer(const char* filename, size_t* file_size);


//! The fucntion for counting symbols of the file (lenght)
//! @param[in] FILE* poems - file which text a measured
//! The function return number of symbols from file

int Lenght_Of_File(FILE* poems);


//! 

int String_Counter(const char* buffer, size_t buffer_size, char symbol);

//! The function for creating poinets to the begin of string(in buffer, of course)
//! @param[in] buffer - buffer for making pointers
//! @param[in] symbol - key-symbol(parametr) for quick counting with help memchr()
//! @param[in] file_size - byte size of file, parametr for quick counting with help memchr()
//! @param[in] counter_of_str - pointer to the real number of string
//! The function return massive os structure

Strings* Create_Ptr_Buf(char* buffer, size_t buffer_size, size_t* counter_of_strs, char symbol);



bool Put_Buf_Into_File(const char* file_name, const char* buf, size_t buf_size);



int CompareFunc_Begin(const char* str1, const char* str2);

#endif //__STRINGS_H__

