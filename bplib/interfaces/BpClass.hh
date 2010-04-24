/******************************************************************************
FILE:               BpClass.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the definition of the BpClass class.
    This class represent the BpObject sub*-classes at runtime.
    The current implementation only implements the inheritance hierarchy,
    and may be used to dynamically check membership or kindship, or to 
    dynamically intanciate these classes.
    The use of this class outdates the need for the className() method that
    needed to be overridden by sub*-classes of BpObject, but needs the 
    overriding of the makeBrother method.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.6  95/11/30  10:31:37  pascal
    Fix apres fusion avec les objets developpes par ERS
    
    Revision 1.5  95/11/25  09:26:18  pascal
    Removed virtual inheritance.
    
    Revision 1.4  95/11/25  09:24:22  pascal
    Added virtual inheritance for MetaObject.
    
    Revision 1.3  95/11/24  16:14:28  pascal
    Added retain/release for isa.
    
    Revision 1.2  95/11/24  14:19:56  pascal
    Corrected BpClass_PLUG and constructor.
    
    Revision 1.1  95/11/19  11:13:17  pascal
    Initial revision
    
    1995-11-19 <PJB> Creation. 
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
#ifndef __BpClass__
#define __BpClass__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh

#define BpClass_SUPER BpObject
class BpClass:public BpClass_SUPER
{
public:
// birth and death:

    CONSTRUCTOR(BpClass)
    DESTRUCTOR(BpClass)

    // These methods can be called only by the constructors, thru BcClass_PLUG.
    METHOD(BpClass,nameSet,(const char* nName),void)
    METHOD(BpClass,superClassSet,(BpClass* nSuper),void)
    METHOD(BpClass,factorySet,(BpObject* nFactory),void)
    
// override of BpObject methods:

    METHOD(BpClass,makeBrother,(void),BpObject*)
    METHOD(BpClass,printOnLevel,(FILE* file,CARD32 level),void)

// BpClass methods:

    METHOD(BpClass,name,(void),const char*) 
    METHOD(BpClass,superClass,(void),BpClass*)
    METHOD(BpClass,factory,(void),BpObject*)
    METHOD(BpClass,makeInstance,(void),BpObject*)
    
    METHOD(BpClass,isSubClassOf,(BpClass* aClass),BOOLEAN)
        /*
            RETURN:     aClass is a super class of this class, or of a super
                        class of this class.
            NOTE:       to test direct superClass use:
                            (aClass==this->superClass())
        */
    
protected:
    const char*     fName;
    BpClass*        fSuperClass;
    BpObject*       fFactory;
    FRIENDPROC(BpClass_CreateMetaClasses,(void),BpClass*)
};


/*
    In each constructor of subclasses of BpObject, use this macro
    to initialize the BpClass instance associated to the constructed
    object:
        BpClass_PLUG(TheClassName);

    WARNING:    BpClass::BpClass() does not use this macro. When modifying
                BpClass_PLUG, check BpClass::BpClass().
*/

#define BpClass_PLUG(className)                             \
    {                                                       \
        static BpClass* className##Class=(BpClass*)NIL;     \
        if(className##Class==NIL){                          \
            className##Class=NEW(BpClass);                  \
            className##Class->nameSet(#className);          \
            className##Class->superClassSet(isa);           \
            className##Class->factorySet(NEW(className));   \
        }                                                   \
        isa->release();                                     \
        isa=className##Class;                               \
        isa->retain();                                      \
    }
//end BpClass_PLUG

#define BpClass_PLUG_ABSTRACT(className)                    \
    {                                                       \
        static BpClass* className##Class=(BpClass*)NIL;     \
        if(className##Class==NIL){                          \
            className##Class=NEW(BpClass);                  \
            className##Class->nameSet(#className);          \
            className##Class->superClassSet(isa);           \
        }                                                   \
        isa->release();                                     \
        isa=className##Class;                               \
        isa->retain();                                      \
    }
//end BpClass_PLUG_ABSTRACT


    PROCEDURE(BpClass_classNamed,(const char* className),BpClass*)
        /*
            RETURN:     if there is a class named className then return it,
                        else return NIL.
            NOTE:       Not implemented yet.
        */





#endif // BpClass.
