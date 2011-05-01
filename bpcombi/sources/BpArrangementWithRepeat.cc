/******************************************************************************
FILE:               BpArrangementWithRepeat.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the implementation of the BpArrangementWithRepeat class.
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
    Copyright Pascal J. Bourguignon 1996 - 2011
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#include <names.h>
#include BpArrangementWithRepeat_hh
#include BpClass_hh
#include BcImplementation_h

    static const char rcsid[]="$Id";

// birth and death:

    CONSTRUCTOR(BpArrangementWithRepeat)
    {
        BpClass_PLUG(BpArrangementWithRepeat);
        
    }//BpArrangementWithRepeat;
        
    
    DESTRUCTOR(BpArrangementWithRepeat)
    {
    }//~BpArrangementWithRepeat;


// BpObject methods:

    METHOD(BpArrangementWithRepeat,makeBrother,(void),BpObject*)
    {
        return(NEW(BpArrangementWithRepeat));
    }//className;


    METHOD(BpArrangementWithRepeat,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpArrangementWithRepeat_SUPER::printOnLevel(file,level);
    //  PRINTONLEVEL(file,level,"%FORMAT",NEWFIELD,NEWFIELD);
    }//printOnLevel;

    
// BpSetEnumerator methods:

    METHOD(BpArrangementWithRepeat,done,(void),BOOLEAN)
    {
            CARD32      i;
        i=_elementSize-1;
        while(i>0){
            if(_choice[i]!=0){
                return(FALSE);
            }
            i--;
        }
        return(_choice[0]==_baseCardinal);
    }//done;
    


// BpSetFunctor methods:

    CARD32 power(CARD32 x,CARD32 exponent)
    {
            CARD32      r;
        r=1;
        while(exponent>0){
            if((exponent&1)==0){
                x*=x;
                exponent/=2;
            }else{
                r*=x;
                exponent--;
            }
        }
        return(r);
    }//power;
    
    
    METHOD(BpArrangementWithRepeat,computeCardinal,(void),void)
    {
        _cardinal=power(_baseCardinal,_elementSize);
    }//computeCardinal;
    

    METHOD(BpArrangementWithRepeat,initialize,(void),void)
    {
            CARD32      i;
        for(i=0;i<_elementSize;i++){
            _choice[i]=0;
        }
    }//initialize;
    

    METHOD(BpArrangementWithRepeat,next,(void),void)
    {
            CARD32      k;
        k=_elementSize-1;
        (_choice[k])++;
        while((k>0)&&(_choice[k]>=_baseCardinal)){
            _choice[k]=0;
            k--;
            (_choice[k])++;
        }
    }//next;
    

//END BpArrangementWithRepeat.

/*** BpArrangementWithRepeat.cc       --                     --          ***/
