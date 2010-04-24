/******************************************************************************
FILE:               BoObject.m
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
    Copyright Pascal J. Bourguignon 1992 - 1993
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#include <BoObject.h>
#include <BoListNoRetain.h>

@interface DeletePool:Object
{
    BoObject**      pool;
    long            poolCapacity;
    long            poolCount;
}
    -(id)init;
    -(id)free;
    -(long)count;
    -(void)addObject:(BoObject*)obj;
    -(void)removeObject:(BoObject*)obj;
    -(void)deleteObjects;
@end /*DeletePool;*/


@implementation DeletePool
    
    -(id)init
    {
        [super init];
        poolCount=0;
        poolCapacity=256;
        pool=(BoObject**)BcMem_Allocate(sizeof(BoObject*)*poolCapacity);
        return(self);
    }/*init;*/
    
    
    -(id)free
    {
        [self deleteObjects];
        BcMem_Deallocate((void**)&pool);
        [super free];
        return(nil);
    }/*free;*/
    
    
    -(long)count
    {
        return(poolCount);
    }/*count;*/
    
    
    -(void)addObject:(BoObject*)obj
    {
        if(poolCount>=poolCapacity){
                BoObject**      newPool;
                long            i;
                
            poolCapacity*=2;
            newPool=(BoObject**)BcMem_Allocate((sizeof(BoObject*)
                                        *poolCapacity));
            for(i=0;i<poolCount;i++){
                newPool[i]=pool[i];
            }
            BcMem_Deallocate((void**)&pool);
            pool=newPool;
        }
        pool[poolCount++]=obj;
    }/*addObject:;*/
    
    
    -(void)removeObject:(BoObject*)obj
    {
            long            i;
        
        /* we are optimist: obj should be in the pool*/
        i=poolCount;
        while(i>0){
            i--;
            if(pool[i]==obj){
                /* ok remove it by moving upper obj down on it.*/
                poolCount--;
                while(i<poolCount){
                    pool[i]=pool[i+1];
                    i++;
                }
                return;
            }
        }
        /* obj was not in the pool. Too bad!*/
    }/*removeObject:;*/
    
    
    -(void)deleteObjects
    {
        while(poolCount>0){
            poolCount--; 
            [pool[poolCount] free];
        } 
    }/*deleteObjects;*/
    
    
@end /*DeletePool*/



    static DeletePool* deletePool; /* We count on static => set to 0.*/
    static DeletePool* secondPool; /* We count on static => set to 0.*/
    /* We don't initialize them ourselves since this may occur*/
    /* after the allocation of a new BoObject, where they are*/
    /* allocated properly.                      */



@implementation BoObject


#ifdef MPW
    +(id)alloc
    {
        return([self new]);
    }/*alloc;*/
#endif


    -(id)init
    {
#ifdef MPW
        [self initialize];
#else
        [super init];
#endif
        _useCount=0;
        if(deletePool==NIL){ 
         /* We cannot guarantee the order of initialization of */
         /* statics, therefore we must do it now:*/
            deletePool=[[DeletePool alloc]init];
            secondPool=[[DeletePool alloc]init];
        }
        [deletePool addObject:self];
        _dependants=NIL;
        return(self);
    }/*init;*/

    
    -(id)free   
    {
        if(_useCount>0){
            fprintf(stderr,"Trying to free a BoObject while its useCount>0! "
                    "(self=%p, class=%s, useCount=%lu)\n",
                    (void*)self,[[self class]name],_useCount);
            return(self);
        }
        [self changed:BoObject_cause_deleting];
        [deletePool removeObject:self];
        [secondPool removeObject:self];   /* SEE:*/
        [_dependants free];
        return([super free]);
    }/*free;*/
    
    
    -(void)printOn:(FILE*)file
    {
        fprintf(file,"------------------------------\n");
        fprintf(file,"class=          %s\n",[[self class] name]);
        fprintf(file,"address=        %p\n",(void*)self);
    }/*printOn:;*/
    
    
    -(void)retain
    {
        _useCount++;
        if(_useCount==1){
            [deletePool removeObject:self];
        }
    }/*retain;*/
    
    
    -(void)release
    {
        _useCount--;
        if(_useCount==0){
            [deletePool addObject:self];
        }else if(_useCount<0){
            _useCount=0;
        }
    }/*release;*/
    
    
    -(long)useCount
    {
        return(_useCount);
    }/*useCount;*/
    
    
    +(void)processReleasePool
    {
            DeletePool*     temp;
        while([deletePool count]>0){
            temp=deletePool;
            deletePool=secondPool;
            secondPool=temp;
            [secondPool deleteObjects];
        }
    }/*processReleasePool;*/
    
    
    
    -(void)dependantAdd:(id)aDependant
    {
        if(_dependants==NIL){
            _dependants=[[BoListNoRetain alloc]init];
        }
        [_dependants addObjectIfAbsent:aDependant];
    }/*dependantAdd:;*/
    
    
    -(void)dependantRemove:(id)aDependant
    {
        [_dependants removeObject:aDependant];
    }/*dependantRemove:;*/
    
    
    -(void)dependeeChanged:(BoObject*)aDependee cause:(long)cause
    {
        /* NOP.*/
    }/*dependeeChanged:cause:;*/
    

    -(void)changed:(long)cause
    {
        [_dependants makeObjectsPerform:@selector(dependeeChanged:cause:) 
                        with:self with:(id)cause];
    }/*changed:;        */
    
    
@end
/*** BoObject.m                       -- 2004-01-01 09:58:08 -- pascal   ***/
