/******************************************************************************
FILE:               BpTimer.cc.macintosh
LANGUAGE:           C++
SYSTEM:             MacOS, ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This is an abstract class: the behave method at least must be overwritten.
    This class defines objects who are sent the "behave" message periodically.
    The precision of the period may be less than the millisecond.

        THIS IMPLEMENTATION IS BASED ON THE MAC-OS VBL MANAGER,
        thus the precision is 1/60.15 s   16.625 ms.
        It is inspired from [Etienne Vautherin, Tuyau Soft n  2, 
            La Lettre des Developpeurs Apple, No 12, Septembre 1990].
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.6  95/11/23  03:53:34  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.
    
    Revision 1.5  95/10/22  03:19:15  pascal
    Setting revision name V1.
    
    Revision 1.4  95/10/22  02:58:24  pascal
    Added ' ' in log comment of revision 1.1.
    
    Revision 1.3  95/10/22  02:53:28  pascal
    Changed rcsid from Header to Id.
    
    Revision 1.2  95/10/22  02:39:36  pascal
    Modifications while adding BpDict.
    
    Revision 1.1  95/10/18  06:26:10  pascal
    Initial revision

    1992-02-03 <PJB> Creation. (PeriodicTask)
    1992-08-16 <PJB> Renamed BpTimer and added the one-shot functionnality.
                        Augmented the parameter precision to 1 micro-second.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
    1994-02-05 <PJB> Allowed NIL parameters to start() method.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

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
// Ok, this is a Macintosh file. No need to use <names.h>.
#include <Retrace.h>
#include <BpTimer.h>

    static const char rcsid[]="$Id: BpTimer-MacOS.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";



    class TVBLTask:public VBLTask // actually a struct !
    {
    public:
        CONSTRUCTOR(TVBLTask) // BpTimer* itsTask
        DESTRUCTOR(TVBLTask) // void
        
        METHOD(TVBLTask,install,(BpTimer_TimeT* phase,
                BpTimer_TimeT* interval),OSErr)
        METHOD(TVBLTask,remove,(void),OSErr)
        METHOD(TVBLTask,updateVBLCount,(void),void)
        
        MEMBERPROC(VBLCall,(void),friend pascal void)
        
        BpTimer*                    task;
        BpTimer_TimeT               taskInterval;
        BpTimer_TimeT               currentInterval;    // first, taskPhase
        CARD32                  applicationA5;
        BOOLEAN                 active;
    };//TVBLTask

#include <BcImplementation.h>

    // OK! Here is some constructor with a parameter. But I will remove it
    // as soon as I can.
    TVBLTask::TVBLTask(BpTimer* itsTask)
    {
        CARD32 GetA5(void)=0x200D;  // MOVE.L A5,D0
        
        task=itsTask;   
        taskInterval.seconds=0;
        taskInterval.microseconds=0;
        currentInterval.seconds=0;
        currentInterval.microseconds=0;
        applicationA5=GetA5();
        active=FALSE;
        
        qType=vType;
        vblAddr=VBLCall;
        vblCount=0;
        vblPhase=0;
    }//TVBLTask


    DESTRUCTOR(TVBLTask)
    {
            OSErr       err;
            
        if(active){
            err=remove();
        }
    }//~TVBLTask
    

    METHOD(TVBLTask,install,(BpTimer_TimeT* phase,
                BpTimer_TimeT* interval),OSErr)
    {
            OSErr       err;
        
        if(phase!=NIL){
            currentInterval=(*phase);
        }else{
            currentInterval.second=0;
            currentInterval.microsecond=1;
        }
        if(interval!=NIL){
            taskInterval=(*interval);
        }else{
            taskInterval.second=0;
            taskInterval.microsecond=0;
        }
        updateVBLCount();
        vblPhase=0;
        err=VInstall((QElemPtr)(VBLTask*)self);
        active=(err==noErr);
        return(err);
    }//Install
    

    METHOD(TVBLTask,remove,(void),OSErr)
    {
        active=FALSE;
        return(VRemove((QElemPtr)(VBLTask*)self));
    }//remove
        

    METHOD(TVBLTask,updateVBLCount,(void),void)
    {
        // 32767*16625=544751375
        if((currentInterval.seconds==0)AND(currentInterval.microseconds==0)){
            vblCount=0;
        }else if((currentInterval.seconds<544)
        OR((currentInterval.seconds==544)
        AND(currentInterval.microseconds<=751375))){
            vblCount=(INT16)((currentInterval.seconds*1000000
                                +currentInterval.microseconds)/16625);
            currentInterval.seconds=0;
            currentInterval.microseconds=0;
            if(vblCount==0){
                vblCount=1;
            }
        }else{
            vblCount=32767;
            if(currentInterval.microseconds<751375){
                // cI.microseconds<751375 => cI.seconds>544
                currentInterval.seconds=currentInterval.seconds-545;
                currentInterval.microseconds+=248625;
                        // 248625=1000000-751375;
            }else{
                currentInterval.seconds=currentInterval.seconds-544;
                currentInterval.microseconds-=751375;
            }
        }
    }//updateVBLCount
    

    PROCEDURE(VBLCall,(void),pascal void)
    {
            VBLTask*        GetVBLTask(void)=0x2008; // MOVE.L A0,D0        
            TVBLTask*       vbl;
            CARD32          savedA5;
            
        vbl=(TVBLTask*)GetVBLTask();
        savedA5=SetA5(vbl->applicationA5);
        if((vbl->currentInterval.seconds==0)
        AND(vbl->currentInterval.microseconds==0)){
            vbl->task->behave();
            vbl->currentInterval=vbl->taskInterval;
        }
        vbl->updateVBLCount();
        SetA5(savedA5);
    }//VBLCall
    

// birth and death:

    CONSTRUCTOR(BpTimer)
        //  DO:         initialize a new BpTimer instance.
    {
        opaque=(void*)NEW(TVBLTask(self));
    }//BpTimer

    
    DESTRUCTOR(BpTimer)
        //  DO:         destroy the instance.
    {
            
            TVBLTask*       vbl;
        
        vbl=(TVBLTask*)opaque;
        delete(vbl);
        opaque=NIL;
    }//~BpTimer


// override OsiObject methods:

    METHOD(BpTimer,className,(void),char*)
    {
        return("BpTimer");
    }//className;
    

    METHOD(BpTimer,printOnLevel,(FILE* file,CARD32 level),void)
    {
            TVBLTask*       vbl;
/***
            BOOLEAN         doclose=FALSE;
        
        if(level==0){
            PRINTONLEVEL_OPEN(file,level,className());
            level+=4;
            doclose=TRUE;
        }
***/
        vbl=(TVBLTask*)opaque;
        BpTimer_SUPER::printOnLevel(file,level);
        PRINTONLEVEL(file,level,"%d",taskInterval,vbl->taskInterval);
        PRINTONLEVEL(file,level,"%d",taskInterval,vbl->currentInterval);
        PRINTONLEVEL(file,level,"%p",taskInterval,vbl->applicationA5);
        PRINTONLEVEL(file,level,"%s",active,BOOLSTR(vbl->active));
/***
        if(doclose){
            PRINTLEVEL_CLOSE(file,level);
        }
***/
    }//printOnLevel;


// new methods:

    METHOD(BpTimer,precision,(void),CARD32)
    {
        return(16625);
    }//precision

    METHOD(BpTimer,start,(BpTimer_TimeT* phase,BpTimer_TimeT* interval),void)
    {
            TVBLTask*       vbl;
        
        if(opaque==NIL){
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
            vbl=(TVBLTask*)opaque;
            vbl->remove();
            if(phase==NIL){
                vbl->install(interval,interval);
            }else{
                vbl->install(phase,interval);
            }
        }
        selfChanged(BpTimer_cStarted);
    }//start

    METHOD(BpTimer,stop,(void),void)
    {
            TVBLTask*       vbl;
        
        if(opaque==NIL){
            return;
        }
        vbl=(TVBLTask*)opaque;
        vbl->remove();
        selfChanged(BpTimer_cStopped);
    }//stop

    METHOD(BpTimer,behave,(void),void)
    {
        selfChanged(BpTimer_cBehave);
    }//behave
        
//END BpTimer.
