/******************************************************************************
	* str.c: A header file that provides string manipulation function to
	* C programs.
	* Code samples & inspiration taken from:
	*  - https://github.com/gingerBill/gb/blob/master/gb.h by Ginger Bill
	*  - https://github.com/gingerBill/gb/blob/master/gb_string.h by Ginger Bill
	*  - https://github.com/ennorehling/clibs/blob/master/strings.c by Enno Rehling
	* -------------------------------------------------------------------------
	* MIT License
	*
	* Copyright 2024 AnzenKodo
	*
	* Permission is hereby granted, free of charge, to any person obtaining
	* a copy of this software and associated documentation files (the
	* "Software"), to deal in the Software without restriction, including
	* without limitation the rights to use, copy, modify, merge, publish,
	* distribute, sublicense, and/or sell copies of the Software, and to
	* permit persons to whom the Software is furnished to do so, subject to
	* the following conditions:
	*
	* The above copyright notice and this permission notice shall be
	* included in all copies or substantial portions of the Software.
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

#ifndef STD_STR
#define STD_STR

// String Types
//=============

typedef struct str8 {
	u8 *str;
	u64 size;
} str8;

typedef struct str16 {
	u16 *str;
	u64 size;
} str16;

typedef struct str32 {
	u32 *str;
	u64 size;
}

#endif // STD_STR
