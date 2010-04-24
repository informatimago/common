/******************************************************************************
FILE:               ench2bcd.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the Honeywell 200/2000 series SSF tapes encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: ench2bcd.c,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: ench2bcd.c,v $
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
#include <ench2bcd.h>

    BenEncodingTableT   Honeywell200BCDEncoding={
            "zero",                 /* 0 */
            "one",                  /* 1 */
            "two",                  /* 2 */
            "three",                /* 3 */
            "four",                 /* 4 */
            "five",                 /* 5 */
            "six",                  /* 6 */
            "seven",                /* 7 */
            "eight",                /* 8 */
            "nine",                 /* 9 */
            "quotesingle",          /* ' */
            "equal",                /* = */
            "colon",                /* : */
            "space",                /*   */
            "greater",              /* > */
            "ampersand",            /* & */
            "plus",                 /* + */
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "semicolon",            /* ; */
            "period",               /* . */
            "parenright",           /* ) */
            "percent",              /* % */
            "bracketleft",          /* [ */
            "question",             /* ? */
            "hyphen",               /* - */
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            "numbersign",           /* # */
            "dollar",               /* $ */
            "star",                 /* * */
            "quotedbl",             /* " */
            "bracketright",         /* ] */
            "exclam",               /* ! */
            "less",                 /* < */
            "slash",                /* / */
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            "at",                   /* @ */
            "comma",                /* , */
            "parenleft",            /* ( */
            "braceleft",            /* { */
            "braceright",           /* } */
            0,                  /* padding character */
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0 /*END*/
        };/*Honeywell200BCDEncoding*/
        

/*** ench2bcd.c                       -- 2003-11-30 19:02:29 -- pascal   ***/
