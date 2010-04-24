/******************************************************************************
FILE:               bjfile.c
LANGUAGE:           ANSI-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This module exports some file utility routines.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2001-02-23 <PJB> Introduced file_t, to allow several queries on the statistics.
                     Added file_current_directory_path.
    2001-01-06 <PJB> Added file_exists.
BUGS
    file_check_virus(): We need to run the file thru unmime.
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
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

#include <bjfile.h>

    /* For version & component control: */
    const char bjfile_id[]=
    "$Id: bjfile.c,v 1.1 2004/01/21 06:26:32 pjbpjb Exp $"; 


    static void bjfile_delete(void* object)
    {
        bjfile_t* that=object;
        bjobject_release(that->path);
    }/*bjfile_delete*/


    static bjobject_methods_t bjfile_methods={ "bjfile", bjfile_delete };


    bjfile_t* bjfile_new_with_path(const bjstring_t* path)
    {
        bjfile_t* that=bjobject_new(sizeof(*that),&bjfile_methods);
        that->path=bjstring_new_copy(path);
        bjobject_retain(that->path);
        if(stat(bjstring_string(path),&(that->statistics))==0){
            that->error=0;
        }else{
            that->error=errno;
        }
        return(that);
    }/*bjfile_new_with_path*/


    int bjfile_size(const bjfile_t* that)
    {
        if((that==0)||(that->error!=0)){
            return(-1);
        }else{
            return(that->statistics.st_size);
        }
    }/*bjfile_size*/


    bool bjfile_exists(const bjfile_t* that)
    {
        return((that!=0)&&(that->error==0));
    }/*bjfile_exists*/


    bool bjfile_is_directory(const bjfile_t* that)
    {
         if((that==0)||(that->error!=0)){
             return(no);
         }else{
             return(S_ISDIR(that->statistics.st_mode));
         }
    }/*bjfile_is_directory*/


    bjstring_t* bjfile_current_directory_path(void)
    {
        unsigned int   size=PATH_MAX;
        bjstring_t* path=bjstring_new();
        bjstring_set_capacity_copy(path,size,no);
        errno=0;
        while((!getcwd(bjstring_mutable_string(path),size))&&(errno==ERANGE)){
            size*=2;
            bjstring_set_capacity_copy(path,size,no);
        }
        if(errno!=0){
            return(0);
        }else{
            path->length=strlen(path->data);
            return(path);
        }
    }/*bjfile_current_directory_path*/


    int bjfile_touch_path(const bjstring_t* path)
    {
        const char* filename=bjstring_string(path);
        struct utimbuf utb;
        utb.actime=utb.modtime=time(NULL);
        return(utime(filename,&utb));
    }/*bjfile_touch_path*/



/*** bjfile.c                         -- 2003-12-03 19:55:17 -- pascal   ***/
