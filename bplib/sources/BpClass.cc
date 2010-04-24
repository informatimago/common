/******************************************************************************
FILE:               BpClass.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the implementation of the BpClass class.
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
    
    Revision 1.4  1995/11/30 10:31:44  pascal
    Fix apres fusion avec les objets developpes par ERS

    Revision 1.3  95/11/24  16:13:02  pascal
    Added retain/release for isa.
    
    Revision 1.2  95/11/24  14:24:34  pascal
    Corrected constructor; added friend proc BpClass_CreateMetaClasses in
    BpClass.
    
    Revision 1.1  95/11/19  11:14:01  pascal
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
#include <names.h>
#include BpClass_hh
#include BcImplementation_h

    static const char rcsid[]="$Id";
    
// birth and death:

    /*
        The instances must retain their isa BpClass.
        The BpClasses retains their superclass and their factory.
        As a instance, the factories retain their isa BpClass. This set
        up a loop in the retain dependancy that prevent the BpClasses to 
        be freed. This is intentional.      
    */
    
    static BpClass* BpClassClass=NIL;
    
    FRIENDPROC(BpClass_CreateMetaClasses,(void),BpClass*)
    {
            BpClass*        objectClass;

        objectClass=NEW(BpClass);
        BpClassClass=NEW(BpClass);
        
        if(objectClass->isa!=NIL){  // this should not happen.
            objectClass->isa->release();
        }
        objectClass->isa=BpClassClass;
        objectClass->isa->retain();
        objectClass->superClassSet(objectClass);
        
        if(BpClassClass->isa!=NIL){ // this should not happen.
            BpClassClass->isa->release();
        }
        BpClassClass->isa=BpClassClass;     
        BpClassClass->isa->retain();
        BpClassClass->superClassSet(objectClass);
        
        BpClassClass->nameSet("BpClass");
        BpClassClass->factorySet(BpClassClass);
        
        return(objectClass);
    }//BpClass_CreateMetaClasses;


    CONSTRUCTOR(BpClass)
    {
        // No BpClass_PLUG here: it's done by BpClass_CreateMetaClasses,
        // called by BpObject constructor.
        if((isa!=NIL)&&(isa!=(BpClass*)1)){
            isa->release();
        }
        isa=BpClassClass;
        if(isa!=NIL){
            isa->retain();
        }
        fName=NIL;
        fSuperClass=NIL;
        fFactory=NIL;
    }//BpClass;
        
    
    DESTRUCTOR(BpClass)
    {
        if(fFactory!=NIL){
            fFactory->release();
        }
        if(fSuperClass!=NIL){
            fSuperClass->release();
        }
    }//~BpClass;


    METHOD(BpClass,nameSet,(const char* nName),void)
    {
        fName=nName;
    }//nameSet;
    
    
    METHOD(BpClass,superClassSet,(BpClass* nSuper),void)
    {
        if(fSuperClass!=NIL){
            fSuperClass->release();
        }
        fSuperClass=nSuper;
        fSuperClass->retain();
    }//superClassSet;
    
    
    METHOD(BpClass,factorySet,(BpObject* nFactory),void)
    {
        if(fFactory!=NIL){
            fFactory->release();
        }
        fFactory=nFactory;
        fFactory->retain();
    }//factorySet;
    
    
// override of BpObject methods:

    METHOD(BpClass,makeBrother,(void),BpObject*)
    {
        return(NEW(BpClass));
    }//makeBrother;
    
    
    METHOD(BpClass,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpClass_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%s",fName,fName);
        PRINTONLEVEL(file,level,"%p",fSuperClass,fSuperClass);
        PRINTONLEVEL(file,level,"%p",fFactory,fFactory);
    }//printOnLevel;

    
// BpClass methods:

    METHOD(BpClass,name,(void),const char*)
    {
        return(fName);
    }//name;
    
    
    METHOD(BpClass,superClass,(void),BpClass*)
    {
        if(fSuperClass==NIL){
            return(this);
        }else{
            return(fSuperClass);
        }
    }//superClass;
    

    METHOD(BpClass,factory,(void),BpObject*)
    {
        return(fFactory);
    }//factory;
    
    
    METHOD(BpClass,makeInstance,(void),BpObject*)
    {
        return(fFactory->makeBrother());
    }//makeInstance;
    

    METHOD(BpClass,isSubClassOf,(BpClass* aClass),BOOLEAN)
    {
            BpClass*    current;
            BpClass*    next;

        current=this;
        next=current->superClass();
        while((current!=next)&&(current!=aClass)){
            current=next;
            next=current->superClass();
        }
        return(current==aClass);
    }//isSubClassOf;
    
    
    
    PROCEDURE(BpClass_classNamed,(const char* className),BpClass*)
    {
        // SEE: BpClass_classNamed is not implemented.
        /*
            We should use our own hashtable.
        */
        return(NIL);
    }//BpClass_classNamed;
    
    
//END BpClass.
