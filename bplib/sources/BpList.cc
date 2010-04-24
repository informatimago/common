/******************************************************************************
FILE:               BpList.m
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    A BpList is a collection of objects. The class provBpObject*es an interface 
    that permits easy manipulation of the collection as a fixed or 
    variable-sized list, a set, or an ordered collection. BpLists are 
    implemented as arrays to allow fast random access using an index. 
    Indices start at 0.
    See the NeXT step List Class documentation.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.8  96/12/06  00:35:40  pascal
    RAISE was renamed BcRAISE.
    
    Revision 1.7  95/11/23  03:53:30  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.
    
    Revision 1.6  95/11/16  12:31:59  pascal
    Small corrections to compile on MSVC.
    
    Revision 1.5  95/10/22  03:19:08  pascal
    Setting revision name V1.
    
    Revision 1.4  95/10/22  02:58:20  pascal
    Added ' ' in log comment of revision 1.1.
    
    Revision 1.3  95/10/22  02:53:19  pascal
    Changed rcsid from Header to Id.-u
    
    Revision 1.2  95/10/22  02:39:08  pascal
    Modifications while adding BpDict.
    
    Revision 1.1  95/10/18  06:24:52  pascal
    Initial revision

    1992-07-21 <PJB> Creation (BpArray).
    1992-10-25 <PJB> Upgraded to the same interface as NeXTstep objc/List.h.
    1993-01-12 <PJB> Added exception RAISING (thus drifting from the NeXT List
                        class implementation).
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1994-12-30 <PJB> Added sort.
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
extern "C"{
#include <stdlib.h> // import qsort.
}
#include <names.h>
#include BpList_hh
#include BcImplementation_h

    static const char rcsid[]="$Id: BpList.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";



// birth and death:

    CONSTRUCTOR(BpList)
    {
        BpClass_PLUG(BpList);
        lcount=0;
        lcapacity=BpList_Minimum;
        elements=(BpObject**)BcMem_Allocate(sizeof(BpObject*)*lcapacity);
    }//BpList;


    DESTRUCTOR(BpList)
    {
        this->freeObjects();
        BcMem_Deallocate((void**)&elements);
    }//~BpList;
    
// override BpObject methods:

    METHOD(BpList,makeBrother,(void),BpObject*)
    {
        return(NEW(BpList));
    }//makeBrother;
    

    METHOD(BpList,printOnLevel,(FILE* file,CARD32 level),void)
    {
            CARD32          i;

        BpList_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%8lu",lcount,lcount);
        PRINTONLEVEL(file,level,"%8lu",lcapacity,lcapacity);
        i=0;
        while(i<lcount){
            PRINTONLEVEL_ELEMENT(file,level,"%p",elements,i,
                                            (void*)(elements[i]));
            INC(i);
        }
    }//printOnLevel;
    
    

#if 0
    -(BpObject*)copy
    {
            BpList*         clone;
            CARD32          i;
            
        clone=(BpList*)[[BpList alloc] initCount:lcount];
        i=0;
        while(i<lcount){
            [clone appendList:(BpList*)(elements[i])];
            INC(i);
        }
        return((BpObject*)clone);
    }//copy;
#endif


// new methods:


    METHOD(BpList,freeObjects,(void),BpList*)
    {
            CARD32          i;
        for(i=0;i<lcount;i++){
            elements[i]->release();
        }
        if(lcount!=0){
            lcount=0;
            selfChanged(BpList_cObjectsFreed);
        }
        return(this);
    }//freeObjects;


    METHOD(BpList,isEqual,(BpList* otherList),BOOLEAN)
    {
            CARD32          i;
            
        if(otherList->count()!=lcount){
            return(FALSE);
        }
        i=0;
        while((i<lcount)&&(otherList->objectAt(i)==elements[i])){
            INC(i);
        }
        return((BOOLEAN)(i==lcount));
    }//isEqual;
    
    
    METHOD(BpList,capacity,(void),CARD32)
    {
        return(lcapacity);
    }//capacity;


    METHOD(BpList,capacitySet,(CARD32 newCapacity),BpList*)
    {
            BpObject**          newElements;
            CARD32      i;
        
        if(newCapacity<BpList_Minimum){
            newCapacity=BpList_Minimum;
        }
        if(lcount>newCapacity){
            BcRAISE(BpList_eCapacityTooLow,(void*)this,(void*)newCapacity);
        }else{
            newElements=(BpObject**)BcMem_Allocate(sizeof(BpObject*)*newCapacity);
            i=0;
            while(i<lcount){
                newElements[i]=elements[i];
                INC(i);
            }
            BcMem_Deallocate((void**)&elements);
            elements=newElements;
            lcapacity=newCapacity;
        }
        return(this);
    }//capacity:
    
    
    METHOD(BpList,count,(void),CARD32)
    {
        return(lcount);
    }//count;
    
    
    METHOD(BpList,objectAt,(CARD32 index),BpObject*)
    {
        if(index>=lcount){
            BcRAISE(BpList_eBadIndex,(void*)this,(void*)index);
        }
        return(elements[index]);
    }//objectAt:;
    
    
    METHOD(BpList,lastObject,(void), BpObject*)
    {
        if(lcount>0){
            return(elements[lcount-1]);
        }else{
            return((BpObject*)NIL);
        }          
    }//lastObject;
    
    
    METHOD(BpList,addObject,(BpObject* newObject),BpList*)
    {
        if(newObject==NIL){
            BcRAISE(BpList_eNilObject,(void*)this,NIL);
        }
        if(lcount==lcapacity){
            this->capacitySet(2*lcapacity);
        }
        elements[lcount]=newObject;
        newObject->retain();
        INC(lcount);
        selfChanged(BpList_cObjectAdded);
        return(this);
    }//addObject:;
    
    
    METHOD(BpList,insertObjectAt,(BpObject* newObject,CARD32 index),BpList*)
    {
            CARD32          i;
        
        if(newObject==NIL){
            BcRAISE(BpList_eNilObject,(void*)this,NIL);
        }
        if(lcount==lcapacity){
            this->capacitySet(2*lcapacity);
        }
        i=lcount;
        while(i>index){
            elements[i]=elements[i-1];
            DEC(i);
        }
        elements[i]=newObject;
        newObject->retain();
        INC(lcount);
        selfChanged(BpList_cObjectInserted);
        return(this);
    }//insertObject:at:;;
    

    METHOD(BpList,removeObjectAt,(CARD32 index),BpObject*)
    {
            BpObject*           oldObject;
            
        if(index>=lcount){
            BcRAISE(BpList_eBadIndex,(void*)this,(void*)index);
        }
        oldObject=elements[index];
        while(index<lcount){
            elements[index]=elements[index+1];
            INC(index);
        }
        DEC(lcount);
        oldObject->release();
        selfChanged(BpList_cObjectRemoved);
        return(oldObject);
    }//removeObjectAt:;
    
    
    METHOD(BpList,removeLastObject,(void),BpObject*)
    {
        if(lcount>0){
                BpObject*   removedObject;
            DEC(lcount);
            removedObject=elements[lcount];
            removedObject->release();
            selfChanged(BpList_cObjectRemoved);
            return(removedObject);
        }else{
            return((BpObject*)NIL);
        }
    }//removeLastObject;
    
    
    METHOD(BpList,replaceObjectAtWith,(CARD32 index,BpObject* nObj),BpObject*)
    {
            BpObject*           oldObject;
        
        if(nObj==NIL){
            BcRAISE(BpList_eNilObject,(void*)this,NIL);
        }
        if(index>=lcount){
            BcRAISE(BpList_eBadIndex,(void*)this,(void*)index);
        }
        oldObject=elements[index];
        elements[index]=nObj;
        nObj->retain();
        oldObject->release();
        selfChanged(BpList_cObjectReplaced);
        return(oldObject);
    }//replaceObjectAt:with:;
    
    
    METHOD(BpList,appendList,(BpList* otherList),BpList*)
    {
            CARD32      newCount;
            CARD32      i;
            
        newCount=lcount+otherList->count();
        if(newCount>lcapacity){
            this->capacitySet(newCount);
        }
        i=0;
        while(lcount<newCount){
            elements[lcount]=otherList->objectAt(i);
            elements[lcount]->retain();
            INC(lcount);
            INC(i);
        }
        selfChanged(BpList_cListAppended);
        return(this);
    }//appendList:;
    
    
    METHOD(BpList,indexOf,(BpObject* oldObject),CARD32)
    {
            CARD32      i;
        i=0;
        while((i<lcount)&&(elements[i]!=oldObject)){
            INC(i);
        }
        if(i==lcount){
            return(BpList_NotInList);
        }else{
            return(i);
        }
    }//indexOf:;
    

    METHOD(BpList,addObjectIfAbsent,(BpObject* newObject),BpList*)
    {
        if(this->indexOf(newObject)==BpList_NotInList){
            addObject(newObject);
            selfChanged(BpList_cObjectAdded);
            return(this);
        }else{
            return((BpList*)NIL);
        }
    }//addObjectIfAbsent;
    
    
    METHOD(BpList,removeObject,(BpObject* oldObject),BpObject*)
    {
            CARD32          index;
            
        index=this->indexOf(oldObject);
        if(index==BpList_NotInList){
            return((BpObject*)NIL);
        }else{
            BpObject* removedObject=removeObjectAt(index);
            selfChanged(BpList_cObjectRemoved);
            return(removedObject);
        }
    }//removeObject:;
    
    
    METHOD(BpList,replaceObjectWith,(BpObject* oObj,BpObject* nObj),BpObject*)
    {
            CARD32          index;
            
        index=this->indexOf(oObj);
        if(index==BpList_NotInList){
            return((BpObject*)NIL);
        }else{
            replaceObjectAtWith(index,nObj);
            selfChanged(BpList_cObjectReplaced);
            return(oObj);
        }
    }//replaceObject:with:;
    
    
    METHOD(BpList,empty,(void),BpList*)
    {
        this->freeObjects();
        return(this);
    }//empty;
    
    
    METHOD(BpList,makeObjectsPerform,(BpList_ActionPr proc),BpList*)
    {
            CARD32          i;
        
        i=0;
        while(i<lcount){
            proc(elements[i]);
            INC(i);
        }
        return(this);
    }//makeObjectsPerform:;
    
    
    METHOD(BpList,makeObjectsPerformWith,
            (BpList_ActionWithPr proc,BpObject* anObject),BpList*)
    {
            CARD32          i;
        
        i=0;
        while(i<lcount){
            proc(elements[i],anObject);
            INC(i);
        }
        return(this);
    }//makeObjectsPerform:with:;
    

    METHOD(BpList,withEachMakePerform,
            (BpObject* receiver,BpList_ActionWithPr proc),BpList*)
    {
            CARD32                  i;
        
        i=0;
        while(i<lcount){
            proc(receiver,elements[i]);
            INC(i);
        }
        return(this);
    }//withEachMake:perform:;
    
    
    METHOD(BpList,withEachMakePerformWithAndWith,
            (BpObject* receiver,BpList_ActionWithAndWithPr proc,
             BpObject* obj),BpList*)
    {
            CARD32                  i;
        
        i=0;
        while(i<lcount){
            proc(receiver,elements[i],obj);
            INC(i);
        }
        return(this);
    }//withEachMake:perform:andWith:;


    METHOD(BpList,sort,(BpList_ComparePr compare),BpList*)
    {
        qsort(elements,lcount,sizeof(BpObject*),
                    (int(*)(const void*,const void*))compare);
        selfChanged(BpList_cSorted);
        return(this);
    }//sort;
    
//END BpList.
