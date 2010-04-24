/******************************************************************************
FILE:               bjdict.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     None
DESCRIPTION

        This module implement the 'dictionary' concept.
        Dictionaries are dynamic (resize themselves by doubling when they
        reach a certain maximum), so that callers never have to think about
        allocation.

AUTHOR
        <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2001-01-17 <PJB> Added initialization of that->compare in bjdict_new().
    2001-01-10 <PJB> Added bjdict_set_mode() for case (in)sensitive keys.
    2000-12-21 <PJB> Integrated with AvMailGate.
BUGS
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon     1995 - 2001
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version
    2 of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public
    License along with this program; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
#ifndef bjdict_h
#define bjdict_h
#include <bjobject.h>
#include <bjarray.h>
#include <bjstring.h>

typedef enum {
    bjdict_mode_case_sensitive, /* default */
    bjdict_mode_case_insensitive
}   bjdict_mode_t;

typedef order_t (*bjdict_compare_pr)(const bjstring_t*,const bjstring_t*);
typedef struct {
    bjarray_t*          entries;
    bjdict_mode_t       mode;
    bjdict_compare_pr   compare;
}   bjdict_t;



extern bjdict_t* bjdict_new(void);

extern bjdict_mode_t bjdict_mode(const bjdict_t* that);
extern void bjdict_set_mode(bjdict_t* that,bjdict_mode_t mode);
    /*
        (Going from case_sensitive to case_insensitive may
         colapse some keys and remove some values).
    */
extern void bjdict_init_with_objects_for_keys(bjdict_t* that,
                                              const bjarray_t* objArray,
                                              const bjarray_t* keyArray);
    /*
        objects and keys must have the same number of items;
        All keys must be bjstring_t;
        The current entries are removed (with remove_all_objects).
        The keys are copied. The objects are retained.
    */

extern void bjdict_init_with_objects_for_keys_count(bjdict_t* that,
                                                    void** objects,
                                                    bjstring_t** keys,
                                                    unsigned int count);
    /*
        PRE:            objects and keys points to C-arrays of count elements.
        The current entries are removed (with remove_all_objects).
        The keys are copied. The objects are retained.
    */

extern void bjdict_init_with_dictionary(bjdict_t* that,
                                        const bjdict_t* otherDictionary);
    /*
        The current entries are removed (with remove_all_objects).
        The keys are copied. The objects are retained.
        (Copies the mode too).
    */


extern void bjdict_add_entries_from_dictionary(bjdict_t* that,
                                               const bjdict_t* otherDictionary);
    /*
        The current entries are not removed .
        Inserts all the pairs of other;  in case of pairs with same keys,
        other's pairs win.
        (Don't change the mode! This may colapse some values.)
    */

extern unsigned int bjdict_count(const bjdict_t* that);
    /*
        RETURN:         Number of (key,associated object) pairs in the
                    dictionary.
    */

extern void bjdict_set_object_for_key(bjdict_t* that,
                                      void* obj,bjstring_t* key);
    /*
        Associate an object for a certain key;
        If object is nil an exception is raised.
        -retain is applied to the object inserted in the dictionary.
        and -release is applied to previous element, if any;
        The key is always copied by the dictionary
    */

extern void* bjdict_object_for_key(const bjdict_t* that,const bjstring_t* aKey);
    /*
        Get associated object given its key;
        RETURN:         0 if there is no (key,associated object) pair,
                    the associated object otherwise.
    */

extern void bjdict_remove_object_for_key(bjdict_t* that,const bjstring_t* key);
    /*
        Removes key and associated object from the dictionary;
        Performs -release on previous object if any.
    */


extern void bjdict_remove_all_objects(bjdict_t* that);
    /*
        Empties the dictionary;
        Performs -release on each object removed.
    */

extern void bjdict_remove_objects_for_keys(bjdict_t* that,
                                           const bjarray_t* keyArray);
    /*
        Removes keys and associated objects from the dictionary
    */


extern bjarray_t* bjdict_all_keys(const bjdict_t* that);
    /*
        RETURN:         an array containing all the keys;
                    This snapshots the set of keys;
                    Order is un-defined;
    */

extern bjarray_t* bjdict_all_values(const bjdict_t* that);
    /*
        RETURN:         an array containing all the associated objects;
                    This snapshots the set of objects;
                    Order is un-defined.
    */

extern bjarray_t*  bjdict_all_keys_for_object(const bjdict_t* that,
                                              const void* anObject);
    /*
        RETURN:         all keys for which corresponding object is
                    the given argument;
                    Enumerates the dictionary (=> slow, O(N));
                    0 if none; otherwise an array of count >= 1
    */

#endif
/*** bjdict.h                         -- 2003-12-03 18:43:27 -- pascal   ***/
