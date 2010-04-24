/******************************************************************************
FILE:               BcMem.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (stdlib)
USER-INTERFACE:     None
DESCRIPTION
    This modules defines memory management routines.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:07  pascal
    Initial entry into CVS.
    
    Revision 1.1  95/11/16  06:37:44  pascal
    Initial revision
    
    1990-04-23 <PJB> Creation (M2Mem).
    1992-07-22 <PJB> Added BoMem_Clear.
    1992-09-29 <PJB> Added BoMem_Copy.
    1993-01-12 <PJB> Added BoExcept.
    1993-03-19 <PJB> Renamed BcMem for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1993-12-06 <PJB> Added Fill.
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
#ifndef __BcMem__
#define __BcMem__
#include <names.h>
#include BcInterface_h
#include BcTypes_h

#define BcMem_eBase                 (10000)
#define BcMem_eRequestedNullSize    (BcMem_eBase+0) /* CARD32 size,NIL*/
#define BcMem_eMallocReturnedNIL    (BcMem_eBase+1) /* CARD32 size,NIL*/

    PROCEDURE(BcMem_Allocate,(CARD32 size),void*)
        /*
            RAISE:      BcMem_eRequestedNullSize,BcMem_eMallocReturnedNIL
            DO:         Allocates a new memory block from the heap.
            RETURN:     a pointer to the allocated memory block.
        */
        
    PROCEDURE(BcMem_Deallocate,(void** p),void)
        /*
            DO:         Deallocate a memory block.
            POST:       p=NIL
        */
    
    PROCEDURE(BcMem_Clear,(void* p,CARD32 size),void)
        /*
            DO:         erase size bytes from p.
        */
    
    PROCEDURE(BcMem_Fill,(void* p,CARD32 size,CARD8 value),void)
        /*
            DO:         fills size bytes from p with the value.
        */
    PROCEDURE(BcMem_Copy,(const void* from,void* to,CARD32 size),void)
        /*
            DO:         copies size bytes from from to to.
        */
        
        
#endif /*BcMem.*/


/*** BcMem.h                          -- 2003-11-30 07:14:10 -- pascal   ***/
