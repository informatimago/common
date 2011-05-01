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
    Revision 1.1  2003/12/04 03:36:54  pjbpjb
    Cleaned-up.
    Moved bc*.[hc] in bclib.
    Fix.

    Revision 1.1  2002/08/11 04:12:17  pascal
    Updated with changes from MAPTREE on bclib/bplib/makedir.
    
LEGAL
    Copyright Pascal J. Bourguignon 1996 - 2011
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef __bpcombi_names__
#define __bpcombi_names__


#ifdef MSDOS       

#include "..\\..\\BPLIB\\INTERFAC\\NAMES.H"

#define BpArrangementSansRepeat_hh   <BARRSARE.HPP>
#define BpArrangementWithRepeat_hh   <BARRWIRE.HPP>
#define BpCombination_hh             <BPCOMBIN.HPP>
#define BpSetFunctor_hh              <BPSEFUNC.HPP>
#define BpSetEnumerator_hh           <BPSENUME.HPP>


#else

#define NAME_MISSING
#ifdef UNIX
#include <bplib/interfaces/names.h>
#undef NAME_MISSING
#endif

#ifdef MACOS
#include ":::bplib:interfaces:names.h"
#undef NAME_MISSING
#endif

#ifdef NAME_MISSING
#error You should define the File System used : MSDOS, UNIX, or MACOS.
#error If another File System is used, then add it to the names.h files.
#endif

#define BpArrangementSansRepeat_hh   <BpArrangementSansRepeat.hh>
#define BpArrangementWithRepeat_hh   <BpArrangementWithRepeat.hh>
#define BpCombination_hh             <BpCombination.hh>
#define BpSetFunctor_hh              <BpSetFunctor.hh>
#define BpSetEnumerator_hh           <BpSetEnumerator.hh>

#endif

#endif





/*** names.h                          --                     --          ***/
