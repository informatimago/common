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
    Revision 1.1  2003/12/03 16:40:35  pjbpjb
    Added bc*.[hc] files.

    Revision 1.1  2001/04/30 02:22:16  pascal
    Renamed BcDefault files.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.1  95/11/16  06:28:30  pascal
    Initial revision
    
    1993/01/12 <PJB> Creation. (from NeXTstep defaults.h)
    1993/03/19 <PJB> Renamed BcDefault for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Interface:
        Application Kit,Release 2.0
        Copyright (c) 1988,1989,1990,NeXT,Inc.  All rights reserved.
    Interface and Macintosh Implementation: 
        Copyright Pascal J. Bourguignon 1993 - 1993
        All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
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

    static const char   rcsid[]="$Id: BcDefault-next.c,v 1.2 2004/09/23 04:24:28 pupjb Exp $";

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


/*** BcDefault-next.c                 --                     --          ***/
