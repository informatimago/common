/******************************************************************************
FILE:               BpArrangementWithRepeat.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the definition of the BpArrangementWithRepeat class.
    This class blah_blah_blah.
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
#ifndef __BpArrangementWithRepeat__
#define __BpArrangementWithRepeat__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpSetFunctor_hh

#define BpArrangementWithRepeat_SUPER BpSetFunctor
class BpArrangementWithRepeat:public BpArrangementWithRepeat_SUPER
{
public:
// birth and death:

    CONSTRUCTOR(BpArrangementWithRepeat)
    DESTRUCTOR(BpArrangementWithRepeat)

// BpObject methods:

    METHOD(BpArrangementWithRepeat,makeBrother,(void),BpObject*)
    METHOD(BpArrangementWithRepeat,printOnLevel,(FILE* file,CARD32 level),void)

// BpSetEnumerator methods:

    METHOD(BpArrangementWithRepeat,done,(void),BOOLEAN)
    
protected:

// BpSetFunctor methods:

    METHOD(BpArrangementWithRepeat,computeCardinal,(void),void)
    METHOD(BpArrangementWithRepeat,initialize,(void),void)
    METHOD(BpArrangementWithRepeat,next,(void),void)
};

#endif // BpArrangementWithRepeat.

/*** BpArrangementWithRepeat.hh       --                     --          ***/
