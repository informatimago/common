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
    
    Revision 1.9  1995/11/23 05:51:28  pascal
    Corrected included path.

    Revision 1.8  95/11/23  03:48:48  pascal
    Added BpClass and runtime class support in BpObject.
    Updated subclasses.
    
    Added dependant/dependee in BpObject.
    
    Revision 1.6  95/11/16  12:19:44  pascal
    Small corrections to compile on MSVC.
    
    Revision 1.5  95/10/22  03:19:57  pascal
    Setting revision name V1.
    
    Revision 1.2  95/10/22  03:05:20  pascal
    Modifications while adding BpDict.
    
    1995-10-18 <PJB> Creation.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 2002

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
#ifndef bplib_names_h
#define bplib_names_h


#ifdef MSDOS       

#include "BCLIB\\INTERFAC\\NAMES.H"

#define BpArray_hh          <BPARRAY.HPP>
#define BpClass_hh          <BPCLASS.HPP>
#define BpDict_hh            <BPDICT.HPP>
#define BpList_hh            <BPLIST.HPP>
#define BpObject_hh        <BPOBJECT.HPP>
#define BpString_hh        <BPSTRING.HPP>
#define BpTimer_hh          <BPTIMER.HPP>
#define PrintOnLevel_hh    <PRTONLVL.HPP>


#else

#define NAME_MISSING
#ifdef UNIX
#include <bclib/interfaces/names.h>
#undef NAME_MISSING
#endif

#ifdef MACOS
#include ":bclib:interfaces:names.h"
#undef NAME_MISSING
#endif

#ifdef NAME_MISSING
#error You should define the File System used : MSDOS, UNIX, or MACOS.
#error If another File System is used, then add it to the names.h files.
#endif

#define BpArray_hh         <BpArray.hh>
#define BpClass_hh         <BpClass.hh>
#define BpDict_hh          <BpDict.hh>
#define BpList_hh          <BpList.hh>
#define BpObject_hh        <BpObject.hh>
#define BpString_hh        <BpString.hh>
#define BpTimer_hh         <BpTimer.hh>
#define PrintOnLevel_hh    <PrintOnLevel.hh>

#endif

#endif
