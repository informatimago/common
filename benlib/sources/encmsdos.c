/******************************************************************************
FILE:               encmsdos.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the MS-DOS encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: encmsdos.c,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: encmsdos.c,v $
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
#include <encmsdos.h>

    BenEncodingTableT   MSDOSEncoding={
            "asciinul",
            "asciisoh",
            "asciistx",
            "asciietx",
            "asciieot",
            "asciienq",
            "asciiack",
            "asciibel",
            "asciibs",
            "asciiht",
            "asciilf",
            "asciivt",
            "asciiff",
            "asciicr",
            "asciiso",
            "asciisi",
            "asciidle",
            "asciidc1",
            "asciidc2",
            "asciidc3",
            "asciidc4",
            "asciinak",
            "asciisyn",
            "asciietb",
            "asciican",
            "asciiem",
            "asciisub",
            "asciiesc",
            "asciifs",
            "asciigs",
            "asciirs",
            "asciius",
            "space",
            "exclam",
            "quotedbl",
            "numbersign",
            "dollar",
            "percent",
            "ampersand",
            "quoteright",
            "parenleft",
            "parenright",
            "asterisk",
            "plus",
            "comma",
            "hyphen",
            "period",
            "slash",
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
            "colon",
            "semicolon",
            "less",
            "equal",
            "greater",
            "question",
            "at",
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            "bracketleft",
            "backslash",
            "bracketright",
            "asciicircum",
            "underscore",
            "quoteleft",
            "a",
            "b",
            "c",
            "d",
            "e",
            "f",
            "g",
            "h",
            "i",
            "j",
            "k",
            "l",
            "m",
            "n",
            "o",
            "p",
            "q",
            "r",
            "s",
            "t",
            "u",
            "v",
            "w",
            "x",
            "y",
            "z",
            "braceleft",
            "bar",              /* acutally "brokenbar" ! */
            "braceright",
            "asciitilde",
            "Delta",            /* seems like! */
            "Ccedilla",
            "udieresis",
            "eacute",
            "acircumflex",
            "adieresis",
            "agrave",
            "aring",
            "ccedilla",
            "ecircumflex",
            "edieresis",
            "egrave",
            "idieresis",
            "icircumflex",
            "igrave",
            "Adieresis",
            "Aring",
            "Eacute",
            "ae",
            "fl",
            "ocircumflex",
            "odieresis",
            "ograve",
            "ucircumflex",
            "ugrave",
            "ydieresis",
            "Odieresis",
            "Udieresis",
            "cent",
            "sterling",
            "yen",
            "Pt",                   /**** MSDOS */
            "florin",
            "aacute",
            "iacute",
            "oacute",
            "uacute",
            "ntilde",
            "Ntilde",
            "ordfeminine",
            "ordmasculine",
            "questiondown",
            "logicalnotmirored",    /**** MSDOS */
            "logicalnot",
            "onehalf",
            "onequarter",
            "exclamdown",
            "guillemotleft",
            "guillemotright",
            "darkgray",             /**** MSDOS */
            "gray",                 /**** MSDOS */
            "lightgray",            /**** MSDOS */
            "vertbar",              /**** MSDOS */
            "leftvertbar",          /**** MSDOS */
            "dblleftvertbar",       /**** MSDOS */
            "leftdblvertbar",       /**** MSDOS */
            "leftdbldownbar",       /**** MSDOS */
            "dblleftdownbar",       /**** MSDOS */
            "dblleftdblvertbar",    /**** MSDOS */
            "dblvertbar",           /**** MSDOS */
            "dblleftdbldownbar",    /**** MSDOS */
            "dblleftdblupbar",      /**** MSDOS */
            "leftdblupbar",         /**** MSDOS */
            "dblleftupbar",         /**** MSDOS */
            "leftdownbar",          /**** MSDOS */
            "rightupbar",           /**** MSDOS */
            "horizupbar",           /**** MSDOS */
            "horizdownbar",         /**** MSDOS */
            "rightvertbar",         /**** MSDOS */
            "horizbar",             /**** MSDOS */
            "horizvertbar",         /**** MSDOS */
            "dblrightvertbar",      /**** MSDOS */
            "rightdblvertbar",      /**** MSDOS */
            "dblrightdblupbar",     /**** MSDOS */
            "dblrightdbldownbar",   /**** MSDOS */
            "dblhorizdblupbar",     /**** MSDOS */
            "dblhorizdbldownbar",   /**** MSDOS */
            "dblrightdblvertbar",   /**** MSDOS */
            "dblhorizbar",          /**** MSDOS */
            "dblhorizdblvertbar",   /**** MSDOS */
            "dblhorizupbar",        /**** MSDOS */
            "horizdblupbar",        /**** MSDOS */
            "dblhorizdownbar",      /**** MSDOS */
            "horizdbldownbar",      /**** MSDOS */
            "rightdblupbar",        /**** MSDOS */
            "dblrightupbar",        /**** MSDOS */
            "dblrightdownbar",      /**** MSDOS */
            "dblrightdbldownbar",   /**** MSDOS */
            "horizdblvertbar",      /**** MSDOS */
            "dblhorizvertbar",      /**** MSDOS */
            "leftupbar",            /**** MSDOS */
            "rightdownbar",         /**** MSDOS */
            "white",                /**** MSDOS */
            "whitebottom",          /**** MSDOS */
            "whiteleft",            /**** MSDOS */
            "whiteright",           /**** MSDOS */
            "whitetop",             /**** MSDOS */
            "alpha",
            "beta",
            "Gamma",
            "pi",
            "summation",
            "sigma",
            "mu",
            "tau",
            "Phi",
            "Theta",
            "Omega",
            "delta",
            "infinity",
            "oslash",               /**** ? */
            "element",
            "intersection",
            "congruent",
            "plusminus",
            "lessequal",
            "greaterequal",
            "intergraltp",
            "intergralbt",
            "divide",
            "approxequal",
            "degree",
            "dotmath",              /**** ? */
            "periodcentered",
            "radical",
            "nsuperior",
            "twosuperior",
            "whiteleftbottom",
            0 /*END*/
        };/*MSDOSEncoding*/


/*** encmsdos.c                       -- 2003-11-30 19:03:46 -- pascal   ***/
