/******************************************************************************
FILE:               BcMem.c
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
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.4  1995/11/24 17:26:52  pascal
    Renamed BcExcept objects.

    Revision 1.3  95/11/16  12:31:06  pascal
    Small corrections to compile on NeXT.
    
    Revision 1.2  95/11/16  12:15:27  pascal
    Small corrections to compile with MSVC.
    
    Revision 1.1  95/11/16  06:28:38  pascal
    Initial revision
    
    1990-04-23 <PJB> Creation (M2Mem).
    1992-07-22 <PJB> Added BcMem_Clear.
    1992-09-29 <PJB> Added BcMem_Copy.
    1993-01-12 <PJB> Added BcExcept.
    1993-03-19 <PJB> Renamed BcMem for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1993-12-06 <PJB> Added Fill.
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
/* standard*/
#include <stdlib.h>
#include <string.h>
#if defined(NEXTSTEP) || defined(MACOSX)
#else
/* Where really? */
#include <malloc.h>
#endif
/* application*/
#include <names.h>
#include BcMem_h
#include BcTypes_h
#include BcExcept_h
#include BcImplementation_h

    const char BcMem_ID[]=
    "$Id: BcMem.c,v 1.2 2004/01/02 00:59:24 pjbpjb Exp $";

    PROCEDURE(BcMem_Allocate,(CARD32 size),void*)
    {
            void*       p;
        
        if(size==0){
            BcRAISE(BcMem_eRequestedNullSize,(void*)(CARDPTR)size,NIL);
        }
        p=malloc((size_t)size);
        if(p==NIL){
            BcRAISE(BcMem_eMallocReturnedNIL,(void*)(CARDPTR)size,NIL);
        }
        return(p);
    }/*BcMem_Allocate;*/
    
    
    PROCEDURE(BcMem_Deallocate,(void** p),void)
    {
        free(*p);
        (*p)=NIL;
    }/*BcMem_Deallocate;*/

    
    /*
        These three routines were originally hand-rolled word-at-a-time loops.
        That code computed its alignment masks with &sizeof(T) instead of
        &(sizeof(T)-1) and, in BcMem_Copy, only checked congruence mod 2 before
        a CARD32 word copy and tested the never-advanced original pointer --- so
        it could dereference a misaligned CARD32* (undefined behaviour, and a
        fault on strict-alignment targets).  They are now delegated to the
        standard library, which is correct, alignment-safe, and faster.
        BcMem_Copy keeps its overlap-safe (memmove) contract.
    */

    PROCEDURE(BcMem_Clear,(void* p,CARD32 size),void)
    {
        memset(p,0,(size_t)size);
    }/*BcMem_Clear;*/


    PROCEDURE(BcMem_Fill,(void* p,CARD32 size,CARD8 value),void)
    {
        memset(p,(int)value,(size_t)size);
    }/*BcMem_Fill;*/


    PROCEDURE(BcMem_Copy,(const void* from,void* to,CARD32 size),void)
    {
        memmove(to,from,(size_t)size);
    }/*BcMem_Copy;*/
    
    
/*END BcMem*/


/*** BcMem.c                          -- 2004-01-01 09:33:52 -- pascal   ***/
