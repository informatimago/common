/******************************************************************************
FILE:               BpCombination.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the implementation of the BpCombination class.
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
#include <names.h>
#include BpCombination_hh
#include BpClass_hh
#include BcImplementation_h

    static const char rcsid[]="$Id";

// birth and death:

    CONSTRUCTOR(BpCombination)
    {
        BpClass_PLUG(BpCombination);
        
    }//BpCombination;
        
    
    DESTRUCTOR(BpCombination)
    {
    }//~BpCombination;


// BpObject methods:

    METHOD(BpCombination,makeBrother,(void),BpObject*)
    {
        return(NEW(BpCombination));
    }//className;


    METHOD(BpCombination,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpCombination_SUPER::printOnLevel(file,level);
    //  PRINTONLEVEL(file,level,"%FORMAT",NEWFIELD,NEWFIELD);
    }//printOnLevel;

    
// BpSetEnumerator methods:

    METHOD(BpCombination,done,(void),BOOLEAN)
    {
        if(_choice==NIL){
            return(TRUE);
        }else{
            return(_choice[0]=_baseCardinal-_elementSize-1);
        }
    }//done;
    

    
// BpSetFunctor methods:

    static CARD32 combination(CARD32 n,CARD32 N)
    {
            CARD32      a,b,i,r;
            
        if(n>N-n){
            a=n;
            b=N-n;
        }else{
            a=N-n;
            b=n;
        }
        
        // a>=b
        // N!/(a!b!) = Pi(i=a+1,N,i)/b!
        r=1;
        for(i=a;i<=N;i++){
            r*=i;
        }
        for(i=2;i<=b;i++){
            r/=i;
        }
        return(r);
    }//combination;
    
    
    METHOD(BpCombination,computeCardinal,(void),void)
    {
        _cardinal=combination(_elementSize,_baseCardinal);
    }//computeCardinal;
    

    METHOD(BpCombination,initialize,(void),void)
    {
            CARD32      i;
        for(i=0;i<_elementSize;i++){
            _choice[i]=i;
        }
    }//initialize;
    

    static void nextstep(CARD32* choice,CARD32 limit,CARD32 i)
    {
        (choice[i])++;
        if(choice[i]>=limit+i){
            if(i>0){
                nextstep(choice,limit,i-1);
                choice[i]=choice[i-1]+1;
            }else{
                // done
            }
        }
    }//nextstep;
    
    
    METHOD(BpCombination,next,(void),void)
    {
        nextstep(_choice,_baseCardinal-(_elementSize-1),_elementSize-1);
    }//next;
    

//END BpCombination.

/*** BpCombination.cc                 --                     --          ***/
