/******************************************************************************
FILE:               BpTimer.hh
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This class defines objects who send to themselves the "behave" message 
    after a delay has elapsed or periodically.
    The precision of the period may be less than the millisecond.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.6  95/11/23  03:48:47  pascal
    Added BpClass and runtime class support in BpObject.
    Updated subclasses.
    
    Added dependant/dependee in BpObject.
    
    Revision 1.5  95/10/22  03:19:56  pascal
    Setting revision name V1.
    
    Revision 1.2  95/10/22  03:05:19  pascal
    Modifications while adding BpDict.
    
    1992-02-03 <PJB> Creation. (PeriodicTask)
    1992-08-16 <PJB> Renamed BpTimer and added the one-shot functionnality.
                        Augmented the parameter precision to 1 micro-second.
    1993-03-16 <PJB> Updated.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
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
#ifndef __BpTimer__
#define __BpTimer__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh
#include BpClass_hh

    
    typedef struct {
        CARD32          seconds;
        CARD32          microseconds;
    }               BpTimer_TimeT;

#define BpTimer_SUPER BpObject
class BpTimer:public BpTimer_SUPER
{
public:

// birth and death:

    CONSTRUCTOR(BpTimer)
        /*
            DO:         initialize a new BpTimer instance.
        */

    DESTRUCTOR(BpTimer) 
        /*
            DO:         destroy the instance.
        */

// override BpObject methods:

    METHOD(BpTimer,makeBrother,(void),BpObject*)
    METHOD(BpTimer,printOnLevel,(FILE* file,CARD32 level),void)
            
// new methods:

    METHOD(BpTimer,precision,(void),CARD32)
        /*
            RETURN:     the precision in microseconds of the period.
            NOTE:       this may be greater than 1e6 microseconds.
        */

    METHOD(BpTimer,start,(BpTimer_TimeT* phase,BpTimer_TimeT* interval),void)
        /*
            DO:         sends to itself the behave message at instants:
                            t_0+phase+(k*interval) if interval#0, 
                        or once at t_0+phase is interval=0.
            NOTE:       phase or interval may be NIL, meaning 0 second.
                        start(0,0) is equivalent to stop().
        */

    METHOD(BpTimer,stop,(void),void)
        /*
            DO:         stop sending the behave message.
        */

    METHOD(BpTimer,behave,(void),void)
        /*
            DO:         whatever the concrete subclasses want to do 
                        periodically.
            WARNING:    behave is called at interrupt time.
        */
        
private:
    void*                   opaque;
};//BpTimer

#define BpTimer_cStarted    (1)
#define BpTimer_cStopped    (2)
#define BpTimer_cBehave     (3)


#endif
