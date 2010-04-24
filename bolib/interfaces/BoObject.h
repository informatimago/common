/******************************************************************************
FILE:               BoObject.h
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This class may be used as root for the class tree of applications.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/07/20 <PJB> Creation.
    1992/10/22 <PJB> Renamed printOn to printOn.
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 1992
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef BoObject_h
#define BoObject_h
#include <stdio.h>
#include <objc/Object.h>
#include <BcInterface.h>
#include <BcTypes.h>
@class BoListNoRetain;

@interface BoObject:Object
{
    long                _useCount;
    BoListNoRetain*     _dependants;
}


#ifdef MPW
    +(id)alloc;
#endif
    -(id)init;
    -(id)free;

    -(void)printOn:(FILE*)file;
        /*
            DO:         print it-self onto the file.
        */

    -(void)retain;
    -(void)release;
    -(long)useCount;
    +(void)processReleasePool;
    
    -(void)dependantAdd:(id)aDependant;
    -(void)dependantRemove:(id)aDependant;
    -(void)dependeeChanged:(BoObject*)aDependee cause:(long)cause;
    
    -(void)changed:(long)cause;
        /* private: sends dependeeChanged:cause: to dependants. */
    
#define BoObject_cause_deleting     (-1)
#define assign(variable,value)                          \
    {                                                   \
        if((variable)!=nil){[(variable) release];}      \
        (variable)=(value);                             \
        if((variable)!=nil){[(variable) retain];}       \
    }

@end
#endif
/*** BoObject.h                       -- 2004-01-01 09:56:29 -- pascal   ***/
