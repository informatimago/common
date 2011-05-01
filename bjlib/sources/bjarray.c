/******************************************************************************
FILE:               bjarray.c
LANGUAGE:           ANSI-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This module encapsulate an array object.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2002-02-12 <TS>  Added bjobject_retain() in bjarray_add_element().
    2001-03-16 <PJB> Added bjarray_copy_from_length and bjarray_append.
    2000-12-26 <PJB> Integrated with AvMailGate.
    2000-09-20 <PJB> Creation.
BUGS
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon 2000 - 2011
    
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
#include <bjarray.h>
#include <bjobject.h>

    /* For version & component control: */
    const char bjarray_id[]=
    "$Id: bjarray.c,v 1.1 2004/01/21 06:26:31 pjbpjb Exp $";


#ifdef CHECK_INVARIANTS
#define CHECK(that) \
        do{if(!bjarray_check_invariant(that)){int i=0;i=1/i;}}while(0)
#else
#define CHECK(that)
#endif


    /* invariant :
       0<=count<=size
       0<count  ==>  elements[count-1]!=0
       pour tout i,  count<=i    ==>  elements[i]==0
       pour tout i,  0<=i<size  ==>
                        elements[i]!=0  ==>
                           1<=bjobject_retain_count(elements[i])
    */

    static void bjarray_delete(void* object)
    {
        bjarray_t* that=object;
        unsigned int i;
        CHECK(that);
        for(i=0;i<that->count;i++){
            bjobject_release(that->elements[i]);
        }
        bjobject_release(that->elements);
    }/*bjarray_delete*/


    static bjobject_methods_t bjarray_methods={  "bjarray", bjarray_delete };

    bjarray_t* bjarray_new(unsigned int size)
    {
        unsigned int i;
        bjarray_t* that=bjobject_new(sizeof(*that),&bjarray_methods);
        that->size=size;
        that->count=0;
        that->elements=(void**)bjobject_new((int)sizeof(*(that->elements))*that->size,0);
        bjobject_retain(that->elements);
        for(i=that->count;i<that->size;i++){
            that->elements[i]=0;
        }
        CHECK(that);
        return(that);
    }/*bjarray_new*/


    unsigned int bjarray_size(const bjarray_t* that)
    {
        CHECK(that);
        return(that->size);
    }/*bjarray_size*/


    unsigned int bjarray_count(const bjarray_t* that)
    {
        CHECK(that);
        return(that->count);
    }/*bjarray_count*/



    void bjarray_set_size(bjarray_t* that,unsigned int newSize)
    {
        void**          elements;
        unsigned int             minSize;
        unsigned int             i;
        CHECK(that);
        if(newSize==that->size){
            return;
        }
        if(newSize<that->size){
            unsigned int k;
            for(k=newSize;k<that->count;k++){
                bjobject_release(that->elements[k]);
            }
            minSize=newSize;
        }else{
            minSize=that->size;
        }
        that->size=newSize;
        elements=(void**)bjobject_new((int)sizeof(*elements)*that->size,0);
        /* We're just transfering the elements[i], no need to release/retain! */
        for(i=0;i<minSize;i++){
            elements[i]=that->elements[i];
        }
        for(i=minSize;i<newSize;i++){
            elements[i]=0;
        }
        if(minSize<that->count){
            that->count=minSize;
        }
        bjobject_release(that->elements);
        that->elements=elements;
        bjobject_retain(that->elements);
        CHECK(that);
    }/*bjarray_set_size*/


    void* bjarray_element_at(const bjarray_t* that,unsigned int idx)
    {
        CHECK(that);
        if((that==0)||(that->size<=idx)){
            return(0);
        }else{
            return(that->elements[idx]);
        }
    }/*bjarray_element_at*/


    void* bjarray_set_element_at(bjarray_t* that,unsigned int idx,
                                     void* element)
    {
        void* result;
        CHECK(that);
        if(that->size<=idx){
            return(0);
        }
        bjobject_retain(element);
        result=that->elements[idx];
        that->elements[idx]=element;
        bjobject_release(result);
        if((element!=0)&&(that->count<=idx)){
            that->count=idx+1;
        }
        while((that->count>0)&&(that->elements[that->count-1]==0)){
            that->count--;
        }
        CHECK(that);
        return(result);
    }/*bjarray_set_element_at*/


    void bjarray_insert_element_at(bjarray_t* that,unsigned int idx,
                                     void* element)
    {
        unsigned int i;
        CHECK(that);
        if(that->size<=idx){
            return;
        }
        bjobject_retain(element);
        if(that->count==that->size){
            bjobject_release(that->elements[that->size-1]);
        }
        if(that->count<=idx){
            if(element!=0){
                that->count=idx+1;
            }
        }else{
            for(i=that->count;idx<i;i--){
                that->elements[i]=that->elements[i-1];
            }
            that->count++;
        }
        that->elements[idx]=element;
        CHECK(that);
    }/*bjarray_insert_element_at*/


    void* bjarray_remove_element_at(bjarray_t* that,unsigned int idx)
    {
        void* result;
        CHECK(that);
        if(that->count<=idx){
            return(0);
        }
        result=that->elements[idx];
        bjobject_release(result);
        that->count--;
        while(idx<that->count){
            that->elements[idx]=that->elements[idx+1];
            idx++;
        }
        /* idx==that->count */
        if(idx<that->size-1){
            that->elements[idx]=that->elements[idx+1];
        }else{
            that->elements[idx]=0;
        }
        while((that->count>0)&&(that->elements[that->count-1]==0)){
            that->count--;
        }
        CHECK(that);
        return(result);
    }/*bjarray_remove_element_at*/



    void bjarray_add_element(bjarray_t* that,void* element)
    {
        if(element!=0){
            if(that->count==that->size){
                bjarray_set_size(that,that->size*2);
            }
            that->elements[that->count]=element;
            bjobject_retain(that->elements[that->count]);
            that->count++;
        }
    }/*bjarray_add_element*/



    void bjarray_copy_from_length(bjarray_t* that,
                                  const bjarray_t* source,
                                  unsigned int idx,unsigned int copylen)
    {
        unsigned int i;
        if((that==0)||(source==0)){
            return;
        }
        CHECK(that);
        CHECK(source);
        if(idx+copylen>source->count){
            copylen=source->count-idx;
        }
        for(i=0;i<that->size;i++){
            bjobject_release(that->elements[i]);
            that->elements[i]=0;
        }
        that->count=0;
        if(copylen<=0){
            /* Let's remove all elements from that. */
            CHECK(that);
            return;
        }
        if(copylen>=that->size){
            bjarray_set_size(that,copylen);
        }
        for(i=0;i<copylen;i++){
            that->elements[i]=source->elements[idx+i];
            bjobject_retain(that->elements[i]);
        }
        that->count=copylen;
        CHECK(that);
    }/*bjarray_copy_from_length*/



    static void bjarray_insert_at(bjarray_t* that,
                                  const bjarray_t* subarray,unsigned int idx)
    {
        unsigned int             i;
        unsigned int             nLength;

        if((that==0)||(subarray==0)){
            return;
        }
        CHECK(that);
        CHECK(subarray);
        if(that->count<idx){
            idx=that->count;
        }
        nLength=that->count+subarray->count;
        if(nLength>=that->size){
            /* TODO: We copy some char of that twice !*/
            bjarray_set_size(that,nLength);
        }
        if(idx<that->count){
            for(i=that->count-1;idx<=i;i--){
                that->elements[i+subarray->count]=that->elements[i];
            }
        }
        for(i=0;i<subarray->count;i++){
            that->elements[idx+i]=subarray->elements[i];
            bjobject_retain(that->elements[idx+i]);
        }
        that->count=nLength;
        CHECK(that);
    }/*bjarray_insert_at*/


    void bjarray_append(bjarray_t* that,const bjarray_t* tail)
    {
        if((that==0)||(tail==0)){
            return;
        }
        bjarray_insert_at(that,tail,that->count);
    }/*bjarray_append*/



    void bjarray_remove_from_length(bjarray_t* that,unsigned int idx,
                                    unsigned int delen)
    {
        unsigned int i;
        unsigned int relen; /* Remaining Length after Deleted Elements. */
        if(that==0){
            return;
        }
        CHECK(that);
        if(that->count<=idx){
            return;
        }
        if(delen<=0){
            return;
        }
        if(that->count<idx+delen){
            delen=that->count-idx;
        }
        relen=that->count-idx-delen;
        for(i=0;i<delen;i++){ /* Clean up removed elements. */
            bjobject_release(that->elements[idx+i]);
            that->elements[idx+i]=0;
        }
        for(i=0;i<relen;i++){ /* Move down remaining elements. */
            that->elements[idx+i]=that->elements[idx+delen+i];
        }
        for(i=relen;i<relen+delen;i++){ /* Clean up moved down entries. */
            that->elements[idx+i]=0;
        }
        that->count=that->count-delen;
        CHECK(that);
    }/*bjarray_remove_from_length*/


    short bjarray_check_invariant(const bjarray_t* that)
    {
        unsigned int i;
        if((that->count<0)||(that->size<that->count)){
            return(0);
        }
        if(that->count>0){
            if(that->elements[that->count-1]==0){
                return(0);
            }
        }
        for(i=that->count;i<that->size;i++){
            if(that->elements[i]!=0){
                return(0);
            }
        }
        for(i=0;i<that->count;i++){
            if(that->elements[i]!=0){
                if(bjobject_retain_count(that->elements[i])<1){
                    return(0);
                }
            }
        }
        return(1);
    }/*bjarray_check_invariant*/


/*** bjarray.c                        -- 2003-12-03 18:41:55 -- pascal   ***/
