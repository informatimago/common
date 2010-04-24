/******************************************************************************
FILE:               BpArray.hh
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This C++ class defines arrays of objects.
    Note: if a pre-condition is not fulfilled then the methods will RAISE
    an exception.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.6  95/11/23  03:47:43  pascal
    Added BpClass and runtime class support in BpObject.
    Updated subclasses.
    
    Added dependant/dependee in BpObject.
    
    Revision 1.5  95/10/22  03:19:32  pascal
    Setting revision name V1.
    
    Revision 1.2  95/10/22  03:04:20  pascal
    Modifications while agdding BpDict.
    
    1992-07-21 <PJB> Creation.
    1993-01-18 <PJB> Refined, added exceptions.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
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
#ifndef __BpArray__
#define __BpArray__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh
#include BpClass_hh

#define BpArray_eBadIndex       (10022) // BpArray* array,CARD32 badindex

    typedef void (*BpArray_ActionPr)(BpObject* obj);
    typedef void (*BpArray_ActionWithPr)(BpObject* obj,BpObject* with);
    typedef void (*BpArray_ActionWithAndWithPr)
                    (BpObject* obj,BpObject* with, BpObject* andWith);

#define BpArray_SUPER BpObject
class BpArray:public BpArray_SUPER
{
public:

// birth and death:

    CONSTRUCTOR(BpArray)
        /*
            NOTE:       My constructors have all zero parameters! Use resize
                        to set the newSize.
            POST:       this->size()==0.
                        You should send a resize message to allocate wanted
                        size.
            RETURN:     self;
        */

    DESTRUCTOR(BpArray)
        /*
            DO:         Release the memory used by self.
            NOTE:       This does release the objects in the array.
        */
    
// override BpObject methods:

    METHOD(BpArray,makeBrother,(void),BpObject*)
    METHOD(BpArray,printOnLevel,(FILE* file,CARD32 level),void)
            
// new methods:

    METHOD(BpArray,initWithObjectsCount,(BpObject** objects,CARD32 count),void)
        /*
            POST:       this->size()=count
                        for each i in [0..count-1],
                            objects[i]==this->objectAt(i).
        */
        
    METHOD(BpArray,size,(void),CARD32)
        /*
            RETURN:     the current size of the array.
        */
    
    METHOD(BpArray, resize,(CARD32 newSize),BpArray*)
        /*
            PRE:        newSize>[self size]
                        m=Minimum([self size],newSize)
                        for each i in [0..m-1], t[i]=[self objectAt:i];
            POST:       [self size]=newSize,
                        for each i in [0..m-1], t[i]=[self objectAt:i],
                        for each i in [m..[self size]-1],
                                                [self objectAt:i]=NIL;
            NOTE:       it is possible but meaningless to set the size to 0.
            RETURN:     self.
        */
        
    METHOD(BpArray,objectAt,(CARD32 index),BpObject*)
        /*
            PRE:        index<[self size];
            RETURN:     the element in the slot index of the array self
        */

    METHOD(BpArray,replaceObjectAtWith,
                (CARD32 index,BpObject* newObject), BpObject*)
        /*
            PRE:        index<[self size];
            POST:       [self objectAt:index]=newObject;
            NOTE:       retains newObject and releases returned object.
            RETURN:     the old [self objectAt:index];
        */

    METHOD(BpArray,insertObjectAt,(BpObject* newObject,CARD32 index),BpArray*)
        /*
            PRE:        index<[self size],
                        for each i in [index..[self size]-2],
                                t[i]=[self objectAt:i];
            POST:       [self objectAt:index]=newObject,
                        for each i in [index+1..[self size]-1], 
                                t[i-1]=[self objectAt:i];
            RETURN:     self; 
            NOTE:       [self objectAt:[self size]-1] is lost.
            NOTE:       retains newObject.
        */
        
    METHOD(BpArray,removeObjectAt,(CARD32 index),BpObject*)
        /*
            PRE:        index<[self size],
                        for each i in [index..[self size]-1],
                                t[i]=[self objectAt:i];
            POST:       [self objectAt:[self size]-1]=NIL, 
                        for each i in [index..[self size]-2],
                                t[i+1]=[self objectAt:i];
            NOTE:       releases returned object.
            RETURN:     g => t[index];
        */

    METHOD(BpArray,indexOf,(BpObject* oldObject),CARD32)
        /*
            RETURN:     the smallest index such as
                            [self objectAt:index]=oldObject, 
                        or MAX_CARD32.
        */
        
    METHOD(BpArray,makeObjectsPerform,(BpArray_ActionPr proc),BpArray*)
        /*
            DO:         send the message aSelector:anObject to each element 
                        of the array.
        */

    METHOD(BpArray,makeObjectsPerformWith,
            (BpArray_ActionWithPr proc,BpObject* anObject),BpArray*)
        /*
            DO:         send the message aSelector:anObject to each element 
                        of the array.
        */
    
    METHOD(BpArray,withEachMakePerform,
            (BpObject* receiver,BpArray_ActionWithPr proc),BpArray*)
        /*
            DO:         for each current in self,
                            [receiver perform:sel with:current].
        */
        
    METHOD(BpArray,withEachMakePerformWithAndWith,
            (BpObject* receiver,BpArray_ActionWithAndWithPr proc,
             BpObject* obj),BpArray*)
        /*
            DO:         for each current in self,
                            [receiver perform:sel with:current with:obj].
        */

// SEE: We may need a method stopping the loop when the receiver returns FALSE.
        
protected:
    CARD32          lsize;          // array size
    CARD32          psize;          // size of elements array (size<=psize).
    BpObject**      elements;       // actually ARRAY [0..size-1] OF id;
    // psize is there for when we reduce the size of the array, we don't want
    // to copy the elements array.
};//BpArray.


#define BpArray_cInitializedWithObjects     (1)
#define BpArray_cResized                    (2)
#define BpArray_cObjectReplaced             (3)
#define BpArray_cObjectInserted             (4)
#define BpArray_cObjectRemoved              (5)




#endif
