/******************************************************************************
FILE:               BpSetFunctor.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the implementation of the BpSetFunctor class.
    This is the abstract class of sets or series of integer that are function 
    of another set  of integer.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2003/12/04 03:36:54  pjbpjb
    Cleaned-up.
    Moved bc*.[hc] in bclib.
    Fix.

    Revision 1.1  2002/08/11 04:12:17  pascal
    Updated with changes from MAPTREE on bclib/bplib/makedir.
    
    1996/08/04 <PJB> Creation. 
LEGAL
    Copyright Pascal J. Bourguignon 1996 - 1996
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#include <names.h>
#include BpSetFunctor_hh
#include BpClass_hh
#include BcImplementation_h

    static const char rcsid[]="$Id";

// birth and death:

    CONSTRUCTOR(BpSetFunctor)
    {
        BpClass_PLUG_ABSTRACT(BpSetFunctor);
        _baseCardinal=0;
        _cardinal=0;
        _index=0;
        _elementSize=0;
        _choice=NIL;
        _atBegining=FALSE;
    }//BpSetFunctor;
        
    
    DESTRUCTOR(BpSetFunctor)
    {
        DELETE(_choice);    // valid even when choice==NIL.
    }//~BpSetFunctor;


// BpObject methods:

    METHOD(BpSetFunctor,makeBrother,(void),BpObject*)
    {
        return(NIL/* ABSTRACT CLASS !  NEW(BpSetFunctor) */);
    }//className;


    METHOD(BpSetFunctor,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpSetFunctor_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%ul",_baseCardinal,_baseCardinal);
        PRINTONLEVEL(file,level,"%ul",_cardinal,_cardinal);
        PRINTONLEVEL(file,level,"%ul",_index,_index);
        PRINTONLEVEL(file,level,"%ul",_elementSize,_elementSize);
        PRINTONLEVEL(file,level,"%s",_atBegining,BOOLSTR(_atBegining));
        if(_choice==NIL){
            PRINTONLEVEL(file,level,"%p",_choice,_choice);
        }else{
                CARD32 i;
            PRINTONLEVEL_OPEN(file,level,_choice);
            for(i=0;i<_elementSize;i++){
                PRINTONLEVEL_ELEMENT(file,level,"%ul",_choice,i,_choice[i]);
            }
            PRINTONLEVEL_CLOSE(file,level);
        }
    }//printOnLevel;

    
// BpSetFunctor methods:

    METHOD(BpSetFunctor,cardinal,(void),CARD32)
    {
        return(_cardinal);
    }//cardinal;
    

    METHOD(BpSetFunctor,index,(void),CARD32)
    {
        return(_index);
    }//index;
    

    METHOD(BpSetFunctor,elementSize,(void),CARD32)
    {
        return(_elementSize);
    }//elementSize;
    

    METHOD(BpSetFunctor,reset,(void),void)
    {
        computeCardinal();
        delete(_choice);
        _choice=new CARD32[_cardinal];
        initialize();
        _atBegining=TRUE;
    }//reset;
    

    METHOD(BpSetFunctor,atBegining,(void),BOOLEAN)
    {
        return(_atBegining);
    }//atBegining;
    

    METHOD(BpSetFunctor,getCurrentElement,(CARD32* choice),void)
    {
            CARD32      i;
        
        if(_cardinal>0){
            _atBegining=FALSE;
            for(i=0;i<_elementSize;i++){
                choice[i]=_choice[i];
            }
        }
    }//getCurrentElement;
    

    METHOD(BpSetFunctor,getNextElement,(CARD32* choice),BOOLEAN)
    {
        if((_cardinal>0)&&(!done())){
            if(_atBegining){
                _atBegining=FALSE;
            }else{
                next();
            }
            getCurrentElement(choice);
            return(done());
        }else{
            return(FALSE);
        }
    }//getNextElement;
    


// BpSetFunctor methods:

    METHOD(BpSetFunctor,baseCardinal,(void),CARD32)
    {
        return(_baseCardinal);
    }//baseCardinal;
    

    METHOD(BpSetFunctor,baseCardinal,(CARD32 card),void)
    {
        if(_baseCardinal!=card){
            _baseCardinal=card;
            _cardinal=0;
        }
    }//baseCardinal;
    

    METHOD(BpSetFunctor,elementSize,(CARD32 size),void)
    {
        if(_elementSize!=size){
            _elementSize=size;
            _cardinal=0;
        }
    }//elementSize;
    

//END BpSetFunctor.

/*** BpSetFunctor.cc                  --                     --          ***/
