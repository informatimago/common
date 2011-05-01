/******************************************************************************
FILE:               apraccent.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This file define an approximation of accented characters to sequences
    of '\' accent letter.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    $Id: apraccen.c,v 1.1 2003/12/04 03:36:53 pjbpjb Exp $
    $Log: apraccen.c,v $
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
#include <apraccen.h>

    /* This table must be sorted on the charName (first string) for a dichotomy
        search is used on it in BenFindCharNameInApproximationTable(). */
    

    static BenApproximationT approximations[]={
            { "Aacute",             "\\'A" },
            { "Acircumflex",        "\\^A" },
            { "Adieresis",          "\\\"A" },
            { "Agrave",             "\\`A" },
            { "Aring",              "\\oA" },
            { "Atilde",             "\\~A" },
            { "Ccedilla",           "\\,C" },
            { "Eacute",             "\\'E" },
            { "Ecircumflex",        "\\^E" },
            { "Edieresis",          "\\\"E" },
            { "Egrave",             "\\`E" },
            { "Iacute",             "\\'I" },
            { "Icircumflex",        "\\^I" },
            { "Idieresis",          "\\\"I" },
            { "Igrave",             "\\`I" },
            { "Ntilde",             "\\~N" },
            { "Oacute",             "\\'O" },
            { "Ocircumflex",        "\\^O" },
            { "Odieresis",          "\\\"O" },
            { "Ograve",             "\\`O" },
            { "Omicron",            "\\-O" },
            { "Oslash",             "\\/O" },
            { "Otilde",             "\\~O" },
            { "Uacute",             "\\'U" },
            { "Ucircumflex",        "\\^U" },
            { "Udieresis",          "\\\"U" },
            { "Ugrave",             "\\`U" },
            { "Yacute",             "\\'Y" },
            { "Ydieresis",          "\\\"Y" },
            { "aacute",             "\\'a" },
            { "acircumflex",        "\\^a" },
            { "adieresis",          "\\\"a" },
            { "agrave",             "\\`a" },
            { "approxequal",        "\\~=" },
            { "aring",              "\\oa" },
            { "atilde",             "\\~a" },
            { "ccedilla",           "\\,c" },
            { "eacute",             "\\'e" },
            { "ecircumflex",        "\\^e" },
            { "edieresis",          "\\\"e" },
            { "egrave",             "\\`e" },
            { "iacute",             "\\'i" },
            { "icircumflex",        "\\^i" },
            { "idieresis",          "\\\"i" },
            { "igrave",             "\\`i" },
            { "ntilde",             "\\~n" },
            { "oacute",             "\\'o" },
            { "ocircumflex",        "\\^o" },
            { "odieresis",          "\\\"o" },
            { "ograve",             "\\`o" },
            { "omicron",            "\\-o" },
            { "oslash",             "\\/o" },
            { "otilde",             "\\~o" },
            { "uacute",             "\\'u" },
            { "ucircumflex",        "\\^u" },
            { "udieresis",          "\\\"u" },
            { "ugrave",             "\\`u" },
            { "yacute",             "\\'y" },
            { "ydieresis",          "\\\"y" },
            { 0,                    0 }
        };

    BenApproximationTableT  AccentApproximationTable={0,approximations};

/*** apraccen.c                       -- 2003-11-30 19:01:25 -- pascal   ***/
