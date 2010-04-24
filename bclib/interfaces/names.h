/******************************************************************************
FILE:               names.h
LANGUAGE:           C++
SYSTEM:             None
USER-INTERFACE:     None
DESCRIPTION
    This file defines names for includes of this library on several File 
    Systems.
AUTHOR
    <PJB> Pascal J. Bourguignon
MODIFICATIONS
    Revision 1.1  2001/06/05 06:38:19  uid1006
    Added common libraries and dosname utility to the repository.
    
    Revision 1.1  2001/04/30 01:58:08  pascal
    Initial entry into CVS.
    
    Revision 1.1  95/11/16  06:37:49  pascal
    Initial revision
    
    1995-10-18 <PJB> Creation.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

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
#ifndef bclib_names_h
#define bclib_names_h

#ifdef MSDOS

#define ASCII_h                  <ASCII.H>
#define BcCStr_h                <BCCSTR.H>
#define BcDefault_h           <BCDEFAUL.H>
#define BcExcept_h            <BCEXCEPT.H>
#define BcGeom_h                <BCGEOM.H>
#define BcImplementation_h    <BCIMPLEM.H>
#define BcInterface_h         <BCINTERF.H>
#define BcList_h                <BCLIST.H>
#define BcMem_h                  <BCMEM.H>
#define BcRandom_h            <BCRANDOM.H>
#define BcString_h            <BCSTRING.H>
#define BcTypes_h              <BCTYPES.H>

#else

#define ASCII_h               <ASCII.h>
#define BcCStr_h              <BcCStr.h>
#define BcDefault_h           <BcDefault.h>
#define BcExcept_h            <BcExcept.h>
#define BcGeom_h              <BcGeom.h>
#define BcImplementation_h    <BcImplementation.h>
#define BcInterface_h         <BcInterface.h>
#define BcList_h              <BcList.h>
#define BcMem_h               <BcMem.h>
#define BcRandom_h            <BcRandom.h>
#define BcString_h            <BcString.h>
#define BcTypes_h             <BcTypes.h>

#endif


#endif
