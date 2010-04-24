/******************************************************************************
FILE:               BpString.hh
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This class defines string object. The string data is dynamically allocated
    and reclaimed.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.7  1995/11/23 03:48:46  pascal
    Added BpClass and runtime class support in BpObject.
    Updated subclasses.

    Added dependant/dependee in BpObject.

    Revision 1.6  95/11/15  05:25:45  pascal
    Added BpString(const char*) constructor to easily initialize strings.
    
    Revision 1.5  95/10/22  03:19:54  pascal
    Setting revision name V1.
    
    Revision 1.2  95/10/22  03:05:18  pascal
    Modifications while adding BpDict.
    
    1993-01-29 <PJB> Creation.
    1993-03-16 <PJB> Translated from Objective-C to C++.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1993 - 2002

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
#ifndef __BpString__
#define __BpString__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh
#include BpClass_hh


#define BpString_SUPER BpObject
class BpString:public BpString_SUPER
{
public:

// birth and death:

    CONSTRUCTOR(BpString)
    DESTRUCTOR(BpString)

    BpString(const char* cString);
    // This special constructor can be used to easily build literal strings.
    
// override BpObject methods:

    METHOD(BpString,makeBrother,(void),BpObject*)
    METHOD(BpString,printOnLevel,(FILE* file,CARD32 level),void)

// BpString methods:

    METHOD(BpString,length,(void),INT32)
    METHOD(BpString,string,(void),const char*)
    METHOD(BpString,setString,(const char* nString),BpString*)
    METHOD(BpString,getString,(char* string),BpString*)
    METHOD(BpString,setStringNoCopy,(char* data,INT32 byteCount),void)

    METHOD(BpString,charAt,(INT32 index),char)
    METHOD(BpString,setCharAt,(char nChar,INT32 index),BpString*)
    
    METHOD(BpString,compare,(BpString* otherString),SignT)
    METHOD(BpString,insertAt,(BpString* substring,INT32 index),BpString*)
    METHOD(BpString,deleteFromLength,(INT32 index,INT32 delen),BpString*)
    METHOD(BpString,positionFrom,(BpString* substring,INT32 index),INT32)
    METHOD(BpString,copyFrom,(BpString* source),BpString*)
    METHOD(BpString,copyFromLength,
            (BpString* string,INT32 index,INT32 copylen),BpString*)
    METHOD(BpString,append,(BpString* tail),BpString*)
    METHOD(BpString,appendString,(const char* nString),BpString*)
    


    METHOD(BpString,shellQuoted,(void),BpString*)
        /*
            DO:         Quote the characters in the string so that
                        echo <resulting-string> will display exactly
                        the original string.
                        (All the special characters but +,-./:=@^_ are quoted).
                        The result may be unchanged, quoted inside \' or
                        escaped with \\.
        */

protected:
    char*           data;
    INT32           dlength;
    INT32           allocation;
    METHOD(BpString,setCapacityCopy,(INT32 nAllocation,BOOLEAN copy),BpString*)
    METHOD(BpString,_insertStringAt,
                    (const char* sString,INT32 sLength,INT32 index),BpString*)
};//BpString


#endif
