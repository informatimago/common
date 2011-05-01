/******************************************************************************
FILE:               BpArrangementSansRepeat.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This is the implementation of the BpArrangementSansRepeat class.
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
#include BpArrangementSansRepeat_hh
#include BpClass_hh
#include BcImplementation_h

    static const char rcsid[]="$Id";

// birth and death:

    CONSTRUCTOR(BpArrangementSansRepeat)
    {
        BpClass_PLUG(BpArrangementSansRepeat);
        _done=FALSE;
        _taken=NIL;
    }//BpArrangementSansRepeat;
        
    
    DESTRUCTOR(BpArrangementSansRepeat)
    {
        DELETE(_taken);
    }//~BpArrangementSansRepeat;


// BpObject methods:

    METHOD(BpArrangementSansRepeat,makeBrother,(void),BpObject*)
    {
        return(NEW(BpArrangementSansRepeat));
    }//className;


    METHOD(BpArrangementSansRepeat,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpArrangementSansRepeat_SUPER::printOnLevel(file,level);
    //  PRINTONLEVEL(file,level,"%FORMAT",NEWFIELD,NEWFIELD);
    }//printOnLevel;

    
// BpSetEnumerator methods:

    METHOD(BpArrangementSansRepeat,done,(void),BOOLEAN)
    {
        return(_choice[0]==_baseCardinal);
    }//done;
    

// BpSetFunctor methods:

    CARD32 arrangement(CARD32 n,CARD32 N)
    {
            CARD32      i,r;
            
        r=1;
        for(i=N-n+1;i<=N;i++){
            r*=i;
        }
        return(r);
    }//arrangement;
    
    
    METHOD(BpArrangementSansRepeat,computeCardinal,(void),void)
    {
        _cardinal=arrangement(_elementSize,_baseCardinal);
    }//computeCardinal;
    

    METHOD(BpArrangementSansRepeat,initialize,(void),void)
    {
            CARD32      i;
        
        DELETE(_taken);
        _taken=new BOOLEAN[_baseCardinal];
        for(i=0;i<_baseCardinal;i++){
            _taken[i]=FALSE;
        }
        _done=FALSE;
        step(0);
    }//initialize;
    
    
#define transition(guard,action,state) if(guard){ do{ action }while(0); goto state; }
/*
#define transition(guard,action,state) if(guard){ \
        printf("   [ %-30s ] / %-30s --> %-30s\n",#guard,#action,#state); \
        do{ action }while(0); goto state; }
*/

    METHOD(BpArrangementSansRepeat,step,(CARD32 k),void)
    {
    state_0:
        transition( (k<_elementSize),          {_choice[k]=0;},     state_1)
        transition(!(k<_elementSize),          {k=_elementSize-1;}, state_5)

    state_1:
        transition( (_taken[_choice[k]]),      {},                  state_2)
        transition(!(_taken[_choice[k]]),      {},                  state_3)

    state_2:
        _choice[k]++;
        transition( (_choice[k]<_baseCardinal),{},                  state_1)
        transition((!(_choice[k]<_baseCardinal))&&(k==0), {_done=TRUE;}, terminate)
        transition((!(_choice[k]<_baseCardinal))&&(k!=0), {k--;},   state_5)

    state_3:
        _taken[_choice[k]]=TRUE;
        transition( (k<_elementSize-1),        {k++;},              state_0)
        transition(!(k<_elementSize-1),        {/*uplet(k);*/},     terminate)

    state_5:
        _taken[_choice[k]]=FALSE;
        transition(TRUE,                       {},                  state_2)

    terminate:
        return;
    }//step;


    METHOD(BpArrangementSansRepeat,next,(void),void)
    {
        step(_elementSize);
    }//next;
    

//END BpArrangementSansRepeat.

/*** BpArrangementSansRepeat.cc       --                     --          ***/
