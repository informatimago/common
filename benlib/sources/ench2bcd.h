/******************************************************************************
FILE:               ench2bcd.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the Honeywell 200/2000 series SSF tapes encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: ench2bcd.h,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: ench2bcd.h,v $
    Revision 1.1  2003/12/04 03:36:53  pjbpjb
    Cleaned-up.
    Moved bc*.[hc] in bclib.
    Fix.

    Revision 1.1  2002/08/11 02:36:41  pascal
    Fist check-in.
    
LEGAL
    Copyright Pascal J. Bourguignon 1991 - 1994
    All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef __ench2bcd__
#define __ench2bcd__

#include <Bencoding.h>


    extern BenEncodingTableT    Honeywell200BCDEncoding;

#endif
    
