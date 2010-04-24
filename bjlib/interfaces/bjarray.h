/******************************************************************************
FILE:               bjarray.h
LANGUAGE:           ANSI-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This module encapsulate an array object.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2001-03-16 <PJB> Added bjarray_copy_from_length and bjarray_append.
    2001-03-15 <PJB> Added comments.
    2000-12-26 <PJB> Integrated with AvMailGate.
    2000-09-20 <PJB> Created.
BUGS
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon     2000 - 2001
    
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
#ifndef bjarray_h
#define bjarray_h


typedef struct {
    unsigned int    size;   /* allocated slots. */
    unsigned int    count;  /* 1+idx of last non null element */
    void**          elements;
}       bjarray_t;


extern bjarray_t* bjarray_new(unsigned int size);
    /*
        RETURN: A new array of capacity `size'.
    */

extern unsigned int bjarray_size(const bjarray_t* that);
    /*
        RETURN: The size of the array, that is, it's capacity.
    */

extern unsigned int bjarray_count(const bjarray_t* that);
    /*
        RETURN: The count of elements,
                that is, 1+the idx of the last non null element.
    */

extern void bjarray_set_size(bjarray_t* that,unsigned int newSize);
    /*
        DO:     Change the capacity of the array. If newSize<bjarray_size(that),
                then some elements may be removed from the array, otherwise all
                the elements are kept.
    */

extern void* bjarray_element_at(const bjarray_t* that,unsigned int idx);
    /*
        RETURN: The element at the idx.
    */

extern void* bjarray_set_element_at(bjarray_t* that,unsigned int idx,
                                    void* element);
    /*
        DO:     Replace the element at `idx' by `element'.
        RETURN: The previous element that was at `idx'.
    */

extern void bjarray_insert_element_at(bjarray_t* that,unsigned int idx,
                                      void* element);
    /*
        DO:     Move up all the elements from `idx' to the end of the array,
                and set `element' as the new element at `idx'. The last element
                of the array is removed.
    */

extern void* bjarray_remove_element_at(bjarray_t* that,unsigned int idx);
    /*
        DO:     Remove the element at `idx', and moves down all the elements
                from idx+1 to the end. Nil is put at the last position.
        RETURN: The previous element that was at `idx'.
    */


extern void bjarray_add_element(bjarray_t* that,void* element);
    /*
        DO:     Put the `element' at the position
                just after the last non empty position
                (at idx bjarray_count(that)).
                If size<=count then the size is duplicated.
        NOTE:   The array does not modify the element ; it only increments
                its retain count, which is stored before the element...
    */


extern void bjarray_copy_from_length(bjarray_t* that,
                                     const bjarray_t* source,
                                     unsigned int idx,unsigned int copylen);
    /*
        DO:     Replace all the elements of that by the elements found from
                idx to idx+copylen-1 in source.
        POST:   for all i in 0 .. copylen-1,
                    bjarray_element_at(that,i)==bjarray_element_at(source,idx+i),
                for all i in copylen .. bjarray_size(that)-1,
                    bjarray_element_at(that,i)==0,
                bjarray_count(that)=max(0,bjarray_count(source)-idx).
    */

extern void bjarray_remove_from_length(bjarray_t* that,
                                       unsigned int idx,unsigned int delen);
    /*
        DO:     Remove the elements from idx to idx+delen-1 from that array,
                moving the elements from idx+delen and up downto idx.
    */

extern void bjarray_append(bjarray_t* that,const bjarray_t* tail);
    /*
        DO:     Append the elements from tail to that array (from the position
                after the last non nil entry in that).
        PRE:    bjarray_count(that)==c,
                for all i in 0 .. c-1, bjarray_element_at(that,i)==e[i].
        POST:   for all i in 0 .. c-1, bjarray_element_at(that,i)==e[i],
                for all i in c .. c+bjarray_count(tail)-1,
                    bjarray_element_at(that,i)==bjarray_element_at(source,idx+i),
                bjarray_count(that)==c+bjarray_count(tail)
    */

extern short bjarray_check_invariant(const bjarray_t* that);

#endif
/*** bjarray.h                        -- 2003-12-03 18:38:46 -- pascal   ***/
