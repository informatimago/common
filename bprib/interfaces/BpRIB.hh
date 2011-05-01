/******************************************************************************
FILE:               BpRIB.hh
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This class define the RIB objects, who are composed of three codes and
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
#ifndef __BpRIB__
#define __BpRIB__
#include <names.h>
#include BcInterface_h
#include BcTypes_h
#include BpObject_hh


#define BpRIB_SUPER BpObject
class BpRIB:BpRIB_SUPER
/*
    INVARIANT:  strlen(banque)=5,
                strlen(guichet)=5,
                strlen(compte)=11,
                strlen(cle)=2,
                for each attribute in {banque,guichet,compte,cle},
                    foreach i in [0,strlen(attribute)-1],
                        attribute()[i] in {'0',...,'9','A',...,'Z'}.
                cle=f(banque,guichet,compte).
*/
{
public:
    CONSTRUCTOR(BpRIB)
    DESTRUCTOR(BpRIB)

    METHOD(BpRIB,banque,(void),const char*)
    METHOD(BpRIB,guichet,(void),const char*)
    METHOD(BpRIB,compte,(void),const char*)
    METHOD(BpRIB,cle,(void),const char*)
    METHOD(BpRIB,getRIB,(BOOLEAN withSpaces,char* oRib),void)
    
    METHOD(BpRIB,setBanque,(const char* nBanque),BOOLEAN)
    METHOD(BpRIB,setGuichet,(const char* nGuichet),BOOLEAN)
    METHOD(BpRIB,setCompte,(const char* nCompte),BOOLEAN)
    METHOD(BpRIB,setRIB,(const char* nRIB,BOOLEAN withCle),BOOLEAN)
protected:
    char    fBanque[5+1];
    char    fGuichet[5+1];
    char    fCompte[11+1];
    char    fCle[2+1];
    BOOLEAN cleChanged;
};/*BpRIB*/

#endif //BpRIB;
