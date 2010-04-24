/******************************************************************************
FILE:               BpSetFunctor.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the definition of the BpSetFunctor class.
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
#ifndef __BpSetFunctor__
#define __BpSetFunctor__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh
#include BpSetEnumerator_hh

#define BpSetFunctor_SUPER BpObject
class BpSetFunctor:public BpSetFunctor_SUPER, public BpSetEnumerator
{
public:
// birth and death:

    CONSTRUCTOR(BpSetFunctor)
    DESTRUCTOR(BpSetFunctor)

        
// BpObject methods:

    METHOD(BpSetFunctor,makeBrother,(void),BpObject*)
    METHOD(BpSetFunctor,printOnLevel,(FILE* file,CARD32 level),void)


// BpSetEnumerator methods:

    METHOD(BpSetEnumerator,cardinal,(void),CARD32)
    METHOD(BpSetEnumerator,index,(void),CARD32)
    METHOD(BpSetEnumerator,elementSize,(void),CARD32)
    METHOD(BpSetEnumerator,reset,(void),void)
    METHOD(BpSetEnumerator,atBegining,(void),BOOLEAN)
    METHOD(BpSetEnumerator,getCurrentElement,(CARD32* choice),void)
    METHOD(BpSetEnumerator,getNextElement,(CARD32* choice),BOOLEAN)

// BpSetFunctor methods:



    METHOD(BpSetFunctor,baseCardinal,(void),CARD32)
        /*
            RETURN:     the cardinal of the base set.
        */

    METHOD(BpSetFunctor,baseCardinal,(CARD32 card),void)
        /*
            PRE:        c=card.
            POST:       baseCardinal()=c.
            DO:         informs this about the number of elements in the set of 
                        which this is function.
        */

    METHOD(BpSetFunctor,elementSize,(CARD32 size),void)
        /*
            PRE:        s=size.
            POST:       elementSize()=s. 
            DO:         Sets the elementSize() parameter.
        */

protected:
    ABSTRACTMETHOD(BpSetFunctor,computeCardinal,(void),void)
        /*
            NOTE:       It must be overriden by subclasses to compute the
                        _cardinal from the _baseCardinal and the _elementSize
                        attributes.
        */
    ABSTRACTMETHOD(BpSetFunctor,initialize,(void),void)
        /*
            NOTE:       It must be overriden by subclasses to initialize the 
                        enumeration. It must compute the _cardinal, and set 
                        the_index either to 0 or to _cardinal. If
                        _index != _cardinal then the choice array must be 
                        set to the first enumerated element.
        */

    ABSTRACTMETHOD(BpSetFunctor,next,(void),void)
        /*
            NOTE:       It must be overriden by subclasses to step to the next 
                        element of the enumeration. If _index<_cardinal, then 
                        it must increment _index ; if _index¹_cardinal then the 
                        choice array must be set to the first enumerated 
                        element.
        */

    CARD32          _baseCardinal;
    CARD32          _cardinal;
    CARD32          _index;
    CARD32          _elementSize;
    CARD32*         _choice;
    BOOLEAN         _atBegining;
};

#endif // BpSetFunctor.

/*** BpSetFunctor.hh                  --                     --          ***/
