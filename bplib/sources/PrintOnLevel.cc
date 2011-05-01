/******************************************************************************
FILE:           PrintOnLevel.cc
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
    Copyright Pascal J. Bourguignon 1992 - 2011

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
#include <names.h>
#include PrintOnLevel_hh
#include BcImplementation_h


#if defined(linux) || defined(MACOSX)
#define asSize(x)  ((int)x)
#else
#define asSize(x)  (x)
#endif

    void PrintOnLevel_open(FILE* file,CARD32 level,const char* name)
    {
        fprintf(file,"%*s%-16s=\n%*s{\n",asSize(level),"",name,asSize(level),"");
    }//PrintOnLevel_open;


    void PrintOnLevel_printf(FILE* file,CARD32 level,const char* name,
            const char* format,...)
    {
        va_list parameters;
        va_start(parameters,format);
        fprintf(file,"%*s%-16s=",asSize(level),"",name);
        vfprintf(file,format,parameters);
        fprintf(file,"\n");
        va_end(parameters);
    }//PrintOnLevel_printf;


    void PrintOnLevel_elementPrintf(FILE* file,CARD32 level,const char* name,
                                    CARD32 index,const char* format,...)
    {
        va_list parameters;
        va_start(parameters,format);
        fprintf(file,"%*s%-16s[%4"FMT_CARD32"]=",asSize(level),"",name,index);
        vfprintf(file,format,parameters);
        fprintf(file,"\n");
        va_end(parameters);
    }//PrintOnLevel_elementPrintf;


    void PrintOnLevel_close(FILE* file,CARD32 level)
    {
        fprintf(file,"%*s}\n",asSize(level),"");
    }//PrintOnLevel_close;


//END PrintOnLevel.
