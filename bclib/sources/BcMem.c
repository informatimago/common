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

    
    PROCEDURE(BcMem_Clear,(void* p,CARD32 size),void)
    {
            CARD8*          p1;
            CARD16*         p2;
            CARD32*         p4;
        
        p1=p;
        if((size>=sizeof(CARD8)) AND ((((CARDPTR)p1)&((CARDPTR)(sizeof(CARD8))))!=0)){
            (*p1)=(CARD8)0;
            INC(p1);
            size-=(CARD32)sizeof(CARD8);
        }
        p2=(CARD16*)p1;
        if((size>=sizeof(CARD16))AND((((CARDPTR)p2)&(CARDPTR)(sizeof(CARD16)))!=0)){
            (*p2)=(CARD16)0;
            INC(p2);
            size-=(CARD32)sizeof(CARD16);
        }
        p4=(CARD32*)p2;
        while(size>=sizeof(CARD32)){
            (*p4)=0;
            INC(p4);
            size-=(CARD32)sizeof(CARD32);
        }
        p2=(CARD16*)p4;
        if(size>=sizeof(CARD16)){
            (*p2)=(CARD16)0;
            INC(p2);
            size-=(CARD32)sizeof(CARD16);
        }
        p1=(CARD8*)p2;
        if(size>=sizeof(CARD8)){
            (*p1)=(CARD8)0;
            INC(p1);
            size-=(CARD32)sizeof(CARD8);
        }
    }/*BcMem_Clear;*/


    PROCEDURE(BcMem_Fill,(void* p,CARD32 size,CARD8 value),void)
    {
            union {
                CARD8           array[4];
                CARD8           byte;
                CARD16          word;
                CARD32          longword;
            }               fill;
            CARD8*          p1;
            CARD16*         p2;
            CARD32*         p4;
        
        fill.array[0]=fill.array[1]=fill.array[2]=fill.array[3]=value;
        p1=p;
        if((size>=sizeof(CARD8))AND((((CARDPTR)p1)&(CARDPTR)(sizeof(CARD8)))!=0)){
            (*p1)=fill.byte;
            INC(p1);
            size-=(CARD32)sizeof(CARD8);
        }
        p2=(CARD16*)p1;
        if((size>=sizeof(CARD16))AND((((CARDPTR)p2)&(CARDPTR)(sizeof(CARD16)))!=0)){
            (*p2)=fill.word;
            INC(p2);
            size-=(CARD32)sizeof(CARD16);
        }
        p4=(CARD32*)p2;
        while(size>=sizeof(CARD32)){
            (*p4)=fill.longword;
            INC(p4);
            size-=(CARD32)sizeof(CARD32);
        }
        p2=(CARD16*)p4;
        if(size>=sizeof(CARD16)){
            (*p2)=fill.word;
            INC(p2);
            size-=(CARD32)sizeof(CARD16);
        }
        p1=(CARD8*)p2;
        if(size>=sizeof(CARD8)){
            (*p1)=fill.byte;
            INC(p1);
            size-=(CARD32)sizeof(CARD8);
        }
    }/*BcMem_Fill;*/
    
    
    PROCEDURE(BcMem_Copy,(const void* from,void* to,CARD32 size),void)
    {
            const CARD8*    f1;
            CARD8*          t1;
            const CARD32*   f4;
            CARD32*         t4;
        
        if((((CARDPTR)from)&1)!=(((CARDPTR)to)&1)){
            if((CARDPTR)from<(CARDPTR)to){
                f1=((const CARD8*)from)+size;
                t1=((CARD8*)to)+size;
                while(size>0){
                    DEC(f1);
                    DEC(t1);
                    (*t1)=(*f1);
                    DEC(size);
                }
            }else{
                f1=from;
                t1=to;
                while(size>0){
                    (*t1)=(*f1);
                    INC(f1);
                    INC(t1);
                    DEC(size);
                }
            }
        }else{
            if((CARDPTR)from<(CARDPTR)to){
                f1=((const CARD8*)from)+size;
                t1=((CARD8*)to)+size;
                while((size>0)&&((((CARDPTR)from)&3)!=0)){
                    DEC(f1);
                    DEC(t1);
                    (*t1)=(*f1);
                    DEC(size);
                }
                f4=(const CARD32*)f1;
                t4=(CARD32*)t1;
                while(size>=sizeof(CARD32)){
                    DEC(f4);
                    DEC(t4);
                    (*t4)=(*f4);
                    DECR(size,(CARD32)sizeof(CARD32));
                }
                f1=(const CARD8*)f4;
                t1=(CARD8*)t4;
                while(size>0){
                    DEC(f1);
                    DEC(t1);
                    (*t1)=(*f1);
                    DEC(size);
                }
            }else{
                f1=from;
                t1=to;
                while((size>0)&&((((CARDPTR)from)&3)!=0)){
                    (*t1)=(*f1);
                    INC(f1);
                    INC(t1);
                    DEC(size);
                }
                f4=(const CARD32*)f1;
                t4=(CARD32*)t1;
                while(size>=sizeof(CARD32)){
                    (*t4)=(*f4);
                    INC(f4);
                    INC(t4);
                    DECR(size,(CARD32)sizeof(CARD32));
                }
                f1=(const CARD8*)f4;
                t1=(CARD8*)t4;
                while(size>0){
                    (*t1)=(*f1);
                    INC(f1);
                    INC(t1);
                    DEC(size);
                }
            }
        }
    }/*BcMem_Copy;*/
    
    
/*END BcMem*/


/*** BcMem.c                          -- 2004-01-01 09:33:52 -- pascal   ***/
