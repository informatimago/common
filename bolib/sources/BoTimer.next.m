/******************************************************************************
FILE:               BoTimer.m.next
LANGUAGE:           Objective-C
SYSTEM:             MACH/NeXTstep_3.0, ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    DO NOT EDIT << BoTimer.m >> - EDIT << BoTimer.m.next >> 

    This class defines objects who send to themselves the "behave" message 
    after a delay has elapsed or periodically.
    The precision of the period may be less than the millisecond.
    This is the NeXT Mach implementation.
    
    NOTE: This implementation is based on the real-time timer.
    
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992/08/16 <PJB> Creation.
    1993/01/17 <PJB> Converted from C++ to Objective-C.
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2011
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#include <libc.h>       // ualarm() ...
#include <signal.h>
#include <sys/time.h>
#include <mach/cthreads.h>
#include <mach/mach.h>

#include <BoTimer.h>
#include <BcMem.h>
#include <BcImplementation.h>

@implementation BoTimer

    typedef enum {
        State_Idle,State_Phasing,State_Running,State_Stopped
    }                           StateT;
    
    typedef enum {
        Command_Initialize,Command_Start,Command_Stop,Command_Terminate
    }                           CommandT;
    
    typedef struct {
        BoTimer*                    myself;
        cthread_t                   thread;
        condition_t                 waitCommand;
        mutex_t                     mutex;
        CommandT                    command;
        StateT                      state;
        BoTimer_TimeT               phase;
        BoTimer_TimeT               interval;   // =0 <=> one shot
        struct itimerval            timer;
    }                           PrivateT;
    typedef PrivateT*           PrivateP;
    
    
    PROCEDURE(BoTimer_Handler,(void),void)
    {
            PrivateP            p;
        
        p=(PrivateP)cthread_data(cthread_self());
        mutex_lock(p->mutex);
        switch(p->state){
        case State_Phasing:
            p->state=State_Running;
            // no break;
        case State_Running:
            if((p->timer.it_interval.tv_sec==0)
             &&(p->timer.it_interval.tv_usec==0)){
                p->state=State_Stopped;
            }
            mutex_unlock(p->mutex);
            [p->myself behave];
            break;
        case State_Stopped:
            p->state=State_Idle;
            // no break;
        default:
            // not running => do not call behave!
            mutex_unlock(p->mutex);
            break;
        }
    }//BoTimer_Handler;


    PROCEDURE(BoTimer_Thread,(PrivateP p),void)
        /*
            PRE:            p->state=State_Idle, p->command=Command_None
        */
    {
            struct sigvec       oldvector;
            struct sigvec       newvector;
            int                 oldmask;
            
        cthread_set_data(cthread_self(),(any_t)p);
        mutex_lock(p->mutex);
        while(TRUE){
            condition_wait(p->waitCommand,p->mutex);
            oldmask=sigblock(sigmask(SIGALRM));
            switch(p->command){
            case Command_Initialize:
                p->state=State_Idle;
                p->timer.it_value.tv_sec=0;
                p->timer.it_value.tv_usec=0;
                setitimer(SIGALRM,&(p->timer),NIL);
                newvector.sv_handler=BoTimer_Handler;
                newvector.sv_mask=0;
                newvector.sv_flags=0;
                sigvec(SIGALRM,&newvector,&oldvector);
                break;
            case Command_Start:
                p->state=State_Phasing;
                p->timer.it_interval.tv_sec=p->interval.seconds;
                p->timer.it_interval.tv_usec=p->interval.microseconds;
                p->timer.it_value.tv_sec=p->phase.seconds;
                p->timer.it_value.tv_usec=p->phase.microseconds;
                setitimer(SIGALRM,&(p->timer),NIL);
                break;
            case Command_Stop:
                p->state=State_Stopped;
                p->timer.it_interval.tv_sec=0;
                p->timer.it_interval.tv_usec=0;
                p->timer.it_value.tv_sec=0;
                p->timer.it_value.tv_usec=0;
                setitimer(SIGALRM,&(p->timer),NIL);
                break;
            case Command_Terminate:
                p->state=State_Stopped;
                p->timer.it_interval.tv_sec=0;
                p->timer.it_interval.tv_usec=0;
                p->timer.it_value.tv_sec=0;
                p->timer.it_value.tv_usec=0;
                setitimer(SIGALRM,&(p->timer),NIL);
                sigvec(SIGALRM,&oldvector,NIL);
                mutex_unlock(p->mutex);
                cthread_exit(0); 
                break;
            default:
                // never
                break;
            }//switch;
            sigsetmask(oldmask);
        }//always
    }//BoTimer_Thread;
    
/////////////////////////////////////////
//////////// BoTimer object /////////////
/////////////////////////////////////////

// birth and death:

    -(id)init
    {
            PrivateP            p;
        
        [super init];
        p=BcMem_Allocate(sizeof(PrivateT));
        opaque=p;
        if(p!=NIL){
            p->myself=self;
            p->waitCommand=condition_alloc();
            p->mutex=mutex_alloc();
            p->command=Command_Initialize;
            p->state=State_Idle;
            p->phase.seconds=0;
            p->phase.microseconds=0;
            p->interval.seconds=0;
            p->interval.microseconds=0;
            p->timer.it_interval.tv_sec=0;
            p->timer.it_interval.tv_usec=0;
            p->timer.it_value.tv_sec=0;
            p->timer.it_value.tv_usec=0;
            p->thread=cthread_fork((cthread_fn_t)BoTimer_Thread,(any_t)p);
            condition_signal(p->waitCommand);
        }
        return(self);
    }//BoTimer;
    

    -(id)free
    {
            PrivateP            p;
            
        [self stop];
        p=opaque;
        if(p!=NIL){
            mutex_lock(p->mutex);
            p->command=Command_Terminate;
            condition_signal(p->waitCommand);
            condition_wait(p->waitCommand,p->mutex);
            mutex_unlock(p->mutex);
            cthread_join(p->thread);
            mutex_free(p->mutex);
            condition_free(p->waitCommand);
            BcMem_Deallocate(&opaque);
        }
        return([super free]);
    }//free;

// override BoObject methods:

    -(void)printOn:(FILE*)file
    {
        [super printOn:file];
        fprintf(file,"opaque=       %p\n",opaque);
        if(opaque!=NIL){
                PrivateP        p;
                char*           cmdstring[]={
                                    "Initialize",
                                    "Start",
                                    "Stop",
                                    "Terminate"
                                };
                char*           statestring[]={
                                    "Idle",
                                    "Phasing",
                                    "Running",
                                    "Stopped"
                                };
            p=opaque;
            fprintf(file,"->self=         %p\n",(void*)p->myself);
            if((0<=p->state)&&(p->state<4)){
                fprintf(file,"->state=        %s\n",statestring[p->state]);
            }else{
                fprintf(file,"->state=        %d\n",p->state);
            }
            if((0<=p->command)&&(p->command<4)){
                fprintf(file,"->command=      %s\n",cmdstring[p->command]);
            }else{
                fprintf(file,"->command=      %d\n",p->command);
            }
            fprintf(file,"->phase=        %6lu.%06lu\n",
                                p->phase.seconds,
                                p->phase.microseconds);
            fprintf(file,"->interval=     %6lu.%06lu\n",
                                p->interval.seconds,
                                p->interval.microseconds);
        }
    }//printOn:;
            
// new methods:

    -(CARD32)precision
    {
        return(10000);
    }//precision;

    -(void)startPhase:(BoTimer_TimeT*)phase interval:(BoTimer_TimeT*)interval
    {
            PrivateP            p;

        p=opaque;
        if(p==NIL){
            return;
        }
        mutex_lock(p->mutex);
        if((p->state==State_Phasing)||(p->state==State_Running)){
            p->command=Command_Stop;
            condition_signal(p->waitCommand);
            mutex_unlock(p->mutex);
            mutex_lock(p->mutex);
        }
        p->command=Command_Start;
        p->phase=(*phase);
        p->interval=(*interval);
        condition_signal(p->waitCommand);
        mutex_unlock(p->mutex);
    }//startPhase:interval:;

    -(void)stop
    {
            PrivateP            p;
            
        p=opaque;
        if(p==NIL){
            return;
        }
        mutex_lock(p->mutex);
        p->command=Command_Stop;
        condition_signal(p->waitCommand);
        mutex_unlock(p->mutex);
    }//stop;


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

/*** BoTimer.next.m                   -- 2003-11-30 04:48:37 -- pascal   ***/
