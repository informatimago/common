/******************************************************************************
FILE:               bjdict.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION

    This module implement the 'dictionary' concept.
    Dictionaries are dynamic (resize themselves by doubling when they
    reach a certain maximum), so that callers never have to think about
    allocation.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2001-01-17 <PJB> Added initialization of that->compare in bjdict_new().
    2001-01-10 <PJB> Added bjdict_set_mode() for case (in)sensitive keys.
    2000-12-26 <PJB> Integrated with AvMailGate.
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
#include <bjdict.h>

    /* For version & component control: */
    const char bjdict_id[]=
    "$Id: bjdict.c,v 1.1 2004/01/21 06:26:31 pjbpjb Exp $";

/******************************************************************************/
/* Definition of a private bjdict_entry class *********************************/
/******************************************************************************/


typedef struct {
    bjstring_t* myKey;
    void*       myObject;
}   bjdict_entry_t;


extern bjdict_entry_t* bjdict_entry_new(void);
extern bjdict_entry_t* bjdict_entry_copy(const bjdict_entry_t* that);
extern void bjdict_entry_set_key_object(bjdict_entry_t* that,
                                        bjstring_t* nKey,
                                        void* nObject);
extern void bjdict_entry_set_object(bjdict_entry_t* that,
                                    void* nObject);
extern bjstring_t* bjdict_entry_key(const bjdict_entry_t* that);
extern void* bjdict_entry_object(const bjdict_entry_t* that);


/******************************************************************************/
/** Implementation of a private bjdict_entry class ****************************/
/******************************************************************************/

    static void bjdict_entry_delete(void* object)
    {
        bjdict_entry_t* that=object;
        bjobject_release(that->myKey);
        bjobject_release(that->myObject);
    }/*bjdict_entry_delete*/


    static bjobject_methods_t bjdict_entry_methods={
        "bjdict_entry", bjdict_entry_delete };


    bjdict_entry_t* bjdict_entry_new(void)
    {
        bjdict_entry_t* that=bjobject_new(sizeof(*that),&bjdict_entry_methods);
        that->myKey=0;
        that->myObject=0;
        return(that);
    }/*bjdict_entry_new*/


    bjdict_entry_t* bjdict_entry_copy(const bjdict_entry_t* that)
        /*
            NOTE:       We don't duplicate the myKey here since it is private
                        to another bjdict_entry.
                        We assume bjdict will not do another set_key_object
                        on the same entry.
        */
    {
        bjdict_entry_t*    nEntry=bjdict_entry_new();
        bjobject_retain(that->myKey);
        nEntry->myKey=that->myKey;
        bjobject_retain(that->myObject);
        nEntry->myObject=that->myObject;
        return(nEntry);
    }/*bjdict_entry_copy*/


    void bjdict_entry_set_key_object(bjdict_entry_t* that,
                                     bjstring_t* nKey,
                                     void* nObject)
    {
        bjobject_release(that->myKey);
        that->myKey=bjstring_new_copy(nKey);
        bjobject_retain(that->myKey);

        bjobject_release(that->myObject);
        that->myObject=nObject;
        bjobject_retain(that->myObject);
    }/*bjdict_entry_set_key_object*/


    void bjdict_entry_set_object(bjdict_entry_t* that,void* nObject)
    {
        bjobject_release(that->myObject);
        that->myObject=nObject;
        bjobject_retain(that->myObject);
    }/*bjdict_entry_set_object*/


    bjstring_t* bjdict_entry_key(const bjdict_entry_t* that)
    {
        return(bjstring_new_copy(that->myKey));
    }/*bjdict_entry_key*/


    void* bjdict_entry_object(const bjdict_entry_t* that)
    {
        return(that->myObject);
    }/*bjdict_entry_object*/



/******************************************************************************/
/** Implementation of  bjdict class *******************************************/
/******************************************************************************/


    static void bjdict_delete(void* object)
    {
        bjdict_t*  that=object;
        bjobject_release(that->entries);
    }/*bjdict_delete*/

    static bjobject_methods_t bjdict_methods={ "bjdict", bjdict_delete };

    bjdict_t* bjdict_new(void)
    {
        bjdict_t* that=bjobject_new(sizeof(*that),&bjdict_methods);
        that->entries=bjarray_new(1);
        bjobject_retain(that->entries);
        that->mode=bjdict_mode_case_sensitive;
        that->compare=bjstring_compare;
        return(that);
    }/*bjdict_new*/


    bjdict_mode_t bjdict_mode(const bjdict_t* that)
    {
        if(that==0){
            return(bjdict_mode_case_sensitive);
        }
        return(that->mode);
    }/*bjdict_mode*/


    void bjdict_set_mode(bjdict_t* that,bjdict_mode_t mode)
    {
        if((that==0)||(mode==that->mode)){
            return;
        }
        that->mode=mode;
        if(that->mode==bjdict_mode_case_insensitive){
            bjarray_t* keys=bjdict_all_keys(that);
            bjarray_t* values=bjdict_all_values(that);
            that->compare=bjstring_compare_insensitive;
            bjdict_remove_all_objects(that);
            bjdict_init_with_objects_for_keys(that,values,keys);
        }else{
            that->compare=bjstring_compare;
        }
    }/*bjdict_set_mode*/


    void bjdict_init_with_objects_for_keys(bjdict_t* that,
                                           const bjarray_t* objArray,
                                           const bjarray_t* keyArray)
    {
        unsigned int i;
        unsigned int count;

        bjdict_remove_all_objects(that);
        count=bjarray_count(objArray);
        if(count!=bjarray_count(keyArray)){
            /* BcRAISE(bjdict_keyAndObjNumMismatch,keyArray,objArray); */
            return;
        }
        for(i=0;i<count;i++){
            bjdict_set_object_for_key(that,
                                      bjarray_element_at(objArray,i),
                                      bjarray_element_at(keyArray,i));
        }
    }/*bjdict_init_with_objects_for_keys*/


    void bjdict_init_with_objects_for_keys_count(bjdict_t* that,
                                                 void** objects,
                                                 bjstring_t** keys,
                                                 unsigned int  count)
    {
        unsigned int i;
        bjdict_remove_all_objects(that);
        for(i=0;i<count;i++){
            bjdict_set_object_for_key(that,objects[i],keys[i]);
        }
    }/*bjdict_init_with_objects_for_keys_count*/


    void bjdict_init_with_dictionary(bjdict_t* that,
                                     const bjdict_t* otherDictionary)
    {
        bjdict_remove_all_objects(that);
        bjdict_add_entries_from_dictionary(that,otherDictionary);
    }/*bjdict_init_with_dictionary*/


    void bjdict_add_entries_from_dictionary(bjdict_t* that,
                                            const bjdict_t* otherDictionary)
    {
        bjarray_t*  keys=bjdict_all_keys(otherDictionary);
        unsigned int  count=bjarray_count(keys);
        unsigned int         i;

        for(i=0;i<count;i++){
            bjstring_t* theKey=bjarray_element_at(keys,i);
            bjdict_set_object_for_key(
                that,bjdict_object_for_key(otherDictionary,theKey),theKey);
        }
    }/*bjdict_add_entries_from_dictionary*/


    unsigned int bjdict_count(const bjdict_t* that)
    {
        return(bjarray_count(that->entries));
    }/*bjdict_count*/


    static bool bjdict_search(const bjarray_t* entries,const bjstring_t* key,
                              unsigned int* rNum,order_t* rOrder,
                              bjdict_compare_pr compare)
        /*
            PRE:        entry is the element to be searched in the table.
            POST:        0<=num<entries->size()=max
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
        unsigned int     curmin;
        unsigned int     curmax;
        unsigned int     num;
        order_t order;

        curmin=0;
        curmax=bjarray_count(entries);
        if(curmax==0){
            *rOrder=-1;
            *rNum=0;
            return(no);
        }
        num=(curmin+curmax)/2;
        order=compare(bjdict_entry_key(bjarray_element_at(entries,num)),key);
        while((order!=0)&&(curmin!=num)){
            if(order>0){
                /* the order returned by compare_key is inverted. */
                curmax=num;
            }else{
                curmin=num;
            }
            num=(curmin+curmax)/2;
            order=compare(bjdict_entry_key(bjarray_element_at(entries,num)),
                          key);
        }
        if((0<num)&&(order>0)){
            order=order_less;
            num--;
        }
        *rOrder=-order;
        *rNum=num;
        return(order==order_equal);
    }/*bjdict_search*/


    void bjdict_set_object_for_key(bjdict_t* that,
                                   void* obj,bjstring_t* key)
    {
        unsigned int    num;
        order_t         order;
        bjdict_entry_t* nEntry;

        bjdict_search(that->entries,key,&num,&order,that->compare);
        if(order==order_equal){
            /* | x = a[i]          |   TRUE   |   i   |  equal   |  */
            bjdict_entry_set_object(bjarray_element_at(that->entries,num),obj);
        }else{
            if((order>0)&&((num!=bjarray_count(that->entries)))){
                num++;
            }
            nEntry=bjdict_entry_new();
            bjdict_entry_set_key_object(nEntry,key,obj);
            bjarray_set_size(that->entries,bjarray_count(that->entries)+1);
            bjarray_insert_element_at(that->entries,num,nEntry);
        }
    }/*bjdict_set_object_for_key*/


    void* bjdict_object_for_key(const bjdict_t* that,const bjstring_t* aKey)
    {
        unsigned int     num;
        order_t order;

        bjdict_search(that->entries,aKey,&num,&order,that->compare);
        if(order==order_equal){
            return(bjdict_entry_object(bjarray_element_at(that->entries,num)));
        }else{
            return(0);
        }
    }/*bjdict_object_for_key*/


    void bjdict_remove_object_for_key(bjdict_t* that,const bjstring_t* key)
    {
        unsigned int     num;
        order_t order;

        bjdict_search(that->entries,key,&num,&order,that->compare);
        if(order==order_equal){
            bjarray_remove_element_at(that->entries,num);
        }
    }/*bjdict_remove_object_for_key*/


    void bjdict_remove_all_objects(bjdict_t* that)
    {
        bjobject_release(that->entries);
        that->entries=bjarray_new(1);
        bjobject_retain(that->entries);
    }/*bjdict_remove_all_objects*/


    void bjdict_remove_objects_for_keys(bjdict_t* that,
                                        const bjarray_t* keyArray)
    {
       unsigned  int i;
       unsigned  int count;

        count=bjarray_count(keyArray);
        for(i=0;i<count;i++){
            bjdict_remove_object_for_key(that,bjarray_element_at(keyArray,i));
        }
    }/*bjdict_remove_objects_for_keys*/


    bjarray_t* bjdict_all_keys(const bjdict_t* that)
    {
       unsigned  int        count=bjarray_count(that->entries);
        bjarray_t* keys=bjarray_new(count);
        unsigned int        i;

        for(i=0;i<count;i++){
            bjarray_set_element_at(
                keys,i,bjdict_entry_key(bjarray_element_at(that->entries,i)));
        }
        return(keys);
    }/*bjdict_all_keys*/


    bjarray_t* bjdict_all_values(const bjdict_t* that)
    {
        unsigned int        count=bjarray_count(that->entries);
        bjarray_t* objects=bjarray_new(count);
       unsigned  int        i;

        for(i=0;i<count;i++){
            bjarray_set_element_at(
                objects,i,
                bjdict_entry_object(bjarray_element_at(that->entries,i)));
        }
        return(objects);
    }/*bjdict_all_values*/


    bjarray_t* bjdict_all_keys_for_object(const bjdict_t* that,
                                          const void* anObject)
    {
        bjarray_t*  keys=bjarray_new(1);
        unsigned int         count;
        unsigned int         i;

        count=bjarray_count(that->entries);
        for(i=0;i<count;i++){
            bjdict_entry_t* entry=bjarray_element_at(that->entries,i);
            if(bjdict_entry_object(entry)==anObject){
                bjarray_add_element(keys,bjdict_entry_key(entry));
            }
        }
        return(keys);
    }/*bjdict_all_keys_for_object*/


/*** bjdict.c                         -- 2004-01-01 09:55:56 -- pascal   ***/
