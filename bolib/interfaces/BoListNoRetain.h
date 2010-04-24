/******************************************************************************
FILE:               BoListNoRetain.h
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    A BoListNoRetain is a collection of objects. The class provides an 
    interface that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BoListNoRetain are 
    implemented as arrays to allow fast random access using an idx. 
    Indices start at 0.
    A BoListNoRetain does not retain/release objects it contains. Its subclass
    BoList does.
    See the NeXT step List Class documentation.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1996/09/17 <PJB> Creation (from BoList, which becomes a subclass).
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 1996
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef BoListNoRetain_h
#define BoListNoRetain_h
#include <BcInterface.h>
#include <BcTypes.h>
#include <BoObject.h>
#include <BcExcept.h>
#include <BcMem.h>      /* exceptions.*/

#define BoListNoRetain_eCapacityTooLow  (10010) /* BoListNoRetain*,CARD32 badCapacity*/
#define BoListNoRetain_eNilObject       (10011) /* BoListNoRetain**/
#define BoListNoRetain_eBadIndex        (10012) /* BoListNoRetain*,CARD32 badindex*/


#define BoListNoRetain_Minimum      (8) /* minimum size for a BoListNoRetain.*/
#define BoListNoRetain_NotInList    (MAX_CARD32)

@interface BoListNoRetain:BoObject
{
    CARD32          count;          /* actual number of element.*/
    CARD32          capacity;       /* capacity of the array.*/
    id*             elements;       /* actually ARRAY [0..capacity-1] OF id;*/
}

    -(id)init;
    -(id)initCount:(CARD32)newCapacity;
    -(id)free;
    -(id)copyFromZone:(void*)zone;
    -(BOOLEAN)isEqual:(BoListNoRetain*)otherList;
    -(CARD32)capacity;
    -(id)capacity:(CARD32)newCapacity;
    -(id)setAvailableCapacity:(CARD32)newCapacity;
    -(CARD32)count;
    -(id)objectAt:(CARD32)idx;
    -(id)lastObject;
    -(id)addObject:(id)newObject;
    -(id)insertObject:(id)newObject at:(CARD32)idx;
    -(id)removeObjectAt:(CARD32)idx;
    -(id)removeLastObject;
    -(id)replaceObjectAt:(CARD32)idx with:(id)newObject;
    -(id)appendList:(BoListNoRetain*)otherList;
    -(CARD32)indexOf:(id)oldObject;
    -(id)addObjectIfAbsent:(id)newObject;
    -(id)removeObject:(id)oldObject;
    -(id)replaceObject:(id)oldObject with:(id)newObject;
    -(id)empty;
    -(id)makeObjectsPerform:(SEL)aSelector;
    -(id)makeObjectsPerform:(SEL)aSelector with:(id)anObject;
    -(id)makeObjectsPerform:(SEL)aSelector with:(id)anObject with:(id)another;
    -(id)withEachMake:(id)receiver perform:(SEL)sel;
    -(id)withEachMake:(id)receiver perform:(SEL)sel andWith:(id)obj;

@end
#endif
/*** BoListNoRetain.h                 -- 2004-01-01 09:57:33 -- pascal   ***/
