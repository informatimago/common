/******************************************************************************
FILE:               apraccen.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define an approximation of accented characters to sequences
    of '\' accent letter.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: apraccen.h,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: apraccen.h,v $
    Revision 1.1  2003/12/04 03:36:53  pjbpjb
    Cleaned-up.
    Moved bc*.[hc] in bclib.
    Fix.

    Revision 1.1  2002/08/11 02:36:41  pascal
    Fist check-in.
    
LEGAL
    Copyright Pascal J. Bourguignon 1991 - 1999
    All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef __apraccen__
#define __apraccen__

#include <Bencoding.h>
    
    
    extern BenApproximationTableT   AccentApproximationTable;

#endif /* apraccen */

