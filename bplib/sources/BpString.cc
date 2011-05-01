/******************************************************************************
FILE:               BpString.cc
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
    
    Revision 1.7  1995/11/23 03:53:33  pascal
    Added BpClass and runtime class support in BpObject. Updated subclasses.
    Added dependant/dependee in BpObject.

    Revision 1.6  95/11/15  05:25:07  pascal
    Added BpString(const char*) constructor to easily initialize strings.
    
    Revision 1.5  95/10/22  03:19:13  pascal
    Setting revision name V1.
    
    Revision 1.4  95/10/22  02:58:23  pascal
    Added ' ' in log comment of revision 1.1.
    
    Revision 1.3  95/10/22  02:53:27  pascal
    Changed rcsid from Header to Id.
    
    Revision 1.2  95/10/22  02:39:26  pascal
    Modifications while adding BpDict.
    
    Revision 1.1  95/10/18  06:25:58  pascal
    Initial revision

    1993-01-29 <PJB> Creation.
    1993-03-19 <PJB> Renamed BpXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1993 - 2011

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
extern "C"{
#include <string.h>
#include <ctype.h>
}
#include <names.h>
#include BpString_hh
extern "C"{
#include BcMem_h
}
#include BcImplementation_h

static const char rcsid[]="$Id: BpString.cc,v 1.1 2003/12/04 04:52:58 pjbpjb Exp $";




/*
  INVARIANTS:
  data#NIL
  1<=allocation
  0<=dlength<allocation
  data[dlength]=(char)0
  for all i in [0..dlength-1], data[i]#(char)0
*/

#define AllocIncrement  (128)
#define Minimum(a,b)    (((a)<(b))?(a):(b))

// birth and death:

CONSTRUCTOR(BpString)
{
    BpClass_PLUG(BpString);
    allocation=1;
    data=(char*)BcMem_Allocate(sizeof(char)*allocation);
    dlength=0;
    data[dlength]=(char)0;
}//BpString;
    
DESTRUCTOR(BpString)
{
    BcMem_Deallocate((void**)(&data));
}//~BpString;


BpString::BpString(const char* cString)
{
    BpClass_PLUG(BpString);
    allocation=1;
    data=(char*)BcMem_Allocate(sizeof(char)*allocation);
    dlength=0;
    data[dlength]=(char)0;
    this->setString(cString);
}//BpString;

// override BpObject methods:

METHOD(BpString,makeBrother,(void),BpObject*)
{
    return(NEW(BpString));
}//makeBrother;
    

METHOD(BpString,printOnLevel,(FILE* file,CARD32 level),void)
{
    BpString_SUPER::printOnLevel(file,level);
    PRINTONLEVEL(file,level,"%p",data,(void*)data);
    if(data!=NIL){
        PRINTONLEVEL(file,level,"\"%s\"",*data,data);
    }
    PRINTONLEVEL(file,level,"%ld",dlength,dlength);
    PRINTONLEVEL(file,level,"%ld",allocation,allocation);
}//printOnLevel;


// new methods:

METHOD(BpString,length,(void),CARD32)
{
    return(dlength);
}//length;
    
    
METHOD(BpString,string,(void),const char*)
{
    return(data);
}//string;


METHOD(BpString,setString,(const char* nString),BpString*)
{
    CARD32       nLength;
        
    nLength=(CARD32)strlen(nString);
    if(nLength>=allocation){
        this->setCapacityCopy(nLength+1,FALSE);
    }
    BcMem_Copy((const void*)nString,data,nLength*sizeof(char));
    data[nLength]=(char)0;
    dlength=nLength;
    selfChanged(0);
    return(this);
}//setString:;


METHOD(BpString,setStringNoCopy,(char* someData,CARD32 byteCount),void)
{
    BcMem_Deallocate((void**)(&data));
    data=someData;
    dlength=(CARD32)strlen(someData);
    allocation=byteCount;
    if(dlength>=allocation){
        dlength=allocation-1;
    }
    data[dlength]='\0';
    selfChanged(0);
}//setStringNoCopy;


METHOD(BpString,getString,(char* str),BpString*)
{
    BcMem_Copy(data,str,dlength*sizeof(char));
    str[dlength]=(char)0;
    return(this);
}//getString:;


METHOD(BpString,copyFrom,(BpString* source),BpString*)
{
    dlength=0;
    data[0]='\0';
    _insertStringAt(source->data,source->dlength,0);
    selfChanged(0);
    return(this);
}//copyFrom;
    
    
METHOD(BpString,charAt,(CARD32 index),char)
{
    if((index<0)OR(index>=dlength)){
        return((char)0);
    }else{
        return(data[index]);
    }
}//charAt:;


METHOD(BpString,setCharAt,(char nChar,CARD32 index),BpString*)
{
    if((0<=index)AND(index<=dlength)){
        if(nChar==(char)0){
            dlength=index;
        }else if(index==dlength){
            if(allocation<=dlength+1){
                this->setCapacityCopy(allocation+AllocIncrement,TRUE);
            }
            INC(dlength);
            data[dlength]=(char)0;
        }
        data[index]=nChar;          
        selfChanged(0);
    }
    return(this);
}//setChar:;


METHOD(BpString,compare,(BpString* otherString),SignT)
{
    return(strcmp(this->data,otherString->data));
}//compare;
    
    
METHOD(BpString,_insertStringAt,(const char* sString,CARD32 sLength,CARD32 index),BpString*)
{
    CARD32       nLength;

    if(index<0){
        index=0;
    }else if(dlength<index){
        index=dlength;
    }
    nLength=dlength+sLength;
    if(nLength>=allocation){
        // SEE: We copy some char of this twice !
        this->setCapacityCopy(nLength+1,TRUE);
    }
    BcMem_Copy(data+index,data+index+sLength,
               (dlength-index+1)*sizeof(char));
    BcMem_Copy((const void*)sString,data+index,sLength*sizeof(char));
    dlength=nLength;
    return(this);
}//_insertStringAt;
    
    
METHOD(BpString,insertAt,(BpString* substring,CARD32 index),BpString*)
{
    _insertStringAt(substring->data,substring->dlength,index);
    selfChanged(0);
    return(this);
}//insert:at:;


METHOD(BpString,deleteFromLength,(CARD32 index,CARD32 delen),BpString*)
{
    if(index<0){
        index=0;
    }else if(dlength<=index){
        return(this);
    }
    if(dlength<index+delen){
        delen=dlength-index;
    }
    BcMem_Copy(data+index+delen,data+index,(dlength-(index+delen)+1)*sizeof(char));
    dlength=dlength-delen;
    selfChanged(0);
    return(this);
}//deleteFrom:dlength:;


METHOD(BpString,positionFrom,(BpString* substring,CARD32 index),CARD32)
{
    // SEE: could we use the FastStringSearch algorithm?
    CARD32           pos;
    CARD32           i;
    CARD32           max;
        
    max=dlength-substring->dlength;     
    if(index<0){
        pos=0;
    }else{
        pos=index;
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
    // not found
    return(MAX_CARD32);
}//position:;


METHOD(BpString,copyFromLength,(BpString* str,CARD32 index,CARD32 copylen),BpString*)
{
    if(index+copylen>str->dlength){
        copylen=str->dlength-index;
    }
    if(copylen<=0){
        data[0]=(char)0;
        dlength=0;
        selfChanged(0);
        return(this);
    }
    if(copylen>=allocation){
        this->setCapacityCopy(copylen+1,FALSE);
    }
    BcMem_Copy(str->data+index,data,copylen*sizeof(char));
    data[copylen]=(char)0;
    dlength=copylen;
    selfChanged(0);
    return(this);
}//copy:from:dlength:;


METHOD(BpString,append,(BpString* tail),BpString*)
{
    _insertStringAt(tail->data,tail->dlength,dlength);
    selfChanged(0);
    return(this);
}//append:;
    

METHOD(BpString,appendString,(const char* nString),BpString*)
{
    _insertStringAt(nString,(CARD32)strlen(nString),dlength);
    selfChanged(0);
    return(this);
}//appendString;
    
    
METHOD(BpString,setCapacityCopy,(CARD32 nAllocation,BOOLEAN copy),BpString*)
{
    char*       nData;
    CARD32      nLength;
            
    if(nAllocation>1){
        nData=(char*)BcMem_Allocate(sizeof(char)*nAllocation);
        if(copy){
            nLength=Minimum(nAllocation-1,dlength);
            BcMem_Copy(data,nData,nLength*sizeof(char));
        }else{
            nLength=0;
        }
    }else{
        nAllocation=1;
        nData=(char*)BcMem_Allocate(sizeof(char)*nAllocation);
        nLength=0;
    }
    nData[nLength]=(char)0;
    BcMem_Deallocate((void**)(&data));
    data=nData;
    dlength=nLength;
    allocation=nAllocation;
    return(this);
}//setCapacity;



METHOD(BpString,shellQuoted,(void),BpString*)
{
    static const char acceptedSpecials[]="+,-./:=@^_";
    const char*       p=data;
    BOOLEAN           containsSpecial=FALSE;
    CARD32            quoteCount=0;

    while(*p!='\0'){
        if(!((isalnum(*p))||(strchr(acceptedSpecials,*p)!=0))){
            if(*p=='\''){
                quoteCount++;
            }
            containsSpecial=TRUE;
        }
        p++;
    }
    if(containsSpecial){
        char* d;
        BpString* quotedString=NEW(BpString);
        quotedString->setCapacityCopy(this->length()+2+3*quoteCount+1,FALSE);
        p=data;
        d=quotedString->data;
        (*d++)='\'';
        while(*p!='\0'){
            if(*p=='\''){
                (*d++)='\'';
                (*d++)='\\';
                (*d++)='\'';
                (*d++)='\'';
                p++;
            }else{
                (*d++)=(*p++);
            }
        }
        (*d++)='\'';
        (*d++)='\0';
        quotedString->dlength=(CARD32)(d-quotedString->data);
        return(quotedString);
    }else{
        return(this);
    }
}//shellQuoted;

//// THE END ////
