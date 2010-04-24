/******************************************************************************
FILE:               BpArrangementSansRepeat.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the definition of the BpArrangementSansRepeat class.
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
#ifndef __BpArrangementSansRepeat__
#define __BpArrangementSansRepeat__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpSetFunctor_hh

#define BpArrangementSansRepeat_SUPER BpSetFunctor
class BpArrangementSansRepeat:public BpArrangementSansRepeat_SUPER
{
public:
// birth and death:

    CONSTRUCTOR(BpArrangementSansRepeat)
    DESTRUCTOR(BpArrangementSansRepeat)

// BpObject methods:

    METHOD(BpArrangementSansRepeat,makeBrother,(void),BpObject*)
    METHOD(BpArrangementSansRepeat,printOnLevel,(FILE* file,CARD32 level),void)

// BpSetEnumerator methods:

    METHOD(BpArrangementSansRepeat,done,(void),BOOLEAN)
    
protected:

// BpSetFunctor methods:

    METHOD(BpArrangementSansRepeat,computeCardinal,(void),void)
    METHOD(BpArrangementSansRepeat,initialize,(void),void)
    METHOD(BpArrangementSansRepeat,next,(void),void)

// BpArrangementSansRepeat methods:

    METHOD(BpArrangementSansRepeat,step,(CARD32 k),void)

    BOOLEAN         _done;
    BOOLEAN*        _taken;
};

#endif // BpArrangementSansRepeat.

/*** BpArrangementSansRepeat.hh       --                     --          ***/
