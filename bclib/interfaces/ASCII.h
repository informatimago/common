/******************************************************************************
FILE:               ASCII.h
LANGUAGE:           C
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This module define ASCII non-printable CHARacters.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1991-03-31 <PJB> Translated from Modula-2 to C.
LEGAL
    Copyright Pascal J. Bourguignon 1990 - 2002

    This file is part of the bclib library.

    This  program is  free software;  you can  redistribute  it and/or
    modify it  under the  terms of the  GNU General Public  License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program  is distributed in the  hope that it  will be useful,
    but  WITHOUT ANY WARRANTY;  without even  the implied  warranty of
    MERCHANTABILITY or FITNESS FOR  A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a  copy of the GNU General Public License
    along with  this program; see the  file COPYING; if  not, write to
    the Free  Software Foundation, Inc.,  59 Temple Place,  Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
#ifndef __ASCII__
#define __ASCII__ defined
#include <names.h>
#include BcTypes_h

#define ASCII_NUL                ((CHAR)0x00)   /*  ^@ */
#define ASCII_SOH                ((CHAR)0x01)   /*  ^A */
#define ASCII_STX                ((CHAR)0x02)   /*  ^B */
#define ASCII_ETX                ((CHAR)0x03)   /*  ^C */
#define ASCII_EOT                ((CHAR)0x04)   /*  ^D */
#define ASCII_ENQ                ((CHAR)0x05)   /*  ^E */
#define ASCII_ACK                ((CHAR)0x06)   /*  ^F */
#define ASCII_BEL                ((CHAR)0x07)   /*  ^G */
#define ASCII_BS                 ((CHAR)0x08)   /*  ^H */
#define ASCII_HT                 ((CHAR)0x09)   /*  ^I */
#define ASCII_LF                 ((CHAR)0x0A)   /*  ^J */
#define ASCII_VT                 ((CHAR)0x0B)   /*  ^K */
#define ASCII_FF                 ((CHAR)0x0C)   /*  ^L */
#define ASCII_CR                 ((CHAR)0x0D)   /*  ^M */
#define ASCII_SO                 ((CHAR)0x0E)   /*  ^N */
#define ASCII_SI                 ((CHAR)0x0F)   /*  ^O */
#define ASCII_DLE                ((CHAR)0x10)   /*  ^P */
#define ASCII_DC1                ((CHAR)0x11)   /*  ^Q */
#define ASCII_DC2                ((CHAR)0x12)   /*  ^R */
#define ASCII_DC3                ((CHAR)0x13)   /*  ^S */
#define ASCII_DC4                ((CHAR)0x14)   /*  ^T */
#define ASCII_NAK                ((CHAR)0x15)   /*  ^U */
#define ASCII_SYN                ((CHAR)0x16)   /*  ^V */
#define ASCII_ETB                ((CHAR)0x17)   /*  ^W */
#define ASCII_CAN                ((CHAR)0x18)   /*  ^X */
#define ASCII_EM                 ((CHAR)0x19)   /*  ^Y */
#define ASCII_SUB                ((CHAR)0x1A)   /*  ^Z */
#define ASCII_ESC                ((CHAR)0x1B)   /*  ^[ */
#define ASCII_FS                 ((CHAR)0x1C)   /*  ^\ */
#define ASCII_GS                 ((CHAR)0x1D)   /*  ^] */
#define ASCII_RS                 ((CHAR)0x1E)   /*  ^^ */
#define ASCII_US                 ((CHAR)0x1F)   /*  ^_ */
#define ASCII_SP                 ((CHAR)0x20)   
#define ASCII_DEL                ((CHAR)0x7F)


#endif /* ASCII. */



