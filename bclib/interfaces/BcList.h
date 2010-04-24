/******************************************************************************
FILE:               BcList.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI-C (malloc)
USER-INTERFACE:     None
DESCRIPTION
    A BcList is a collection of objects. The class provides an interface 
    that permits easy manipulation of the collection as a fixed or 
    variable-sized list,a set,or an ordered collection. BcLists are 
    implemented as arrays to allow fast random access using an index. 
    Indices start at 0.
    See the NeXT step List Class documentation.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2001-06-05 <PJB> Added common libraries and dosname utility to the repository.
    1994-10-08 <PJB> Added BcList_Reverse.
    1994-09-25 <PJB> Added BcList_Sort.
    1993-03-19 <PJB> Renamed BcList for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1992-12-29 <PJB> Translated from Objective-C to C.
    1992-10-25 <PJB> Upgraded to the same interface as NeXTstep objc/List.h.
    1992-07-21 <PJB> Creation ,(BoArray).
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2003

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
#ifndef BcList_h__
#define BcList_h__
#include <names.h>
#include BcInterface_h
#include BcTypes_h

#define BcList_Minimum      (8)     /* minimum size for a BcList.*/
#define BcList_NotInList    (MAX_CARD32)

#define BcList_eBase            (10100)
#define BcList_eCapacityTooLow  (BcList_eBase+0) /* BcList* list,CARD32 badCapacity*/
#define BcList_eNilObject       (BcList_eBase+1) /* BcList* list*/
#define BcList_eBadIndex        (BcList_eBase+2) /* BcList* list,CARD32 badindex*/

    typedef void*       BcList_T;
    
    
    PROCEDURE(BcList_Allocate,(void),BcList_T)
    PROCEDURE(BcList_Deallocate,(BcList_T* list),void)
    PROCEDURE(BcList_CopyTo,(BcList_T list,BcList_T clone),void)
    PROCEDURE(BcList_IsEqual,(BcList_T list,BcList_T otherlist),BOOLEAN)
    PROCEDURE(BcList_Capacity,(BcList_T list),CARD32)
    PROCEDURE(BcList_SetCapacity,(BcList_T list,CARD32 newCapacity),void)
    PROCEDURE(BcList_Count,(BcList_T list),CARD32)
    PROCEDURE(BcList_ObjectAt,(BcList_T list,CARD32 idx),void*)
    PROCEDURE(BcList_LastObject,(BcList_T list),void*)
    PROCEDURE(BcList_AddObject,(BcList_T list,void* newObject),void)
        /* Add the object at the end of the list */
    PROCEDURE(BcList_InsertObjectAt,
                    (BcList_T list,void* newObject,CARD32 idx),void)
        /* RAISE:   BcList_eNilObject, BcList_eCapacityTooLow.*/
    PROCEDURE(BcList_RemoveObjectAt,(BcList_T list,CARD32 idx),void*)
        /* RETURN: removed object ,(or NIL).*/
    PROCEDURE(BcList_RemoveLastObject,(BcList_T list),void*)
        /* RETURN: removed object ,(or NIL).*/
    PROCEDURE(BcList_ReplaceObjectAtWith,
                    (BcList_T list,CARD32 idx,void* newObject),void*)
        /* RETURN: removed object ,(or NIL).*/
    PROCEDURE(BcList_AppendList,(BcList_T list,BcList_T otherlist),void)
    PROCEDURE(BcList_IndexOf,(BcList_T list,void* oldObject),CARD32)
    PROCEDURE(BcList_AddObjectIfAbsent,
                    (BcList_T list,void* newObject),BOOLEAN)
        /* RETURN: newObject added ok.*/
    PROCEDURE(BcList_RemoveObject,(BcList_T list,void* oldObject),void*)
        /* RETURN: removed object or NIL.*/
    PROCEDURE(BcList_ReplaceObjectWith,
                    (BcList_T list,void* oldObject,void* newObject),BOOLEAN)
        /* RETURN: newObject replaced ok.*/
    PROCEDURE(BcList_Empty,(BcList_T list),void)
    
    typedef void(*BcList_ActionPr)(void*);
    typedef void(*BcList_ActionWithPr)(void*,void*);
    
    PROCEDURE(BcList_MakeObjectsPerform,
                    (BcList_T list,BcList_ActionPr proc),void)
    PROCEDURE(BcList_MakeObjectsPerformWith,
                    (BcList_T list,BcList_ActionWithPr proc,void* param),
                    void)

    typedef SignT(*BcList_OrderPr)(const void**,const void**);

    PROCEDURE(BcList_Sort,(BcList_T list,BcList_OrderPr order),void)

    PROCEDURE(BcList_Reverse,(BcList_T list),void)
        /*
            PRE:        c=BcList_Count(list),
                        for each i in [0..c-1],
                                e[i]=BcList_ObjectAt(list,i);
            POST:       c=BcList_Count(list),
                        for each i in [0..c-1],
                                e[c-1-i]=BcList_ObjectAt(list,i);
        */
        
#endif /*BcList.*/


/*** BcList.h                         -- 2003-11-30 07:09:29 -- pascal   ***/
