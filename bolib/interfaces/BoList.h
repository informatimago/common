/******************************************************************************
FILE:               BoList.h
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    A BoList is a collection of objects. The class provides an interface 
    that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BoLists are 
    implemented as arrays to allow fast random access using an idx. 
    Indices start at 0.
    See the NeXT step List Class documentation.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/07/21 <PJB> Creation (BoArray).
    1992/10/25 <PJB> Upgraded to the same interface as NeXTstep objc/List.h.
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
    1996/09/17 <PJB> We may have two kind of BoList: retaining and 
                     non-retaining ones. Once created, we cannot change 
                     their kind.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2011
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef BoList_h
#define BoList_h
#include <BcInterface.h>
#include <BoListNoRetain.h>

/* these macros are kept for compatibility with old sources.*/
#define BoList_eCapacityTooLow  (BoListNoRetain_eCapacityTooLow)
#define BoList_eNilObject       (BoListNoRetain_eNilObject)
#define BoList_eBadIndex        (BoListNoRetain_eBadIndex)
#define BoList_Minimum          (BoListNoRetain_Minimum)
#define BoList_NotInList        (BoListNoRetain_NotInList)

@interface BoList:BoListNoRetain
{
    int dummy;
}
    -(id)init;
    -(id)initCount:(CARD32)newCapacity;
    -(id)free;
    -(id)addObject:(id)newObject;
    -(id)insertObject:(id)newObject at:(CARD32)idx;
    -(id)removeObjectAt:(CARD32)idx;
    -(id)removeLastObject;
    -(id)replaceObjectAt:(CARD32)idx with:(id)newObject;
    -(id)appendList:(BoList*)otherList;
    -(id)empty;

@end
#endif
/*** BoList.h                         -- 2004-01-01 09:58:47 -- pascal   ***/
