/******************************************************************************
FILE:               encunifd.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the UnivacFieldData encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: encunifd.h,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: encunifd.h,v $
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
#ifndef __encunifd__
#define __encunifd__

#include <Bencoding.h>


    extern BenEncodingTableT    UnivacFieldDataEncoding;

#endif
    
