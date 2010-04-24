/******************************************************************************
FILE:               bjstring.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     None
DESCRIPTION

    This class  defines string object. The string  data is dynamically
    allocated and reclaimed.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2003-02-19 <PJB> Added bjstring_char_index.
    2002-05-22 <PJB> Added bjstring_search_forward_insensitive and
                     bjstring_search_backward_insensitive, and renamed
                     bjstring_position_from to bjstring_search_forward.
    2001-10-28 <PJB> Corrected an important bug in bjstring_set_format_va.
    2001-03-15 <PJB> Moved file-related function to 'bjstring_file.c'.
    2001-03-14 <PJB> Added bjstring_set_chars and bjstring_new_chars.
    2001-02-23 <PJB> Use new file functions.
    2001-01-17 <PJB> Added bjstring_search_backward().
    2001-01-10 <PJB> Added bjstring_is_suffix()
                     and bjstring_is_suffix_insensitive().
    2000-12-28 <PJB> Added bjstring_is_prefix()
                     and bjstring_is_prefix_insensitive().
    2000-12-18 <PJB> Integrated into AvMailGate project (some renaming) and
                     added bjstring_substitute_from(), bjstring_compare(), and
                     bjstring_compare_insensitive().
    1995-11-16 <PJB> Some small correction to compile in MSVC.
    1993-01-29 <PJB> Creation.
BUGS
    No check is done for out of memory errors.
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon     1993 - 2003
    
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
#include <stdlib.h>
#include <stdio.h> /* import vsnprintf */
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include <bjstring.h>


    /* For version & component control: */
    const char bjstring_id[]=
    "$Id: bjstring.c,v 1.2 2004/10/27 03:38:20 pupjb Exp $";

    static const int AllocIncrement=128;

/*
    INVARIANTS:
        data!=0
        data!=empty_data <=> 1<=allocation && 0<=length<allocation
        data==empty_data <=> 0==allocation && 0==length<=allocation
        for all i in [0..length-1], data[i]!='\0'
        data[length]='\0'
*/


/*
    We cannot use strcpy/strncpy or  memcpy because the source and the
    destination strings  may overlap (and do overlap,  for example, in
    the case of inserting or deleting). Therefore, we consistently use
    memmmove.
*/


    static char* empty_data=0;
        /*
            A   small   optimization.   To  prevent   allocating   and
            deallocating 1-char  block over and  over in bjstring_new,
            we use this empty_data string.
        */

    static void bjstring_delete(void* object)
    {
        bjstring_t* that=object;
        if(that->data!=empty_data){
            bjobject_release(that->data);
        }
    }/*bjstring_delete*/


    static bjobject_methods_t bjstring_methods={ "bjstring", bjstring_delete };

    bjstring_t*  bjstring_new(void)
    {
        bjstring_t*      that;
        that=bjobject_new(sizeof(*that),&bjstring_methods);
        that->allocation=0;
        that->length=0;
        if(empty_data==0){
            empty_data=malloc(1);
            empty_data[0]='\0';
        }
        that->data=empty_data;
        return(that);
    }/*new*/


    bjstring_t*  bjstring_new_copy(const bjstring_t* other)
    {
        bjstring_t* that=bjstring_new();
        bjstring_copy_from(that,other);
        return(that);
    }/*bjstring_new_copy*/


    bjstring_t*  bjstring_new_string(const char* string)
    {
        bjstring_t* that=bjstring_new();
        bjstring_set_string(that,string);
        return(that);
    }/*bjstring_new_string*/


    bjstring_t*  bjstring_new_format(const char* format,...)
    {
        va_list ap;
        bjstring_t* that=bjstring_new();
        va_start(ap,format);
        bjstring_set_format_va(that,format,ap);
        va_end(ap);
        return(that);
    }/*bjstring_new_format*/


    bjstring_t*  bjstring_new_chars(const char* string,unsigned int count)
    {
        bjstring_t* that=bjstring_new();
        bjstring_set_chars(that,string,count);
        return(that);
    }/*bjstring_new_chars*/


    bjstring_t*  bjstring_new_repeat(const char* string,unsigned int count)
    {
        bjstring_t* that=bjstring_new();
        unsigned int length=strlen(string);
        unsigned int pos=0;
        if(count<0){
            count=0;
        }
        bjstring_set_capacity_copy(that,length*count,no);
        while(count>0){
            memmove(/*dst*/that->data+pos,
                    /*src*/string,
                    /*len*/sizeof(char)*length);
            pos+=length;
            count--;
        }
        that->length=pos;
        that->data[that->length]='\0';
        return(that);
    }/*bjstring_new_repeat*/


    void bjstring_set_capacity_copy(bjstring_t* that,
                                    unsigned int nCapacity,bool copy)
    {
        char*        nData;
        unsigned int nLength;
        unsigned int nAllocation=nCapacity+1;
        if(that==0){
            return;
        }
        if(nAllocation>1){
            nData=(char*)bjobject_new(sizeof(*nData)*nAllocation,0);
            /* TODO: Important, we should add here a test nData==0 and behave. */
            if(copy){
                if(nCapacity<that->length){
                    nLength=nCapacity;
                }else{
                    nLength=that->length;
                }
                memmove(/*dst*/nData,
                        /*src*/that->data,
                        /*len*/sizeof(*nData)*nLength);
            }else{
                nLength=0;
            }
            if(that->data!=empty_data){
                bjobject_release(that->data);
            }
            that->data=nData;
            bjobject_retain(that->data);
            that->allocation=nAllocation;
            that->length=nLength;
            that->data[that->length]='\0';
        }else{
            /* We revert to empty_data here,  */
            if(that->data!=empty_data){
                bjobject_release(that->data);
            }
            that->data=empty_data;
            that->allocation=0;
            that->length=0;
        }
    }/*set_capacity_copy*/



    unsigned int bjstring_length(const bjstring_t* that)
    {
        if(that==0){
            return(0);
        }
        return(that->length);
    }/*bjstring_length*/


    const char* bjstring_string(const bjstring_t* that)
    {
        if(that==0){
            return(0);
        }
        return(that->data);
    }/*bjstring_string*/


    char* bjstring_mutable_string(bjstring_t* that)
    {
        if(that==0){
            return(0);
        }
        return(that->data);
    }/*bjstring_mutable_string*/


    void bjstring_set_chars(bjstring_t* that,const char* chars,
                            unsigned int count)
    {
        unsigned int i;
        if((that==0)||(chars==0)){
            return;
        }
        i=0;
        while((i<count)&&(chars[i]!='\0')){
            i++;
        }
        count=i;
        if(count>=that->allocation){
            bjstring_set_capacity_copy(that,count,no);
        }
        if(count>0){
            memmove(/*dst*/that->data,
                    /*src*/chars,
                    /*len*/sizeof(*(that->data))*count);
            that->length=count;
            that->data[that->length]='\0';
        }else if(that->data!=empty_data){
            that->length=count;
            that->data[that->length]='\0';
        }
    }/*set_chars*/


    void bjstring_set_string(bjstring_t* that,const char* nString)
    {
        bjstring_set_chars(that,nString,strlen(nString));
    }/*set_string*/


    void bjstring_get_string(const bjstring_t* that,char* string)
    {
        if(that==0){
            string[0]='\0';
            return;
        }
        memmove(/*dst*/string,
                /*src*/that->data,
                /*len*/sizeof(*string)*that->length);
        string[that->length]='\0';
    }/*get_string*/


    void bjstring_append_string(bjstring_t* that,const char* str)
    {
        unsigned int    nLength;
        unsigned int    sLength;

        if((that==0)||(str==0)){
            return;
        }
        sLength=strlen(str);
        nLength=that->length+sLength;
        if(nLength>=that->allocation){
            bjstring_set_capacity_copy(that,nLength,yes);
        }
        if(that->data!=empty_data){
            memmove(/*dst*/that->data+that->length,
                    /*src*/str,
                    /*len*/sizeof(*(that->data))*sLength);
            that->length=nLength;
            that->data[that->length]='\0';
        }
    }/*bjstring_append_string*/


    char bjstring_char_at(const bjstring_t* that,unsigned int idx)
    {
        if(that==0){
            return('\0');
        }
        if((idx<0)||(idx>=that->length)){
            return('\0');
        }else{
            return(that->data[idx]);
        }
    }/*char_at*/


    void bjstring_set_char_at(bjstring_t* that,char nChar,unsigned int idx)
    {
        if(that==0){
            return;
        }
        if(idx<=that->length){
            if(nChar=='\0'){
                if(that->data!=empty_data){
                    that->length=idx;
                    that->data[that->length]='\0';
                }
            }else if(idx==that->length){
                if(that->allocation<=that->length+1){
                    bjstring_set_capacity_copy(
                        that,that->allocation+AllocIncrement,yes);
                }
                that->data[idx]=nChar;
                that->length++;
                that->data[that->length]='\0';
            }else{
                that->data[idx]=nChar;
            }
        }
    }/*set_char_at*/


    unsigned int bjstring_char_index(const bjstring_t* that,char aChar,
                                     unsigned int fromIdx)
    {
        if(that==0){
            return(that->length);
        }
        if(fromIdx<0){
            fromIdx=0;
        }else if(that->length<=fromIdx){
            return(that->length);
        }
        while((fromIdx<that->length)&&(that->data[fromIdx]!=aChar)){
            fromIdx++;
        }
        if(fromIdx<that->length){
            return(fromIdx);
        }else{
            return(that->length);
        }
    }/*bjstring_char_index*/


    void bjstring_insert_at(bjstring_t* that,
                            const bjstring_t* substring,unsigned int idx)
    {
        unsigned int    nLength;

        if((that==0)||(substring==0)){
            return;
        }
        if(idx<0){
            idx=0;
        }else if(that->length<idx){
            idx=that->length;
        }
        nLength=that->length+substring->length;
        if(nLength>=that->allocation){
            /* TODO: We copy some char of that twice !*/
            bjstring_set_capacity_copy(that,nLength,yes);
        }
        if(that->data!=empty_data){
            memmove(/*dst*/that->data+idx+substring->length,
                    /*src*/that->data+idx,
                    /*len*/sizeof(*(that->data))*(that->length-idx+1));
            memmove(/*dst*/that->data+idx,
                    /*src*/substring->data,
                    /*len*/sizeof(*(that->data))*substring->length);
            that->length=nLength;
            that->data[that->length]='\0';
        }
    }/*insert_at*/


    void bjstring_delete_from_length(bjstring_t* that,unsigned int idx,
                                     unsigned int delen)
    {
        if(that==0){
            return;
        }
        if(that->data==empty_data){
            return;
        }
        if(idx<0){
            idx=0;
        }else if(that->length<=idx){
            return;
        }
        if(delen<=0){
            return;
        }
        if(that->length<idx+delen){
            delen=that->length-idx;
        }
        if(that->length>idx+delen){
            memmove(/*dst*/that->data+idx,
                    /*src*/that->data+idx+delen,
                    /*len*/sizeof(*(that->data))*(that->length-(idx+delen)));
        }
        that->length=that->length-delen;
        that->data[that->length]='\0';
    }/*delete_from_length*/



    void bjstring_replace_from_length(bjstring_t* that,
                                      const bjstring_t* substring,
                                      unsigned int idx,unsigned int delen)
    {
        unsigned int nLength;

        if(that==0){
            return;
        }
        if((substring==0)||(bjstring_length(substring)==0)){
            bjstring_delete_from_length(that,idx,delen);
            return;
        }

        if(idx<0){
            idx=0;
        }else if(that->length<=idx){
            idx=that->length;
        }
        if(delen<=0){
            delen=0;
        }
        if(that->length<idx+delen){
            delen=that->length-idx;
        }

        nLength=that->length+substring->length-delen;
        /*
            0 < substring->length
            && 0 <= idx
            && 0 <= delen <= that->length - idx
            ==> 0 <= that->length - delen
            ==> 0 <  that->length - delen + substring->length = nLength
        */
        if(nLength>=that->allocation){
            /* TODO: We copy some char of that twice !*/
            bjstring_set_capacity_copy(that,nLength,yes);
        }

        memmove(/*dst*/that->data+idx+substring->length,
                /*src*/that->data+idx+delen,
                /*len*/sizeof(*(that->data))*(that->length-(idx+delen)+1));

        memmove(/*dst*/that->data+idx,
                /*src*/substring->data,
                /*len*/sizeof(*(that->data))*substring->length);

        that->length=nLength;
        that->data[that->length]='\0';
    }/*bjstring_replace_from_length*/



    unsigned int bjstring_search_forward(const bjstring_t* that,
                                const bjstring_t* substring,
                                unsigned int idx)
    {
        /* TODO: could we use the FastStringSearch algorithm? */
        unsigned int    pos;
        unsigned int    i;
        unsigned int    max;

        if(that==0){
            return(0);
        }else if(substring==0){
            return(that->length);
        }
        if(idx<0){
            pos=0;
        }else{
            pos=idx;
        }
        max=that->length-substring->length;
        while(pos<=max){
            i=0;
            while((pos+i<that->length)
                  &&(that->data[pos+i]==substring->data[i])){
                i++;
            }
            if(substring->data[i]=='\0'){
                return(pos);
            }
            pos++;
        }
        /* not found*/
        return(that->length);
    }/*bjstring_search_forward*/


    unsigned int bjstring_search_forward_insensitive(const bjstring_t* that,
                                const bjstring_t* substring,unsigned int idx)
    {
        /* TODO: could we use the FastStringSearch algorithm? */
        unsigned int             pos;
        unsigned int             max;

        if(that==0){
            return(0);
        }else if(substring==0){
            return(that->length);
        }
        if(idx<0){
            pos=0;
        }else{
            pos=idx;
        }
        max=that->length-substring->length;
        while(pos<=max){
            if(strncasecmp(that->data+pos,
                           substring->data,substring->length)==0){
                return(pos);
            }
            pos++;
        }
        /* not found*/
        return(that->length);
    }/*bjstring_search_forward_insensitive*/


    unsigned int bjstring_search_backward(const bjstring_t* that,
                                          const bjstring_t* substring,
                                          unsigned int idx)
    {
        /* TODO: could we use the FastStringSearch algorithm?*/
        unsigned int             pos;
        unsigned int             i;
        unsigned int             max;

        if(that==0){
            return(0);
        }else if((substring==0)||(idx<0)){
            return(that->length);
        }
        max=that->length-substring->length;
        if(max<idx){
            pos=max;
        }else{
            pos=idx;
        }
        while(0<=pos){
            i=0;
            while((i<substring->length)
                  &&(that->data[pos+i]==substring->data[i])){
                i++;
            }
            if(i==substring->length){
                return(pos);
            }
            pos--;
        }
        /* not found*/
        return(that->length);
    }/*bjstring_search_backward*/


    unsigned int bjstring_search_backward_insensitive(const bjstring_t* that,
                                          const bjstring_t* substring,
                                          unsigned int idx)
    {
        /* TODO: could we use the FastStringSearch algorithm?*/
        unsigned int             pos;
        unsigned int             max;

        if(that==0){
            return(0);
        }else if((substring==0)||(idx<0)){
            return(that->length);
        }
        max=that->length-substring->length;
        if(max<idx){
            pos=max;
        }else{
            pos=idx;
        }
        while(0<=pos){
            if(strncasecmp(that->data+pos,
                           substring->data,substring->length)==0){
                return(pos);
            }
            pos--;
        }
        /* not found*/
        return(that->length);
    }/*bjstring_search_backward_insensitive*/


    void bjstring_copy_from(bjstring_t* that,
                            const bjstring_t* string)
    {
        bjstring_copy_from_length(that,string,0,string->length);
    }/*copy_from*/


    void bjstring_copy_from_length(bjstring_t* that,
                                   const bjstring_t* string,
                                   unsigned int idx,unsigned int copylen)
    {
        if((that==0)||(string==0)){
            return;
        }
        if(idx+copylen>string->length){
            copylen=string->length-idx;
        }
        if(copylen<=0){
            if(that->data!=empty_data){
                that->length=0;
                that->data[that->length]='\0';
            }
            return;
        }
        if(copylen>=that->allocation){
            bjstring_set_capacity_copy(that,copylen,no);
        }
        if(that->data!=empty_data){
            memmove(/*dst*/that->data,
                    /*src*/string->data+idx,
                    /*len*/sizeof(*(that->data))*copylen);
            that->length=copylen;
            that->data[that->length]='\0';
        }
    }/*copy_from_length*/


    bjstring_t* bjstring_substring(const bjstring_t* that,
                                   unsigned int idx,
                                   unsigned int copylen)
    {
        bjstring_t* result=bjstring_new();
        bjstring_set_capacity_copy(result,copylen,no);
        bjstring_copy_from_length(result,that,idx,copylen);
        return(result);
    }/*bjstring_substring*/


    void bjstring_append(bjstring_t* that,const bjstring_t* tail)
    {
        if((that==0)||(tail==0)){
            return;
        }
        bjstring_insert_at(that,tail,that->length);
    }/*append*/


    void bjstring_set_format_va(bjstring_t* that,
                                const char* format,va_list ap)
        /*
            DOES:    Actually _append_ the formated string to that string.
                     (We should change the name of this function).
        */
    {
        va_list save_ap;
        int available; /* to vsnprintf ; up to then, it's "willBeNeeded". */
        int formatlen;
        int inc;
        bool firstTime=yes; 
        va_copy(save_ap,ap);
        if((that==0)||(format==0)){
            return;
        }
        available=that->allocation-that->length;
        formatlen=strlen(format);
        if(available<formatlen){
            available=formatlen;
        }
        inc=-1;
        do{
            if(inc<0){
                /* We don't know exactly how many bytes are needed. */
                if(firstTime){
                    /* The first time, we just try with what's available. */
                    firstTime=no;
                }else{
                    /* Next iteration, we double the available size. */
                    available*=2;
                }
            }else{
                /* We know exactly how many bytes are needed. */
                available=inc+1;
            }
            bjstring_set_capacity_copy(that,that->length+available,yes);
            ap=save_ap;
            /*
                We would like to do something like {va_start(ap,format);}
                With GNU-C, reseting ap like this will work, but there's
                no guaranty with other compilers.
            */
            inc=vsnprintf(that->data+that->length,
                          (unsigned)available,format,ap);
            /* va_end(ap); */
        }while((inc<0)||(available<=inc));
        that->length+=inc;
    }/*bjstring_set_format_va*/


    void bjstring_append_format(bjstring_t* that,const char* format,...)
    {
        va_list ap;
        va_start(ap,format);
        bjstring_set_format_va(that,format,ap);
        va_end(ap);
    }/*bjstring_append_format*/



    unsigned int bjstring_substitute_from(bjstring_t* that,
                                          const bjstring_t* match,
                                          const bjstring_t* replacement,
                                          unsigned int from,
                                          unsigned int occurences)
    {
        unsigned int count=0;
        if(occurences==0){
            occurences=UINT_MAX;
        }
        while((occurences!=0)&&(from<that->length-match->length)){
            from=bjstring_search_forward(that,match,from);
            if(from<0){
                return(count);
            }
            count++;
            if(occurences>0){
                occurences--;
            }
            bjstring_delete_from_length(that,from,match->length);
            bjstring_insert_at(that,replacement,from);
            from+=replacement->length;
        }
        return(count);
    }/*bjstring_substitute_from*/




    order_t bjstring_compare(const bjstring_t* that,const bjstring_t* other)
    {
        int cmp;
        if((that==0)||(other==0)){
            return(order_unordered);
        }
        cmp=strcmp(that->data,other->data);
        if(cmp<0){
            return(order_less);
        }else if(cmp==0){
            return(order_equal);
        }else{
            return(order_more);
        }
    }/*bjstring_compare*/


    order_t bjstring_compare_insensitive(const bjstring_t* that,
                                         const bjstring_t* other)
    {
        int cmp;
        if((that==0)||(other==0)){
            return(order_unordered);
        }
        cmp=strcasecmp(that->data,other->data);
        if(cmp<0){
            return(order_less);
        }else if(cmp==0){
            return(order_equal);
        }else{
            return(order_more);
        }
    }/*bjstring_compare_insensitive*/



    bool bjstring_is_prefix(const bjstring_t* that,
                            const bjstring_t* prefix)
    {
        if((that==0)||(prefix==0)){
            return(no);
        }
        return(strncmp(that->data,prefix->data,prefix->length)==0);
    }/*bjstring_is_prefix*/


    bool bjstring_is_prefix_insensitive(const bjstring_t* that,
                                        const bjstring_t* prefix)
    {
        if((that==0)||(prefix==0)){
            return(no);
        }
        return(strncasecmp(that->data,prefix->data,prefix->length)==0);
    }/*bjstring_is_prefix_insensitive*/

    bool bjstring_is_suffix(const bjstring_t* that,
                            const bjstring_t* suffix)
    {
        if((that==0)||(suffix==0)){
            return(no);
        }
        return(strncmp(that->data+that->length-suffix->length,
                       suffix->data,suffix->length)==0);
    }/*bjstring_is_suffix*/


    bool bjstring_is_suffix_insensitive(const bjstring_t* that,
                                        const bjstring_t* suffix)
    {
        if((that==0)||(suffix==0)){
            return(no);
        }
        return(strncasecmp(that->data+that->length-suffix->length,
                           suffix->data,suffix->length)==0);
    }/*bjstring_is_suffix_insensitive*/


/*** bjstring.c                       --                     --          ***/
