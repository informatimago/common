/******************************************************************************
FILE:               BcList.c
LANGUAGE:           ANSI-C
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    A BcList is a collection of objects. The class provides an interface 
    that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BcLists are 
    implemented as arrays to allow fast random access using an index. 
    Indices start at 0.
    See the NeXTstep List Class documentation.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2001-06-05 <PJB> Added common libraries and dosname utility to the repository.
    1995-11-24 <PJB> Renamed BcExcept objects.
    1995-11-16 <PJB> Small corrections to compile with MSVC.
    1994-09-25 <PJB> Added BcList_Sort.
    1993-03-19 <PJB> Renamed BcList for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1993-03-03 <PJB> Renamed DEBUG flag to BcList_DEBUG.
    1992-12-29 <PJB> Translated from Objective-C to C.
    1992-10-25 <PJB> Upgraded to the same interface as NeXTstep objc/List.h.
    1992-07-21 <PJB> Creation (BoArray).
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
#include <names.h>
#include <stdlib.h> /* import qsort */
#include BcList_h
#include BcMem_h
#include BcExcept_h
#include BcImplementation_h

    const char BcList_ID[]=
    "$Id: BcList.c,v 1.4 2004/11/09 18:57:32 pupjb Exp $";


    typedef struct { 
        CARD32                  count;      /* actual number of element.*/
        CARD32                  capacity;   /* capacity of the array.*/
        void**                  elements;
            /* actually, POINTER TO ARRAY [0..capacity-1] OF ADDRESS;*/
    }                       BcList_R;
    typedef BcList_R*       BcList_P;
    
    PROCEDURE(BcList_Allocate,(void),BcList_T)
    {
            BcList_P        plist;
            
        plist=(BcList_P)BcMem_Allocate(sizeof(BcList_R));
        plist->count=0;
        plist->capacity=BcList_Minimum;
        plist->elements=(void**)BcMem_Allocate((CARD32)sizeof(void*)*plist->capacity);
        return((BcList_T)plist);
    }/*BcList_Allocate;*/
    
    
    PROCEDURE(BcList_Deallocate,(BcList_T* list),void)
    {
            BcList_P            plist;
        
        plist=(BcList_P)(*list);
        BcMem_Deallocate((void**)(&(plist->elements)));
        BcMem_Deallocate((void**)(&plist));
        (*list)=NIL;
    }/*BcList_Deallocate;*/


    PROCEDURE(BcList_CopyTo,(BcList_T list,BcList_T clone),void)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        BcList_SetCapacity(clone,plist->count);
        BcList_AppendList(clone,list);
    }/*BcList_CopyTo;*/


    PROCEDURE(BcList_IsEqual,(BcList_T list,BcList_T otherlist),BOOLEAN)
    {
            CARD32              i;
            BcList_P            plist,otherplist;
        
        plist=(BcList_P)list;
        otherplist=(BcList_P)otherlist;
        if(otherplist->count!=plist->count){
            return(FALSE);
        }
        i=0;
        while((i<plist->count)&&(otherplist->elements[i]==plist->elements[i])){
            i++;
        }
        return(i==(plist->count));
    }/*BcList_IsEqual;*/
    
    
    PROCEDURE(BcList_Capacity,(BcList_T list),CARD32)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        return(plist->capacity);
    }/*BcList_Capacity;*/
    
    
    PROCEDURE(BcList_SetCapacity,(BcList_T list,CARD32 newCapacity),void)
    {
            void**      newElements;
            CARD32      i;
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(newCapacity<BcList_Minimum){
            newCapacity=BcList_Minimum;
        }
        if(plist->count>newCapacity){
            BcRAISE(BcList_eCapacityTooLow,(void*)list,(void*)(CARDPTR)newCapacity);
        }else{
            newElements=(void**)BcMem_Allocate((CARD32)sizeof(void*)*newCapacity);
            i=0;
            while(i<plist->count){
                newElements[i]=plist->elements[i];
                i++;
            }
            BcMem_Deallocate((void**)&(plist->elements));
            plist->elements=newElements;
            plist->capacity=newCapacity;
        }
    }/*BcList_SetCapacity;*/


    PROCEDURE(BcList_Count,(BcList_T list),CARD32)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        return(plist->count);
    }/*BcList_Count;*/
    
    
    PROCEDURE(BcList_ObjectAt,(BcList_T list,CARD32 idx),void*)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(idx>=plist->count){
            BcRAISE(BcList_eBadIndex,list,(void*)(CARDPTR)idx);
        }
        return(plist->elements[idx]);
    }/*BcList_ObjectAt;*/
    
    
    PROCEDURE(BcList_LastObject,(BcList_T list),void*)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(plist->count>0){
            return(plist->elements[plist->count-1]);
        }else{
            return(NIL);
        }
    }/*BcList_LastObject;*/


    PROCEDURE(BcList_AddObject,(BcList_T list,void* newObject),void)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(newObject==NIL){
            BcRAISE(BcList_eNilObject,(void*)list,NIL);
        }
        if(plist->count==plist->capacity){
            BcList_SetCapacity(plist,2*plist->capacity);
        }
        plist->elements[plist->count]=newObject;
        (plist->count)++;
    }/*BcList_AddObject;*/
    
    
    PROCEDURE(BcList_InsertObjectAt,
                    (BcList_T list,void* newObject,CARD32 idx),void)
    {
            CARD32          i;
            BcList_P            plist;
        
        plist=(BcList_P)list;

#ifdef BcList_DEBUG
Console_fprintf(console,"BcList_InsertObjectAt\n");
Console_fprintf(console,
    " -> plist.count=    %d\n"
    " -> plist.capacity= %d\n"
    " -> plist.elements= %08lx %08lx %08lx %08lx\n\n"
    " -> newObject=     %08lx\n"
    " -> idx=         %d\n",
    plist->count,plist->capacity,
    plist->elements[0],plist->elements[1],
    plist->elements[2],plist->elements[3],
    newObject,idx);
#endif
        if(newObject==NIL){
            BcRAISE(BcList_eNilObject,(void*)list,NIL);
        }
        if(plist->count>=plist->capacity){
            BcList_SetCapacity(plist,2*plist->capacity);
        }
        i=plist->count;
        while(idx<i){
            plist->elements[i]=plist->elements[i-1];
            i--;
        }
        plist->elements[i]=newObject;
        (plist->count)++;
#ifdef BcList_DEBUG
Console_fprintf(console,
    "<-  plist.count=    %d\n"
    "<-  plist.capacity= %d\n"
    "<-  plist.elements= %08lx %08lx %08lx %08lx\n",
    plist->count,plist->capacity,
    plist->elements[0],plist->elements[1],plist->elements[2],plist->elements[3]);
Console_fprintf(console,"BcList_InsertObjectAt returns TRUE\n");
#endif
    }/*BcList_InsertObjectAt;*/


    PROCEDURE(BcList_RemoveObjectAt,(BcList_T list,CARD32 idx),void*)
        /* RETURN: removed object (or NIL).*/
    {
            void*               oldObject;
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(idx>=plist->count){
            BcRAISE(BcList_eBadIndex,(void*)list,(void*)(CARDPTR)idx);
        }
        oldObject=plist->elements[idx];
        while(idx<plist->count){
            plist->elements[idx]=plist->elements[idx+1];
            idx++;
        }
        (plist->count)--;
        return(oldObject);
    }/*BcList_RemoveObjectAt;*/


    PROCEDURE(BcList_RemoveLastObject,(BcList_T list),void*)
        /* RETURN: removed object (or NIL).*/
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(plist->count>0){
            (plist->count)--;
            return(plist->elements[plist->count]);
        }else{
            return(NIL);
        }
    }/*BcList_RemoveLastObject;*/


    PROCEDURE(BcList_ReplaceObjectAtWith,
                    (BcList_T list,CARD32 idx,void* newObject),void*)
    {
            void*           oldObject;
            BcList_P            plist;
        
        plist=(BcList_P)list;
        if(newObject==NIL){
            BcRAISE(BcList_eNilObject,(void*)list,NIL);
        }
        if(idx>=plist->count){
            BcRAISE(BcList_eBadIndex,(void*)list,(void*)(CARDPTR)idx);
        }
        oldObject=plist->elements[idx];
        plist->elements[idx]=newObject;
        return(oldObject);
    }/*BcList_ReplaceObjectAtWith;*/


    PROCEDURE(BcList_AppendList,(BcList_T list,BcList_T otherlist),void)
    {
            CARD32              newCount;
            CARD32              i;
            BcList_P            plist,otherplist;
        
        plist=(BcList_P)list;
        otherplist=(BcList_P)otherlist;
        newCount=plist->count+otherplist->count;
        if(newCount>plist->capacity){
            BcList_SetCapacity(plist,newCount);
        }
        i=0;
        while(plist->count<newCount){
            plist->elements[plist->count]=otherplist->elements[i];
            (plist->count)++;
            i++;
        }
    }/*BcList_AppendList;*/


    PROCEDURE(BcList_IndexOf,(BcList_T list,void* oldObject),CARD32)
    {
            CARD32              i;
            BcList_P            plist;
        
        plist=(BcList_P)list;
        i=0;
        while((i<plist->count)&&(plist->elements[i]!=oldObject)){
            i++;
        }
        if(i==plist->count){
            return(BcList_NotInList);
        }else{
            return(i);
        }
    }/*BcList_IndexOf;*/


    PROCEDURE(BcList_AddObjectIfAbsent,
                    (BcList_T list,void* newObject),BOOLEAN)
        /* RETURN: newObject added ok.*/
    {
        if(BcList_IndexOf(list,newObject)==BcList_NotInList){
            BcList_AddObject(list,newObject);
            return(TRUE);
        }else{
            return(FALSE);
        }
    }/*BcList_AddObjectIfAbsent;*/
    
    
    PROCEDURE(BcList_RemoveObject,(BcList_T list,void* oldObject),void*)
        /* RETURN: removed object or NIL.*/
    {
            CARD32          idx;
            
        idx=BcList_IndexOf(list,oldObject);
        if(idx==BcList_NotInList){
            return(NIL);
        }else{
            return(BcList_RemoveObjectAt(list,idx));
        }
    }/*BcList_RemoveObject;*/


    PROCEDURE(BcList_ReplaceObjectWith,
                    (BcList_T list,void* oldObject,void* newObject),BOOLEAN)
        /* RETURN: newObject replaced ok.*/
    {
            CARD32          idx;
            
        idx=BcList_IndexOf(list,oldObject);
        if(idx==BcList_NotInList){
            return(FALSE);
        }else{
            return(BcList_ReplaceObjectAtWith(list,idx,newObject)!=NIL);
        }
    }/*BcList_ReplaceObjectWith;*/


    PROCEDURE(BcList_Empty,(BcList_T list),void)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        plist->count=0;
    }/*BcList_Empty;*/
    
        
    PROCEDURE(BcList_MakeObjectsPerform,
                    (BcList_T list,BcList_ActionPr proc),void)
    {
            CARD32              i;
            BcList_P            plist;
        
        plist=(BcList_P)list;       
        i=0;
        while(i<plist->count){
            proc(plist->elements[i]);
            i++;
        }
    }/*BcList_MakeObjectsPerform;*/


    PROCEDURE(BcList_MakeObjectsPerformWith,
                    (BcList_T list,BcList_ActionWithPr proc,void* param),
                    void)
    {
            CARD32              i;
            BcList_P            plist;
        
        plist=(BcList_P)list;
        
#ifdef BcList_DEBUG
Console_fprintf(console,"BcList_MakeObjectsPerformWith\n");
Console_fprintf(console,
    " -> plist.count=    %d\n"
    " -> plist.capacity= %d\n"
    " -> plist.elements= %08lx %08lx %08lx %08lx\n",
    plist->count,plist->capacity,
    plist->elements[0],plist->elements[1],plist->elements[2],plist->elements[3]);
#endif
        i=0;
        while(i<plist->count){
#ifdef BcList_DEBUG
Console_fprintf(console,"elements[%d]=%08lx\n",i,plist->elements[i]);
#endif
            proc(plist->elements[i],param);
            i++;
        }
    }/*BcList_MakeObjectsPerformWith;*/


    PROCEDURE(BcList_Sort,(BcList_T list,BcList_OrderPr order),void)
    {
            BcList_P            plist;
        
        plist=(BcList_P)list;
        qsort(plist->elements,(size_t)plist->count,sizeof(void*),
                (int(*)(const void*,const void*))order);    
    }/*BcList_Sort*/


    PROCEDURE(BcList_Reverse,(BcList_T list),void)
    {
            BcList_P            plist;
            void*               t;
            void**              a;
            void**              b;
                    
        plist=(BcList_P)list;

        a=plist->elements;
        b=plist->elements+plist->count-1;
        while(a<b){
            t=(*a);
            (*a)=(*b);
            (*b)=t;
            a++;
            b--;
        }
    /*
_BcList_Reverse:
00000514        linkw   a6,#0x0
00000518        movel   a6@(0x8:w),a0
0000051c        movel   a0@,d0
0000051e        movel   a0@(0x8:w),a1
00000522        asll    #2,d0
00000524        addl    a0@(0x8:w),d0
00000528        movel   d0,a0
0000052a        bra     0x532:b
0000052c        movel   a1@,d0
0000052e        movel   a0@,a1@+
00000530        movel   d0,a0@
00000532        subqw   #0x4,a0
00000534        cmpl    a1,a0
00000536        bhi     0x52c:b
00000538        unlk    a6
0000053a        rts

            INT32               i;

        for(i=0;i<plist->count/2;i++){
            t=plist->elements[i];
            plist->elements[i]=plist->elements[plist->count-1-i];
            plist->elements[plist->count-1-i]=t;
        }
_BcList_Reverse:
00000514        linkw   a6,#0x0
00000518        moveml  d2/d3/a2,sp@-
0000051c        movel   a6@(0x8:w),a2
00000520        subal   a1,a1
00000522        movel   a2@,d0
00000524        lsrl    #1,d0
00000526        clrl    d3
00000528        cmpl    d3,d0
0000052a        bls     0x558:b
0000052c        movel   a2@(0x8:w),a0
00000530        movel   a0@(0x0:b,a1:l:4),d2
00000534        movel   a1,d1
00000536        addql   #0x1,d1
00000538        movel   a2@,d0
0000053a        subl    d1,d0
0000053c        movel   a0@(0x0:b,d0:l:4),a0@(0x0:b,a1:l:4)
00000542        movel   a2@,d0
00000544        subl    d1,d0
00000546        movel   a2@(0x8:w),a0
0000054a        movel   d2,a0@(0x0:b,d0:l:4)
0000054e        movel   d1,a1
00000550        movel   a2@,d0
00000552        lsrl    #1,d0
00000554        cmpl    a1,d0
00000556        bhi     0x52c:b
00000558        moveml  a6@(0xfff4:w),d2/d3/a2
0000055e        unlk    a6
00000560        rts
00000562        nop
    */
    }/*BcList_Reverse*/
    

/*END BcList.*/


/*** BcList.c                         -- 2004-01-01 09:33:10 -- pascal   ***/
