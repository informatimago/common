/******************************************************************************
FILE:               encnxstp.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define the NeXTSTEP encoding array.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: encnxstp.c,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: encnxstp.c,v $
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
#include <encnxstp.h>

    BenEncodingTableT   NextStepEncoding={
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
            "bar",
            "braceright",
            "asciitilde",
            "asciidel",
            0,
            "Agrave",
            "Aacute",
            "Acircumflex",
            "Atilde",
            "Adieresis",
            "Aring",
            "Ccedilla",
            "Egrave",
            "Eacute",
            "Ecircumflex",
            "Edieresis",
            "Igrave",
            "Iacute",
            "Icircumflex",
            "Idieresis",
            "Eth",
            "Ntilde",
            "Ograve",
            "Oacute",
            "Ocircumflex",
            "Otilde",
            "Odieresis",
            "Ugrave",
            "Uacute",
            "Ucircumflex",
            "Udieresis",
            "Yacute",
            "Thorn",
            "mu",
            "multiply",
            "divide",
            "copyright",
            "exclamdown",
            "cent",
            "sterling",
            "fraction",
            "yen",
            "florin",
            "section",
            "currency",
            "quotesingle",
            "quotedblleft",
            "guillemotleft",
            "guilsinglleft",
            "guilsinglright",
            "fi",
            "fl",
            "registered",
            "endash",
            "dagger",
            "daggerdbl",
            "periodcentered",
            "brokenbar",
            "paragraph",
            "bullet",
            "quotesinglbase",
            "quotedblbase",
            "quotedblright",
            "guillemotright",
            "ellipsis",
            "perthousand",
            "logicalnot",
            "questiondown",
            "onesuperior",
            "grave",
            "acute",
            "circumflex",
            "tilde",
            "macron",
            "breve",
            "dotaccent",
            "dieresis",
            "twosuperior",
            "ring",
            "cedilla",
            "threesuperior",
            "hungarumlaut",
            "ogonek",
            "caron",
            "emdash",
            "plusminus",
            "onequarter",
            "onehalf",
            "threequarters",
            "agrave",
            "aacute",
            "acircumflex",
            "atilde",
            "adieresis",
            "aring",
            "ccedilla",
            "egrave",
            "eacute",
            "ecircumflex",
            "edieresis",
            "igrave",
            "AE",
            "iacute",
            "ordfeminine",
            "icircumflex",
            "idieresis",
            "eth",
            "ntilde",
            "Lslash",
            "Oslash",
            "OE",
            "ordmasculine",
            "ograve",
            "oacute",
            "ocircumflex",
            "otilde",
            "odieresis",
            "ae",
            "ugrave",
            "uacute",
            "ucircumflex",
            "dotlessi",
            "udieresis",
            "yacute",
            "lslash",
            "oslash",
            "oe",
            "germandbls",
            "thorn",
            "ydieresis",
            0,
            0 /*END*/
        };/*NextStepEncoding*/

/*** encnxstp.c                       -- 2003-11-30 19:04:11 -- pascal   ***/
