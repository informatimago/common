/******************************************************************************
FILE:               BoList.m
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    A BoList is a collection of objects. The class provides an interface 
    that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BoLists are 
    implemented as arrays to allow fast random access using an index. 
    Indices start at 0.
    See the NeXT step List Class documentation.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/07/21 <PJB> Creation (BoArray).
    1992/10/25 <PJB> Upgraded to the same interface as NeXTstep objc/List.h.
    1993/01/12 <PJB> Added exception RAISING (thus drifting from the NeXT List
                        class implementation).
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
    1996/04/20 <PJB> Updated to use retain/release BoObjects.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 1996
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#include <BoList.h>
#include <BcImplementation.h>

@implementation BoList

    -(id)init
    {
        return([self initCount:BoListNoRetain_Minimum]);
    }/*init;*/


    -(id)initCount:(CARD32)newCapacity
    {       
        return([super initCount:newCapacity]);
    }/*initCount:;*/
    
    
    -(id)free
    {
        [self empty];
        return([super free]);
    }/*free;*/
    

    -(id)addObject:(id)newObject
    {
        [super addObject:newObject];
        /* retain must be done after for the case where an exception is raised.*/
        [newObject retain];
        return(self);
    }/*addObject:;*/
    
    
    -(id)insertObject:(id)newObject at:(CARD32)idx
    {
        [super insertObject:newObject at:idx];
        /* retain must be done after for the case where an exception is raised.*/
        [newObject retain];
        return(self);
    }/*insertObject:at:;*/
    

    -(id)removeObjectAt:(CARD32)idx
    {
            id          oldObject;
        oldObject=[super removeObjectAt:idx];
        [oldObject release];
        return(oldObject);
    }/*removeObjectAt:;*/
    
    
    -(id)removeLastObject
    {
            id          oldObject;
        oldObject=[super removeLastObject];
        [oldObject release]; /* (it may be NIL).*/
        return(oldObject);
    }/*removeLastObject;*/
    
    
    -(id)replaceObjectAt:(CARD32)idx with:(id)newObject
    {
            id          oldObject;
        oldObject=[super replaceObjectAt:idx with:newObject];
        [newObject retain];
        [oldObject release];
        return(oldObject);
    }/*replaceObjectAt:with:;*/
    
    
    -(id)appendList:(BoList*)otherList
    {
            CARD32      newCount;
            CARD32      i;
            
        newCount=count+[otherList count];
        if(newCount>capacity){
            [self capacity:newCount];
        }
        i=0;
        while(count<newCount){
            elements[count]=[otherList objectAt:i];
            [elements[count] retain];
            INC(count);
            INC(i);
        }
        return(self);
    }/*appendList:;*/
    
    
    -(id)empty
    {
        [self makeObjectsPerform:@selector(release)];
        return([super empty]);
    }/*empty;*/
    
    
@end
/*** BoList.m                         -- 2004-01-01 09:57:58 -- pascal   ***/
