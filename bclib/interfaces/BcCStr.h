/******************************************************************************
FILE:               BcCStr.h
LANGUAGE:           ANSI-C
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This modules defines C some string handling routines.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:18  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:07  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/16  11:56:08  pascal
    Converted a C++ comment.
    
    Revision 1.1  95/11/16  06:37:35  pascal
    Initial revision
    
    1992-07-04 <PJB> Creation.
    1993-03-19 <PJB> Renamed BcCStr for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

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
#ifndef __BcCStr__
#define __BcCStr__
#include <names.h>
#include BcInterface_h
#include BcTypes_h

    PROCEDURE(BcCStr_Assign,(const CHAR* from,CHAR* to,INT32 sizeofto),void)
        /*
            PRE:        k=MU(i,from[i]=(CHAR)0)
                        foreach i in [0..k], from[i]=f[i]
                        sizeofto = s > 0
    
            POST:       k< s => foreach i in [0..k] to[i]=f[i]
                        k>=s => foreach i in [0..s-2] to[i]=f[i]
                                to[s-1]=(CHAR)0
        */
        
    PROCEDURE(BcCStr_AssignToLower,(CHAR* from,CHAR* to,INT32 sizeofto),void)
        /*
            PRE:        k=MU(i,from[i]=(CHAR)0)
                        foreach i in [0..k], from[i]=f[i]
                        sizeofto = s > 0
    
            POST:       k< s => foreach i in [0..k] 
                                    if isupper(f[i])
                                        then to[i]=tolower(f[i])
                                        else to[i]=f[i]
                        k>=s => foreach i in [0..s-2]
                                    if isupper(f[i])
                                        then to[i]=tolower(f[i])
                                        else to[i]=f[i]
                                to[s-1]=(CHAR)0
        */

    PROCEDURE(BcCStr_RepeatChar,(INT32 count,CHAR c),CHAR*)
        /*
            PRE:        count<=1023
            RETURN:     a pointer to a static buffer containting
                        MIN(1023,count) c CHARacters.
        */
    
    PROCEDURE(BcCStr_Terminate,(CHAR* string,INT32 length),CHAR*)
        /*
            PRE:        length<=1023
            RETURN:     a pointer to a static buffer containing up to 
                        MIN(1023,length) CHAR from the string, and 
                        null terminated.
        */
        
#endif /*BcCStr.*/
