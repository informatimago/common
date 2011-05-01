    /******************************************************************************
FILE:               bjobject.c
LANGUAGE:           ANSI-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This module encapsulate a generic object.

AUTHORS
    <PJB> Pascal J. Bourguignon <pjb@informatimago.com>
MODIFICATIONS
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
#include <stdlib.h>
#ifdef USE_PTHREAD
#include <pthread.h>
#endif
#ifdef TRACE_RETAINS
#include <stdio.h>
#include <unistd.h>
#endif

#include <bjobject.h>


    /* For version & component control: */
    const char bjobject_id[]=
    "$Id: bjobject.c,v 1.2 2006/05/27 21:32:06 pupjb Exp $";

    typedef struct {
        const bjobject_methods_t*   methods;
        int                         retain_count;
        int                         data[1];
    }                           bjobject_t;

    /* ---------------------------------------------------------------------- */

    typedef struct bcpurgatory_t {
        int                     size;
        int                     count;
        bjobject_t**            objects;
        bjobject_t**            deads;
    }                       bcpurgatory_t;


    static void bjobject_delete(void* object);
    static bcpurgatory_t* bcpurgatory_new(void);
#ifdef USE_PTHREAD
    static void bcpurgatory_delete(bcpurgatory_t* that);
#endif
    static void bcpurgatory_add_object(bcpurgatory_t* that,
                                       bjobject_t* object);
    static void bcpurgatory_remove_object(bcpurgatory_t* that,
                                          bjobject_t* object);
    static void bcpurgatory_delete_objects(bcpurgatory_t* that);


    static bcpurgatory_t* bcpurgatory_new(void)
    {
        bcpurgatory_t* that;
        that=(bcpurgatory_t*)malloc(sizeof(*that));
        that->count=0;
        that->size=256;
        that->objects=(bjobject_t**)malloc(sizeof(*(that->objects))*(size_t)(that->size));
        return(that);
    }/*bcpurgatory_new*/


#ifdef TRACE_OBJECTS
    static void bcpurgatory_delete(bcpurgatory_t* that)
    {
        bcpurgatory_delete_objects(that);
        free(that->objects);
        free(that);
    }/*bcpurgatory_delete*/


    static void bcpurgatory_delete_but_not_objects(bcpurgatory_t* that)
    {
        free(that->objects);
        free(that);
    }/*bcpurgatory_delete_but_not_objects*/
#endif

    static void bcpurgatory_add_object(bcpurgatory_t* that,
                                       bjobject_t* object)
    {
        if(that->count>=that->size){
            bjobject_t**       objects;
            int                 i;
            that->size*=2;
            objects=(bjobject_t**)malloc(sizeof(*objects)*(size_t)(that->size));
            for(i=0;i<that->count;i++){
                objects[i]=that->objects[i];
            }
            free(that->objects);
            that->objects=objects;
        }
        that->objects[that->count++]=object;
    }/*bcpurgatory_add_object*/


    static void bcpurgatory_remove_object(bcpurgatory_t* that,
                                          bjobject_t* object)
    {
        int i;
        /* Soyons optimiste, object devrait etre dans la liste. */
        i=that->count;
        while(i>0){
            i--;
            if(that->objects[i]==object){
                that->count--;
                while(i<that->count){
                    that->objects[i]=that->objects[i+1];
                    i++;
                }
                return;
            }
        }
    }/*bcpurgatory_remove_object*/


    static void bcpurgatory_delete_objects(bcpurgatory_t* that)
    {
        int i;
        for(i=0;i<that->count;i++){
            bjobject_delete(&(that->objects[i]->data));
        }
        that->count=0;
    }/*bcpurgatory_delete_objects*/





    /* ---------------------------------------------------------------------- */

    typedef struct {
        bcpurgatory_t*   to_delete;
        bcpurgatory_t*   to_delete_2;
#ifdef TRACE_OBJECTS
        bcpurgatory_t*   instances;
#endif
    }                       bjobject_globals_t;


#ifdef USE_PTHREAD
    static pthread_key_t    bjobject_key;
#endif

    static bjobject_globals_t* globals(void)
    {
#ifdef USE_PTHREAD
        bjobject_the_globals_t* the_globals=pthread_getspecific(bjobject_key);
#else
        static bjobject_globals_t* the_globals=0;
#endif
        if(the_globals==0){
            the_globals=(bjobject_globals_t*)malloc(sizeof(*the_globals));
            the_globals->to_delete=bcpurgatory_new();
            the_globals->to_delete_2=bcpurgatory_new();
#ifdef TRACE_OBJECTS
            the_globals->instances=bcpurgatory_new();
#endif
#ifdef USE_PTHREAD
            pthread_setspecific(bjobject_key,the_globals);
#endif
        }
        return(the_globals);
    }/*globals*/

#ifdef USE_PTHREAD
    static void bjobject_global_delete(void* glob)
    {
        bjobject_globals_t* globals=glob;
        bjobject_delete_the_objects();
        bcpurgatory_delete(globals->to_delete);
        bcpurgatory_delete(globals->to_delete_2);
#ifdef TRACE_OBJECTS
        bcpurgatory_delete_but_not_objects(globals->instances);
#endif
    }/*bjobject_global_delete*/
#endif

    /* ---------------------------------------------------------------------- */

#define v2o(v) ((bjobject_t*)(((char*)v)-((char*)(&(((bjobject_t*)0)->data)))))

    void bjobject_initialize(void)
    {
#ifdef USE_PTHREAD
        pthread_key_create(&bjobject_key,bjobject_global_delete);
#endif
    }/*bjobject_initialize*/


    static void delete_nop(void* object)
    {
#ifdef TRACE_OBJECTS
        bjobject_t* that=v2o(object);
        bcpurgatory_remove_object(globals()->instances,that)
#endif
        /* NOP */
        }/*delete_nop*/

    static bjobject_methods_t nop_methods={ "bjobject", delete_nop };


    void* bjobject_new(unsigned int size,const bjobject_methods_t* methods)
    {
        if(size<0){
            return(0);
        }else{
            bjobject_t* that=(bjobject_t*)malloc(sizeof(bjobject_t)
                                                 -sizeof(that->data)+size);
            that->retain_count=0;
            if(methods==0){
                methods=&nop_methods;
            }
            that->methods=methods;
            bcpurgatory_add_object(globals()->to_delete,that);
#ifdef TRACE_OBJECTS
            bcpurgatory_add_object(globles()->instances,that);
#endif
#ifdef TRACE_RETAINS
            fprintf(stderr,
                    "%5d:CREATE    %08x:%08x [%6d] %3d ((%s_t*)0x%08x)\n",
                    getpid(),(int)(&(that->data)),(int)(that->methods),
                    size,that->retain_count,
                    that->methods->class_name,(int)that);
#endif
            return(&(that->data));
        }
    }/*bjobject_new*/


    const char* bjobject_class_name(void* object)
    {
        if(object==0){
            return("nil");
        }
        return(bjobject_methods(object)->class_name);
    }/*bjobject_class_name*/


    void bjobject_delete_the_objects(void)
    {
        int c;
        bjobject_globals_t*       glob=globals();
        bcpurgatory_t*   swap;
        c=glob->to_delete->count;
        while(c>0){
            swap=glob->to_delete;
            glob->to_delete=glob->to_delete_2;
            glob->to_delete_2=swap;
            bcpurgatory_delete_objects(glob->to_delete_2);
            c=glob->to_delete->count;
        }
    }/*bjobject_delete_the_objects*/


    static void bjobject_delete(void* object)
    {
        bjobject_t* that=v2o(object);
        if(object==0){
            return;
        }
#ifdef TRACE_RETAINS
        fprintf(stderr,
                "%5d:DELETE    %08x:%08x          %3d ((%s_t*)0x%08x)\n",
                getpid(),(int)object,(int)(that->methods),
                that->retain_count,that->methods->class_name,(int)that);
#endif
        that->methods->delete(object);
        free(that);
    }/*bjobject_delete*/


    void bjobject_retain(void* object)
    {
        bjobject_t* that=v2o(object);
        if(object==0){
            return;
        }
        that->retain_count++;
#ifdef TRACE_RETAINS
        fprintf(stderr,
                "%5d:RETAIN    %08x:%08x          %3d ((%s_t*)0x%08x)\n",
                getpid(),(int)object,(int)(that->methods),
                that->retain_count,that->methods->class_name,(int)that);
#endif
        if(that->retain_count==1){
            bcpurgatory_remove_object(globals()->to_delete,that);
        }
    }/*bjobject_retain*/


    void bjobject_release(void* object)
    {
        bjobject_t* that=v2o(object);
        if(object==0){
            return;
        }
        that->retain_count--;
#ifdef TRACE_RETAINS
        fprintf(stderr,
                "%5d:RELEASE   %08x:%08x          %3d ((%s_t*)0x%08x)\n",
                getpid(),(int)object,(int)(that->methods),
                that->retain_count,that->methods->class_name,(int)that);
        if(that->retain_count<0){ int i=0;i=1/i; }
#endif
        if(that->retain_count==0){
            bcpurgatory_add_object(globals()->to_delete,that);
        }
    }/*bjobject_release*/


    int bjobject_retain_count(void* object)
    {
        bjobject_t* that=v2o(object);
        if(object==0){
            return(0);
        }
        return(that->retain_count);
    }/*bjobject_retain_count*/


    const bjobject_methods_t* bjobject_methods(void* object)
    {
        bjobject_t* that=v2o(object);
        if(object==0){
            return(0);
        }
        return(that->methods);
    }/*bjobject_methods*/


    void bjobject_set_methods(void* object,
                              const bjobject_methods_t* methods)
    {
        bjobject_t* that=v2o(object);
        if(object==0){
            return;
        }
        that->methods=methods;
    }/*bjobject_set_methods*/




    /*** bjobject.c                       -- 2004-01-01 09:40:55 -- pascal   ***/
