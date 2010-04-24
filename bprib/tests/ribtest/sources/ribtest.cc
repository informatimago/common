/******************************************************************************
FILE:               ribtest.cc
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
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
#include <stdio.h>
}
#include <BpRIB.hh>
#include <BcImplementation.h>

    typedef struct {
        char        command;
        char*       title;
        void (*action)(BpRIB*,int);
        int         argument;
    }           MenuT;
    
    PROCEDURE(readstring,(char* buffer),void)
    {
        gets(buffer);
    }//readstring;
    

    PROCEDURE(readchar,(char* c),void)
    {
            char    buffer[BUFSIZ];
        gets(buffer);
        (*c)=buffer[0];
    }//readchar;
    
    
    PROCEDURE(getAttribute,(BpRIB* rib,int argument),void)
    {
        switch(argument){
        case 0:
            printf("\nBANQUE =%s\n",rib->banque());
            break;
        case 1:
            printf("\nGUICHET=%s\n",rib->guichet());
            break;
        case 2:
            printf("\nCOMPTE =%s\n",rib->compte());
            break;
        case 3:
            printf("\nCLE    =%s\n",rib->cle());
            break;
        default:
            printf("Internal error: bad argument for getAttribute (%d)\n",argument);
        }
    }//getAttribute;
    
    
    PROCEDURE(getRIB,(BpRIB* rib,int argument),void)
    {
            char    ribstr[64];
        rib->getRIB(argument!=0,ribstr);
        printf("\nRIB    =%s\n",ribstr);
    }//getRIB;
    

    PROCEDURE(setAttribute,(BpRIB* rib,int argument),void)
    {
            char    buffer[BUFSIZ];

        switch(argument){
        case 0:
            printf("\nBANQUE >");
            readstring(buffer);
            printf("BANQUE >%s\n",buffer);
            printf(" > > > >%s\n",rib->setBanque(buffer)?"OK":"ERROR");
            break;
        case 1:
            printf("\nGUICHET>");
            readstring(buffer);
            printf("GUICHET>%s\n",buffer);
            printf(" > > > >%s\n",rib->setGuichet(buffer)?"OK":"ERROR");
            break;
        case 2:
            printf("\nCOMPTE >");
            readstring(buffer);
            printf("COMPTE >%s\n",buffer);
            printf(" > > > >%s\n",rib->setCompte(buffer)?"OK":"ERROR");
            break;
        default:
            printf("Internal error: bad argument for setAttribute (%d)\n",argument);
        }
    }//setAttribute;
    
    
    PROCEDURE(setRIB,(BpRIB* rib,int argument),void)
    {
            char    buffer[BUFSIZ];
            
        printf("\nRIB    >");
        readstring(buffer);
        printf("BpRIB    >%s\n",buffer);
        printf(" > > > >%s\n",rib->setRIB(buffer,argument!=0)?"OK":"ERROR");
    }//setRIB;
    
    
    
    static BOOLEAN      running=TRUE;
    
    PROCEDURE(stop,(BpRIB* rib,int argument),void)
    {
        running=FALSE;
    }//stop;
    

    MenuT       menu[]={
        {'b',"Extraire le code banque",getAttribute,0},
        {'g',"Extraire le code guichet",getAttribute,1},
        {'c',"Extraire le code compte",getAttribute,2},
        {'k',"Extraire le code cle",getAttribute,3},
        {'r',"Afficher le R.I.B. complet, sans espace",getRIB,0},
        {'s',"Afficher le R.I.B. complet, avec espaces",getRIB,1},
        {'B',"Changer le code banque",setAttribute,0},
        {'G',"Changer le code guichet",setAttribute,1},
        {'C',"Changer le code compte",setAttribute,2},
        {'R',"Changer le R.I.B. complet, sans cle",setRIB,0},
        {'S',"Changer le R.I.B. complet, avec cle",setRIB,1},
        {'q',"Quitter",stop,0},
        {'\0',NULL,NULL,0}
    };

    
    PROCEDURE(getChoice,(void),int)
    {
            int     i;
            char    c;
            
        while(1){
            printf("\n\n-------------------------------------------------\n");
            for(i=0;menu[i].title!=NULL;i++){
                printf("%c) %s.\n",menu[i].command,menu[i].title);
            }
            printf("\n>");
            readchar(&c);
            for(i=0;menu[i].title!=NULL;i++){
                if(menu[i].command==c){
                    return(i);
                }
            }
        }
    }//getChoice;
    
    
    

int main(int argc,char** argv)
{
        BpRIB*      rib=NIL;
        int         c;
        int         i;
        char        ribstr[BUFSIZ];
    
    rib=NEW(BpRIB);
    if(argc==1){
        while(running){
            getRIB(rib,1);
            c=getChoice();
            menu[c].action(rib,menu[c].argument);
        }
    }else{
        for(i=1;i<argc;i++){
            if(!(rib->setRIB(argv[i],FALSE))){
                strcpy(ribstr,"ERROR");
            }else{
                rib->getRIB(TRUE,ribstr);
            }
            printf("%30s %30s\n",argv[i],ribstr);
        }
    }
    DELETE(rib);
    
    return(0);
}//main.

/*** ribtest.cc                       -- 2004-01-17 16:43:41 -- pascal   ***/
