/******************************************************************************
FILE:               CheckRIB.h
LANGUAGE:           Objective-C
SYSTEM:             NEXTSTEP_3.0
USER-INTERFACE:     NEXTSTEP_3.0
DESCRIPTION
    This program tests the BpRIB class.
BUGS
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    1994/12/28 <PJB> Creation.
LEGAL
    Copyright Pascal J. Bourguignon 1994 - 1995
    All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
extern "C"{
#import <appkit/appkit.h>
}
#import <BpRIB.hh>

@interface CheckRIB:Object
{
    id          messageText;
    id          ribText;
    BpRIB*      rib;
    BOOLEAN     ribLock;
}
    
    - computeKey:sender;

@end
