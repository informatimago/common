/******************************************************************************
FILE:           BpTimer.cc.next
LANGUAGE:       C++
SYSTEM:         MACH/NeXTstep_3.0, ANSI (stdio)
USER-INTERFACE: None
DESCRIPTION
    This class defines objects who send to themselves the "behave" message 
    after a delay has elapsed or periodically.
    The precision of the period may be less than the millisecond.
    This is the NeXT Mach implementation.
    NOTE: This implementation is based on the real-time timer.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.6  95/11/23  03:53:35  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.
    
    Revision 1.5  95/10/22  03:19:18  pascal
    Setting revision name V1.
    
    Revision 1.4  95/10/22  02:58:25  pascal
    Added ' ' in log comment of revision 1.1.
    
    Revision 1.3  95/10/22  02:53:28  pascal
    Changed rcsid from Header to Id.
    
    Revision 1.2  95/10/22  02:39:39  pascal
    Modifications while adding BpDict.
    
    Revision 1.1  95/10/18  06:26:23  pascal
    Initial revision

    1992-08-16 <PJB> Creation.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1994-02-05 <PJB> Allowed NIL parameters to start() method.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2011

    This file is part of the bplib library..

    This  program is  free software;  you can  redistribute  it and/or
    modify it  under the  terms of the  GNU General Public  License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program  is distributed in the  hope that it  will be useful,
    but  WITHOUT ANY WARRANTY;  without even  the implied  warranty of
    MERCHANTABILITY or FITNESS FOR  A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a  copy of the GNU General Public License
    along with  this program; see the  file COPYING; if  not, write to
    the Free  Software Foundation, Inc.,  59 Temple Place,  Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
extern "C" {
#include <libc.h>       // ualarm() ...
#include <signal.h>
#include <mach/mach.h>
#include <mach/cthreads.h>
#include <sys/time.h>
}
// Ok, this is a UNIX file. No need to use <names.h>.
#include <BpTimer.hh>
extern "C" {
#include <BcMem.h>
}
#include <BcImplementation.h>

    static const char rcsid[]="$Id: BpTimer-NEXTSTEP.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";




    typedef enum {
        State_Idle,State_Phasing,State_Running,State_Stopped
    }                           StateT;
    
    typedef enum {
        Command_Initialize,Command_Start,Command_Stop,Command_Terminate
    }                           CommandT;
    
    typedef struct {
        BpTimer*                    myself;
        cthread_t                   thread;
        condition_t                 waitCommand;
        mutex_t                     mutex;
        CommandT                    command;
        StateT                      state;
        BpTimer_TimeT               phase;
        BpTimer_TimeT               interval;   // =0 <=> one shot
        struct itimerval            timer;
    }                           PrivateT;
    typedef PrivateT*           PrivateP;
    
    
    PROCEDURE(BpTimer_Handler,(),void)
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
            p->myself->behave();
            break;
        case State_Stopped:
            p->state=State_Idle;
            // no break;
        default:
            // not running => do not call behave!
            mutex_unlock(p->mutex);
            break;
        }
    }//BpTimer_Handler;


    PROCEDURE(BpTimer_Thread,(PrivateP p),void)
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
                newvector.sv_handler=BpTimer_Handler;
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
    }//BpTimer_Thread;
    
/////////////////////////////////////////
//////////// BpTimer object ///////////////
/////////////////////////////////////////

// birth and death:

    CONSTRUCTOR(BpTimer)
    {
            PrivateP            p;
        
        BpClass_PLUG(BpTimer);
        p=(PrivateP)BcMem_Allocate(sizeof(PrivateT));
        opaque=p;
        if(p!=NIL){
            p->myself=this;
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
            p->thread=cthread_fork((cthread_fn_t)BpTimer_Thread,(any_t)p);
            condition_signal(p->waitCommand);
        }
    }//BpTimer;
    

    DESTRUCTOR(BpTimer)
    {
            PrivateP            p;
            
        this->stop();
        p=(PrivateP)opaque;
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
    }//~BpTimer;


// override BpObject methods:

    METHOD(BpTimer,makeBrother,(void),BpObject*)
    {
        return(NEW(BpTimer));
    }//makeBrother;
    

    METHOD(BpTimer,printOnLevel,(FILE* file,CARD32 level),void)
    {
        BpTimer_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%p",opaque,opaque);
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
            p=(PrivateP)opaque;
            PRINTONLEVEL_OPEN(file,level,opaque);
            level+=2;
            PRINTONLEVEL(file,level,"%p",this,p->myself);
            if((0<=p->state)&&(p->state<4)){
                PRINTONLEVEL(file,level,"%s",state,statestring[p->state]);
            }else{
                PRINTONLEVEL(file,level,"%d",state,p->state);
            }
            if((0<=p->command)&&(p->command<4)){
                PRINTONLEVEL(file,level,"%s",command,cmdstring[p->command]);
            }else{
                PRINTONLEVEL(file,level,"%d",command,p->command);
            }
            PRINTONLEVEL2(file,level,"%6d.%06d",phase,
                            p->phase.seconds,       p->phase.microseconds);
            PRINTONLEVEL2(file,level,"%6d.%06d",interval,
                            p->interval.seconds,    p->interval.microseconds);
            PRINTONLEVEL(file,level,"%s",opaque,"{");
            level-=2;
            PRINTONLEVEL_CLOSE(file,level);
        }
    }//printOnLevel;
    
    
// new methods:

    METHOD(BpTimer,precision,(void),CARD32)
    {
        return(10000);
    }//precision;


    METHOD(BpTimer,start,(BpTimer_TimeT* phase,BpTimer_TimeT* interval),void)
    {
            PrivateP            p;
            BpTimer_TimeT       zero;
        
        p=(PrivateP)opaque; 
        if(p==NIL){
            return;
        }
        if(phase==NIL){
            zero.seconds=0;
            zero.microseconds=0;
            phase=&zero;
        }else if(interval==NIL){
            zero.seconds=0;
            zero.microseconds=0;
            interval=&zero;
        }
        if((phase->seconds==0)&&(phase->microseconds==0)
        &&(interval->seconds==0)&&(interval->microseconds==0)){
            this->stop();
        }else{
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
        }
        selfChanged(BpTimer_cStarted);
    }//start;


    METHOD(BpTimer,stop,(void),void)
    {
            PrivateP            p;
            
        p=(PrivateP)opaque;
        if(p==NIL){
            return;
        }
        mutex_lock(p->mutex);
        p->command=Command_Stop;
        condition_signal(p->waitCommand);
        mutex_unlock(p->mutex);
        selfChanged(BpTimer_cStopped);
    }//stop;


    METHOD(BpTimer,behave,(void),void)
    {
        selfChanged(BpTimer_cBehave);
    }//behave;
        

//END BpTimer.
