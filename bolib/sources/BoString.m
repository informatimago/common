/******************************************************************************
FILE:               BoString.m
LANGUAGE:           Objective-C
SYSTEM:             ANSI (stdio,string)
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
#include <string.h>
#include <BoString.h>
#include <BcMem.h>
#include <BcImplementation.h>

@implementation BoString
/*
  char*           data
  INT32           length
  INT32           allocation
*/

/*
  INVARIANTS:
  data#NIL
  1<=allocation
  0<=length<allocation
  data[length]=(char)0
  for all i in [0..length-1], data[i]#(char)0
*/

#define AllocIncrement  (128)
#define Minimum(a,b)    (((a)<(b))?(a):(b))

-(id)setCapacity:(INT32)nAllocation copy:(BOOLEAN)copy
{
    char*       nData;
    INT32       nLength;
            
    if(nAllocation>1){
        nData=BcMem_Allocate((CARD32)sizeof(char)*(CARD32)nAllocation);
        if(copy){
            nLength=Minimum(nAllocation-1,length);
            BcMem_Copy(data,nData,(CARD32)nLength*(CARD32)sizeof(char));
        }else{
            nLength=0;
        }
    }else{
        nAllocation=1;
        nData=BcMem_Allocate((CARD32)sizeof(char)*(CARD32)nAllocation);
        nLength=0;
    }
    nData[nLength]=(char)0;
    BcMem_Deallocate((void**)(&data));
    data=nData;
    length=nLength;
    allocation=nAllocation;
    return(self);
}/*setCapacity;*/


/* Object:*/

-(id)init
{
    [super init];
    allocation=1;
    data=BcMem_Allocate((CARD32)sizeof(char)*(CARD32)allocation);
    length=0;
    data[length]=(char)0;
    return(self);
}/*init;*/


-(id)initCapacity:(INT32)size
{
    [self init];
    [self setCapacity:size copy:FALSE];
    return(self);
}/*initCapacity:;*/
    

-(id)free
{
    [self setCapacity:0 copy:FALSE];
    return([super free]);
}/*free;*/


/* BoObject:*/


-(void)printOn:(FILE*)file
{
    [super printOn:file];
    fprintf(file,"data=           %p\n",(void*)data);
    if(data!=NIL){
        fprintf(file,"*data=          \"%s\"\n",data);
    }
    fprintf(file,"length=         %"FMT_CARD32"\n",length);
    fprintf(file,"allocation=     %"FMT_CARD32"\n",allocation);
}/*printOn:;*/
    
    
/* BoString:*/

-(INT32)length
{
    return(length);
}/*length;*/
    
    
-(const char*)string
{
    return(data);
}/*string;*/


-(id)setString:(const char*)nString
{
    INT32       nLength;
        
    nLength=(INT32)strlen(nString);
    if(nLength>=allocation){
        [self setCapacity:nLength+1 copy:FALSE];
    }
    BcMem_Copy((const void*)nString,data,(CARD32)nLength*(CARD32)sizeof(char));
    data[nLength]=(char)0;
    length=nLength;
    return(self);
}/*setString:;*/


-(id)getString:(char*)string
{
    BcMem_Copy(data,string,(CARD32)length*(CARD32)sizeof(char));
    string[length]=(char)0;
    return(self);
}/*getString:;*/


-(char)charAt:(INT32)idx
{
    if((idx<0)OR(idx>=length)){
        return((char)0);
    }else{
        return(data[idx]);
    }
}/*charAt:;*/


-(id)setChar:(char)nChar at:(INT32)idx
{
    if((0<=idx)AND(idx<=length)){
        if(nChar==(char)0){
            length=idx;
        }else if(idx==length){
            if(allocation<=length+1){
                [self setCapacity:allocation+AllocIncrement copy:TRUE];
            }
            INC(length);
            data[length]=(char)0;
        }
        data[idx]=nChar;            
    }
    return(self);
}/*setChar:;*/


-(id)insert:(BoString*)substring at:(INT32)idx
{
    INT32       nLength;

    if(idx<0){
        idx=0;
    }else if(length<idx){
        idx=length;
    }
    nLength=length+substring->length;
    if(nLength>=allocation){
        /* SEE: We copy some char of self twice !*/
        [self setCapacity:nLength+1 copy:TRUE];
    }
    BcMem_Copy(data+idx,data+idx+substring->length,(CARD32)(length-idx+1)*(CARD32)sizeof(char));
    BcMem_Copy(substring->data,data+idx,(CARD32)(substring->length)*(CARD32)sizeof(char));
    length=nLength;
    return(self);
}/*insert:at:;*/


-(id)deleteFrom:(INT32)idx length:(INT32)delen
{
    if(idx<0){
        idx=0;
    }else if(length<=idx){
        return(self);
    }
    if(length<idx+delen){
        delen=length-idx;
    }
    BcMem_Copy(data+idx+delen,data+idx,(CARD32)(length-(idx+delen)+1)*(CARD32)sizeof(char));
    length=length-delen;
    return(self);
}/*deleteFrom:length:;*/


-(INT32)position:(BoString*)substring from:(INT32)idx
{
    /* SEE: could we use the FastStringSearch algorithm?*/
    INT32           pos;
    INT32           i;
    INT32           max;
        
    max=length-substring->length;       
    if(idx<0){
        pos=0;
    }else{
        pos=idx;
    }
    while(pos<=max){
        i=0;
        while(data[pos+i]==substring->data[i]){
            INC(i);
        }
        if(substring->data[i]==(char)0){
            return(pos);
        }
        INC(pos);
    }
    /* not found*/
    return(-1);
}/*position:;*/


-(id)copy:(BoString*)string from:(INT32)idx length:(INT32)copylen
{
    if(idx+copylen>string->length){
        copylen=string->length-idx;
    }
    if(copylen<=0){
        data[0]=(char)0;
        length=0;
        return(self);
    }
    if(copylen>=allocation){
        [self setCapacity:copylen+1 copy:FALSE];
    }
    BcMem_Copy(string->data+idx,data,(CARD32)copylen*(CARD32)sizeof(char));
    data[copylen]=(char)0;
    length=copylen;
    return(self);
}/*copy:from:length:;*/


-(id)append:(BoString*)tail
{
    return([self insert:tail at:length]);
}/*append:;*/


-(int)compare:(BoString*)other
{
    return(strcmp([self string],[other string]));   
}/*compare:;*/
    
@end
/*** BoString.m                       -- 2004-01-01 09:58:19 -- pascal   ***/
