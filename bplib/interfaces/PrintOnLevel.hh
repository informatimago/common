/******************************************************************************
FILE:           PrintOnLevel.hh
LANGUAGE:       C++
SYSTEM:         ANSI
USER-INTERFACE: ANSI
DESCRIPTION

    At the beginning was only some simple macros. But Linux gcc insists on 
    having __signed__ integers as size parameters, while NeXTSTEP gcc was
    happy with __unsigned__ integers. 

    Negative values for our level parameter have no meaning, so we'll keep
    them as __unsigned__ integers, and now, we have this PrintOnLevel
    package.

    Note that from now on, the prefered way is to use these PrintOnLevel
    functions, instead of macros. The problem of the macros is that when
    the implementation must change, as well must change the header files
    where these macros are defined. Bad, bad, bad.

AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1992-08-16 <PJB> Creation.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

    This file is part of the bplib library..

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
#ifndef __PrintOnLevel__
#define __PrintOnLevel__ 1
extern "C"{
#include <stdio.h>
#include <stdarg.h>
}
#include <names.h>
#include BcInterface_h
#include BcTypes_h

    extern void PrintOnLevel_open(FILE* file,CARD32 level,const char* name);
    extern void PrintOnLevel_printf(FILE* file,CARD32 level,
            const char* name,const char* format,...);
    extern void PrintOnLevel_elementPrintf(FILE* file,CARD32 level,
            const char* name,CARD32 index,const char* format,...);
    extern void PrintOnLevel_close(FILE* file,CARD32 level);


#endif



