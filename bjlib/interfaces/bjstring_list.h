/*****************************************************************************
FILE:               bjstring_list.h
LANGUAGE:           c
SYSTEM:             POSIX
USER-INTERFACE:     NONE
DESCRIPTION
    
    This module exports routines to manipulate strings and list of strings.
    
AUTHORS
    <PJB> Pascal Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2003-12-03 <PJB> Created.
BUGS
LEGAL
    GPL
    
    Copyright Pascal Bourguignon 2003 - 2003
    
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
*****************************************************************************/
#ifndef inhibit_bjstring_list_h    
#define inhibit_bjstring_list_h    
#include <bjstring.h>
#include <bjarray.h>


    extern unsigned int bjstring_count_occurences(const bjstring_t* string,
                                                  const bjstring_t* substring);
        /*
            RETURN:      The number of non overlaping occurences 
                         of substring in string. 
        */

    extern bjarray_t* bjstring_split_string(const bjstring_t* string,
                                            const bjstring_t* separator);
        /*
            separators:  a string, or 0 for space.
            RETURN:      An array containing the split substrings of strings.
        */

    extern bjstring_t* bjstring_unsplit_string(const bjarray_t* strings,
                                               const bjstring_t* separator);
        /*
            separators:  a string, or 0 for space.
            RETURN:      A string containing the concatenation of the 
                         strings in the array separated by the separator.
        */



    extern void bjstring_test_split_unsplit(void);
        /*
            DO:   dumps on stdout test case result.
        */  

#endif
/*** bjstring_list.h                  -- 2003-12-03 18:37:45 -- pascal   ***/
