/******************************************************************************
FILE:               BcRandom.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     None
DESCRIPTION
    This module compute random numbers.
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/16  12:15:27  pascal
    Small corrections to compile with MSVC.
    
    Revision 1.1  95/11/16  06:28:38  pascal
    Initial revision
    
    1992-07-18 <PJB> Extracted from cookies.c.
    1993-09-08 <PJB> Removed RANDOMFILE. Now, the random file is found 
                     from environment variable.
LEGAL
    Copyright Pascal J. Bourguignon 1990 - 2002

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
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <names.h>
#include BcRandom_h
#include BcImplementation_h

    const char BcRandom_ID[]=
    "$Id: BcRandom.c,v 1.2 2004/01/02 00:59:24 pjbpjb Exp $";
    
#ifdef MACOS
#define RANDOMFILE  "Lacuste:local:lib:random.data"
#endif
#ifdef UNIX
#define RANDOMFILE  "/local/lib/random.data"
#endif  
#ifdef MSDOS
#define RANDOMFILE  "C:\\LOCAL\\LIB\\RANDOM.DAT"
#endif


    PROCEDURE(BcRandom_random,(CARD32 X[56]),CARD32)
    {
    /*
            55-54= 1     55-23=32
            77-54=23     77-23=54
            78-54=24     78-23=55
            79-54=25     79-23=56    79-55-23= 1
           109-54=55    109-78=31
                        109-79=30


        current := X[ n - 24 + 1 ] + X[ n - 55 + 1 ];
        if ( current >= M ) then
            current := current - M;
        X[n] := current;
    */
            CARD32      n;
            CARD32      current;
    
        n=X[0];
        if(n<79){
            current=X[n-23]+X[n-54];
            X[n-54]=current;
            n++;
            X[0]=n;
        }else{
            current=X[n-78]+X[n-54];
            X[n-54]=current;
            n++;
            if(n>109){
                X[0]=55;
            }else{
                X[0]=n;
            }
        }
        return(current);
    }/*BcRandom_random; */
    


    static  CARD32  defaultX[56]    ={  55,
                1607813071, 410442638,  1521159381, 471588148,  1656306875, 
                1877698854, 1457017985, 1885636224, 2120983145, 838865274,  
                622391523,  1599495796, 1589420163, 646358994,  1902836023, 
                294190104,  528352961,  810165570,  2008068603, 2064065124, 
                148481515,  1874022922, 444511217,  1229535568, 1447190841, 
                97924086,   1532317171, 1092420292, 112366451,  1855143102, 
                1983737863, 650553016,  612584047,  899301394,  863131509,  
                204748396,  1301536603, 1906202310, 284925217,  1675295776, 
                619597367,  965140710,  413816387,  831647212,  960766755,  
                2021366322, 1709289321, 745170552,  719637471,  174912226,  
                524134565,  1957015236, 1065289589, 490210922,  644050577
            };/*defaultX[]*/


    static
    PROCEDURE(load,(FILE* fd,CARD32 X[56]),void)
    {
        INT32       i;
        for(i=0;i<56;i++){
            fscanf(fd,"%lu",&(X[i]));
        }
    }/*load; */
    
    
    static
    PROCEDURE(save,(FILE* fd,CARD32 X[56]),void)
    {
        INT32       i;
        for(i=0;i<56;i++){
            fprintf(fd,"%lu ",X[i]);
        }
    }/*save*/
    

    PROCEDURE(BcRandom_load,(CARD32 X[56]),FILE*)
    {
            FILE*       fd;
            const char* fname;
        
        fname=getenv("BcRandom_FilePath");
        if(fname==NIL){
            fname=RANDOMFILE;
        }
        fd=fopen(RANDOMFILE,"r");
        if(fd==NIL){
            fd=fopen(RANDOMFILE,"w+");
            save(fd,defaultX);
            fseek(fd,0,SEEK_SET);
        }
        if(fd!=NIL){
            load(fd,X);
        }
        return(fd);
    }/*BcRandom_load; */

    
    PROCEDURE(BcRandom_save,(FILE* fd,CARD32 X[56]),void)
    {
        fd=freopen(RANDOMFILE,"w",fd);
        if(fd==NULL){
            fprintf(stderr,"Warning: BcRandom cannot reopen %s\n",RANDOMFILE);
        }else{
            save(fd,X);
            fclose(fd);
        }
    }/*BcRandom_save; */
    

    PROCEDURE(BcRandom_fromfile,(void),CARD32)
    {
            FILE*       fd;
            CARD32      X[56];
            CARD32      r;
        
        fd=BcRandom_load(X);
        r=BcRandom_random(X);
        BcRandom_save(fd,X);
        return(r);
    }/*BcRandom_fromfile; */


/*END BcRandom. */

/*** BcRandom.c                       -- 2004-01-01 09:39:00 -- pascal   ***/
