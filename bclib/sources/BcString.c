/******************************************************************************
FILE:               BcString.cc
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
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/16  12:15:28  pascal
    Small corrections to compile with MSVC.
    
    Revision 1.1  95/11/16  06:28:41  pascal
    Initial revision
    
    1993-01-29 <PJB> Creation.
    1993-03-19 <PJB> Renamed BcXxxx for "B"ourguignon's C"P"lusplus library;
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's "C" library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
LEGAL
    Copyright Pascal J. Bourguignon 1993 - 2002

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
******************************************************************************/
#include <string.h>
#include <names.h>
#include BcString_h
#include BcMem_h
#include BcImplementation_h



    const char BcString_ID[]=
    "$Id: BcString.c,v 1.3 2004/01/21 06:26:09 pjbpjb Exp $";
    
    typedef struct {
        char*               data;
        INT32               dlength;
        INT32               allocation;
    }                   BcString_S;
    typedef BcString_S* BcString_P;
    

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


    PROCEDURE(BcString_SetCapacityCopy,
            (BcString_T t,INT32 nAllocation,BOOLEAN copy),BcString_T)

    {
            BcString_P      this=(BcString_P)t;
            char*           nData;
            INT32           nLength;
            
        if(nAllocation>1){
            nData=BcMem_Allocate(sizeof(char)*nAllocation);
            if(copy){
                nLength=Minimum(nAllocation-1,this->dlength);
                BcMem_Copy(this->data,nData,nLength*sizeof(char));
            }else{
                nLength=0;
            }
        }else{
            nAllocation=1;
            nData=BcMem_Allocate(sizeof(char)*nAllocation);
            nLength=0;
        }
        nData[nLength]=(char)0;
        BcMem_Deallocate((void**)(&(this->data)));
        this->data=nData;
        this->dlength=nLength;
        this->allocation=nAllocation;
        return(this);
    }/*setCapacity;*/


/* birth and death:*/

    PROCEDURE(BcString_Allocate,(void),BcString_T)
    {
            BcString_P      this;
        this=BcMem_Allocate(sizeof(BcString_S));
        this->allocation=1;
        this->data=BcMem_Allocate(sizeof(char)*this->allocation);
        this->dlength=0;
        this->data[this->dlength]=(char)0;
        return(this);
    }/*BcString;*/
    
    PROCEDURE(BcString_Deallocate,(BcString_T* t),void)
    {
            BcString_P      this=(BcString_P)(*t);

        BcString_SetCapacityCopy(this,0,FALSE);
        BcMem_Deallocate(t);
    }/*~BcString;*/


/* override BcObject methods:*/

    PROCEDURE(BcString_ClassName,(BcString_T t),const char*)
    {
#ifdef MSVC
        t=t;
#endif
        return("BcString");
    }/*className;*/
    
    
    PROCEDURE(BcString_PrintOn,(BcString_T t,FILE* file),void)
    {
            BcString_P      this=(BcString_P)t;
            
        /* BcString_SUPER::printOn(file); */
        fprintf(file,"data=           %p\n",(void*)(this->data));
        if(this->data!=NIL){
            fprintf(file,"*data=          \"%s\"\n",this->data);
        }
        fprintf(file,"dlength=         %ld\n",this->dlength);
        fprintf(file,"allocation=     %ld\n",this->allocation);
    }/*printOn:;*/
    
    
/* new methods:*/

    PROCEDURE(BcString_Length,(BcString_T t),INT32)
    {
            BcString_P      this=(BcString_P)t;

        return(this->dlength);
    }/*length;*/
    
    
    PROCEDURE(BcString_String,(BcString_T t),const char*)
    {
            BcString_P      this=(BcString_P)t;
            
        return(this->data);
    }/*string;*/


    PROCEDURE(BcString_SetString,
                (BcString_T t,const char* nString),BcString_T)
    {
            BcString_P      this=(BcString_P)t;
            INT32           nLength;
        
        nLength=strlen(nString);
        if(nLength>=this->allocation){
            BcString_SetCapacityCopy(this,nLength+1,FALSE);
        }
        BcMem_Copy((const void*)nString,this->data,nLength*sizeof(char));
        this->data[nLength]=(char)0;
        this->dlength=nLength;
        return(this);
    }/*setString:;*/


    PROCEDURE(BcString_GetString,(BcString_T t,char* string),BcString_T)
    {
            BcString_P      this=(BcString_P)t;

        BcMem_Copy(this->data,string,this->dlength*sizeof(char));
        string[this->dlength]=(char)0;
        return(this);
    }/*getString:;*/
    
    
    PROCEDURE(BcString_AppendString,(BcString_T t,const char* str),BcString_T)
    {
            BcString_P      this=(BcString_P)t;
            INT32           nLength;
            INT32           sLength;
        
        sLength=strlen(str);
        nLength=sLength+this->dlength;
        if(nLength>=this->allocation){
            BcString_SetCapacityCopy(this,nLength+1,TRUE);
        }
        BcMem_Copy((const void*)str,
                   this->data+this->dlength,sLength*sizeof(char));
        this->data[nLength]=(char)0;
        this->dlength=nLength;
        return(this);
    }/*BcString_AppendString*/
    

    PROCEDURE(BcString_CharAt,(BcString_T t,INT32 idx),char)
    {
            BcString_P      this=(BcString_P)t;

        if((idx<0)OR(idx>=this->dlength)){
            return((char)0);
        }else{
            return(this->data[idx]);
        }
    }/*charAt:;*/


    PROCEDURE(BcString_SetCharAt,
                (BcString_T t,char nChar,INT32 idx),BcString_T)
    {
            BcString_P      this=(BcString_P)t;

        if((0<=idx)AND(idx<=this->dlength)){
            if(nChar==(char)0){
                this->dlength=idx;
            }else if(idx==this->dlength){
                if(this->allocation<=this->dlength+1){
                    BcString_SetCapacityCopy(this,
                                    this->allocation+AllocIncrement,TRUE);
                }
                INC(this->dlength);
                this->data[this->dlength]=(char)0;
            }
            this->data[idx]=nChar;
        }
        return(this);
    }/*setChar:;*/


    
    PROCEDURE(BcString_InsertAt,
                (BcString_T t,BcString_T substring,INT32 idx),BcString_T)
    {
            BcString_P      this=(BcString_P)t;
            BcString_P      sub=(BcString_P)substring;
            INT32           nLength;

        if(idx<0){
            idx=0;
        }else if(this->dlength<idx){
            idx=this->dlength;
        }
        nLength=this->dlength+sub->dlength;
        if(nLength>=this->allocation){
            /* SEE: We copy some char of this twice !*/
            BcString_SetCapacityCopy(this,nLength+1,TRUE);
        }
        BcMem_Copy(this->data+idx,
                    this->data+idx+sub->dlength,
                    (this->dlength-idx+1)*sizeof(char));
        BcMem_Copy(sub->data,
                    this->data+idx,
                    sub->dlength*sizeof(char));
        this->dlength=nLength;
        return(this);
    }/*insert:at:;*/


    PROCEDURE(BcString_DeleteFromLength,
                (BcString_T t,INT32 idx,INT32 delen),BcString_T)
    {
            BcString_P      this=(BcString_P)t;

        if(idx<0){
            idx=0;
        }else if(this->dlength<=idx){
            return(this);
        }
        if(this->dlength<idx+delen){
            delen=this->dlength-idx;
        }
        BcMem_Copy(this->data+idx+delen,this->data+idx,
                    (this->dlength-(idx+delen)+1)*sizeof(char));
        this->dlength=this->dlength-delen;
        return(this);
    }/*deleteFrom:dlength:;*/


    PROCEDURE(BcString_PositionFrom,
                (BcString_T t,BcString_T substring,INT32 idx),INT32)
    {
        /* SEE: could we use the FastStringSearch algorithm?*/
            BcString_P      this=(BcString_P)t;
            BcString_P      sub=(BcString_P)substring;
            INT32           pos;
            INT32           i;
            INT32           max;
        
        max=this->dlength-sub->dlength;     
        if(idx<0){
            pos=0;
        }else{
            pos=idx;
        }
        while(pos<=max){
            i=0;
            while(this->data[pos+i]==sub->data[i]){
                INC(i);
            }
            if(sub->data[i]==(char)0){
                return(pos);
            }
            INC(pos);
        }
        /* not found*/
        return(-1);
    }/*position:;*/


    PROCEDURE(BcString_CopyFromLength,
            (BcString_T t,BcString_T string,INT32 idx,INT32 copylen),
            BcString_T)
    {
            BcString_P      this=(BcString_P)t;
            BcString_P      str=(BcString_P)string;

        if(idx+copylen>str->dlength){
            copylen=str->dlength-idx;
        }
        if(copylen<=0){
            this->data[0]=(char)0;
            this->dlength=0;
            return(this);
        }
        if(copylen>=this->allocation){
            BcString_SetCapacityCopy(this,copylen+1,FALSE);
        }
        BcMem_Copy(str->data+idx,this->data,copylen*sizeof(char));
        this->data[copylen]=(char)0;
        this->dlength=copylen;
        return(this);
    }/*copy:from:dlength:;*/


    PROCEDURE(BcString_Append,(BcString_T t,BcString_T tail),BcString_T)
    {
            BcString_P      this=(BcString_P)t;

        return(BcString_InsertAt(this,tail,this->dlength));
    }/*append:;*/
    


/*END BcString.*/


/*** BcString.c                       -- 2003-11-30 07:25:46 -- pascal   ***/
