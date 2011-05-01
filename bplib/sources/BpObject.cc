/******************************************************************************
FILE:               BpObject.cc
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This is the root class for all C++ objects.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.16  96/10/29  00:44:21  pascal
    Corrected a :: to , in a macro call.
    
    Revision 1.15  96/07/25  06:18:04  pascal
    Made ProcessReleasePool a static method instead of a procedure.
    
    Revision 1.14  95/11/30  10:31:46  pascal
    Fix apres fusion avec les objets developpes par ERS
    
    Revision 1.13  95/11/24  17:30:22  pascal
    Renamed BcExcept objects.
    
    Revision 1.12  95/11/24  16:13:24  pascal
    Added retain/release for isa.
    
    Revision 1.11  95/11/24  14:24:06  pascal
    Corrected constructor; added friend proc BpClass_CreateMetaClasses in
    BpClass.
    
    Revision 1.10  95/11/23  05:51:51  pascal
    Added BpObject::makeBrother.
    
    Revision 1.9  95/11/23  03:53:32  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.
    
    Revision 1.8  95/11/16  12:32:00  pascal
    Small corrections to compile on MSVC.
    
    Revision 1.7  95/11/15  10:54:07  pascal
    Added some more debug tracing.
    
    Revision 1.6  95/11/04  03:36:30  pascal
    removed in excess rcsid.
    
    Revision 1.5  95/10/22  03:19:11  pascal
    Setting revision name V1.
    
    Revision 1.4  95/10/22  02:58:22  pascal
    Added ' ' in log comment of revision 1.1.
    
    Revision 1.3  95/10/22  02:53:20  pascal
    Changed rcsid from Header to Id.-u
    
    Revision 1.2  95/10/22  02:39:25  pascal
    Modifications while adding BpDict.
    
    Revision 1.1  95/10/18  06:25:45  pascal
    Initial revision

    1992-05-25 <PJB> Creation.
    1993-03-16 <PJB> Updated.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2011

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
extern "C"{
#include <string.h>
}
#include <names.h>
#include BpObject_hh
extern "C"{
#include BcExcept_h
#include BcMem_h
}
#include BpList_hh
#include BpClass_hh

//define DEBUG_POOL

static const char rcsid[]="$Id: BpObject.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";

class BpObject;

class DeletePool
{
public:
    CONSTRUCTOR(DeletePool)
    DESTRUCTOR(DeletePool)
    METHOD(DeletePool,count,(),CARD32)
    METHOD(DeletePool,addObject,(BpObject* obj),void)
    METHOD(DeletePool,removeObject,(BpObject* obj),void)
    METHOD(DeletePool,deleteObjects,(void),void)
    protected:
    BpObject**      pool;
    CARD32          poolCapacity;
    CARD32          poolCount;
};//DeletePool;
        

#include BcImplementation_h


CONSTRUCTOR(DeletePool)
{
    poolCount=0;
    poolCapacity=256;
    pool=(BpObject**)BcMem_Allocate((CARD32)sizeof(BpObject*)*poolCapacity);
}//DeletePool;
    
    
DESTRUCTOR(DeletePool)
{
    this->deleteObjects();
    BcMem_Deallocate((void**)&pool);
}//~DeletePool;
    
    
METHOD(DeletePool,count,(),CARD32)
{
    return(poolCount);
}//count;
    
    
METHOD(DeletePool,addObject,(BpObject* obj),void)
{
#ifdef DEBUG_POOL
    CARD32      i;
    for(i=0;i<poolCount;i++){
        if(pool[i]==obj){
            BcRAISE(BpObject_eDeleteInternal,obj,0);
        }
    }
    fprintf(stderr,"%p %s [%d] added to delete pool.\n", 
            obj,obj->className(),obj->retainCount());
#endif
    if(poolCount>=poolCapacity){
        BpObject**      newPool;
        CARD32          i;
                
        poolCapacity*=2;
        newPool=(BpObject**)BcMem_Allocate((CARD32)sizeof(BpObject*)*poolCapacity);
        for(i=0;i<poolCount;i++){
            newPool[i]=pool[i];
        }
        BcMem_Deallocate((void**)&pool);
        pool=newPool;
    }
    pool[poolCount++]=obj;
}//addObject;
    
    
METHOD(DeletePool,removeObject,(BpObject* obj),void)
{
    CARD32          i;
        
    // we are optimist: obj should be in the pool
    i=poolCount;
    while(i>0){
        i--;
        if(pool[i]==obj){
#ifdef DEBUG_POOL
            fprintf(stderr,"%p %s [%d] removed from delete pool %d/%d = %5.3f %%.\n",
                    obj,obj->className(),obj->retainCount(),
                    poolCount-i,poolCount,(float)(poolCount-i)/(float)poolCount);
#endif
            // ok remove it by moving upper obj down on it.
            poolCount--;
            while(i<poolCount){
                pool[i]=pool[i+1];
                i++;
            }
            return;
        }
    }
    BcRAISE(BpObject_eDeleteInternal,obj,(void*)1);
}//removeObject;
    
    
METHOD(DeletePool,deleteObjects,(void),void)
{
    CARD32          i;
            
    for(i=0;i<poolCount;i++){
#ifdef DEBUG_POOL
        fprintf(stderr,"%p %s [%d] deleted for good.\n",
                pool[i],pool[i]->className(),pool[i]->retainCount());
#endif
        DELETE(pool[i]);
    }
    poolCount=0;
}//deleteObjects;



static DeletePool*      deletePool=NEW(DeletePool);
static DeletePool*      secondPool=NEW(DeletePool);
// secondPool is used while freeing objects in deletePool.


// birth and death:

CONSTRUCTOR(BpObject)
{
    isa=NIL;
    fDependants=NIL;
    fRetainCount=0;
#ifdef DEBUG_POOL
    fprintf(stderr,"%p %s [%d] construction.\n",(void*)this,this->className(),fRetainCount);
#endif
    deletePool->addObject(this);
    {
        static BpClass* BpObjectClass=NIL;
        if(BpObjectClass==NIL){
            BpObjectClass=(BpClass*)1;
            BpObjectClass=BpClass::createMetaClasses();
            BpObjectClass->nameSet("BpObject");
            BpObjectClass->factorySet(NEW(BpObject));
        }
        // isa is NIL. BpObjectClass is not NIL. BpObjectClass may be 1.
        isa=BpObjectClass;
        if(isa!=(BpClass*)1){
            isa->retain();
        }
    }
}//BpObject;


DESTRUCTOR(BpObject)
{
    if(isa!=NIL){
        isa->release();
    }
    if(fDependants!=NIL){
        fDependants->release();
    }
#ifdef DEBUG_POOL
    fprintf(stderr,"%p %s [%d] destruction.\n",(void*)this,this->className(),fRetainCount);
#endif
    if(fRetainCount!=0){
        BcRAISE(BpObject_eDeleteRetained,(void*)this,(void*)fRetainCount);
    }
}//~BpObject;


METHOD(BpObject,retain,(void),BpObject*)
{
    if(fRetainCount==0){
        deletePool->removeObject(this);
    }
    fRetainCount++;
#ifdef DEBUG_POOL
    fprintf(stderr,"%p %s retain -> %d\n",(void*)this,this->className(),fRetainCount);
#endif  
    return(this);
}//retain;
    

METHOD(BpObject,release,(void),BpObject*)
{
    fRetainCount--;
    if(fRetainCount==0){
        deletePool->addObject(this);
    }
#ifdef DEBUG_POOL
    fprintf(stderr,"%p %s release -> %d\n",(void*)this,this->className(),fRetainCount);
#endif              
    return(this);
}//release;
    
    
METHOD(BpObject,retainCount,(void),INT32)
{
    return(fRetainCount);
}//retainCount;
    
    
METHOD(BpObject,processDeletePool,(void),void)
{
    CARD32          c;
    DeletePool*     swap;
        
    c=deletePool->count();
    while(c>0){
        swap=deletePool;
        deletePool=secondPool;
        secondPool=swap;
        secondPool->deleteObjects();
        c=deletePool->count();
    }
}//processDeletePool;
    
    
// utility methods:

METHOD(BpObject,makeBrother,(void),BpObject*)
{
    return(NEW(BpObject));
}//makeBrother;


METHOD(BpObject,className,(void),const char*)
{
    return(isa->name());
}//className;


METHOD(BpObject,runtimeClass,(void),BpClass*)
{
    return(isa);
}//runtimeClass;
    
    
METHOD(BpObject,superClass,(void),BpClass*)
{
    return(isa->superClass());
}//superClass;
    
    
METHOD(BpObject,isKindOf,(const BpClass* aClass),BOOLEAN)
{
    if(aClass==isa){
        return(TRUE);
    }else{
        BpClass* curClass=isa;
        BpClass* aSuperClass=curClass->superClass();
        while(aSuperClass!=curClass){
            if(aClass==curClass){
                return(TRUE);
            }
            curClass=aSuperClass;
            aSuperClass=curClass->superClass();
        }
        return((BOOLEAN)(aClass==curClass));
    }
}//isKindOf;
    
    
METHOD(BpObject,isKindOfClassNamed,(const char* aClassName),BOOLEAN)
{
    if(strcmp(aClassName,isa->name())==0){
        return(TRUE);
    }else{
        BpClass* curClass=isa;
        BpClass* aSuperClass=curClass->superClass();
        while(aSuperClass!=curClass){
            if(strcmp(aClassName,curClass->name())==0){
                return(TRUE);
            }
            curClass=aSuperClass;
            aSuperClass=curClass->superClass();
        }
        return((BOOLEAN)(strcmp(aClassName,curClass->name())==0));
    }
}//isKindOfClassNamed;
    
    
METHOD(BpObject,isMemberOf,(const BpClass* aClass),BOOLEAN)
{
    return((BOOLEAN)(isa==aClass));
}//isMemberOf;
    
    
METHOD(BpObject,isMemberOfClassNamed,(const char* aClassName),BOOLEAN)
{
    return(strcmp(aClassName,isa->name())==0);
}//isMemberOfClassNamed;


METHOD(BpObject,dependantCount,(void),CARD32)
{
    if(fDependants==NIL){
        return(0);
    }else{
        return(fDependants->count());
    }
}//dependantCount;
    
    
METHOD(BpObject,dependantAt,(CARD32 index),BpObject*)
{
    if(fDependants==NIL){
        return(NIL);
    }else{
        return(fDependants->objectAt(index));
    }
}//dependantAt;
    
    
METHOD(BpObject,dependantAdd,(BpObject* nDependant),void)
{
    if(fDependants==NIL){
        fDependants=NEW(BpList);
        fDependants->retain();
    }
    fDependants->addObject(nDependant);
}//dependantAdd;
    
    
METHOD(BpObject,dependantRemove,(BpObject* nDependant),void)
{
    if(fDependants!=NIL){
        fDependants->removeObject(nDependant);
        if(fDependants->count()==0){
            fDependants->release();
            fDependants=NIL;
        }
    }
}//dependantRemove;
    
    
METHOD(BpObject,dependantRemoveAt,(CARD32 index),BpObject*)
{
    if(fDependants!=NIL){
        BpObject*       oldObject;
        oldObject=fDependants->removeObjectAt(index);
        if(fDependants->count()==0){
            fDependants->release();
            fDependants=NIL;
        }
        return(oldObject);
    }else{
        return(NIL);
    }
}//dependantRemoveAt;
    
    
METHOD(BpObject,selfChanged,(INT32 cause),void)
{
    CARD32      i;
    CARD32      c;
            
    c=dependantCount();
    for(i=0;i<c;i++){
        dependantAt(i)->dependeeChanged(this,cause);
    }
}//selfChanged;


METHOD(BpObject,dependeeChanged,(BpObject* dependee,INT32 cause),void)
{
    //NOP.
}//dependeeChanged;


METHOD(BpObject,printOnLevel,(FILE* file,CARD32 level),void)
{
    PRINTONLEVEL(file,level,"%s",class,this->className());
    PRINTONLEVEL(file,level,"%p",address,(void*)this);
}//printOnLevel;


METHOD(BpObject,printOn,(FILE* file),void)
{
    printOnLevel(file,0);
}//print;
    
    
//END BpObject.

/*** BpObject.cc                      -- 2003-11-20 03:19:30 -- pascal   ***/
