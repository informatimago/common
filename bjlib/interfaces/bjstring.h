/******************************************************************************
FILE:               bjstring.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     None
DESCRIPTION

    This class  defines string object. The string  data is dynamically
    allocated and reclaimed.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2003-12-03 <PJB> Added bjstring_substring.
    2003-12-03 <PJB> Remplaced int by unsigned int where possible.
    2003-02-19 <PJB> Added bjstring_char_index.
    2002-05-22 <PJB> Added bjstring_search_forward_insensitive and
                     bjstring_search_backward_insensitive, and renamed
                     bjstring_position_from to bjstring_search_forward.
    2001-03-15 <PJB> Added bjstring_new_format.
    2001-03-14 <PJB> Added bjstring_set_chars and bjstring_new_chars.
    2001-01-17 <PJB> Added bjstring_search_backward().
    2001-01-10 <PJB> Added bjstring_is_suffix()
                     and bjstring_is_suffix_insensitive().
    2000-12-28 <PJB> Added bjstring_is_prefix()
                     and bjstring_is_prefix_insensitive().
    2000-12-18 <PJB> Integrated into AvMailGate project (some renaming) and
                     added bjstring_substitute_from(), bjstring_compare(), and
                     bjstring_compare_insensitive().
    1995-11-16 <PJB> Some small correction to compile in MSVC.
    1993-01-29 <PJB> Creation.
BUGS
    No check is done for out of memory errors.
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon     1993 - 2003
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version
    2 of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public
    License along with this program; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
#ifndef bjstring_h
#define bjstring_h
#include <stdio.h>
#include <stdarg.h>
#include <bjobject.h>

    typedef struct {
        char*               data;
        unsigned int        length;
        unsigned int        allocation;
    }                   bjstring_t;


    extern bjstring_t* bjstring_new(void);
    extern bjstring_t* bjstring_new_string(const char* string);
    extern bjstring_t* bjstring_new_format(const char* format,...);
    extern bjstring_t* bjstring_new_chars(const char* string,
                                          unsigned int count);
    extern bjstring_t* bjstring_new_repeat(const char* string,
                                           unsigned int count);
    extern bjstring_t* bjstring_new_copy(const bjstring_t* other);


/* File Functions */

    extern bjstring_t* bjstring_new_from_file(const bjstring_t* path);

    extern int bjstring_save_to_file(const bjstring_t* that,
                                     const bjstring_t* path);
        /*
            RETURN: The number of bytes written to the file, or -1, and errno
        */

    extern int bjstring_read_a_line_from_file(bjstring_t* that,
                                              FILE* input,bool grow);
        /*
            PRE:    The file does not contain any null byte between the
            current position and the end of line.

            DO:     Read a  line from the  file 'input' and  stores it
            into that string. The end-of-line character, LF is
            read into the string too.

            The default is to  read up to the current capacity
            of  the  string.    Using  the  grow  option,  the
            capacity  of  the string  will  be incremented  to
            accomodate the length of the line, which can be as
            big as the file itself  if it does not contain any
            LF. Or which could lead to an out-of-memory error.

            RETURN: -1 in case of error (some characters may be read),
            0 == bjstring_length(that) in case of end of file, or
            the number of characters read = bjstring_length(that).
        */

/* String Functions */

    extern void bjstring_set_capacity_copy(bjstring_t* that,
                                           unsigned int nAllocation,
                                           bool copy);

    extern unsigned int bjstring_length(const bjstring_t* that);
    extern const char* bjstring_string(const bjstring_t* that);
    extern char* bjstring_mutable_string(bjstring_t* that);
        /* same as bjstring_string, only that the content may be modified. */

    extern void bjstring_set_string(bjstring_t* that,const char* nString);

    extern void bjstring_set_format_va(bjstring_t* that,
                                       const char* format,va_list ap);

    extern void bjstring_get_string(const bjstring_t* that,char* string);
    extern void bjstring_append_string(bjstring_t* that,const char* str);

    extern char bjstring_char_at(const bjstring_t* that,unsigned int idx);
    extern void bjstring_set_char_at(bjstring_t* that,char nChar,
                                     unsigned int idx);
    extern unsigned int bjstring_char_index(const bjstring_t* that,char aChar,
                                            unsigned int fromIdx);
        /*
            PRE:    e <=> there exists a i in [fromIdx..bjstring_length(that)-1]
            such as bjstring_char_at(that,i)==aChar
            RETURN: e ==> the smallest i such as i>=fromIdx 
            and bjstring_char_at(that,i)==aChar
            !e ==> bjstring_length(that)
        */

    extern void bjstring_set_chars(bjstring_t* that,
                                   const char* chars,unsigned int count);


    extern void bjstring_insert_at(bjstring_t* that,
                                   const bjstring_t* substring,
                                   unsigned int idx);

    extern void bjstring_delete_from_length(bjstring_t* that,
                                            unsigned int idx,
                                            unsigned int delen);

    extern void bjstring_replace_from_length(bjstring_t* that,
                                             const bjstring_t* substring,
                                             unsigned int idx,
                                             unsigned int delen);
        /*
            DO: bjstring_delete_from_length((that,idx,delen);
            bjstring_insert_at(that,substring,idx);
            Only a little more efficiently.
        */

    extern unsigned int bjstring_search_forward(const bjstring_t* that,
                                                const bjstring_t* substring,
                                                unsigned int idx);
#define bjstring_position_from(t,s,i) bjstring_search_forward((t),(s),(i))
        /*
            RETURN: the position of the first occurence of substring in that,
            starting the search from idx and going backward.
            If the substring is not found, 
            bjstring_length(that) is returned.
        */

    extern unsigned int bjstring_search_forward_insensitive(
        const bjstring_t* that,
        const bjstring_t* substring,
        unsigned int idx);

    extern unsigned int bjstring_search_backward(const bjstring_t* that,
                                                 const bjstring_t* substring,
                                                 unsigned int idx);
        /*
            RETURN: the position of the first occurence of substring in that,
            starting the search from idx and going backward.
            If the substring is not found, 
            bjstring_length(that) is returned.
        */

    extern unsigned int bjstring_search_backward_insensitive(
        const bjstring_t* that,
        const bjstring_t* substring,
        unsigned int idx);
        /*
            RETURN: the position of the first occurence of substring in that,
            starting the search from idx and going backward.
            If the substring is not found, 
            bjstring_length(that) is returned.
            The substring matching is done case insensitively.
        */


    extern void bjstring_copy_from(bjstring_t* that,
                                   const bjstring_t* string);
    extern void bjstring_copy_from_length(bjstring_t* that,
                                          const bjstring_t* string,
                                          unsigned int idx,
                                          unsigned int copylen);
    extern bjstring_t* bjstring_substring(const bjstring_t* that,
                                          unsigned int idx,
                                          unsigned int copylen);

    extern void bjstring_append(bjstring_t* that,const bjstring_t* tail);

    extern void bjstring_append_format(bjstring_t* that,const char* format,...);


    extern unsigned int bjstring_substitute_from(bjstring_t* that,
                                                 const bjstring_t* match,
                                                 const bjstring_t* replacement,
                                                 unsigned int from,
                                                 unsigned int occurences);
        /*
            Replaces in that, the number of occurences given by `occurences',
            from the position `from' of each occurences of match, by 
            replacement.
            If occurences==0 then replace all occurences found from `from'.
            The next seach starts after replacement.
            Return the number of substitions done.
        */


    extern order_t bjstring_compare(const bjstring_t* that,
                                    const bjstring_t* other);
    extern order_t bjstring_compare_insensitive(const bjstring_t* that,
                                                const bjstring_t* other);

    extern bool bjstring_is_prefix(const bjstring_t* that,
                                   const bjstring_t* prefix);
    extern bool bjstring_is_prefix_insensitive(const bjstring_t* that,
                                               const bjstring_t* prefix);

    extern bool bjstring_is_suffix(const bjstring_t* that,
                                   const bjstring_t* suffix);
    extern bool bjstring_is_suffix_insensitive(const bjstring_t* that,
                                               const bjstring_t* suffix);


#endif
/*** bjstring.h                       -- 2003-12-03 18:47:42 -- pascal   ***/
