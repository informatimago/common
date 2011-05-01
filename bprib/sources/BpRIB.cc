/******************************************************************************
FILE:               BpRIB.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This class define the BpRIB objects, who are composed of three codes and
    a key value: (banque, guichet, compte, cle).
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
    See the copyleft legaleese for the 'number' module from GNU.
******************************************************************************/
extern "C"{
#include <string.h>
#include <stdio.h> // import BUFSIZ
#include <number.h>
}
#include <names.h>
#include BpRIB_hh
#include BcImplementation_h


/*
  We test and convert to upper case letters ourselves, because
  the RIB may contain only the following characters:
  0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ 
  and ctype macro may classify and process also accented letters.
*/


#ifndef TARGET_USE_ASCII
static const char*  alphabet_from=
  "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const char   alphabet_value[]=
  "012345678912345678912345678923456789";
#endif


PROCEDURE(inRibAlphabet,(char c),BOOLEAN)
/*
  RETURN:     c in {'0',...,'9','A',...,'Z','a',...,'z'}.
*/
{
#ifdef TARGET_USE_ASCII
    return((('0'<=c)&&(c<='9'))
           ||(('A'<=c)&&(c<='Z'))
           ||(('a'<=c)&&(c<='z')));
#else
    int     i;

    for(i=0;alphabet_from[i]!='\0';i++){
        if(alphabet_from[i]==c){
            return(TRUE);
        }
    }
    return(FALSE);
#endif
}//inRibAlphabet;



PROCEDURE(convertToRibCase,(char c),char)
/*
  PRE:        inRibAlphabet(c).
  POST:       d=convertToRibCase(c) =>
  c in {'0',...,'9','A',...,'Z'} => d=c.
  c='a' => d='A',
  c='b' => d='b',
  ...
  c='z' => d='Z'.
*/
{
#ifdef TARGET_USE_ASCII
    if(('a'<=c)&&(c<='z')){
        return(c-'a'+'A');
    }else{
        return(c);
    }   
#else
    int     i;

    for(i=0;alphabet_from[i]!='\0';i++){
        if(alphabet_from[i]==c){
            if(i<10+26){
                return(c);
            }else{
                return(alphabet_from[i-26]);
            }
        }
    }
    // If pre-condition is fullfilled, then we never pass here.
    // SEE: we should raise an exception here.
    return('0');
#endif
}//convertToRibCase;
                

PROCEDURE(ribValue,(char c),char)
/*
  PRE:        inRibAlphabet(c), convertToRibCase(c)=c.
  POST:       d=convertToRibCase(c) =>
  c in {'0',...,'9'} => d=c.
  c='A' => d='1',
  ...
  c='I' => d='9',
  c='J' => d='1',
  ...
  c='R' => d='9',
  c='S' => d='2',
  ...
  c='Z' => d='9'.
*/
{
#ifdef TARGET_USE_ASCII
    if(c<='9'){
        return(c);
    }else if(c<='I'){
        return(c-'A'+'1');
    }else if(c<='R'){
        return(c-'J'+'1');
    }else{
        return(c-'S'+'2');
    }
#else
    int     i;

    for(i=0;alphabet_from[i]!='\0';i++){
        if(alphabet_from[i]==c){
            return(alphabet_value[i]);
        }
    }
    // If pre-condition is fullfilled, then we never pass here.
    // SEE: we should raise an exception here.
    return('0');
#endif  
}//ribValue;
    
    
PROCEDURE(getAndCheckAlphaNum,(int cnt,char* a,const char* s),BOOLEAN)
{
    int     i,j;

    i=0;
    j=0;
    while((i<cnt)&&(s[j]!='\0')){
        if(s[j]!=' '){
            if(inRibAlphabet(s[j])){
                a[i++]=convertToRibCase(s[j]);
            }else{
                a[i]='\0';
                return(FALSE);
            }
        }           
        j++;
    }
    a[i]='\0';
    return((i==cnt)&&(s[j]=='\0'));
}//getAndCheckAlphaNum;
    
    
PROCEDURE(computeCle,(const char* nBanque,const char* nGuichet,
                      const char* nCompte),const char*)
{
    static BOOLEAN  number_inited=FALSE;
    static bc_num   quatrevingtdixsept;

    int             i;
    char            rib[23+1];
    static char     rescle[BUFSIZ];
    bc_num          ribnum;
    bc_num          remainder;
    long int        r;
            
    if(!number_inited){
        init_numbers();
        quatrevingtdixsept=new_num(2,0);
        int2num(&quatrevingtdixsept,97);
        number_inited=TRUE;
    }

    sprintf(rib,"%5s%5s%11s00",nBanque,nGuichet,nCompte);
    for(i=0;rib[i]!='\0';i++){
        rib[i]=ribValue(rib[i]);
    }
        
    ribnum=new_num(23,0);
    str2num(&ribnum,rib,0);
    remainder=new_num(2,0);
    bc_modulo(ribnum,quatrevingtdixsept,&remainder,0);
    r=num2long(remainder);
    sprintf(rescle,"%02ld",(r==0)?r:97-r);
    return(rescle);
}//computeCle;


CONSTRUCTOR(BpRIB)
{
    strcpy(fBanque,"00000");
    strcpy(fGuichet,"00000");
    strcpy(fCompte,"00000000000");
    strcpy(fCle,computeCle(fBanque,fGuichet,fCompte));
    cleChanged=FALSE;
}//BpRIB;
    
    
DESTRUCTOR(BpRIB)
{
    // NOP
}//~RIB;
    

METHOD(BpRIB,banque,(void),const char*)
{
    return(fBanque);
}//banque;
    

METHOD(BpRIB,guichet,(void),const char*)
{
    return(fGuichet);
}//guichet;
    

METHOD(BpRIB,compte,(void),const char*)
{
    return(fCompte);
}//compte;
    

METHOD(BpRIB,cle,(void),const char*)
{
    if(cleChanged){
        strcpy(fCle,computeCle(fBanque,fGuichet,fCompte));
        cleChanged=FALSE;
    }
    return(fCle);
}//cle;

    
METHOD(BpRIB,getRIB,(BOOLEAN withSpaces,char* oRib),void)
{
    if(withSpaces){
        sprintf(oRib,"%5s %5s %11s %2s",fBanque,fGuichet,fCompte,cle());
    }else{
        sprintf(oRib,"%5s%5s%11s%2s",fBanque,fGuichet,fCompte,cle());
    }
}//getRIB;
    
    
METHOD(BpRIB,setBanque,(const char* nBanque),BOOLEAN)
{
    char    temp[5+1];
            
    if(getAndCheckAlphaNum(5,temp,nBanque)){
        strcpy(fBanque,temp);
        cleChanged=TRUE;
        return(TRUE);
    }else{
        return(FALSE);
    }
}//setBanque;

    
METHOD(BpRIB,setGuichet,(const char* nGuichet),BOOLEAN)
{
    char    temp[5+1];
            
    if(getAndCheckAlphaNum(5,temp,nGuichet)){
        strcpy(fGuichet,temp);
        cleChanged=TRUE;
        return(TRUE);
    }else{
        return(FALSE);
    }
}//setGuichet;

    
METHOD(BpRIB,setCompte,(const char* nCompte),BOOLEAN)
{
    char    temp[11+1];
            
    if(getAndCheckAlphaNum(11,temp,nCompte)){
        strcpy(fCompte,temp);
        cleChanged=TRUE;
        return(TRUE);
    }else{
        return(FALSE);
    }
}//setCompte;
    
    
METHOD(BpRIB,setRIB,(const char* nRIB,BOOLEAN withCle),BOOLEAN)
{
    char    temp[23+1];
    char    tBanque[5+1];
    char    tGuichet[5+1];
    char    tCompte[11+1];
    char    tCle[2+1];
    int     len;
        
    len=withCle?23:21;
    if(getAndCheckAlphaNum(len,temp,nRIB)){
        strncpy(tBanque,temp,5);        tBanque[5]='\0';
        strncpy(tGuichet,temp+5,5);     tGuichet[5]='\0';
        strncpy(tCompte,temp+10,11);    tCompte[11]='\0';
        if(withCle){
            strncpy(tCle,temp+21,2);        tCle[2]='\0';
            if(strcmp(tCle,computeCle(tBanque,tGuichet,tCompte))!=0){
                return(FALSE);
            }
        }else{
            strcpy(tCle,computeCle(tBanque,tGuichet,tCompte));
        }
        strcpy(fBanque,tBanque);
        strcpy(fGuichet,tGuichet);
        strcpy(fCompte,tCompte);
        strcpy(fCle,tCle);
        cleChanged=FALSE;
        return(TRUE);
    }else{
        return(FALSE);
    }
}//setRIB;
    
    
/*
  The following functions should not be called by number module for 
  a simple bc_modulo.
*/
extern "C"{

    void rt_error(char* message,...)
    {
    }//rt_error;
    
    void rt_warn(char* message,...)
    {
    }//rt_warn;
    
    void out_of_memory(void)
    {
    }//out_of_memory;
    
}   
    
//END BpRIB;

/*** BpRIB.cc                         --                     --          ***/
