/******************************************************************************
FILE:               BcExcept.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (setjmp)
USER-INTERFACE:     None
DESCRIPTION
    In routine or in any procedure (recursively) while inside TRY/HANDLER block 
    you can call RAISE(resultCode).
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.3  95/11/24  17:26:49  pascal
    Renamed BcExcept objects.
    
    Revision 1.2  95/11/16  12:15:24  pascal
    Small corrections to compile with MSVC.
    
    Revision 1.1  95/11/16  06:28:33  pascal
    Initial revision
    
    1992-01-27 <PJB> Creation. Adapted from old Except.
    1992-12-21 <PJB> Translated from Modula2.
    1993-03-19 <PJB> Renamed BcExcept for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

    This file is part of the bclib library.

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
/* standard*/
#include <stdio.h> 
#include <stdlib.h> /* exit */ 
#ifdef UNIX
#include <signal.h>
#include <unistd.h>
#endif
#include <setjmp.h>
/* bclib*/
#include <names.h>
#include BcExcept_h
#include BcImplementation_h

    const char BcExcept_ID[]=
    "$Id: BcExcept.c,v 1.2 2004/01/02 00:59:24 pjbpjb Exp $";

    BcTRY_EnvironmentP BcTRY_CurrentEnvironment=NIL;
        
    PROCEDURE(BcRAISE,(INT32 code,const void* data1,const void* data2),void)
    {
        if(BcTRY_CurrentEnvironment==NIL){
            fprintf(stderr,"BpExcept_BcRAISE: Uncatched exception code=%ld data1=%p data2=%p\n",code,data1,data2);
#ifdef UNIX                       
            /* We use a kill instead of exit to let the debugger catch it here. */
            signal(SIGQUIT,SIG_DFL);
            kill(getpid(),SIGQUIT);
#else
            exit(1);
#endif
        }else{
            BcTRY_CurrentEnvironment->code=code;
            BcTRY_CurrentEnvironment->data1=data1;
            BcTRY_CurrentEnvironment->data2=data2;
            longjmp(BcTRY_CurrentEnvironment->jmpEnv,1);
        }
    }/*BcRAISE;*/

/*END BcExcept.*/


/*** BcExcept.c                       -- 2004-01-01 09:38:50 -- pascal   ***/
