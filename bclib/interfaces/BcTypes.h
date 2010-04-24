/******************************************************************************
FILE:               BcTypes.h
LANGUAGE:           ANSI-C
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This file defines general types and constants.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.2  2001/05/15 23:54:26  pascal
    Prefixed "inhibit_" to the name of the macro used to inhibit multiple inclusion.

    Made use of  macros instead of file names to be  able to redefine them
    when porting to  and compiling on old and awkward  OS with short names
    such as  Macintosh (do anybody still  use MS-DOS? No,  I thing they've
    all switched to MS-Windows where at least they don't have anymore this
    problem, not like those hard headed MacOS users...).

    Revision 1.1  2001/05/10 05:34:14  pascal
    Initial entry into CVS.

    Revision 1.1  2001/04/30 06:11:38  pjb
    Initial entry into CVS.

    Revision 1.3  1995/11/30 10:31:21  pascal
    Fix apres fusion avec les objets developpes par ERS

    Revision 1.2  95/11/16  12:07:22  pascal
    Some small correction to compile in MSVC.
    
    Revision 1.1  95/11/16  06:37:47  pascal
    Initial revision
    
    1989-08-07 <PJB> Creation.
    1991-03-04 <PJB> Updated for use with C version of Isdn Driver.
    1992-02-03 <PJB> Added PROCEDURE, METHOD, CONSTRUCTOR, DESTRUCTOR,
                        IN, OUT, INOUT, FIELD, and VAR macros.
    1992-07-22 <PJB> Splited PJBTypes into BoInterface, BoTypes and 
                        BoImplementation.
    1993-01-12 <PJB> Added SignT, CHAR & UNICODE.
    1993-03-19 <PJB> Renamed BcTypes for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1989 - 2002

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
*****************************************************************************/
#ifndef inhibit_inhibit_BcTypes_h
#define inhibit_inhibit_BcTypes_h
#include <limits.h> /* import CHAR_BIT */

#ifdef _WIN32
    typedef __int64                 INT64;
    typedef unsigned __int64        CARD64;
#else
#if 0
        /* long long is not ISO C */
    typedef long long int           INT64;
    typedef unsigned long long int  CARD64;
#endif
#endif
    typedef long int                INT32;
    typedef short int               INT16;
    typedef char                    INT8;
    typedef unsigned long int       CARD32;
    typedef unsigned short int      CARD16;
    typedef unsigned char           CARD8;
    typedef int                     SignT;  /* [ -1, 0,  +1 ] */
    typedef unsigned char           CHAR;
    typedef CARD16                  UNICODE;
    typedef double                  DECIMAL;
    typedef void*                   ADDRESS;

#define MIN_INT32           ((INT32)0x80000000)
#define MAX_INT32           ((INT32)0x7fffffff)
#define MAX_CARD32          ((CARD32)0xffffffff)
#define MIN_INT16           ((INT32)0x8000)
#define MAX_INT16           ((INT32)0x7fff)
#define MAX_CARD16          ((CARD32)0xffff)
#define MIN_INT8            ((INT32)0x80)
#define MAX_INT8            ((INT32)0x7f)
#define MAX_CARD8           ((CARD32)0xff)

    typedef CHAR                CSTRING255[256];
    typedef CHAR                CSTRING63[64];
    typedef CHAR                CSTRING31[32];

#undef NIL
#define NIL                 (0) /*((void*)(0))*/


#ifdef __cplusplus
#undef  BOOLEAN
#undef  TRUE
#undef  FALSE
#define BOOLEAN bool
#define TRUE    true
#define FALSE   false
#else
#undef  TRUE
#undef  FALSE
    typedef enum {FALSE=0,TRUE} BOOLEAN;
#endif


#define INC(i)       (++(i))
#define DEC(i)       (--(i))
#define INCR(i,n)    ((i)+=(n))
#define DECR(i,n)    ((i)-=(n))
#ifndef ODD
#define ODD(i)       ((((CARD32)(i))&1)!=0)
#endif
#define CHR(i)       ((CHAR)(i))
#define ORD(i)       ((CARD32)(i))
#define VAL(t,v)     ((t)(v))
#define ADR(v)       (&(v))
#define MOD          %
#define DIV          /
#define AND          &&
#define OR           ||
#define NOT          !
#define LSHIFT(x,y)  ((((y)<0)||((sizeof((x)+0)*CHAR_BIT)<=(y)))?0:((x)<<(y)))
#define RSHIFT(x,y)  ((((y)<0)||((sizeof((x)+0)*CHAR_BIT)<=(y)))?0:((x)>>(y)))
#define INCL(s,x)    ((s)|=LSHIFT(1,x))
#define EXCL(s,x)    ((s)&=(~LSHIFT(1,x)))
#define FLAGIN(f,s)  (((f)&(s))!=0)
#define ULSHIFT(x,y) ((x)<<(y))
#define BITIN(b,s)   FLAGIN(ULSHIFT(1,b),(s))

#endif 
/*** BcTypes.h                        --                     --          ***/
