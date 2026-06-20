/******************************************************************************
FILE:               BoTimer-posix.m
LANGUAGE:           Objective-C
SYSTEM:             POSIX
USER-INTERFACE:     None
DESCRIPTION

    This class defines objects who send to themselves the "behave" message
    after a delay has elapsed or periodically.
    The precision of the period may be less than the millisecond.
    This is the POSIX (Linux) implementation.

    It uses POSIX per-process timers (timer_create) with SIGEV_THREAD
    notification: each expiration runs BoTimer_Fire() in a helper thread
    created by the C library, which then sends -behave.  This avoids signal
    handlers entirely, so -behave (and the delegate's -behave) run in an
    ordinary thread context rather than at signal-interrupt time.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2026-06-20 <PJB> Reimplemented for POSIX (was NeXT/Mach cthreads).
    1993-03-19 <PJB> Updated to use newly Bc- prefixed interfaces.
    1993-01-17 <PJB> Converted from C++ to Objective-C.
    1992-08-16 <PJB> Creation.
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
#include <signal.h>
#include <time.h>
#include <string.h>
#include <BoTimer.h>
#include <BcMem.h>
#include <BcImplementation.h>


    typedef struct {
        timer_t         timerid;
        BOOLEAN         armed;
    }                   BoTimer_Private;
    typedef BoTimer_Private*    BoTimer_PrivateP;


    /* Called by the C library in a helper thread on each timer expiration. */
    static void BoTimer_Fire(union sigval value)
    {
        BoTimer*    timer=(BoTimer*)value.sival_ptr;
        [timer behave];
    }/*BoTimer_Fire;*/


@implementation BoTimer

    -(id)init
    {
        [super init];
        delegate=nil;
        opaque=BcMem_Allocate((CARD32)sizeof(BoTimer_Private));
        ((BoTimer_PrivateP)opaque)->armed=FALSE;
        return(self);
    }/*init;*/


    -(id)free
    {
        [self stop];
        if(opaque!=NIL){
            BcMem_Deallocate((void**)&opaque);
        }
        return([super free]);
    }/*free;*/


    -(void)printOn:(FILE*)file
    {
        [super printOn:file];
        fprintf(file,"delegate=        %p\n",(void*)delegate);
    }/*printOn:;*/


    -(CARD32)precision
    {
        /* POSIX timers are nanosecond-specified; report 1 microsecond. */
        return(1);
    }/*precision;*/


    -(void)startPhase:(BoTimer_TimeT*)phase interval:(BoTimer_TimeT*)interval
    {
            BoTimer_PrivateP    p=(BoTimer_PrivateP)opaque;
            struct sigevent     event;
            struct itimerspec   spec;

        [self stop];

        memset(&event,0,sizeof(event));
        event.sigev_notify=SIGEV_THREAD;
        event.sigev_notify_function=BoTimer_Fire;
        event.sigev_value.sival_ptr=self;

        if(timer_create(CLOCK_MONOTONIC,&event,&(p->timerid))!=0){
            return; /* could not create the timer; stay disarmed. */
        }
        p->armed=TRUE;

        spec.it_value.tv_sec=(time_t)phase->seconds;
        spec.it_value.tv_nsec=(long)phase->microseconds*1000L;
        spec.it_interval.tv_sec=(time_t)interval->seconds;
        spec.it_interval.tv_nsec=(long)interval->microseconds*1000L;

        /* A zero it_value disarms the timer.  If the phase is zero but the
           interval is not, fire almost immediately so periodic timers with a
           null phase still start. */
        if((spec.it_value.tv_sec==0)&&(spec.it_value.tv_nsec==0)
           &&((spec.it_interval.tv_sec!=0)||(spec.it_interval.tv_nsec!=0))){
            spec.it_value.tv_nsec=1;
        }

        timer_settime(p->timerid,0,&spec,NIL);
    }/*startPhase:interval:;*/


    -(void)stop
    {
            BoTimer_PrivateP    p=(BoTimer_PrivateP)opaque;

        if((p!=NIL)&&(p->armed)){
            timer_delete(p->timerid);
            p->armed=FALSE;
        }
    }/*stop;*/


    -(void)behave
    {
        [delegate behave];
    }/*behave;*/


    -(id)delegate:(id)newdelegate
    {
            id      old;

        old=delegate;
        delegate=newdelegate;
        return(old);
    }/*delegate:;*/


    -(id)delegate
    {
        return(delegate);
    }/*delegate;*/

@end //BoTimer.

/*** BoTimer-posix.m                  --                     --          ***/
