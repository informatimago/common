/******************************************************************************
FILE:               BpArray.m
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This C++ class defines arrays of objects.
    Note: if a pre-condition is not fulfilled then the methods will BcRAISE
    an exception.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.8  95/11/24  17:30:06  pascal
    Renamed BcExcept objects.
    
    Revision 1.7  95/11/23  03:52:52  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.
    
    Revision 1.6  95/11/16  12:31:47  pascal
    Small corrections to compile on MSVC.
    
    Revision 1.5  95/10/22  03:18:26  pascal
    Setting revision name V1.
    
    Revision 1.4  95/10/22  02:57:51  pascal
    Added ' ' in log comment of revision 1.1.
    
    Revision 1.3  95/10/22  02:53:18  pascal
    Changed rcsid from Header to Id.-u
    
    Revision 1.2  95/10/22  02:35:50  pascal
    Modifications while adding BpDict.
    
    Revision 1.1  95/10/18  06:24:21  pascal
    Initial revision

    1992-07-21 <PJB> Creation.
    1992-10-22 <PJB> Renamed dumpOn to printOn.
    1993-01-18 <PJB> Refined, added exceptions.
    1993-03-16 <PJB> Translated from Objective-C to C++.
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
#include <names.h>
#include BpArray_hh
extern "C"{
#include BcMem_h
#include BcExcept_h
}
#include BcImplementation_h

static const char rcsid[]="$Id: BpArray.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";



// birth and death:

CONSTRUCTOR(BpArray)
{
    BpClass_PLUG(BpArray);
    psize=0;
    lsize=0;
    elements=(BpObject**)NIL;
}//BpArray:;


DESTRUCTOR(BpArray) // void
{
    if(elements!=NIL){
        CARD32      i;
        for(i=0;i<lsize;i++){
            if(elements[i]!=NIL){
                elements[i]->release();
            }
        }
        BcMem_Deallocate((void**)&elements);
    }
}//~BpArray;
    

// overrBpObject*e BpObject methods:

METHOD(BpArray,makeBrother,(void),BpObject*)
{
    return(NEW(BpArray));
}//makeBrother;
    

METHOD(BpArray,printOnLevel,(FILE* file,CARD32 level),void)
{
    CARD32          i;

    BpArray_SUPER::printOnLevel(file,level);
    PRINTONLEVEL(file,level,"%8lu",lsize,lsize);
    PRINTONLEVEL(file,level,"%8lu",psize,psize);
    i=0;
    while(i<lsize){
        PRINTONLEVEL_ELEMENT(file,level,"%p",elements,i,
                             (void*)(elements[i]));
        INC(i);
    }
}//printOnLevel;
    
    
// new methods:

METHOD(BpArray,initWithObjectsCount,(BpObject** objects,CARD32 count),void)
{
    CARD32      i;
            
    this->resize(count);
    for(i=0;i<count;i++){
        objects[i]->retain();
        if(elements[i]!=NIL){
            elements[i]->release();
        }
        elements[i]=objects[i];
    }
    selfChanged(BpArray_cInitializedWithObjects);
}//initWithObjectsCount;
    
    
METHOD(BpArray,size,(void),CARD32)
{
    return(lsize);
}//size;
    
        
METHOD(BpArray,resize,(CARD32 newSize),BpArray*)
{
    BpObject**      newElements;
    CARD32          i;
            
    if(newSize>psize){
        newElements=(BpObject**)BcMem_Allocate((CARD32)sizeof(BpObject*)*newSize);
        psize=newSize;
        i=0;
        while(i<lsize){
            newElements[i]=elements[i];
            INC(i);
        }
        while(i<psize){
            newElements[i]=(BpObject*)NIL;
            INC(i);
        }
        if(elements!=NIL){
            BcMem_Deallocate((void**)&elements);
        }
        elements=newElements;
        lsize=newSize;
    }else if(newSize>lsize){
        // lsize < newSize <= psize
        i=lsize;
        while(i<newSize){
            elements[i]=(BpObject*)NIL;
            INC(i);
        }
        lsize=newSize;
    }else{
        // newSize <= lsize
        for(i=newSize;i<lsize;i++){
            if(elements[i]!=NIL){
                elements[i]->release();
            }
        }
        lsize=newSize;
    }
    selfChanged(BpArray_cResized);
    return(this);
}//resize:;
            

METHOD(BpArray,objectAt,(CARD32 index),BpObject*)
{
    if(index>=lsize){
        BcRAISE(BpArray_eBadIndex,(void*)this,(void*)index);
    }
    return(elements[index]);
}//objectAt:;
    

METHOD(BpArray,replaceObjectAtWith,
       (CARD32 index,BpObject* newObject), BpObject*)
{
    BpObject*           old;
            
    if(index>=lsize){
        BcRAISE(BpArray_eBadIndex,(void*)this,(void*)index);
    }
    old=elements[index];
    elements[index]=newObject;
    if(old!=NIL){
        old->release();
    }
    if(newObject!=NIL){
        newObject->retain();
    }
    selfChanged(BpArray_cObjectReplaced);
    return(old);
}//replaceObjectAt:with:;


METHOD(BpArray,insertObjectAt,(BpObject* newObject,CARD32 index),BpArray*)
{
    CARD32              i;
            
    if(index>=lsize){
        BcRAISE(BpArray_eBadIndex,(void*)this,(void*)index);
    }
    i=lsize-1;
    while(i>index){
        elements[i]=elements[i-1];
        DEC(i);
    }
    elements[i]=newObject;
    if(newObject!=NIL){
        newObject->retain();
    }
    selfChanged(BpArray_cObjectInserted);
    return(this);
}//insertObject:at:;
    
        
METHOD(BpArray,removeObjectAt,(CARD32 index),BpObject*)
{
    CARD32              i;
    BpObject*           old;
            
    if(index>=lsize){
        BcRAISE(BpArray_eBadIndex,(void*)this,(void*)index);
    }
    old=elements[index];
    i=index;
    while(i<lsize-1){
        elements[i]=elements[i+1];
        INC(i);
    }
    elements[i]=(BpObject*)NIL;
    if(old!=NIL){
        old->release();
    }
    selfChanged(BpArray_cObjectRemoved);
    return(old);
}//removeObjectAt:;
    
    
METHOD(BpArray,indexOf,(BpObject* oldObject),CARD32)
{
    CARD32          i;
        
    i=0;
    while((i<lsize)AND(elements[i]!=oldObject)){
        INC(i);
    }
    if(i==lsize){
        return(MAX_CARD32);
    }else{
        return(i);
    }   
}//indexOf:;
    
            
METHOD(BpArray,makeObjectsPerform,(BpArray_ActionPr proc),BpArray*)
{
    CARD32                  i;
        
    i=0;
    while(i<lsize){
        proc(elements[i]);
        INC(i);
    }
    return(this);
}//makeOjectsPerform:;
    
    
METHOD(BpArray,makeObjectsPerformWith,(BpArray_ActionWithPr proc,BpObject* anObject),BpArray*)
{
    CARD32                  i;
        
    i=0;
    while(i<lsize){
        proc(elements[i],anObject);
        INC(i);
    }
    return(this);
}//makeOjectsPerform:with:;
    

METHOD(BpArray,withEachMakePerform,
       (BpObject* receiver,BpArray_ActionWithPr proc),BpArray*)
{
    CARD32                  i;
        
    i=0;
    while(i<lsize){
        proc(receiver,elements[i]);
        INC(i);
    }
    return(this);
}//withEachMake:perform:;
    

METHOD(BpArray,withEachMakePerformWithAndWith,
       (BpObject* receiver,BpArray_ActionWithAndWithPr proc,
        BpObject* obj),BpArray*)
{
    CARD32                  i;
        
    i=0;
    while(i<lsize){
        proc(receiver,elements[i],obj);
        INC(i);
    }
    return(this);
}//withEachMake:perform:andWith:;
        
//END BpArray.
