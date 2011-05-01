/******************************************************************************
FILE:               BcDefault.c
LANGUAGE:           ANSI-C
SYSTEM:             NeXTstep_3.0
USER-INTERFACE:     None
DESCRIPTION
    --- NeXTstep implementation ---
    typedefs and external functions for defaults processing.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.1  95/11/16  06:28:30  pascal
    Initial revision
    
    1993-01-12 <PJB> Creation. (from NeXTstep defaults.h)
    1993-03-19 <PJB> Renamed BcDefault for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1993 - 2011

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
/*application */
/* This is a UNIX file. No need to use names.h. */
#include <BcDefault.h>
#include <BcImplementation.h>
/*NeXT */
/* import <defaults/defaults.h> */
extern int NXRegisterDefaults(const char *owner,const BcDefault_T* vector); 
extern const char *NXGetDefaultValue(const char *owner,const char *name);
extern int NXSetDefault(const char *owner,const char *name,const char *value);
extern int NXWriteDefault(const char *owner,const char *name,const char *value);
extern int NXWriteDefaults(const char *owner,const BcDefault_T* vector);
extern int NXRemoveDefault(const char *owner,const char *name);
extern const char *NXReadDefault(const char *owner,const char *name);
extern void NXUpdateDefaults(void);
extern const char *NXUpdateDefault(const char *owner,const char *name);
extern const char *NXSetDefaultsUser(const char *newUser);
/* end import <defaults/defaults.h> */

    const char BcDefault_ID[]=
    "$Id: BcDefault.c,v 1.1 2003/12/03 16:40:35 pjbpjb Exp $";

    PROCEDURE(BcDefault_Register,
                (const char* owner,const BcDefault_T* vector),INT32) 
    {
        return(NXRegisterDefaults(owner,vector));
    }/*BcDefault_Register; */
    
    
    PROCEDURE(BcDefault_Get,
                (const char* owner,const char* name),const char*)
    {
        return(NXGetDefaultValue(owner,name));
    }/*BcDefault_Get; */
    
    
    PROCEDURE(BcDefault_Set,
                (const char* owner,const char* name,const char* value),INT32)
    {
        return(NXSetDefault(owner,name,value));
    }/*BcDefault_Set; */
    
                
    PROCEDURE(BcDefault_Write,
                (const char* owner,const char* name,const char* value),INT32)
    {
        return(NXWriteDefault(owner,name,value));
    }/*BcDefault_Write; */
    

    PROCEDURE(BcDefault_WriteVector,
                (const char* owner,const BcDefault_T* vector),INT32)
    {
        return(NXWriteDefaults(owner,vector));
    }/*BcDefault_WriteVector; */
    

    PROCEDURE(BcDefault_Remove,
                (const char* owner,const char* name),INT32)
    {
        return(NXRemoveDefault(owner,name));
    }/*BcDefault_Remove; */
    

    PROCEDURE(BcDefault_Read,
                (const char* owner,const char* name),const char*)
    {
        return(NXReadDefault(owner,name));
    }/*BcDefault_Read; */
    
        
    PROCEDURE(BcDefault_UpdateAll,(void),void)
    {
        NXUpdateDefaults();
    }/*BcDefault_UpdateAll; */
    
    
    PROCEDURE(BcDefault_Update,
                (const char* owner,const char* name),const char*)
    {
        return(NXUpdateDefault(owner,name));
    }/*BcDefault_Update; */
    

    PROCEDURE(BcDefault_SetUser,
                (const char* newUser),const char*)
    {
        return(NXSetDefaultsUser(newUser));
    }/*BcDefault_SetUser; */


/*END BcDefault. */


/*** BcDefault.c                      -- 2003-11-30 03:29:12 -- pascal   ***/
