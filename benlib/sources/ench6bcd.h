/******************************************************************************
FILE:               ench6bcd.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the Honeywell 600/6000 series SSF tapes encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: ench6bcd.h,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: ench6bcd.h,v $
    Revision 1.1  2003/12/04 03:36:53  pjbpjb
    Cleaned-up.
    Moved bc*.[hc] in bclib.
    Fix.

    Revision 1.1  2002/08/11 02:36:41  pascal
    Fist check-in.
    
LEGAL
    Copyright Pascal J. Bourguignon 1991 - 2011
    All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef __ench6bcd__
#define __ench6bcd__

#include <Bencoding.h>


    extern BenEncodingTableT    Honeywell600BCDEncoding;

#endif
    
