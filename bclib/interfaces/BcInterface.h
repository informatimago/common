/******************************************************************************
FILE:               BcInterface.h
LANGUAGE:           ANSI-C
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This file defines macro to be used by C++ programs.
    (The PROCEDURE macro may be used by C and Objective-C programs).
    Usage:
#include <names.h>
#include BcInterface_h
#include BcTypes_h
            #include <...>
#include BcImplementation_h
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

    Revision 1.4  96/08/04  07:09:58  pascal
    *** empty log message ***
    
    Revision 1.3  95/11/30  10:31:17  pascal
    Fix apres fusion avec les objets developpes par ERS
    
    Revision 1.2  95/11/24  08:35:34  pascal
    Replaced MEMBERPROC by FRIENDPROC.
    
    Revision 1.1  95/11/16  06:37:41  pascal
    Initial revision
    
    1989-08-07 <PJB> Creation.
    1991-03-04 <PJB> Updated for use with C version of Isdn Driver.
    1992-02-03 <PJB> Added PROCEDURE, METHOD, CONSTRUCTOR, DESTRUCTOR,
                        IN, OUT, INOUT, FIELD, and VAR macros.
    1992-07-22 <PJB> Splited PJBTypes into BoInterface, BoTypes and 
                        BoImplementation.
    1993-03-19 <PJB> Renamed BcInterface for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1989 - 2011

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
#ifndef inhibit_inhibit_BcInterface_h
#define inhibit_inhibit_BcInterface_h


#undef  CONSTRUCTOR2
#undef  CONSTRUCTOR
#undef  DESTRUCTOR
#undef  CLASSMETHOD
#undef  METHOD
#undef  ABSTRACTMETHOD
#undef  FRIENDPROC
#undef  PROCEDURE

#undef  IN
#undef  OUT
#undef  INOUT
#undef  FIELD
#undef  VAR
#undef  TYPE


#define CONSTRUCTOR2(cls,prm)                                cls  prm    ;
#define CONSTRUCTOR(cls)                                     cls  (void) ;
#define DESTRUCTOR(cls)                     virtual         ~cls  (void) ;
#define CLASSMETHOD(cls,met,prm,res) static         res      met  prm    ;
#define METHOD(cls,met,prm,res)             virtual res      met  prm    ;
#define ABSTRACTMETHOD(cls,met,prm,res)     virtual res      met  prm =0 ;
#define FRIENDPROC(nam,prm,res)      friend         res      nam  prm    ;
#define PROCEDURE(nam,prm,res)       extern         res      nam  prm    ;

#define IN(nam,typ)      const   typ  nam
#define OUT(nam,typ)             typ& nam
#define INOUT(nam,typ)           typ& nam
#define FIELD(nam,typ)           typ  nam;
#define VAR(nam,typ)             typ  nam;
#define TYPE(nam,typ)    typedef typ  nam;

#endif /*BcInterface.*/
/*** BcInterface.h                    -- 2001-04-10 16:31:01 -- pascal   ***/
