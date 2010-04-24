/******************************************************************************
FILE:               BpObject.hh
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This is the root class for all C++ objects.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
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
    
    1992-05-25 <PJB> Creation.
    1992-08-14 <PJB> Added printOn.
    1993-03-16 <PJB> Updated.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

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
#ifndef __BpObject__
#define __BpObject__
extern "C"{
#include <stdio.h>
}
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include PrintOnLevel_hh
class BpClass;
class BpList;

#define BpObject_eDeleteRetained    (10080) // BpObject*,INT32 releaseCount
#define BpObject_eDeleteInternal    (10081) // BpObject*,INT32 condition
#define BpObject_eSubclassResponsibility    (10082) //BpObject*,char* method

#define BpObject_ProcessDeletePool BpObject::processDeletePool
    // Obsolete: call BpObject::processDeletePool();
    
#ifdef MPW
#define BpObject_SUPER SimpleObject
class BpObject:public BpObject_SUPER
#else
#define BpObject_SUPER BpObject
class BpObject
#endif
{
public:

// birth and death:

    CONSTRUCTOR(BpObject)
        /*
            DO:         initialize self.
            POST:       retainCount()=0; this object is in the pool of objects
                        to be deleted. If this is not a temporary object, then
                        the client should send it a retain message.
        */

    DESTRUCTOR(BpObject)
        /*
            DO:         delete this object. Your subclasses should have their
                        own destructor, in which they should release associated
                        objects.
        */


    METHOD(BpObject,makeBrother,(void),BpObject*)
        /*
            RETURN:     a new BpObject.
            NOTE:       this method must be overridden by each sub*-class
                        to make a new instance of the sub*-class.
        */
        
        
// Runtime class management methods:

    /*
        These methods do not need to be overridden, provided that the
        constructor of every sub*-class of BpObject use the BpClass_PLUG
        macro.
    */
    
    METHOD(BpObject,runtimeClass,(void),BpClass*)
    METHOD(BpObject,superClass,(void),BpClass*)
    METHOD(BpObject,className,(void),const char*)
        /*
            RETURN:     a read-only string containing the name of the class.
        */

    METHOD(BpObject,isKindOf,(const BpClass* aClass),BOOLEAN)
    METHOD(BpObject,isKindOfClassNamed,(const char* aClassName),BOOLEAN)
        /*
            RETURN:     this is member of class named aClassName or
                        this is member of a sub*-class of class named
                        aClassName.
        */
        
    METHOD(BpObject,isMemberOf,(const BpClass* aClass),BOOLEAN)
    METHOD(BpObject,isMemberOfClassNamed,(const char* aClassName),BOOLEAN)
        /*
            RETURN:     this is member of class named aClassName.
        */


// Memory management methods:

    METHOD(BpObject,retain,(void),BpObject*)
        /*
            DO:         increment the retain count so that this object will
                        not be deleted.
            RETURN:     this.
        */

    METHOD(BpObject,release,(void),BpObject*)
        /*
            DO:         decrement the retain count. When the retain count
                        becomes null, this object add itself to the pool
                        of object to be deleted.
            RETURN:     this.
        */
    
    METHOD(BpObject,retainCount,(void),INT32)
        /*
            NOTE:       this method should be used for debugging only.
            RETURN:     the retain count for this object.
        */

    CLASSMETHOD(BpObject,processDeletePool,(void),void)
        /*
            NOTE:       Call this once in a while, when we can delete released
                        objects, ie. in the event loop.
        */


// Dependants methods:


    METHOD(BpObject,dependantCount,(void),CARD32)
    METHOD(BpObject,dependantAt,(CARD32 index),BpObject*)
    METHOD(BpObject,dependantAdd,(BpObject* nDependant),void)
    METHOD(BpObject,dependantRemove,(BpObject* nDependant),void)
    METHOD(BpObject,dependantRemoveAt,(CARD32 index),BpObject*)
        /*
            NOTE:       The dependant-dependee relation.
        */
    METHOD(BpObject,selfChanged,(INT32 cause),void)
        /*
            NOTE:       this method should be called by this object
                        every time this object's state changes.
                        
            DO:         foreach i in [0..dependantCount()-1],
                            dependantAt(i)->dependeeChanged(this,cause);
        */
    METHOD(BpObject,dependeeChanged,(BpObject* dependee,INT32 cause),void)
        /*
            NOTE:       this must not remove itself from the dependee's
                        dependant list while running this method.
                        
            NOTE:       this method gets called when the dependee receives
                        a selfChanged message. The interpretation of the
                        cause value depends on the class of the dependee. 
        */
    
    METHOD(BpObject,printOnLevel,(FILE* file,CARD32 level),void)
        /*
            NOTE:       you should override this method, begining with a:
                        SubClass_SUPER::printOnLevel(file,level);  
        */
    METHOD(BpObject,printOn,(FILE* file),void)
        /*
            DO:         prints self on the file.
        */

protected:
    BpClass*        isa;
    INT32           fRetainCount;
    BpList*         fDependants;
};//BpObject



// Debugging. From now on, please use the functions instead of the macros.

#define PRINTONLEVEL_OPEN(file,level,name) \
        PrintOnLevel_open(file,level,#name)

#define PRINTONLEVEL(file,level,format,name,value) \
        PrintOnLevel_printf(file,level,#name,format,value)

#define PRINTONLEVEL2(file,level,format,name,v1,v2) \
        PrintOnLevel_printf(file,level,#name,format,v1,v2)

#define PRINTONLEVEL_ELEMENT(file,level,format,name,index,value) \
        PrintOnLevel_elementPrintf(file,level,#name,index,format,value)

#define PRINTONLEVEL_CLOSE(file,level) \
        PrintOnLevel_close(file,level)

#define BOOLSTR(b) ((b)?"TRUE":"FALSE")
#define NILSTR(b)  ((b)?(b):"NIL")
#define NULLSTR(b) ((b)?(b):"NULL")



#endif


