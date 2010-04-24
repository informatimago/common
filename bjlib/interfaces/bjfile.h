/******************************************************************************
FILE:               bjfile.h
LANGUAGE:           ANSI-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This module exports some file utility routines.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2001-02-23 <PJB> Introduced bjfile_t, to allow several queries on the statistics.
    2001-01-06 <PJB> Added bjfile_exists.
BUGS
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon 2000 - 2001
    
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
#ifndef inhibit_bjfile_h
#define inhibit_bjfile_h
#include <sys/stat.h>
#include <bjstring.h>


    typedef struct {
        bjstring_t* path;
        int         error;
        struct stat statistics;
    }           bjfile_t;


extern bjfile_t* bjfile_new_with_path(const bjstring_t* path);
    /*
        RETURN: A new file instance. 
                The statistics are filled and can be checked.
    */

extern int bjfile_size(const bjfile_t* that);
    /*
        RETURN: The size of that file when that instance was created,
                or -1 and errno.
    */

extern bool bjfile_exists(const bjfile_t* that);
    /*
        RETURN: Whether a file existed in the file system when that
                bjfile_t instance were created. (It can be whatever,
                file, directory, device, ...).
    */

extern bool bjfile_is_directory(const bjfile_t* that);
    /*
        RETURN: Whether that file existed and was a directory
                (or a sym-link to a directory).
    */


extern bjstring_t* bjfile_current_directory_path(void);
    /*
        RETURN: the path of the current directory.
    */

extern int bjfile_touch_path(const bjstring_t* path);
    /*
        RETURN:  0, or errno.
    */



#endif
/*** bjfile.h                         -- 2003-12-03 17:05:50 -- pascal   ***/
