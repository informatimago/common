/******************************************************************************
FILE:               BpCombination.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the definition of the BpCombination class.
    This class enumerate the set of the parts of E containing n elements.
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
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef __BpCombination__
#define __BpCombination__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpSetFunctor_hh

#define BpCombination_SUPER BpSetFunctor
class BpCombination:public BpCombination_SUPER
{
public:
// birth and death:

    CONSTRUCTOR(BpCombination)
    DESTRUCTOR(BpCombination)

// BpObject methods:

    METHOD(BpCombination,makeBrother,(void),BpObject*)
    METHOD(BpCombination,printOnLevel,(FILE* file,CARD32 level),void)

// BpSetEnumerator methods:

    METHOD(BpCombination,done,(void),BOOLEAN)
    
protected:

// BpSetFunctor methods:

    METHOD(BpCombination,computeCardinal,(void),void)
    METHOD(BpCombination,initialize,(void),void)
    METHOD(BpCombination,next,(void),void)

};

#endif // BpCombination.

/*** BpCombination.hh                 --                     --          ***/
