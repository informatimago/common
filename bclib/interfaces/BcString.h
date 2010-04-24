/******************************************************************************
FILE:               BcString.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This class defines string object. The string data is dynamically allocated
    and reclaimed.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:07  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/16  12:07:20  pascal
    Some small correction to compile in MSVC.
    
    Revision 1.1  95/11/16  06:37:47  pascal
    Initial revision
    
    1993-01-29 <PJB> Creation.
    1993-03-16 <PJB> Translated from Objective-C to C++.
    1993-03-19 <PJB> Renamed BcXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1994-10-08 <PJB> Translated from C++ to C.
    1994-10-09 <PJB> Added AppendString.
LEGAL
    Copyright Pascal J. Bourguignon 1993 - 2002

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
#ifndef __BcString__
#define __BcString__
#include <stdio.h>
#include <names.h>
#include BcInterface_h
#include BcTypes_h

    typedef void*       BcString_T;
    

/*
    INVARIANTS:
        data#NIL
        1<=allocation
        0<=dlength<allocation
        data[dlength]=(char)0
        for all i in [0..dlength-1], data[i]#(char)0
*/

#define AllocIncrement  (128)
#define Minimum(a,b)    (((a)<(b))?(a):(b))


    PROCEDURE(BcString_SetCapacityCopy,
              (BcString_T t,INT32 nAllocation,BOOLEAN copy),BcString_T)



/* birth and death:*/

    PROCEDURE(BcString_Allocate,(void),BcString_T)
    PROCEDURE(BcString_Deallocate,(BcString_T* t),void)

/* override BcObject methods: */

    PROCEDURE(BcString_ClassName,(BcString_T t),const char*)
    PROCEDURE(BcString_PrintOn,(BcString_T t,FILE* file),void)

/* new methods: */

    PROCEDURE(BcString_Length,(BcString_T t),INT32)
    PROCEDURE(BcString_String,(BcString_T t),const char*)
    PROCEDURE(BcString_SetString,
                (BcString_T t,const char* nString),BcString_T)
    PROCEDURE(BcString_GetString,(BcString_T t,char* string),BcString_T)
    PROCEDURE(BcString_AppendString,(BcString_T t,const char* str),BcString_T)
    
    PROCEDURE(BcString_CharAt,(BcString_T t,INT32 idx),char)
    PROCEDURE(BcString_SetCharAt,
                (BcString_T t,char nChar,INT32 idx),BcString_T)
    
    PROCEDURE(BcString_InsertAt,
                (BcString_T t,BcString_T substring,INT32 idx),BcString_T)
    PROCEDURE(BcString_DeleteFromLength,
                (BcString_T t,INT32 idx,INT32 delen),BcString_T)
    PROCEDURE(BcString_PositionFrom,
                (BcString_T t,BcString_T substring,INT32 idx),INT32)
    PROCEDURE(BcString_CopyFromLength,
            (BcString_T t,BcString_T string,INT32 idx,INT32 copylen),
            BcString_T)
    PROCEDURE(BcString_Append,(BcString_T t,BcString_T tail),BcString_T)
    

#endif /*END BcString.*/


/*** BcString.h                       -- 2003-11-30 07:20:33 -- pascal   ***/
