/******************************************************************************
FILE:               CheckRIB.m
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
    Copyright Pascal J. Bourguignon 1994 - 2011
    All Rights Reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#import <CheckRIB.h>
#import <BpRIB.hh>
#include <BcImplementation.h>

@implementation CheckRIB

    - init
    {
        [super init];
        ribLock=FALSE;
        rib=NEW(BpRIB);
        return(self);
    }//init;
    
    
    - appDidInit:sender
    {
        [[[ribText window] getFieldEditor:YES for:ribText] 
            setCharFilter:NXFieldFilter];
        // done in nib // [ribText setTextDelegate:self];
        return(self);
    }//appDidInit:;
    
    
    - (BOOL)textWillEnd:textObject
    {
        return(NO);
    }//textWillEnd:;
    
    
    - textDidEnd:sender endChar:(unsigned short)whyEnd
    {
        if(ribLock){
            return(self);
        }else{
            return([self computeKey:sender]);
        }
    }//textDidEnd:endChar:;
    
    
    - computeKey:sender
    {
            char        ribstr[64];
            const char* value;
            
        ribLock=TRUE;
        value=[ribText stringValue];
        if((rib->setRIB(value,FALSE))||(rib->setRIB(value,TRUE))){
            rib->getRIB(TRUE,ribstr);
            [ribText setStringValue:ribstr];
            [messageText setStringValue:NXLocalizedString("",NULL,Valid RIB Message)];
        }else{
            [messageText setStringValue:NXLocalizedString("Invalid R.I.B.",NULL,Invalid RIB Message)];
        }
        [ribText selectText:self];
        ribLock=FALSE;
        return(self);
    }//computeKey:;

@end
