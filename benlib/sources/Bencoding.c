/******************************************************************************
FILE:               Bencoding.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     ANSI
DESCRIPTION
    This module exports types and routines to manage 8-bit character encodings,
    and convert strings from one encoding to an other.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    2003-11-30 <PJB> Replaced BenStringP with const char* for gcc...
    1999-09-13 PJB Made this module from the encoding (nema) tool.
LEGAL
    GPL
    
    Copyright Pascal Bourguignon 2003 - 2003
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version
    2 of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public
    License along with this program; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330,
    Boston, MA 02111-1307 USA
******************************************************************************/
#include <string.h>
#include <stdlib.h>

#include <Bencoding.h>
#include <BcTypes.h>

#include <approxim.h>
#include <apraccen.h>
#include <encascii.h>
#include <encisla1.h>
#include <encmacos.h>
#include <encmsdos.h>
#include <encmswin.h>
#include <encnxstp.h>
#include <encpsstd.h>
#include <encsymbl.h>
#include <ench2bcd.h>
#include <ench6bcd.h>
#include <encunifd.h>
#include <encibbcd.h>
#include <encebcdi.h>

    
    static BOOLEAN                      initialized;
    static INT32                        eSize;
    static INT32                        eCount;
    static const char**                  encodingTableNames;
    static BenEncodingTableT**          encodingTables;
    static INT32                        aSize;
    static INT32                        aCount;
    static const char**                  approximationTableNames;
    static BenApproximationTableT**     approximationTables;


    static void BenInitialize(void)
    {
        eSize=32;
        eCount=0;
        encodingTableNames=(const char**)
            malloc(sizeof(const char*)*eSize);
        encodingTables=(BenEncodingTableT**)
            malloc(sizeof(BenEncodingTableT*)*eSize);

        aSize=8;
        aCount=0;
        approximationTableNames=(const char**)
            malloc(sizeof(const char*)*aSize);
        approximationTables=(BenApproximationTableT**)
            malloc(sizeof(BenApproximationTableT*)*aSize);

        initialized=TRUE;

        BenAddEncodingTable(&ASCIIEncoding,          "ascii");
        BenAddEncodingTable(&ISOLatin1Encoding,      "isolatin1");
        BenAddEncodingTable(&MacintoshEncoding,      "macintosh");
        BenAddEncodingTable(&MSDOSEncoding,          "msdos");
        BenAddEncodingTable(&MSWindowsEncoding,      "mswindows");
        BenAddEncodingTable(&NextStepEncoding,       "nextstep");
        BenAddEncodingTable(&PSStandardEncoding,     "postscript");
        BenAddEncodingTable(&SymbolEncoding,         "symbol");
        BenAddEncodingTable(&Honeywell200BCDEncoding,"honeywell200bcd");
        BenAddEncodingTable(&Honeywell600BCDEncoding,"honeywell600bcd");
        BenAddEncodingTable(&UnivacFieldDataEncoding,"univacfielddata");
        BenAddEncodingTable(&IBMBCDEncoding,         "ibmbcd");
        BenAddEncodingTable(&EBCDICEncoding,         "ebcdic");

        BenAddApproximationTable(&ApproximationTable,"approximation");
        BenAddApproximationTable(&AccentApproximationTable,"accentApproximation");

    }/*BenInitialize*/



    const char** BenEncodingTableNames(void)
    {
        if(!initialized){
            BenInitialize();
        }
        return(encodingTableNames);
    }/*BenEncodingTableNames*/


    BenEncodingTableT* BenEncodingTableNamed(const char* tabName)
    {
        INT32 i;
        if(!initialized){
            BenInitialize();
        }
        for(i=0;i<eCount;i++){
            if(strcmp(tabName,encodingTableNames[i])==0){
                return(encodingTables[i]);
            }
        }
        return((BenEncodingTableT*)0);
    }/*BenEncodingTableNamed*/


    void BenAddEncodingTable(BenEncodingTableT* table,
                             const char* tabName)
    {
        INT32 i;
        if(!initialized){
            BenInitialize();
        }
        for(i=0;i<eCount;i++){
            if(strcmp(tabName,encodingTableNames[i])==0){
                encodingTables[i]=table;
                return;
            }
        }
        if(eCount>=eSize){
            const char**         nNames;
            BenEncodingTableT** nTables;
            eSize*=2;
            nNames=(const char**)malloc(sizeof(const char*)*eSize);
            nTables=(BenEncodingTableT**)
                malloc(sizeof(BenEncodingTableT*)*eSize);
            for(i=0;i<eCount;i++){
                nNames[i]=encodingTableNames[i];
                nTables[i]=encodingTables[i];
            }
            free(encodingTableNames);
            free(encodingTables);
            encodingTableNames=nNames;
            encodingTables=nTables;
        }
        encodingTableNames[eCount]=tabName;
        encodingTables[eCount]=table;
        eCount++;
    }/*BenAddEncodingTable*/



    const char** BenApproximationNames(void)
    {
        if(!initialized){
            BenInitialize();
        }
        return(approximationTableNames);
    }/*BenApproximationNames*/



    BenApproximationTableT* BenApproximationTableNamed(const char* tabName)
    {
        INT32 i;
        if(!initialized){
            BenInitialize();
        }
        for(i=0;i<aCount;i++){
            if(strcmp(tabName,approximationTableNames[i])==0){
                return(approximationTables[i]);
            }
        }
        return((BenApproximationTableT*)0);
    }/*BenApproximationTableNamed*/



    static void BenCountApproximationTable(BenApproximationTableT* table)
    {
        INT32 i=0;
        while(table->approximations[i].charName!=0){
            i++;
        }
        table->count=i;
    }/*BenCountApproximationTable*/
        


    void BenAddApproximationTable(BenApproximationTableT* table,
                                  const char* tabName)
     {
        INT32 i;
        if(!initialized){
            BenInitialize();
        }
        BenCountApproximationTable(table);
        for(i=0;i<aCount;i++){
            if(strcmp(tabName,approximationTableNames[i])==0){
                approximationTables[i]=table;
                return;
            }
        }
        if(aCount>=aSize){
            const char**              nNames;
            BenApproximationTableT** nTables;
            aSize*=2;
            nNames=(const char**)malloc(sizeof(const char*)*aSize);
            nTables=(BenApproximationTableT**)
                malloc(sizeof(BenApproximationTableT*)*aSize);
            for(i=0;i<aCount;i++){
                nNames[i]=approximationTableNames[i];
                nTables[i]=approximationTables[i];
            }
            free(approximationTableNames);
            free(approximationTables);
            approximationTableNames=nNames;
            approximationTables=nTables;
        }
        approximationTableNames[aCount]=tabName;
        approximationTables[aCount]=table;
        aCount++;
    }/*BenAddApproximationTable*/



    int BenFindCharNameInEncoding(BenEncodingTableT* encoding,
                                    const char* charName)
    {
        int code=0;
        while(code<256){
            if(((*encoding)[code]!=0)
               &&(strcmp(charName,(*encoding)[code])==0)){
                return(code);
            }
            code++;
        }
        return(-1);
    }/*BenFindCharNameInEncoding*/


    int BenFindCharNameInApproximationTable(BenApproximationTableT* approx,
                                              const char* charName)
    {
        int       min,max,cur;
        int       cmp;
            
        min=0;
        max=approx->count;
        cur=(min+max)/2;
        cmp=strcmp(approx->approximations[cur].charName,charName);
        while((cmp!=0)&&(min!=cur)){
            if(cmp<0){
                min=cur;
            }else{
                max=cur;
            }
            cur=(min+max)/2;
            cmp=strcmp(approx->approximations[cur].charName,charName);
        }
        if(cmp==0){
            return(cur);
        }else{
            return(-1);
        }
    }/*BenFindCharNameInApproximationTable*/



    static const char* EncodeToString(int code)
    {
        /*
           Pre-builds an array of const char* such as:
                code2string[i]=sprintf("%c",i)
           Return a string containing only one character `code'.
        */
        static char code2string[2*256];
        static BOOLEAN code2stringInitialized=FALSE;

        if(!code2stringInitialized){
            int i=0;
            while(i<256){
                code2string[2*i]=(char)i;
                code2string[2*i+1]=(char)0;
                i++;
            }
            code2stringInitialized=TRUE;
        }
        return(&(code2string[2*code])); 
    }/*EncodeToString;*/

    
    void BenBuildConversionTable(BenModeT mode,
                                 BenEncodingTableT* from,
                                 BenEncodingTableT* to,
                                 BenApproximationTableT* approx,
                                 const char* replacement,
                                 BenConversionTableT* convtable)
    {
        int       outcode;
        int       code;
        int       i;
        for(i=0;i<256;i++){
            if((*from)[i]==0){
                outcode=-1;
            }else{
                outcode=BenFindCharNameInEncoding(to,(*from)[i]);
            }
            if(outcode<0){
                switch(mode){
                case BenMode_Normal:
                    (*convtable)[i]=replacement;
                    break;
                case BenMode_Approximation:
                    if((*from)[i]==0){
                        code=-1;
                    }else{
                        code=BenFindCharNameInApproximationTable(approx,
                                                                 (*from)[i]);
                    }
                    if((code<0)
                       ||(approx->approximations[code].asciiApproximation==0)){
                        (*convtable)[i]=replacement;
                    }else{
                        (*convtable)[i]=
                            approx->approximations[code].asciiApproximation;
                    }
                    break;
                case BenMode_CharName:
                    if((*from)[i]==0){
                        (*convtable)[i]=replacement;
                    }else{
                        (*convtable)[i]=(*from)[i];
                    }
                    break;
                default:
                    break;
                }
            }else{
                (*convtable)[i]=EncodeToString(outcode);
                /*** SEE: if outcode = 0 then (*convtable)[i] = "" ***/
            }
        }
    }/*BenBuildConversionTable*/


    BcString_T BenEscapeString(const char* string)
    {
        BcString_T result=BcString_Allocate();
        char buffer[1024];
        unsigned int i=0;
        unsigned int j;
        while(string[i]!='\0'){
            j=0;
            while((string[i]!='\0')&&(j<sizeof(buffer)-5)){
                if((string[i]<32)||(126<string[i])){
                    buffer[j++]='\\';
                    sprintf(buffer+j,"%03o",(unsigned char)(string[i]));
                    j+=3;
                }else if((string[i]=='\\')||(string[i]=='"')){
                    buffer[j++]='\\';
                    buffer[j++]=string[i];
                }else{
                    buffer[j++]=string[i];
                }
                i++;
            }
            buffer[j]='\0';
            BcString_AppendString(result,buffer);
        }
        return(result);
    }/*BenEscapeString*/



    BcString_T BenConvertString(BenConversionTableT* table,
                                char* string)
    {
        BcString_T result=BcString_Allocate();
        char buffer[1024];
        int ml=0;
        int i;

        /* Get the longest converted string */
        for(i=0;i<256;i++){
            int l=strlen((*table)[i]);
            if(l>ml){
                ml=l;
            }
        }
        ml++;
        
        ml=sizeof(buffer)-ml; /* the limit in the buffer */

        if(ml<=1){
            /* degenerated case, let's do it anyway */
            while(string[i]!='\0'){
                BcString_AppendString(result,(*table)[(int)(string[i])]);
                i++;
            }
            return(result);
        }

        while(string[i]!='\0'){
            int j=0;
            while((string[i]!='\0')&&(j<ml)){
                const char* converted=(*table)[(int)(string[i])];
                while((*converted)!='\0'){
                    buffer[j++]=(*converted);
                    converted++;
                }
            }
            buffer[j]='\0';
            BcString_AppendString(result,buffer);
        }
        return(result);        
    }/*BenConvertString*/



/*** Bencoding.c                      -- 2003-12-03 16:39:56 -- pascal   ***/
