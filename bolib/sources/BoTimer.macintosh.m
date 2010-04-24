/******************************************************************************
FILE:               Timer.m.macintosh
LANGUAGE:           Objective-C
SYSTEM:             MacOS, ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    DO NOT EDIT << Timer.m >> - EDIT << Timer.m.macintosh >> 
    This is an abstract class: the Behave method at least must be overwritten.
    This class defines objects who are sent the "Behave" message periodically.
    The precision of the period may be less than the millisecond.

        THIS IMPLEMENTATION IS BASED ON THE MAC-OS VBL MANAGER,
        thus the precision is 1/60.15 s   17 ms.
        It is inspired from [Etienne Vautherin, Tuyau Soft n  2, 
            La Lettre des Developpeurs Apple, N  12 Septembre 1990].
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/02/03 <PJB> Creation. (PeriodicTask)
    1992/08/16 <PJB> Renamed Timer and added the one-shot functionnality.
                        Augmented the parameter precision to 1 micro-second.
    1993/01/17 <PJB> Converted from C++ to Objective-C.
LEGAL
    GPL
    
    Copyright Pascal Bourguignon 1992 - 2003
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version
    2 of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public
    License along with this program; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
//application:
#import <BoTimer.h>
#import <TVBLTask.h>    // from ~/src/common/objectivec/mxlib
#import <BoImplementation.h>


@implementation BoTimer

// birth and death:

    -(id)init
    {
        [super init];
        opaque=(void*)[[TVBLTask alloc] initTimer:(id)self];
        return(self);
    }//init;
    
    -(id)free
    {
            
            TVBLTask*       vbl;
        
        vbl=(TVBLTask*)opaque;
        [vbl free];
        opaque=NIL;
        return([super free]);
    }//free;

// override BoObject methods:
    
    -(void)printOn:(FILE*)file
    {
            TVBLTaskP       vbl;
            
        vbl=(TVBLTaskP)opaque;
        [super printOn:file];
        fprintf(file,"taskInterval=   %d\n",vbl->taskInterval);
        fprintf(file,"currentInterval=%d\n",vbl->currentInterval);
        fprintf(file,"applicationA5=  %8p\n",vbl->applicationA5);
        fprintf(file,"active=         %s\n",vbl->active?"TRUE":"FALSE");
    }//printOn:;
    
// new methods:

    -(CARD32)precision
    {
        return(16625);
    }//precision

    -(void)startPhase:(BoTimer_TimeT*)phase interval:(BoTimer_TimeT*)interval
    {
            TVBLTask*       vbl;
        
        vbl=(TVBLTask*)opaque;
        [vbl remove];
        if(phase==NIL){
            [vbl installPhase:interval interval:interval];
        }else{
            [vbl installPhase:phase interval:interval];
        }
    }//start

    -(void)stop
    {
            TVBLTask*       vbl;
        
        vbl=(TVBLTask*)opaque;
        [vbl remove];
    }//stop

    -(void)behave
    {
        [delegate behave];
    }//behave
        

    -(id)delegate:(id)newdelegate
    {
            id      old;
        old=delegate;
        delegate=newdelegate;
        return(old);
    }//delegate:;
        
        
    -(id)delegate
    {
        return(delegate);
    }//delegate;
    

@end //BoTimer.

/*** BoTimer.macintosh.m              -- 2003-11-30 04:51:32 -- pascal   ***/
