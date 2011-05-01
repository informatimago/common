/******************************************************************************
FILE:               BoTimer.h
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This class defines objects who send to themselves the "behave" message 
    after a delay has elapsed or periodically.
    The precision of the period may be less than the millisecond.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1993-03-19 <PJB> Updated to use newly Bc- prefixed interfaces.
    1993-01-17 <PJB> Converted from C++ to Objective-C.
    1992-08-16 <PJB> Renamed BoTimer and added the one-shot functionnality.
                        Augmented the parameter precision to 1 micro-second.
    1992-02-03 <PJB> Creation. (PeriodicTask)
LEGAL
    GPL
    
    Copyright Pascal Bourguignon 1992 - 2011
    
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
#ifndef BoTimer_h
#define BoTimer_h
#include <BcInterface.h>
#include <BcTypes.h>
#include <BoObject.h>

    
    typedef struct {
        CARD32          seconds;
        CARD32          microseconds;
    }               BoTimer_TimeT;

@interface BoTimer:BoObject
{
    id                      delegate;
    void*                   opaque;
}

// birth and death:

    -(id)init;
        /*
            DO:         initialize self.
            RETURN:     self.
            NOTE:       [[BoTimer alloc] init];
        */

    -(id)free;
        /*
            DO:         free self.
            RETURN:     NIL.
        */

// override BoObject methods:

    -(void)printOn:(FILE*)file;
        /*
            DO:         dumps self on the file.
        */
            
// new methods:

    -(CARD32)precision;
        /*
            RETURN:     the precision in microseconds of the period.
            NOTE:       this may be greater than 1e6 microseconds.
        */

    -(void)startPhase:(BoTimer_TimeT*)phase interval:(BoTimer_TimeT*)interval;
        /*
            DO:         sends to itself the behave message at instants:
                            t_0+phase+(k*interval) if interval#0, 
                        or once at t_0+phase if interval=0.
        */

    -(void)stop;
        /*
            DO:         stop sending the behave message.
        */

    -(void)behave;
        /*
            DO:         whatever the concrete subclasses want to do 
                        periodically.
            WARNING:    behave is called at interrupt time.
            NOTE:       sends a behave message to the delegate 
                        by [delegate behave].
        */
        
    -(id)delegate:(id)newdelegate;
        /*
            NOTE:       the delegate is send a behave message by 
                        [self behave] (at interrupt time!)
            DO:         set the delegate.
            RETURN:     the old delegate.
        */
        
    -(id)delegate;
        /*
            RETURN:     the current delegate.
        */
    
@end
#endif
/*** BoTimer.h                        -- 2003-11-30 05:19:52 -- pascal   ***/
