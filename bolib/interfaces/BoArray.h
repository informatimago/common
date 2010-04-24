/******************************************************************************
FILE:               BoArray.h
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This Objective-C class defines arrays of objects.
    Note: if a pre-condition is not fulfilled then the methods will RAISE
    an exception.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/07/21 <PJB> Creation.
    1993/01/18 <PJB> Refined, added exceptions.
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 1993
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef BoArray_h
#define BoArray_h
#include <BcInterface.h>
#include <BcTypes.h>
#include <BoObject.h>

#define BoArray_eBadIndex       (10022) /* BoArray* array,CARD32 badindex*/

@interface BoArray:BoObject
{
    CARD32          size;           /* array size*/
    CARD32          psize;          /* size of elements array (size<=psize).*/
    id*             elements;       /* actually ARRAY [0..size-1] OF id;*/
    /* psize is there for when we reduce the size of the array, we don't want*/
    /* to copy the elements array.*/
}

    -(id)initCount:(CARD32)newSize;
        /*
            POST:       [self size]=newSize,
                        for each i in [0..[self size]-1],
                                [self objectAt:i]=NIL;
            RETURN:     self;
        */

    -(id)free;
        /*
            DO:         Release the memory used by self.
            RETURN:     NIL;
            NOTE:       This does not free the objects in the array.
        */
    
    -(CARD32)size;
        /*
            RETURN:     the current size of the array.
        */
    
    -(void)resize:(CARD32)newSize;
        /*
            PRE:        newSize>[self size]
                        m=Minimum([self size],newSize)
                        for each i in [0..m-1], t[i]=[self objectAt:i];
            POST:       [self size]=newSize,
                        for each i in [0..m-1], t[i]=[self objectAt:i],
                        for each i in [m..[self size]-1],
                                                [self objectAt:i]=NIL;
            NOTE:       it is possible but meaningless to set the size to 0.
        */
        
    -(id)objectAt:(CARD32)idx;
        /*
            PRE:        idx<[self size];
            RETURN:     the element in the slot idx of the array self
        */

    -(id)replaceObjectAt:(CARD32)idx with:(id)newObject;
        /*
            PRE:        idx<[self size];
            POST:       [self objectAt:idx]=newObject;
            RETURN:     the old [self objectAt:idx];
        */

    -(id)insertObject:(id)newObject at:(CARD32)idx;
        /*
            PRE:        idx<[self size],
                        for each i in [idx..[self size]-2],
                                t[i]=[self objectAt:i];
            POST:       [self objectAt:idx]=newObject,
                        for each i in [idx+1..[self size]-1], 
                                t[i-1]=[self objectAt:i];
            RETURN:     self; 
            NOTE:       [self objectAt:[self size]-1] is lost.
        */
        
    -(id)removeObjectAt:(CARD32)idx;
        /*
            PRE:        idx<[self size],
                        for each i in [idx..[self size]-1],
                                t[i]=[self objectAt:i];
            POST:       [self objectAt:[self size]-1]=NIL, 
                        for each i in [idx..[self size]-2],
                                t[i+1]=[self objectAt:i];
            RETURN:     g => t[idx];
        */

    -(CARD32)indexOf:(id)oldObject;
        /*
            RETURN:     the smallest idx such as
                            [self objectAt:idx]=oldObject, 
                        or MAX_CARD32.
        */
        
    -(id)makeObjectsPerform:(SEL)aSelector;
        /*
            DO:         send the message aSelector:anObject to each element 
                        of the array.
        */

    -(id)makeObjectsPerform:(SEL)aSelector with:anObject;
        /*
            DO:         send the message aSelector:anObject to each element 
                        of the array.
        */
    
    -(void)withEachMake:(id)receiver perform:(SEL)sel;
        /*
            DO:         for each current in self,
                            [receiver perform:sel with:current].
        */
        
    -(void)withEachMake:(id)receiver perform:(SEL)sel andWith:(id)obj;
        /*
            DO:         for each current in self,
                            [receiver perform:sel with:current with:obj].
        */

/* SEE: We may need a method stopping the loop when the receiver returns FALSE.*/
        
@end
#endif
/*** BoArray.h                        -- 2004-01-01 09:57:22 -- pascal   ***/
