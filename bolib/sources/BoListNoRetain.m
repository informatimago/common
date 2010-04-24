/******************************************************************************
FILE:               BoListNoRetain.m
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    A BoListNoRetain is a collection of objects. The class provides an 
    interface that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BoListNoRetain are 
    implemented as arrays to allow fast random access using an index. 
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
#include <BoListNoRetain.h>
#include <BcImplementation.h>

@implementation BoListNoRetain

    -(id)init
    {
        return([self initCount:BoListNoRetain_Minimum]);
    }/*init;*/


    -(id)initCount:(CARD32)newCapacity
    {       
        [super init];
        count=0;
        if(newCapacity<BoListNoRetain_Minimum){
            capacity=BoListNoRetain_Minimum;
        }else{
            capacity=newCapacity;
        }
        elements=(id*)BcMem_Allocate(sizeof(id)*capacity);
        return(self);
    }/*initCount:;*/


    -(id)free
    {
        BcMem_Deallocate((void**)&elements);
        return([super free]);
    }/*free;*/
    

    -(id)copy
    {
            BoListNoRetain*         clone;
                        
        clone=(BoListNoRetain*)[[BoListNoRetain alloc] initCount:count];
        [clone appendList:self];
        return((id)clone);
    }/*copy;*/
    

    -(id)copyFromZone:(void*)zone
    {
        return([self copy]);
    }/*copyFromZone:;*/


    -(void)printOn:(FILE*)file
    {
            CARD32          i;
            
        [super printOn:file];
        fprintf(file,"count=          %8lu\n",count);
        fprintf(file,"capacity=       %8lu\n",capacity);
        i=0;
        while(i<count){
            fprintf(file,"[%4lu]=         %p\n",i,(void*)(elements[i]));
            INC(i);
        }
    }/*printOn:;*/


    -(BOOLEAN)isEqual:(BoListNoRetain*)otherList
    {
            CARD32          i;
            
        if([otherList count]!=count){
            return(FALSE);
        }
        i=count;
        while(i>0){
            i--;
            if([otherList objectAt:i]!=elements[i]){
                return(FALSE);
            }
        }
        return(TRUE);
    }/*isEqual;*/
    
    
    -(CARD32)capacity
    {
        return(capacity);
    }/*capacity;*/


    -(id)capacity:(CARD32)newCapacity
    {
            id*         newElements;
            CARD32      i;
        
        if(newCapacity<BoListNoRetain_Minimum){
            newCapacity=BoListNoRetain_Minimum;
        }
        if(count>newCapacity){
            BcRAISE(BoListNoRetain_eCapacityTooLow,(void*)self,(void*)newCapacity);
        }else{
            newElements=(id*)BcMem_Allocate(sizeof(id)*newCapacity);
            i=0;
            while(i<count){
                newElements[i]=elements[i];
                INC(i);
            }
            BcMem_Deallocate((void**)&elements);
            elements=newElements;
            capacity=newCapacity;
        }
        return(self);
    }/*capacity:*/
    
    
    -(id)setAvailableCapacity:(CARD32)newCapacity
    {
        return([self capacity:newCapacity]);
    }/*setAvailableCapacity:;*/
    
    
    -(CARD32)count
    {
        return(count);
    }/*count;*/
    
    
    -(id)objectAt:(CARD32)idx
    {
        if(idx>=count){
            BcRAISE(BoListNoRetain_eBadIndex,(void*)self,(void*)idx);
        }
        return(elements[idx]);
    }/*objectAt:;*/
    
    
    -(id)lastObject
    {
        if(count>0){
            return(elements[count-1]);
        }else{
            return(NIL);
        }
    }/*lastObject;*/
    
    
    -(id)addObject:(id)newObject
    {
        if(newObject==NIL){
            BcRAISE(BoListNoRetain_eNilObject,(void*)self,NIL);
        }
        if(count==capacity){
            [self capacity:2*capacity];
        }
        elements[count]=newObject;
        INC(count);
        return(self);
    }/*addObject:;*/
    
    
    -(id)insertObject:(id)newObject at:(CARD32)idx
    {
            CARD32          i;
        
        if(newObject==NIL){
            BcRAISE(BoListNoRetain_eNilObject,(void*)self,NIL);
        }
        if(count==capacity){
            [self capacity:2*capacity];
        }
        i=count;
        while(i>idx){
            elements[i]=elements[i-1];
            DEC(i);
        }
        elements[i]=newObject;
        INC(count);
        return(self);
    }/*insertObject:at:;;*/
    

    -(id)removeObjectAt:(CARD32)idx
    {
            id          oldObject;
            
        if(idx>=count){
            BcRAISE(BoListNoRetain_eBadIndex,(void*)self,(void*)idx);
        }
        oldObject=elements[idx];
        while(idx<count){
            elements[idx]=elements[idx+1];
            INC(idx);
        }
        DEC(count);
        return(oldObject);
    }/*removeObjectAt:;*/
    
    
    -(id)removeLastObject
    {
        if(count>0){
            DEC(count);
            return(elements[count]);
        }else{
            return(NIL);
        }
    }/*removeLastObject;*/
    
    
    -(id)replaceObjectAt:(CARD32)idx with:(id)newObject
    {
            id          oldObject;
        
        if(newObject==NIL){
            BcRAISE(BoListNoRetain_eNilObject,(void*)self,NIL);
        }
        if(idx>=count){
            BcRAISE(BoListNoRetain_eBadIndex,(void*)self,(void*)idx);
        }
        oldObject=elements[idx];
        elements[idx]=newObject;
        return(oldObject);
    }/*replaceObjectAt:with:;*/
    
    
    -(id)appendList:(BoListNoRetain*)otherList
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
            INC(count);
            INC(i);
        }
        return(self);
    }/*appendList:;*/
    
    
    -(CARD32)indexOf:(id)oldObject
    {
            CARD32      i;
        i=0;
        while((i<count)&&(elements[i]!=oldObject)){
            INC(i);
        }
        if(i==count){
            return(BoListNoRetain_NotInList);
        }else{
            return(i);
        }
    }/*indexOf:;*/
    

    -(id)addObjectIfAbsent:(id)newObject
    {
        if([self indexOf:newObject]==BoListNoRetain_NotInList){
            return([self addObject:newObject]);
        }else{
            return(NIL);
        }
    }/*addObjectIfAbsent;*/
    
    
    -(id)removeObject:(id)oldObject
    {
            CARD32          idx;
            
        idx=[self indexOf:oldObject];
        if(idx==BoListNoRetain_NotInList){
            return(NIL);
        }else{
            return([self removeObjectAt:idx]);
        }
    }/*removeObject:;*/
    
    
    -(id)replaceObject:(id)oldObject with:(id)newObject
    {
            CARD32          idx;
            
        idx=[self indexOf:oldObject];
        if(idx==BoListNoRetain_NotInList){
            return(NIL);
        }else{
            return([self replaceObjectAt:idx with:newObject]);
        }
    }/*replaceObject:with:;*/
    
    
    -(id)empty
    {
        count=0;
        return(self);
    }/*empty;*/
    
    
    -(id)makeObjectsPerform:(SEL)aSelector
    {
            CARD32          i;
        
        i=0;
        while(i<count){
            [elements[i] perform:aSelector];
            INC(i);
        }
        return(self);
    }/*makeObjectsPerform:;*/
    
    
    -(id)makeObjectsPerform:(SEL)aSelector with:(id)anObject
    {
            CARD32          i;
        
        i=0;
        while(i<count){
            [elements[i] perform:aSelector with:anObject];
            INC(i);
        }
        return(self);
    }/*makeObjectsPerform:with:;*/


    -(id)makeObjectsPerform:(SEL)aSelector with:(id)anObject with:(id)another
    {
            CARD32          i;
        
        i=0;
        while(i<count){
            [elements[i] perform:aSelector with:anObject with:another];
            INC(i);
        }
        return(self);
    }/*makeObjectsPerform:with:with:;*/


    

    -(id)withEachMake:(id)receiver perform:(SEL)sel
    {
            CARD32                  i;
        
        i=0;
        while(i<count){
            [receiver perform:sel with:elements[i]];
            INC(i);
        }
        return(self);
    }/*withEachMake:perform:;*/
    
    
    -(id)withEachMake:(id)receiver perform:(SEL)sel andWith:(id)obj
    {
            CARD32                  i;
        
        i=0;
        while(i<count){
            [receiver perform:sel with:elements[i] with:obj];
            INC(i);
        }
        return(self);
    }/*withEachMake:perform:andWith:;*/

@end
/*** BoListNoRetain.m                 -- 2004-01-01 09:57:44 -- pascal   ***/
