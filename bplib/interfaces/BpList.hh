/******************************************************************************
FILE:               BpList.hh
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    A BpList is a collection of objects. The class provides an interface 
    that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BpLists are 
    implemented as arrays to allow fast random access using an index. 
    Indices start at 0.
    See the NeXT step Objective-C List Class documentation.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.6  95/11/23  03:48:43  pascal
    Added BpClass and runtime class support in BpObject.
    Updated subclasses.
    
    Added dependant/dependee in BpObject.
    
    Revision 1.5  95/10/22  03:19:51  pascal
    Setting revision name V1.
    
    Revision 1.2  95/10/22  03:05:08  pascal
    Modifications while adding BpDict.
    
    1992-07-21 <PJB> Creation (BpArray).
    1992-10-25 <PJB> Upgraded to the same interface as NeXTstep objc/List.h.
    1993-03-16 <PJB> Translated from Objective-C to C++.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1994-12-30 <PJB> Added sort.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

    This file is part of the bplib library..

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
#ifndef __BpList__
#define __BpList__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh
#include BpClass_hh
extern "C"{
#include BcExcept_h
#include BcMem_h        // exceptions.
}

#define BpList_eCapacityTooLow  (10010) // BpList* list,CARD32 badCapacity
#define BpList_eNilObject       (10011) // BpList* list
#define BpList_eBadIndex        (10012) // BpList* list,CARD32 badindex


#define BpList_Minimum      (8)     // minimum size for a BpList.
#define BpList_NotInList    (MAX_CARD32)

    typedef void (*BpList_ActionPr)(BpObject* obj);
    typedef void (*BpList_ActionWithPr)(BpObject* obj,BpObject* with);
    typedef void (*BpList_ActionWithAndWithPr)
                    (BpObject* obj,BpObject* with,BpObject* andWith);
    typedef SignT (*BpList_ComparePr)(BpObject**,BpObject**);
    
#define BpList_SUPER BpObject
class BpList:public BpList_SUPER
{
public:

// birth and death:

    CONSTRUCTOR(BpList)
    DESTRUCTOR(BpList)

// override BpObject methods:

    METHOD(BpList,makeBrother,(void),BpObject*)
    METHOD(BpList,printOnLevel,(FILE* file,CARD32 level),void)
            
// new methods:

    METHOD(BpList,freeObjects,(void),BpList*)
    METHOD(BpList,isEqual,(BpList* otherList),BOOLEAN)
    METHOD(BpList,capacity,(void),CARD32)
    METHOD(BpList,capacitySet,(CARD32 newCapacity),BpList*)
    METHOD(BpList,count,(void),CARD32)
    METHOD(BpList,objectAt,(CARD32 index),BpObject*)
    METHOD(BpList,lastObject,(void), BpObject*)
    METHOD(BpList,addObject,(BpObject* newObject),BpList*)
    METHOD(BpList,insertObjectAt,(BpObject* newObject,CARD32 index),BpList*)
    METHOD(BpList,removeObjectAt,(CARD32 index),BpObject*)
    METHOD(BpList,removeLastObject,(void),BpObject*)
    METHOD(BpList,replaceObjectAtWith,(CARD32 index,BpObject* nObj),BpObject*)
    METHOD(BpList,appendList,(BpList* otherList),BpList*)
    METHOD(BpList,indexOf,(BpObject* oldObject),CARD32)
    METHOD(BpList,addObjectIfAbsent,(BpObject* newObject),BpList*)
    METHOD(BpList,removeObject,(BpObject* oldObject),BpObject*)
    METHOD(BpList,replaceObjectWith,(BpObject* oObj,BpObject* nObj),BpObject*)
    METHOD(BpList,empty,(void),BpList*)
    METHOD(BpList,makeObjectsPerform,(BpList_ActionPr proc),BpList*)
    METHOD(BpList,makeObjectsPerformWith,
            (BpList_ActionWithPr proc,BpObject* anObject),BpList*)
    METHOD(BpList,withEachMakePerform,
            (BpObject* receiver,BpList_ActionWithPr proc),BpList*)
    METHOD(BpList,withEachMakePerformWithAndWith,
            (BpObject* receiver,BpList_ActionWithAndWithPr proc,
             BpObject* obj),BpList*)

    METHOD(BpList,sort,(BpList_ComparePr compare),BpList*)
    
protected:
    CARD32          lcount;         // actual number of element.
    CARD32          lcapacity;      // capacity of the array.
    BpObject**      elements;       // actually ARRAY [0..capacity-1] OF id;
};//BpList.

// Causes sent to dependants:
#define BpList_cObjectsFreed    (1)
#define BpList_cObjectAdded     (2)
#define BpList_cObjectInserted  (3)
#define BpList_cObjectRemoved   (4)
#define BpList_cObjectReplaced  (5)
#define BpList_cListAppended    (6)
#define BpList_cSorted          (7)



#endif

