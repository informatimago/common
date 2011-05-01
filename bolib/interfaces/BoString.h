/******************************************************************************
FILE:               BoString.h
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This class defines string object. The string data is dynamically allocated
    and reclaimed.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1993/01/29 <PJB> Creation.
    1993/03/19 <PJB> Updated to use newly Bc- prefixed interfaces.
LEGAL
    Copyright Pascal J. Bourguignon 1993 - 2011
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef BoString_h
#define BoString_h
#include <BcInterface.h>
#include <BcTypes.h>
#include <BoObject.h>

@interface BoString:BoObject
{
    char*           data;
    INT32           length;
    INT32           allocation;
}

    -(id)init;
    -(id)initCapacity:(INT32)size;
    
    
    -(INT32)length;
    -(const char*)string;
    -(id)setString:(const char*)value;
    -(id)getString:(char*)string;
    
    -(char)charAt:(INT32)idx;
    -(id)setChar:(char)nChar at:(INT32)idx;
    
    -(id)insert:(BoString*)substring at:(INT32)idx;
    -(id)deleteFrom:(INT32)idx length:(INT32)delen;
    -(INT32)position:(BoString*)substring from:(INT32)idx;
    -(id)copy:(BoString*)string from:(INT32)idx length:(INT32)copylen;
    -(id)append:(BoString*)tail;
    -(int)compare:(BoString*)other;
        
@end
#endif
/*** BoString.h                       -- 2003-11-30 07:34:05 -- pascal   ***/
