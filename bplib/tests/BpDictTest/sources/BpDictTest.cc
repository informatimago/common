/******************************************************************************
FILE:               BpDictTest.cc
LANGUAGE:           C++
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    This module implement the 'dictionary' concept.
    Dictionaries are dynamic (resize themselves by doubling when they
    reach a certain maximum), so that callers never have to think about 
    allocation;
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
LEGAL
    Copyright Pascal J. Bourguignon 1995 - 2011

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
#include <stdio.h>

#include <names.h>
#include BpDict_hh
extern"C"{
#include BcExcept_h
}
#include BcImplementation_h

    BpString* S(const char* s)
    {
            BpString*   t;
        t=NEW(BpString);
        t->setString(s);
        return(t);
    }//S;

#define GS(s)   ss=(BpString*)(d1->objectForKey(S(s)));\
                if(ss==NIL){ printf("%s <NIL>\n",s); }else{ \
                printf("%s  %s\n",s,ss->string()); }

#define DS(s)   GS(s);d1->removeObjectForKey(S(s));GS(s)

    void AP(BpArray* a,const char* name)
    {
            BpString*   element;
            CARD32      i;
            CARD32      s;
        
        s=a->size();
        for(i=0;i<s;i++){
            element=(BpString*)(a->objectAt(i));
            printf("        %s[%u]=%s\n",name,i,element->string());
        }
        BpObject_ProcessDeletePool();
    }//AP;
    
    
    void DP(BpDict* d)
    {
            BpArray*        keys;
            BpArray*        values;
            CARD32          c;
            CARD32          i;
            
        printf("%p %s count = %u\n",(void*)d,d->className(),d->count());
        keys=d->allKeys();
        keys->retain();
        AP(keys,"keys");
        values=d->allValues();
        values->retain();
        AP(values,"values");
        c=keys->size();
        if(c!=d->count()){
            printf("%p %s  returned a key array with %u elements while it said it contains %u entries.\n",(void*)d,d->className(),c,d->count());
        }
        if(c!=values->size()){
            printf("%p %s  returned a key array with %u elements and a values array with %u elements (this may be normal).\n",(void*)d,d->className(),c,values->size());
        }
        for(i=0;i<c;i++){
                BpString*       value;
                BpArray*        otherKeys;
            value=((BpString*)(d->objectForKey(
                                    (BpString*)(keys->objectAt(i)))));
            if(values->indexOf(value)==MAX_CARD32){
                printf("%p %s  objectForKey returned an object %p (%s) not returned by allValues!\n",(void*)d,d->className(),(void*)value,value->string());
            }
            otherKeys=d->allKeysForObject(value);
            if(otherKeys->size()==1){
                printf("    %s: %s\n",
                    ((BpString*)(keys->objectAt(i)))->string(),
                    value->string());
            }else{
                    CARD32      j;
                    CARD32      os;
                printf("    %s: %s  <-  ",
                    ((BpString*)(keys->objectAt(i)))->string(),
                    value->string());
                os=otherKeys->size();
                for(j=0;j<os;j++){
                    printf(" %s", 
                        ((BpString*)(otherKeys->objectAt(j)))->string());;
                }
                printf("\n");
            }
        }
        values->release();
        keys->release();
    }//DP;
    

int main(void)
{
        BpDict*     d1;
        BpDict*     d2;
        BpString*   ss;
        
        
    d1=NEW(BpDict);
    d1->retain();
    d2=NEW(BpDict);
    d2->retain();

    d1->setObjectForKey(S("galatina"),S("192.161.1.2"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("larissa"),S("192.161.1.3"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("proteus"),S("192.161.1.4"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("triton"),S("192.161.1.5"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("nereide"),S("192.161.1.6"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("rogix"),S("192.161.2.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("magix"),S("192.161.2.2"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("casiopee"),S("1.0.0.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("despina"),S("192.161.1.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("pancake"),S("194.51.30.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("bun"),S("194.51.30.8"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("lepiote"),S("192.161.3.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("ormius"),S("192.1.5.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("ormium"),S("192.1.5.2"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("maya"),S("192.1.5.9"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("burgond"),S("192.161.1.1"));
    GS("1.0.0.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("192.161.3.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    printf("\n");
    BpObject_ProcessDeletePool();
    
    d1->printOnLevel(stdout,0);

    GS("galatina");
    GS("larissa");
    GS("192.161.1.2");
    GS("192.161.1.3");
    GS("192.161.1.4");
    GS("192.161.1.5");
    GS("192.161.1.6");
    GS("192.161.2.1");
    GS("192.161.2.2");
    GS("1.0.0.1");
    GS("192.161.1.1");
    GS("194.51.30.1");
    GS("194.51.30.8");
    GS("192.161.3.1");
    GS("192.1.5.1");
    GS("192.1.5.2");
    GS("192.1.5.9");
    GS("192.161.1.1");
    BpObject_ProcessDeletePool();


    DS("1.0.0.1");
    DS("192.161.1.1");
    DS("192.161.1.1");
    DS("192.161.2.1");
    DS("192.161.3.1");
    DS("192.1.5.1");
    DS("194.51.30.1");
    DS("192.161.1.2");
    DS("192.161.2.2");
    DS("192.1.5.2");
    DS("192.161.1.3");
    DS("192.161.1.4");
    DS("192.161.1.5");
    DS("192.161.1.6");
    DS("194.51.30.8");
    DS("192.1.5.9");
    DS("1.0.0.1");
    BpObject_ProcessDeletePool();

    d1->setObjectForKey(S("galatina"),S("192.161.1.2"));
    d1->setObjectForKey(S("larissa"),S("192.161.1.3"));
    d1->setObjectForKey(S("proteus"),S("192.161.1.4"));
    d1->setObjectForKey(S("triton"),S("192.161.1.5"));
    d1->setObjectForKey(S("nereide"),S("192.161.1.6"));
    d1->setObjectForKey(S("rogix"),S("192.161.2.1"));
    d1->setObjectForKey(S("magix"),S("192.161.2.2"));
    d1->setObjectForKey(S("casiopee"),S("1.0.0.1"));
    d1->setObjectForKey(S("despina"),S("192.161.1.1"));
    d1->setObjectForKey(S("pancake"),S("194.51.30.1"));
    d1->setObjectForKey(S("bun"),S("194.51.30.8"));
    d1->setObjectForKey(S("lepiote"),S("192.161.3.1"));
    d1->setObjectForKey(S("ormius"),S("192.1.5.1"));
    d1->setObjectForKey(S("ormium"),S("192.1.5.2"));
    d1->setObjectForKey(S("maya"),S("192.1.5.9"));
    d1->setObjectForKey(S("burgond"),S("192.161.1.1"));
    DP(d1);
    {
            BpString*   keys[8]={
                            S("name"),
                            S("passwd"),
                            S("uid"),
                            S("gid"),
                            S("realname"),
                            S("home"),
                            S("shell"),
                            S("_writers_passwd")
                        };
            BpString*   keys2[8]={
                            S("2-name"),
                            S("2-passwd"),
                            S("2-uid"),
                            S("2-gid"),
                            S("2-realname"),
                            S("2-home"),
                            S("2-shell"),
                            S("2-_writers_passwd")
                        };
            BpObject*   values[8]={
                            S("pascal"),
                            S("trucmuche"),
                            S("1000"),
                            S("1000"),
                            S("Pascal Bourguignon"),
                            S("/users/pascal"),
                            S("/bin/csh"),
                            S("pascal")
                        };
            CARD32      i;
            BpArray*    akeys;
            
        for(i=0;i<8;i++){
            keys[i]->retain();
            keys2[i]->retain();
            values[i]->retain();
        }
        d2->initWithObjectsForKeysCount(values,keys,8);
        DP(d2);
        d1->addEntriesFromDictionary(d2);
        DP(d1);
        d2->initWithObjectsForKeysCount(values,keys2,8);
        DP(d2);
        d1->addEntriesFromDictionary(d2);
        DP(d1);
        
        akeys=NEW(BpArray);
        akeys->initWithObjectsCount((BpObject**)keys2,8);
        d1->removeObjectsForKeys(akeys);
        DP(d1);
        
        for(i=0;i<8;i++){
            keys[i]->release();
            keys2[i]->release();
            values[i]->release();
        }
        BpObject_ProcessDeletePool();
        DP(d2);
        DP(d1);
    }

    BpObject_ProcessDeletePool();
    return(0);
}//main.


/*** BpDictTest.cc                    -- 2004-01-01 09:59:35 -- pascal   ***/
