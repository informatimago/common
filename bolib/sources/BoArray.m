/******************************************************************************
FILE:               BoArray.m
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This Objective-C class defines arrays of objects.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/07/21 <PJB> Creation.
    1992/10/22 <PJB> Renamed dumpOn to printOn.
    1993/01/18 <PJB> Refined, added exceptions.
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
    1996/04/20 <PJB> Updated to use retain/release BoObjects.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 1996
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#include <BoArray.h>
#include <BcMem.h>
#include <BcExcept.h>
#include <BcImplementation.h>

@implementation BoArray

    -(id)init
    {
        return([self error:"You must use initCount: on a BoArray "
                            "instead of init.\n"]);
    }/*init;*/
    
    -(void)printOn:(FILE*)file
    {
            CARD32          i;
            
        [super printOn:file];
        fprintf(file,"size=           %8lu\n",size);
        fprintf(file,"psize=          %8lu\n",psize);
        i=0;
        while(i<size){
            fprintf(file,"[%4lu]=         %p\n",i,(void*)(elements[i]));
            INC(i);
        }
    }/*printOn:;*/


    -(id)initCount:(CARD32)newSize
    {
            CARD32          i;
        
        if(newSize>0){
            elements=BcMem_Allocate(sizeof(id)*newSize);
            psize=newSize;
            size=newSize;
            i=0;
            while(i<size){
                elements[i]=NIL;
                INC(i);
            }
        }else{
            psize=0;
            size=0;
            elements=NIL;
        }
        return(self);
    }/*initCount:;*/


    -(id)free
    {
        [self makeObjectsPerform:@selector(release)];
        if(elements!=NIL){
            BcMem_Deallocate((void**)&elements);
        }
        return([super free]);
    }/*free;*/
    
        
    -(CARD32)size
    {
        return(size);
    }/*size;*/
    
        
    -(void)resize:(CARD32)newSize
    {
            id*             newElements;
            CARD32          i;
            
        if(newSize>psize){
            newElements=BcMem_Allocate(sizeof(id)*newSize);
            psize=newSize;
            i=0;
            while(i<size){
                newElements[i]=elements[i];
                INC(i);
            }
            while(i<psize){
                newElements[i]=NIL;
                INC(i);
            }
            if(elements!=NIL){
                BcMem_Deallocate((void**)&elements);
            }
            elements=newElements;
            size=newSize;
        }else if(newSize>size){
            /* size < newSize <= psize*/
            i=size;
            while(i<newSize){
                elements[i]=NIL;
                INC(i);
            }
            size=newSize;
        }else{
            /* newSize <= size*/
            size=newSize;
            /* if there was a garbage collector, */
            /* then we would set to NIL the forgotten elements.*/
        }
    }/*resize:;*/
            

    -(id)objectAt:(CARD32)idx
    {
        if(idx>=size){
            BcRAISE(BoArray_eBadIndex,(void*)self,(void*)idx);
        }
        return(elements[idx]);
    }/*objectAt:;*/
    

    -(id)replaceObjectAt:(CARD32)idx with:(id)newObject
    {
            id          old;
            
        if(idx>=size){
            BcRAISE(BoArray_eBadIndex,(void*)self,(void*)idx);
        }
        old=elements[idx];
        elements[idx]=newObject;
        [newObject retain];
        [old release];
        return(old);
    }/*replaceObjectAt:with:;*/


    -(id)insertObject:(id)newObject at:(CARD32)idx
    {
            CARD32              i;
            
        if(idx>=size){
            BcRAISE(BoArray_eBadIndex,(void*)self,(void*)idx);
        }
        i=size-1;
        [elements[i] release];
        [newObject retain];
        while(i>idx){
            elements[i]=elements[i-1];
            DEC(i);
        }
        elements[i]=newObject;
        return(self);
    }/*insertObject:at:;*/
    
        
    -(id)removeObjectAt:(CARD32)idx
    {
            CARD32              i;
            id                  old;
            
        if(idx>=size){
            BcRAISE(BoArray_eBadIndex,(void*)self,(void*)idx);
        }
        old=elements[idx];
        [old release];
        i=idx;
        while(i<size-1){
            elements[i]=elements[i+1];
            INC(i);
        }
        elements[i]=NIL;
        return(old);
    }/*removeObjectAt:;*/
    
    
    -(CARD32)indexOf:(id)oldObject
    {
            CARD32          i;
        
        i=0;
        while((i<size)AND(elements[i]!=oldObject)){
            INC(i);
        }
        if(i==size){
            return(MAX_CARD32);
        }else{
            return(i);
        }   
    }/*indexOf:;*/
    
            
    -(id)makeObjectsPerform:(SEL)aSelector
    {
            CARD32                  i;
        
        i=0;
        while(i<size){
            [elements[i] perform:aSelector];
            INC(i);
        }
        return(self);
    }/*makeOjectsPerform:;*/
    
    
    -(id)makeObjectsPerform:(SEL)aSelector with:anObject
    {
            CARD32                  i;
        
        i=0;
        while(i<size){
            [elements[i] perform:aSelector with:anObject];
            INC(i);
        }
        return(self);
    }/*makeOjectsPerform:with:;*/
    

    -(void)withEachMake:(id)receiver perform:(SEL)sel
    {
            CARD32                  i;
        
        i=0;
        while(i<size){
            [receiver perform:sel with:elements[i]];
            INC(i);
        }
    }/*withEachMake:perform:;*/
    

    -(void)withEachMake:(id)receiver perform:(SEL)sel andWith:(id)obj
    {
            CARD32                  i;
        
        i=0;
        while(i<size){
            [receiver perform:sel with:elements[i] with:obj];
            INC(i);
        }
    }/*withEachMake:perform:andWith:;*/
        
@end
/*** BoArray.m                        -- 2004-01-01 09:57:02 -- pascal   ***/
