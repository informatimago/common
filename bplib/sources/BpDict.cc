/******************************************************************************
FILE:               BpDict.hh
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This module implement the 'dictionary' concept.
    Dictionaries are dynamic (resize themselves by doubling when they
    reach a certain maximum), so that callers never have to think about 
    allocation.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.8  95/11/24  17:30:19  pascal
    Renamed BcExcept objects.
    
    Revision 1.7  95/11/23  03:53:28  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.
    
    Revision 1.6  95/11/16  12:31:57  pascal
    Small corrections to compile on MSVC.
    
    Revision 1.5  95/10/22  03:19:05  pascal
    Setting revision name V1.
    
    Revision 1.2  95/10/22  02:53:19  pascal
    Changed rcsid from Header to Id.-u
    
    Revision 1.1  95/10/22  02:36:15  pascal
    Initial revision
    
LEGAL
    Copyright Pascal J. Bourguignon 1995 - 2011

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
#include BpDict_hh                     

extern "C" {
#include BcExcept_h
}                  



    static const char rcsid[]="$Id: BpDict.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";

//////////////////////////////////////////////////////////////////////////////
// Definition of a private BpDict_Entry class ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define BpDict_Entry_SUPER BpObject
class BpDict_Entry:public BpDict_Entry_SUPER
{
public:
// birth and death:

    CONSTRUCTOR(BpDict_Entry)
    DESTRUCTOR(BpDict_Entry)

// override BpObject methods:

    METHOD(BpDict_Entry,makeBrother,(void),BpObject*)
    METHOD(BpDict_Entry,printOnLevel,(FILE* file,CARD32 level),void)

// BpDict_Entry methods:
    
    METHOD(BpDict_Entry,copy,(void),BpDict_Entry*)
    METHOD(BpDict_Entry,setKeyObject,(BpString* nKey,BpObject* nObject),void)
    METHOD(BpDict_Entry,setObject,(BpObject* nObject),void)
    METHOD(BpDict_Entry,key,(void), BpString*)
    METHOD(BpDict_Entry,object,(void),BpObject*)
    METHOD(BpDict_Entry,compare,(BpDict_Entry* otherEntry),SignT)
    METHOD(BpDict_Entry,compareKey,(BpString* otherKey),SignT)
    
protected:
    BpString*       myKey;
    BpObject*       myObject;
};//BpDict_Entry;






#include BcImplementation_h



//////////////////////////////////////////////////////////////////////////////
// Implementation of a private BpDict_Entry class ////////////////////////////
//////////////////////////////////////////////////////////////////////////////


// birth and death:

    CONSTRUCTOR(BpDict_Entry)
    {
        BpClass_PLUG(BpDict_Entry);
        myKey=(BpString*)NIL;
        myObject=(BpObject*)NIL;
    }//BpDict_Entry;
    
    
    DESTRUCTOR(BpDict_Entry)
    {
        if(myKey!=NIL){
            myKey->release();
        }
        if(myObject!=NIL){
            myObject->release();
        }
    }//~BpDict_Entry

// override BpObject methods:

    METHOD(BpDict_Entry,makeBrother,(void),BpObject*)
    {
        return(NEW(BpDict_Entry));
    }//makeBrother;
    

    METHOD(BpDict_Entry,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpDict_Entry_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%p",myKey,(void*)myKey);
        if(myKey!=NIL){
            myKey->printOnLevel(file,level+1);
        }
        PRINTONLEVEL(file,level,"%p",myObject,(void*)myObject);
        if(myObject!=NIL){
            myObject->printOnLevel(file,level+1);
        }
    }//printOnLevel;
    
    
// BpDict_Entry methods:
    
    METHOD(BpDict_Entry,copy,(void),BpDict_Entry*)
        /*
            NOTE:       We don't duplicate the myKey here since it is private
                        to another BpDict_Entry.
                        We assume BpDict will not do another setKeyObject
                        on the same entry.
        */
    {
            BpDict_Entry*   nEntry;
            
        nEntry=NEW(BpDict_Entry);
        if(myKey!=NIL){
            myKey->retain();
            nEntry->myKey=myKey;
        }
        if(myObject!=NIL){
            myObject->retain();
            nEntry->myObject=myObject;
        }
        return(nEntry);
    }//copy;
    
    
    METHOD(BpDict_Entry,setKeyObject,(BpString* nKey,BpObject* nObject),void)
    {
        if(myKey!=NIL){
            BcRAISE(BpDict_Internal00,nKey,nObject);
        }
        myKey=NEW(BpString);
        myKey->retain();
        myKey->copyFrom(nKey);
        if(myObject!=NIL){  
            // this could happen if setObject were called before setKeyObject.
            myObject->release();
        }
        myObject=nObject;
        myObject->retain();
    }//setKeyObject;
    
    
    METHOD(BpDict_Entry,setObject,(BpObject* nObject),void)
    {
        if(myObject!=NIL){
            myObject->release();
        }
        myObject=nObject;
        myObject->retain();
    }//setObject;
    
    
    METHOD(BpDict_Entry,key,(void),BpString*)
    {
            BpString*       nKey;
        nKey=NEW(BpString);
        nKey->copyFrom(myKey);
        return(nKey);
    }//key;
    
    
    METHOD(BpDict_Entry,object,(void),BpObject*)
    {
        return(myObject);
    }//object;
    
    
    METHOD(BpDict_Entry,compare,(BpDict_Entry* otherEntry),SignT)
    {
        return(myKey->compare(otherEntry->myKey));
    }//compare;
    
    
    METHOD(BpDict_Entry,compareKey,(BpString* otherKey),SignT)
    {
        return(myKey->compare(otherKey));
    }//compareKey;
    
    

//////////////////////////////////////////////////////////////////////////////
// Implementation of  BpDict class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


// birth and death:

    CONSTRUCTOR(BpDict)
    {
            BpArray*        entries;

        BpClass_PLUG(BpDict);
        entries=NEW(BpArray);
        entries->retain();
        opaque=(void*)entries;
    }//BpDict;
    
    
    DESTRUCTOR(BpDict)
    {
            BpArray*        entries;
        
        entries=(BpArray*)opaque;
        entries->release();
    }//BpDict;
    
    
    

// override BpObject methods:

    METHOD(BpDict,makeBrother,(void),BpObject*)
    {
        return(NEW(BpDict));
    }//makeBrother;
    

    METHOD(BpDict,printOnLevel,(FILE* file,CARD32 level),void)
    {
            BpArray*        entries;
        
        entries=(BpArray*)opaque;
        BpDict_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%p", entries,(void*)entries);
        if(entries!=NIL){
            entries->printOnLevel(file,level+1);
        }
    }//printOnLevel;
    
    

// BpDict methods:
    
    METHOD(BpDict, initWithObjectsForKeys,
                        (BpArray* objArray,BpArray* keyArray),void)
    {
        CARD32          i,cnt;

        this->removeAllObjects();
        cnt=objArray->size();
        if(cnt!=keyArray->size()){
            BcRAISE(BpDict_keyAndObjNumMismatch,keyArray,objArray);
        }
        for(i=0;i<cnt;i++){
            this->setObjectForKey(objArray->objectAt(i),
                            (BpString*)(keyArray->objectAt(i)));
        }
        selfChanged(BpDict_cInitialized);
    }//initWithObjectsForKeys;
    
    
    METHOD(BpDict,initWithObjectsForKeysCount,
                        (BpObject** objects,BpString** keys,CARD32 cnt),void)
    {
        CARD32          i;
            
        this->removeAllObjects();
        for(i=0;i<cnt;i++){
            this->setObjectForKey(objects[i],keys[i]);
        }
        selfChanged(BpDict_cInitialized);
    }//initWithObjectsForKeysCount;
    
    
    METHOD(BpDict,initWithDictionary,(BpDict* otherDictionary),void)
    {
        this->removeAllObjects();
        addEntriesFromDictionary(otherDictionary);
        selfChanged(BpDict_cInitialized);
    }//initWithDictionary;
    

    METHOD(BpDict,addEntriesFromDictionary,(BpDict* otherDictionary),void)
    {
            BpArray*            keys;
            INT32               i,cnt;
                
        keys=otherDictionary->allKeys();
        cnt=keys->size();
        for(i=0;i<cnt;i++){
                BpString*   theKey;
            theKey=(BpString*)(keys->objectAt(i));
            setObjectForKey(otherDictionary->objectForKey(theKey),theKey);
        }
        // We don't do any other thing to the keys array. It will be
        // automatically deallocated the next time we call
        // BpObject_ProcessDeletePool.
    }//addEntriesFromDictionary;
    
    
    METHOD(BpDict,count,(void),CARD32)
    {
            BpArray*        entries;
        
        entries=(BpArray*)opaque;
        return(entries->size());
    }//count;
    
    
    PROCEDURE(BpDict_Search,(BpArray* entries,BpString* key,
                        CARD32* rNum,SignT* rOrder),BOOLEAN)
        /*
            PRE:        entry is the element to be searched in the table.
            POST:       0<=num<entries->size()=max
                        +-------------------+----------+-------+----------+
                        | Case              |  Search  |  num  |  order   |
                        +-------------------+----------+-------+----------+
                        | x < a[0]          |   FALSE  |   0   |  less    |
                        | a[i] < x < a[i+1] |   FALSE  |   i   |  greater |
                        | x = a[i]          |   TRUE   |   i   |  equal   |
                        | a[max-1] < x      |   FALSE  |  max  |  greater |
                        +-------------------+----------+-------+----------+
        */
    {
            CARD32          curmin;
            CARD32          curmax;
            CARD32          num;
            SignT           order;
    
        curmin=0;
        curmax=entries->size();
        if(curmax==0){
            *rOrder=-1;
            *rNum=0;
            return(FALSE);
        }
        num=(curmin+curmax)/2;
        order=((BpDict_Entry*)(entries->objectAt(num)))->compareKey(key);
        while((order!=0)&&(curmin!=num)){
            if(order>0){
                // the order returned by compareKey is inverted.
                curmax=num;
            }else{
                curmin=num;
            }
            num=(curmin+curmax)/2;
            order=((BpDict_Entry*)(entries->objectAt(num)))->compareKey(key);
        }
        if((0<num)&&(order>0)){
            order=-1;
            num--;
        }
        *rOrder=-order;
        *rNum=num;
        return((BOOLEAN)(order==0));
    }//BpDict_Search;
    

    METHOD(BpDict,setObjectForKey,(BpObject* obj,BpString* key),void)
    {
            BpArray*        entries;
            CARD32          num;
            SignT           order;
            BpDict_Entry*   nEntry;
            
        entries=(BpArray*)opaque;
        BpDict_Search(entries,key,&num,&order);
        if(order==0){
                    // | x = a[i]          |   TRUE   |   i   |  equal   |
            ((BpDict_Entry*)(entries->objectAt(num)))->setObject(obj);
        }else{
            if((order>0)&&((num!=entries->size()))){
                num++;
            }
            nEntry=NEW(BpDict_Entry);
            nEntry->setKeyObject(key,obj);
            entries->resize(entries->size()+1);
            entries->insertObjectAt(nEntry,num);    
        }
        selfChanged(BpDict_cAssociationSet);
    }//setObjectForKey;
    
    
    METHOD(BpDict,objectForKey,(BpString* aKey),BpObject*)
    {
            BpArray*        entries;
            CARD32          num;
            SignT           order;
            
        entries=(BpArray*)opaque;
        BpDict_Search(entries,aKey,&num,&order);
        if(order==0){
            return(((BpDict_Entry*)(entries->objectAt(num)))->object());
        }else{
            return((BpObject*)NIL);
        }
    }//objectForKey;
    
    
    METHOD(BpDict,removeObjectForKey,(BpString* key),void)
    {
            BpArray*        entries;
            CARD32          num;
            SignT           order;
            
        entries=(BpArray*)opaque;
        BpDict_Search(entries,key,&num,&order);
        if(order==0){
            entries->removeObjectAt(num);
            entries->resize(entries->size()-1);
        }
        selfChanged(BpDict_cAssociationRemoved);
    }//removeObjectForKey;
    
    
    METHOD(BpDict,removeAllObjects,(void),void)
    {
            BpArray*        entries;
        
        entries=(BpArray*)opaque;
        entries->resize(0);
        selfChanged(BpDict_cAssociationsFreed);
    }//removeAllObjects;
    
    
    METHOD(BpDict,removeObjectsForKeys,(BpArray* keyArray),void)
    {
            CARD32          i;
            CARD32          max;

        max=keyArray->size();
        for(i=0;i<max;i++){
            this->removeObjectForKey((BpString*)(keyArray->objectAt(i)));
        }
    }//removeObjectsForKeys;
    
    
    METHOD(BpDict,allKeys,(void),BpArray*)
    {
            BpArray*        entries;
            BpArray*        keys;
            CARD32          i;
            CARD32          max;
            
        entries=(BpArray*)opaque;
        keys=NEW(BpArray);
        max=entries->size();
        keys->resize(max);
        for(i=0;i<max;i++){
            keys->replaceObjectAtWith(i,
                        ((BpDict_Entry*)(entries->objectAt(i)))->key());
        }
        return(keys);
    }//allKeys;
    
    
    METHOD(BpDict,allValues,(void),BpArray*)
    {
            BpArray*        entries;
            BpArray*        objects;
            CARD32          i;
            CARD32          max;
            
        entries=(BpArray*)opaque;
        objects=NEW(BpArray);
        max=entries->size();
        objects->resize(max);
        for(i=0;i<max;i++){
            objects->replaceObjectAtWith(i,
                        ((BpDict_Entry*)(entries->objectAt(i)))->object());
        }
        return(objects);
    }//allValues;
    
    
    METHOD(BpDict,allKeysForObject,(BpObject* anObject),BpArray*)
    {
            BpArray*        entries;
            BpArray*        keys;
            CARD32          i;
            CARD32          max;
            CARD32          j;
            
        entries=(BpArray*)opaque;
        keys=NEW(BpArray);
        j=0;
        max=entries->size();
        for(i=0;i<max;i++){
                BpDict_Entry*   entry;
            entry=(BpDict_Entry*)(entries->objectAt(i));
            if(entry->object()==anObject){
                keys->resize(j+1);
                keys->replaceObjectAtWith(j,entry->key());
                j++;
            }
        }
        return(keys);
    }//allKeysForObject;
    
    
    

/*** BpDict.cc                        -- 2003-11-30 07:37:23 -- pascal   ***/
