/******************************************************************************
FILE:               BcCStr.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (ctype)
USER-INTERFACE:     None
DESCRIPTION
    This modules defines C string handling routines.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/16  12:15:13  pascal
    Small corrections to compile with MSVC.
    
    Revision 1.1  95/11/16  06:28:25  pascal
    Initial revision
    
    1992-07-04 <PJB> Creation.
    1993-03-19 <PJB> Renamed BcCStr for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2011

    This file is part of the bclib library.

    This  program is  free software;  you can  redistribute  it and/or
    modify it  under the  terms of the  GNU General Public  License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program  is distributed in the  hope that it  will be useful,
    but  WITHOUT ANY WARRANTY;  without even  the implied  warranty of
    MERCHANTABILITY or FITNESS FOR  A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a  copy of the GNU General Public License
    along with  this program; see the  file COPYING; if  not, write to
    the Free  Software Foundation, Inc.,  59 Temple Place,  Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
/* standard */
#include <ctype.h>
/* BcLib */
#include <names.h>
#include BcCStr_h
#include BcImplementation_h


    const char BccStr_ID[]=
    "$Id: BcCStr.c,v 1.2 2004/01/02 00:59:24 pjbpjb Exp $";

    PROCEDURE(BcCStr_Assign,(const CHAR* from,CHAR* to,INT32 sizeofto),void)
    {
        INT32 i=0;
        while((i<sizeofto-1)&&(from[i]!=CHR(0))){
            to[i]=from[i];
            INC(i);
        }
        /* i=sizeofto-1 || from[i]=0 */
        to[i]=CHR(0);
    }/*BcCStr_Assign */


    PROCEDURE(BcCStr_AssignToLower,(CHAR* from,CHAR* to,INT32 sizeofto),void)
    {
            INT32       i;
        
        i=0;
        while((i<sizeofto-1)&&(from[i]!=CHR(0))){
            if(isupper(from[i])){
                to[i]=(CHAR)tolower(from[i]);
            }else{
                to[i]=from[i];
            }
            INC(i);
        }
        /* i=sizeofto-1 || from[i]=0 */
        to[i]=CHR(0);
    }/*BcCStr_AssignToLower */


    PROCEDURE(BcCStr_RepeatChar,(INT32 count,CHAR c),CHAR*)
    {
            static CHAR         buffer[1024];
            static INT32        oldcount=0;
            static CHAR         oldc=(CHAR)0;
        
        if((count<=oldcount)&&(c==oldc)){
            buffer[count]=(CHAR)0;
            return(buffer);
        }
        if(count<0){
            count=0;
        }else if(count>1023){
            count=1023;
        }
        oldcount=count;
        oldc=c;
        buffer[count]=(CHAR)0;
        DEC(count);
        while(count>=0){
            buffer[count]=c;
            DEC(count);
        }
        return(buffer);
    }/*BcCStr_RepeatChar; */


    PROCEDURE(BcCStr_Terminate,(CHAR* string,INT32 length),CHAR*)
    {
            static CHAR         buffer[1024];
        
        if(length<0){
            length=0;
        }else if(length>1023){
            length=1023;
        }
        BcCStr_Assign(string,buffer,length);
        buffer[length+1]=(CHAR)0;
        return(buffer);
    }/*BcCStr_Terminate; */
    
/*END BcCStr. */

/*** BcCStr.c                         -- 2004-01-01 09:32:31 -- pascal   ***/
