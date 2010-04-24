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
    1995/10/18 <PJB> Creation.
LEGAL
    Copyright Pascal J. Bourguignon 1992 - 1993
    All rights reserved.
    This program may not be included in any commercial product without the 
    author written permission. It may be used freely for any non-commercial 
    purpose, provided that this header is always included.
******************************************************************************/
#ifndef __bprib_names__
#define __bprib_names__

#ifdef MSDOS

#include "..\..\..\C\BCLIB\INTERFAC\NAMES.H"
#include "..\..\BPLIB\INTERFAC\NAMES.H"

#define BpRIB_hh          <BPRIB.HH>

#else

#define NAME_MISSING
#ifdef UNIX
#include <bclib/interfaces/names.h>
#include <bplib/interfaces/names.h>
#undef NAME_MISSING
#endif

#ifdef MACOS
#include "::::c:bclib:interfaces:names.h"
#include ":::bplib:interfaces:names.h"
#undef NAME_MISSING
#endif

#ifdef NAME_MISSING
#error You should define the File System used : MSDOS, UNIX, or MACOS.
#error If another File System is used, then add it to the names.h files.
#endif

#define BpRIB_hh       <BpRIB.hh>

#endif


#endif

/*** names.h                          -- 2003-11-30 06:16:12 -- pascal   ***/
