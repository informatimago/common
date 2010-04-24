/******************************************************************************
FILE:               encebcdi.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the EBCDIC encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: encebcdi.c,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: encebcdi.c,v $
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
#include <encebcdi.h>

    BenEncodingTableT   EBCDICEncoding={
            0,  /* 00 */
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
            0,  /* 10 */
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
            0,  /* 20 */
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
            0,  /* 30 */
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
            "space",    /* 40 */
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            "cent",
            "period",
            "less",
            "parenleft",
            "plus",
            "brokenbar",
            "ampersand",    /* 50 */
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            "exclam",
            "dollar",
            "star",
            "parenright",
            "semicolon",
            "asciitilde",
            "hyphen",   /* 60 */
            "slash",
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            "asciicircum",
            "comma",
            "percent",
            "underscore",
            "greater",
            "question",
            0,  /* 70 */
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            "cent",
            "colon",
            "numbersign",
            "at",
            "quotesingle",
            "equal",
            "quotedbl",
            "onequater",
            "a",
            "b",
            "c",
            "d",
            "e",
            "f",
            "g",
            "h",
            "i",
            0,
            "braceleft",
            0,
            0,
            0,
            0,
            "onehalf",
            "j",
            "k",
            "l",
            "m",
            "n",
            "o",
            "p",
            "q",
            "r",
            0,
            "braceright",
            0,
            0,
            0,
            0,
            0,  /* A0 */
            0,
            "s",
            "t",
            "u",
            "v",
            "w",
            "x",
            "y",
            "z",
            0,
            0,
            0,
            "bracketleft",
            0,
            0,
            0,  /* 80 */
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
            "bracketright",
            0,
            0,
            "braceleft",
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            0,
            0,
            0,
            0,
            0,
            0,
            "braceright",
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            0,
            0,
            0,
            0,
            0,
            0,
            "backslash",
            0,
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            0,
            0,
            0,
            0,
            0,
            0,
            "zero",
            "one",
            "two",
            "three",
            "four",
            "five",
            "six",
            "seven",
            "eight",
            "nine",
            "brokenbar",
            0,
            0,
            0,
            0,
            0 /*END*/
        };/*EBCDICEncoding*/


/*** encebcdi.c                       -- 2003-11-30 19:02:33 -- pascal   ***/
