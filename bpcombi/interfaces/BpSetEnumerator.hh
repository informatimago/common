/******************************************************************************
FILE:               BpSetEnumerator.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the definition of the BpSetEnumerator class.
    This is the abstract class of objects that can enumerate sets (or series) 
    of integer, returned as an array of integer.
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
    Copyright Pascal J. Bourguignon 1996 - 2011
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purposeprovided that this header is always included.
******************************************************************************/
#ifndef __BpSetEnumerator__
#define __BpSetEnumerator__
#include <names.h>
#include BcInterface_h
#include BcTypes_h

class BpSetEnumerator
{
public:
    DESTRUCTOR(BpSetEnumerator)

// BpSetEnumerator methods:

    ABSTRACTMETHOD(BpSetEnumerator,cardinal,(void),CARD32)
        /*
            PRE:        !atBegining()..
            RETURN:     the number of elements enumerated by this object.
        */

    ABSTRACTMETHOD(BpSetEnumerator,index,(void),CARD32)
        /*
            PRE:        !atBegining()..
            RETURN:     the index of the current element enumerated by 
                        this object.
        */

    ABSTRACTMETHOD(BpSetEnumerator,elementSize,(void),CARD32)
        /*
            RETURN:     the size of each element returned by getCurrentElement 
                        and getNextElement in the choice arrays.
        */

    ABSTRACTMETHOD(BpSetEnumerator,reset,(void),void)
        /*
            POST:       atBegining().
            DO:         resets the enumeration.
        */

    ABSTRACTMETHOD(BpSetEnumerator,atBegining,(void),BOOLEAN)
        /*
            RETURN:     whether the reset() method has been called and 
                        getNextElement() (or getCurrentElement()) has not 
                        already been called. 
        */

    ABSTRACTMETHOD(BpSetEnumerator,getCurrentElement,(CARD32* choice),void)
        /*
            PRE:        cardinal()>0.
            POST:       !atBegining(),
                        choice[0]...choice[elementSize()-1] are set.
            DO:         Sets the choice array to the current enumerated 
                        element. (ie. the last element retrived with the 
                        getNextElement method). The choice array must contain 
                        at least elementSize() integers.
        */

    ABSTRACTMETHOD(BpSetEnumerator,getNextElement,(CARD32* choice),BOOLEAN)
        /*
            PRE:        cardinal()>0, !done(), atBegining()=b, 
                        (!b => index()=a).
            POST:       !atBegining(), (!b => index()=a+1),
                        choice[0]...choice[elementSize()-1] are set.
            DO:         Computes the next element to be enumerated and sets the
                        choice array to it. It returns TRUE when the last 
                        element is retrived, ie. all elements have been 
                        enumerated. The choice array must contain at least 
                        elementSize() integers.
        */

    ABSTRACTMETHOD(BpSetEnumerator,done,(void),BOOLEAN)
        /*
            RETURN:     !atBegining() 
                        && ((cardinal()=0) || (index()=cardinal())).
        */
};

#endif // BpSetEnumerator.

/*** BpSetEnumerator.hh               --                     --          ***/
