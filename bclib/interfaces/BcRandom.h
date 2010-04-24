/******************************************************************************
FILE:               BcRandom.h
LANGUAGE:           ANSI-C
SYSTEM:             ANSI
USER-INTERFACE:     None
DESCRIPTION
    This module compute random numbers.
    The routine BcRandom_random needs static data to compute a new random
    value. This static data can be obtained from a file with BcRandom_load,
    and saved with BcRandom_save. For a single value, BcRandom_fromFile
    performs these three steps.
    The random data file path is found from the environment variable 
    "BcRandomFilePath". If this environment variable does not exists or
    leads to no file, then a system dependant default file path is tried. 
    (on queen: "/local/lib/random.data").
    If the random data file does not exist then it is created and filled
    with default data (always the same). 
AUTHORS
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:07  pascal
    Initial entry into CVS.
    
    Revision 1.2  95/11/16  12:07:17  pascal
    Some small correction to compile in MSVC.
    
    Revision 1.1  95/11/16  06:37:44  pascal
    Initial revision
    
    1992-07-18 <PJB> Extracted from cookies.c.
    1993-09-08 <PJB> Removed RANDOMFILE. Now, the random file path is found 
                     from the environment variable.  
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
#ifndef __BcRandom__
#define __BcRandom__
#include <stdio.h>
#include <names.h>
#include BcInterface_h
#include BcTypes_h


    PROCEDURE(BcRandom_load,(CARD32 X[56]),FILE*)
        /*
            DO:         open and load the RANDOMFILE.
            POST:       X contains the random seed.
        */
        
    PROCEDURE(BcRandom_random,(CARD32 X[56]),CARD32)
        /*
            RETURN:     a new random value.
            POST:       X contains the new random seed.
            NOTE:       current := X[ n - 24 + 1 ] + X[ n - 55 + 1 ];
                        if ( current >= M ) then
                            current := current - M;
                        X[n] := current;
        */

    PROCEDURE(BcRandom_save,(FILE* fd,CARD32 X[56]),void)
        /*
            DO:         save the random seed and close the RANDOMFILE.
        */

    PROCEDURE(BcRandom_fromfile,(void),CARD32)
        /*
            RETURN:     a new random value.
        */
        
#endif /*BcRandom*/
