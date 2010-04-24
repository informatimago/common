/******************************************************************************
FILE:               BcExcept.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (setjmp)
USER-INTERFACE:     None
DESCRIPTION
    In routine or in any procedure (recursively) while inside TRY/HANDLER block 
    you can call RAISE(resultCode,data1,data2).
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:18  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:07  pascal
    Initial entry into CVS.
    
    Revision 1.3  95/11/24  17:27:01  pascal
    Renamed BcExcept objects.
    
    Revision 1.2  95/11/16  12:07:09  pascal
    Some small correction to compile in MSVC.
    
    Revision 1.1  95/11/16  06:37:37  pascal
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
#ifndef __BcExcept__
#define __BcExcept__ defined
/* standard*/ 

#ifdef MSWINDOWS 
#include <winstjmp.h>
#else
#include <setjmp.h>
#endif
/* bclib*/
#include <names.h>
#include BcInterface_h
#include BcTypes_h


    typedef struct BcTRY_EnvironmentT*      BcTRY_EnvironmentP;
    typedef struct BcTRY_EnvironmentT {
        jmp_buf                     jmpEnv;
        BcTRY_EnvironmentP          next;
        INT32                       code;
        const void*                 data1;
        const void*                 data2;
    }                           BcTRY_EnvironmentT;

    extern BcTRY_EnvironmentP   BcTRY_CurrentEnvironment;



#define BcTRY       \
        {       BcTRY_EnvironmentT  __tryEnvironment;               \
            __tryEnvironment.code=0;                                \
            __tryEnvironment.next=BcTRY_CurrentEnvironment;         \
            BcTRY_CurrentEnvironment=&__tryEnvironment;             \
            if(setjmp(BcTRY_CurrentEnvironment->jmpEnv)==0){

    PROCEDURE(BcRAISE,(INT32 code,const void* data1,const void* data2),void)
        /*
            DO:         exits from the last TRY called.
        */

#define BcRERAISE   (BcRAISE(__tryEnvironment.code,\
                        __tryEnvironment.data1,__tryEnvironment.data2))

#if defined(MPW) || defined(AIX)
/* !!! Warning !!!*/
/* !!! Warning !!! With MPW-C, RETURNVALUE can be applied only to simple*/
/* !!! Warning !!! values*/
/* !!! Warning !!!!*/
#define BcRETURNVALUE(val)  \
            do {                                                            \
                BcTRY_CurrentEnvironment=BcTRY_CurrentEnvironment->next;    \
                return(val);                                                \
            } while(0);             
#else
#define BcRETURNVALUE(val)  \
            do {                                                            \
                typeof(val) temp=(val);                                     \
                BcTRY_CurrentEnvironment=BcTRY_CurrentEnvironment->next;    \
                return(temp);                                               \
            } while(0);             
#endif

#define BcRETURNVOID    \
            do {                                                            \
                BcTRY_CurrentEnvironment=BcTRY_CurrentEnvironment->next;    \
                return;                                                     \
            } while(0);             


#define BcHANDLER   \
                BcTRY_CurrentEnvironment=BcTRY_CurrentEnvironment->next;    \
            }else{                                                          \
                BcTRY_CurrentEnvironment=BcTRY_CurrentEnvironment->next;

#define BcEXCEPTIONCODE     (__tryEnvironment.code)

#define BcEXCEPTIONDATA1    (__tryEnvironment.data1)

#define BcEXCEPTIONDATA2    (__tryEnvironment.data2)

#define BcENDTRY            }}
                
#endif /*BcExcept.*/







