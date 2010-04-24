/******************************************************************************
FILE:               bjstring.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     None
DESCRIPTION

    This class  defines string object. The string  data is dynamically
    allocated and reclaimed.

    This file contains only file-related bjstring functions,
    to avoid linking them when not useful.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2001-03-15 <PJB> Extracted from 'bjstring.c'.
BUGS
    No check is done for out of memory errors.
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon     1993 - 2001
    
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <bjstring.h>
#include <bjfile.h>

    /* For version & component control: */
    const char bjstring_file_id[]=
    "$Id: bjstring_file.c,v 1.1 2004/01/21 06:26:32 pjbpjb Exp $";

    bjstring_t*  bjstring_new_from_file(const bjstring_t* path)
    {
        bjstring_t* that;
        int         size;
        FILE*       file;
        size=bjfile_size(bjfile_new_with_path(path));
        if(size<0){
            return(0);
        }
        file=fopen(bjstring_string(path),"r");
        if(file==0){
            return(0);
        }
        that=bjstring_new();
        bjstring_set_capacity_copy(that,(unsigned)size,no);
        that->length=fread(that->data,sizeof(*(that->data)),
                           (unsigned)size,file);
        if (that->length!=0)
            that->data[that->length]='\0';
        fclose(file);
        return(that);
    }/*bjstring_new_from_file*/


    int bjstring_save_to_file(const bjstring_t* that,const bjstring_t* path)
    {
        int         result;
        FILE*       file;
        file=fopen(bjstring_string(path),"w");
        if(file==0){
            return(-1);
        }
        result=fwrite(that->data,sizeof(*(that->data)),that->length,file);
        fclose(file);
        return(result);
    }/*bjstring_save_to_file*/





    int bjstring_read_a_line_from_file(bjstring_t* that,FILE* input,bool grow)
        /*
            DO:     Read a  line from the  file 'input' and  stores it
                    into that string. The end-of-line character, LF is
                    read into the string too.

                    The default is to  read up to the current capacity
                    of  the  string.    Using  the  grow  option,  the
                    capacity  of  the string  will  be incremented  to
                    accomodate the length of the line, which can be as
                    big as the file itself  if it does not contain any
                    LF. Or which could lead to an out-of-memory error.

            NOTE:   Bad things occurs when the file contains null bytes.

            RETURN: -1 in case of error,
                    0 in case of end of file, or
                    the number of characters read, or
                    the position of the first null byte in the line.
        */
    {
        if(that->allocation==0){
            /* we make a default buffer */
            bjstring_set_capacity_copy(that,1024,no);
        }

        clearerr(input);
        if(fgets(that->data,(signed)that->allocation,input)==0){
            if(feof(input)){
                /* end-of-file */
                that->length=0;
                return(0);
            }else{
                /* error */
                that->length=0;
                return(-1);
            }
        }else{
            /* read at least part of the line */

            that->length=strlen(that->data);
            /*  Note that if the line contains null bytes,
                it will be truncated and it may be cut if it's longer
                than the buffer.
                But then, we should not be using fgets, since it does
                not report the number of bytes read.
            */

            if(grow){
                while(that->data[that->length-1]!='\n'){
                    bjstring_set_capacity_copy(that,that->allocation*2,yes);
                    if(fgets(that->data+that->length,
                             (signed)(that->allocation-that->length),input)==0){
                        if(feof(input)){
                            /* end-of-file without end-of-line*/
                            return(that->length);
                        }else{
                            /* error */
                            return(-1);
                        }
                    }else{
                        that->length+=strlen(that->data+that->length);
                    }
                }
            }
            return(that->length);
        }
    }/*bjstring_read_a_line_from_file*/



/*** bjstring_file.c                  -- 2003-12-03 17:33:47 -- pascal   ***/
