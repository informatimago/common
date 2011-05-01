/******************************************************************************
FILE:               bjobject.h
LANGUAGE:           ANSI-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This module encapsulate a generic object.

    Well  actually,  what  is  implemented  is  only  a  quite-generic
    allocator with reference counter.

    Instead of using malloc, and having to remember when to call free,
    we  use bjobject_new(),  and  the object  will be  "automatically"
    deallocated when the it will not be used anymore.

    To know when a object is  used, the "object" object use it must call
    bjobject_retain(),    and   when    it's    finished   with    it,
    bjobject_release().    These    functions   maintain   a   "retain
    count". When this retain count becomes 0, the object is added to a
    list of object to be delete.

    However,  they're not deleted  until bjobject_delete_the_objects()
    is  called, which is  usually done  in the  event loop,  for event
    driven applications.

    By default, when created the objects  have a retain count of 0 and
    may  be  deleted by  bjobject_delete_the_objects(),  which is  the
    setting  for temporary  objects. If  the new  object must  be kept
    arround, bjobject_retain must be called.

    Since the objects are deleted by bjobject_delete_the_objects(), in
    a  way unrelated  to the  environment where  they were  created, a
    clean up  function is needed  before actually deleting  them. It's
    the role  of the delete  function given in  the bjobject_methods_t
    structure.

    These delete  functions usually only call  bjobject_relaese on the
    objects object were referenced by the object being deleted.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
    2003-12-03 <PJB> Added order_smaller,order_same,and order_greater.
    2001-03-15 <PJB> Added comments.
    2000-12-19 <PJB> Integrated with AvMailGate.

        Revision 1.10  96/07/25  06:14:31  pascal
        *** empty log message ***

        Revision 1.9  95/11/30  10:31:40  pascal
        Fix apres fusion avec les objets developpes par ERS

        Revision 1.8  95/11/23  03:48:44  pascal
        Added BpClass and runtime class support in BpObject.
        Updated subclasses.

        Added dependant/dependee in BpObject.

        Revision 1.7  95/11/16  12:19:24  pascal
        Small corrections to compile on MSVC.

        Revision 1.6  95/11/16  07:00:12  pascal
        Added BpObject_eSubclassResponsibility exception.

        Revision 1.5  95/10/22  03:19:53  pascal
        Setting revision name V1.

        Revision 1.2  95/10/22  03:05:16  pascal
        Modifications while adding BpDict.

    1993/03/19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                    "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1993/03/16 <PJB> Updated.
    1992/08/14 <PJB> Added printOn.
    1992/05/25 <PJB> Creation.
BUGS
    No check is done for out of memory errors.
LEGAL
    GPL
    
    Copyright Pascal J. Bourguignon 1992 - 2011
    
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
#ifndef bjobject_h
#define bjobject_h

typedef enum { no,
               yes } bool;

typedef enum { order_smaller=-1,
               order_less=-1,
               order_equal=0,
               order_same=0,
               order_more=1,
               order_greater=1,
               order_unordered=2 } order_t;

typedef struct {
    const char* class_name;
    void (*delete)(void* object);
}       bjobject_methods_t;

extern void bjobject_initialize(void);

extern void* bjobject_new(unsigned int size,const bjobject_methods_t* methods);
    /*
        NOTE:   methods==0 ==> a default destructor is used,
                               and bjobject_class_name returns "bjobject".
        POST:   bjobject_retain_count(bjobject_new(x,y))==0, which means that
                the newly created object will be deleted by
                bjobject_delete_the_objects unless somebody calls bjobject_retain.
                (Objects are created temporary).
    */

extern const char* bjobject_class_name(void* object);
    /*
        RETURN: The class_name specified in the methods given when creating
                this object.
    */

extern void bjobject_retain(void* object);
    /*
        NOTE:   We don't modify the object, only it's retain count which is
                stored just before it.
        DO:     Increment the retain count of this object. This will prevent
                deleting this object (by bjobject_delete_the_objects()).
    */

extern void bjobject_release(void* object);
    /*
        NOTE:   We don't modify the object, only it's retain count which is
                stored just before it. However, this could lead to its deleting!!!
        DO:     Decrement the retain count of this object. If the release count
                reach 0
    */

extern int bjobject_retain_count(void* object);
    /*
        RETURN: The retain count for the object,
                = number of retain - number of release.
    */

extern void bjobject_delete_the_objects(void);
    /*
        DO:     Delete all the objects whose retain count is not strictly 
                positive.  Should call this function in the main loop, 
                or at other strategical places where garbage-collection 
                can be done.
    */

extern const bjobject_methods_t* bjobject_methods(void* object);
    /*
        RETURN: The method record for the object.
    */

extern void bjobject_set_methods(void* object,const bjobject_methods_t* methods);
    /*
        DO:     Change the method record of the object.
    */

#endif
/*** bjobject.h                       -- 2003-12-03 18:30:37 -- pascal   ***/
