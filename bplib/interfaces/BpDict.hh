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
    
    Revision 1.6  95/11/23  03:48:39  pascal
    Added BpClass and runtime class support in BpObject.
    Updated subclasses.
    
    Added dependant/dependee in BpObject.
    
    Revision 1.5  95/10/22  03:19:48  pascal
    Setting revision name V1.
    
    Revision 1.1  95/10/22  03:04:35  pascal
    Initial revision
    
LEGAL
    Copyright Pascal J. Bourguignon 1995 - 2002

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
#ifndef __BpDict__
#define __BpDict__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh
#include BpClass_hh
#include BpArray_hh
#include BpString_hh


#define BpDict_keyAndObjNumMismatch (10070) // BpArray* keys,BpArray* objs
#define BpDict_Internal00           (10071) // BpString* key,BpObject* obj


#define BpDict_SUPER BpObject
class BpDict:public BpDict_SUPER
{
public:

// birth and death:
    CONSTRUCTOR(BpDict)
    DESTRUCTOR(BpDict)

// override BpObject methods:

    METHOD(BpDict,makeBrother,(void),BpObject*)
    METHOD(BpDict,printOnLevel,(FILE* file,CARD32 level),void)

// BpDict methods:
    
    METHOD(BpDict, initWithObjectsForKeys,
                        (BpArray* objArray,BpArray* keyArray),void)
        /*
            objects and keys must have the same number of items;
            All keys must be BpString;
            The current entries are removed (with removeAllObjects).
            The keys are copied. The objects are retained.
        */

    METHOD(BpDict,initWithObjectsForKeysCount,
                        (BpObject** objects,BpString** keys,CARD32 count),void)
        /*
            PRE:        objects and keys points to C-arrays of count elements.
            The current entries are removed (with removeAllObjects).
            The keys are copied. The objects are retained.
        */

    METHOD(BpDict,initWithDictionary,(BpDict* otherDictionary),void)
        /*
            The current entries are removed (with removeAllObjects).
            The keys are copied. The objects are retained.
        */


    METHOD(BpDict,addEntriesFromDictionary,(BpDict* otherDictionary),void)
        /*
            The current entries are not removed .
            Inserts all the pairs of other;  in case of pairs with same keys, 
            other's pairs win.
        */



    METHOD(BpDict,count,(void),CARD32)
        /* 
            RETURN:     Number of (key,associated object) pairs in the 
                        dictionary.
        */
        
    METHOD(BpDict,setObjectForKey,(BpObject* obj,BpString* key),void)
        /*
            Associate an object for a certain key; 
            If object is nil an exception is raised.
            -retain is applied to the object inserted in the dictionary.
            and -release is applied to previous element, if any;
            The key is always copied by the dictionary
        */
    
    METHOD(BpDict,objectForKey,(BpString* aKey),BpObject*)
        /*
            Get associated object given its key;
            RETURN:     NIL if there is no (key,associated object) pair,
                        the associated object otherwise.
        */

    METHOD(BpDict,removeObjectForKey,(BpString* key),void)
        /*
            Removes key and associated object from the dictionary;
            Performs -release on previous object if any.
        */
    

    METHOD(BpDict,removeAllObjects,(void),void)
        /*
            Empties the dictionary; 
            Performs -release on each object removed.
        */

    METHOD(BpDict,removeObjectsForKeys,(BpArray* keyArray),void)
        /*
            Removes keys and associated objects from the dictionary
        */
    

    METHOD(BpDict,allKeys,(void),BpArray*)
        /*
            RETURN:     an array containing all the keys;
                        This snapshots the set of keys;
                        Order is un-defined;
        */

    METHOD(BpDict,allValues,(void),BpArray*)
        /*
            RETURN:     an array containing all the associated objects;
                        This snapshots the set of objects;
                        Order is un-defined.
        */

    METHOD(BpDict,allKeysForObject,(BpObject* anObject),BpArray*)
        /*
            RETURN:     all keys for which corresponding object is
                        the given argument;
                        Enumerates the dictionary (=> slow, O(N));
                        NIL if none; otherwise an array of count >= 1
        */
    
protected:
    void*           opaque;
};//BpDict.

#define BpDict_cInitialized         (1)
#define BpDict_cAssociationSet      (2)
#define BpDict_cAssociationRemoved  (3)
#define BpDict_cAssociationsFreed   (4)

#endif
