#******************************************************************************
#FILE:				$(COMMON)/bprib/sources/Makefile
#LANGUAGE:			make
#SYSTEM:			UNIX
#USER-INTERFACE:	None
#DESCRIPTION
#	This is the makefile for the bprib module.
#
#	This makefile uses the following environment variables:
#
#	Input variables are:
#
#       $(MAKEDIR)      where the makefiles are located.
#
#       $(PREFIX)   where the libraries are installed.
#                       It will be created a subdirectory in this 
#                       $(PREFIX) for each library compiled by 
#                       this makefile.
#
#       $(TARGET)       the name of the platform on which we're compiling.
#                       This is just used to include platform specific
#                       makefile rules.
#
#		$(MODULE)		bpcombi, the name of this module.
#
#	Output:
#
#		$(PREFIX)/$(MODULE)/interfaces/    the interface of the module,
#		$(PREFIX)/$(MODULE)/documentation/ the documentation of the module,
#		$(PREFIX)/$(MODULE)/libraries/     the libraries of the module.
#
#AUTHORS
#	<PJB> Pascal J. Bourguignon
#MODIFICATIONS
#	1993-03-16 <PJB> Creation.
#LEGAL
#	Copyright Pascal J. Bourguignon 1993 - 2002
#
#   This script is free software; you can redistribute it and/or
#   modify it under the terms of the GNU  General Public
#   License as published by the Free Software Foundation; either
#   version 2 of the License, or (at your option) any later version.
#
#   This script is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public
#   License along with this library; see the file COPYING.LIB.
#   If not, write to the Free Software Foundation,
#   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#******************************************************************************

INTERFACES=\
	BpRIB.hh \
	names.h 

CSOURCES=\
	number.c

OBJCSOURCES=

CPLUSSOURCES=\
	BpRIB.cc


INCLUDES=\
	-I../sources \
	-I../interfaces \
	-I$(PREFIX)/lib \
	-I$(PREFIX)/lib/bclib/interfaces \
	-I$(PREFIX)/lib/bplib/interfaces \
	$(TARGET_INCLUDES)


LIBRARIES=bprib
bprib_OBJECTS=$(CSOURCES:.c=.o) $(OBJCSOURCES:.m=.o) $(CPLUSSOURCES:.cc=.o)
DOCUMENTATION=

PROGRAMS=
MANPAGES=

include $(MAKEDIR)/common
-include Makefile.depend

install::all

#### Makefile                         -- 2004-01-20 09:31:21 -- pascal   ####
