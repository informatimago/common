/******************************************************************************
FILE:               BcDefault.h
LANGUAGE:           ANSI-C
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    typedefs and external functions for defaults processing.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:18  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:07  pascal
    Initial entry into CVS.
    
    Revision 1.1  95/11/16  06:37:36  pascal
    Initial revision
    
    1993-01-12 <PJB> Creation. (inspired from NeXTstep defaults.h)
    1993-03-19 <PJB> Renamed BcDefault for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL

    Interface:
        Application Kit,Release 2.0
        Copyright (c) 1988,1989,1990,NeXT,Inc.  All rights reserved.

    Copyright Pascal J. Bourguignon 1993 - 2002

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
#ifndef __BcDefault__
#define __BcDefault__
#include <names.h>
#include BcInterface_h
#include BcTypes_h

    typedef struct {
        char*           name;
        char*           value;
    }                   BcDefault_T;


    PROCEDURE(BcDefault_Register,
                (const char* owner,const BcDefault_T* vector),INT32) 

    PROCEDURE(BcDefault_Get,
                (const char* owner,const char* name),const char*)

    PROCEDURE(BcDefault_Set,
                (const char* owner,const char* name,const char* value),INT32)
                
    PROCEDURE(BcDefault_Write,
                (const char* owner,const char* name,const char* value),INT32)

    PROCEDURE(BcDefault_WriteVector,
                (const char* owner,const BcDefault_T* vector),INT32)

    PROCEDURE(BcDefault_Remove,
                (const char* owner,const char* name),INT32)

    PROCEDURE(BcDefault_Read,
                (const char* owner,const char* name),const char*)
        
    PROCEDURE(BcDefault_UpdateAll,(void),void)
    
    PROCEDURE(BcDefault_Update,
                (const char* owner,const char* name),const char*)

    PROCEDURE(BcDefault_SetUser,
                (const char* newUser),const char*)


#endif 
/*** BcDefault.h                      -- 2004-01-01 09:32:52 -- pascal   ***/
