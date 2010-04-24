/******************************************************************************
FILE:               BcDefaultTest.c
LANGUAGE:           ANSI-C
SYSTEM:             ANSI (stdio)
USER-INTERFACE:     None
DESCRIPTION
    --- Macintosh implementation ---
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.1  95/11/16  06:28:30  pascal
    Initial revision
    
    1993-01-12 <PJB> Creation. (inspired from NeXTstep defolts.h)
    1993-01-13 <PJB> Wrote (objective-c).
    1993-03-19 <PJB> Renamed BcDefaultTest.c for "B"ourguignon's "C" library.
                    (instead of "B"ourguignon's "O"bjective-C library, or
                                "B"ourguignon's C"P"lusplus library).
                    This is needed for we can mix Objective-C with CPlusPlus
                    in the same sources.
BUGS
    The semantics of this implementation is not *exactly* the same as those
    of NeXTstep implementation. This should not be a problem for dumb use. 
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
#import <stdio.h>
#include <names.h>
#include BcDefault_h
#include BcImplementation_h

    static const char   rcsid[]="$Id: BcDefaultTest.c,v 1.1 2003/12/03 16:40:35 pjbpjb Exp $";

#define OWNER "TestDefault"
main()
{
        static BcDefault_T vector[] = {
            {"NXFont",              "Helvetica"},
            {"NXFontSize",          "12.0"},
            {"Nom avec: \\<-ici",   "Donn›e avec tabulation: <  >"},
            {"Donn›e avec return",  "Le retour est l’: <\n> nouvelle ligne"},
            {NIL,               NIL}
        };
        INT32           i;
        const char*     value;
        
    BcDefault_Register(OWNER,vector);
    i=0;
    while(vector[i].name!=NIL){
        value=BcDefault_Get(OWNER,vector[i].name);
        fprintf(stdout,"Get(%s,%s)=\n    [%s]\n    (%s)\n",
                        OWNER,vector[i].name,value,vector[i].value);
        INC(i);
    }

    BcDefault_Set(OWNER,"NXFont","Times");
    value=BcDefault_Get(OWNER,"NXFont");
    fprintf(stdout,"Get(%s,%s)=\n    [%s]\n",OWNER,"NXFont",value);

    BcDefault_Set(OWNER,"NXFontSize","145.0");
    value=BcDefault_Get(OWNER,"NXFontSize");
    fprintf(stdout,"Get(%s,%s)=\n    [%s]\n",OWNER,"NXFontSize",value);
    
    BcDefault_Set(OWNER,"Nouveaux default","Le grand-p‹re de ma "
                    "grand-m‹re et le p‹re de la m‹re de mon grand-frﬁre.");
    value=BcDefault_Get(OWNER,"Nouveaux default");
    fprintf(stdout,"Get(%s,%s)=\n    [%s]\n",OWNER,"Nouveaux default",value);
    
    BcDefault_WriteVector(OWNER,vector);

    return(0);
}
