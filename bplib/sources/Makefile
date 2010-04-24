#******************************************************************************
#FILE:				$(COMMON)/bplib/sources/Makefile
#LANGUAGE:			make
#SYSTEM:			UNIX
#USER-INTERFACE:	None
#DESCRIPTION
#	This is the makefile for the bplib module.
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
#		$(MODULE)		bplib, the name of this module.
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
#	Revision 1.6  1995/11/23 03:53:39  pascal
#	Added BpClass and runtime class support in BpObject. Updated subclasses.
#	Added dependant/dependee in BpObject.
#
#	Revision 1.2  95/10/22  02:42:24  pascal
#	Modifications while adding BpDict.
#
#	1992-09-29 <PJB> Nouvelle version simplifiee.
#LEGAL
#	Copyright Pascal J. Bourguignon 1992 - 2002
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
	names.h \
	BpArray.hh \
	BpClass.hh \
	BpDict.hh \
	BpList.hh \
	BpObject.hh \
	BpString.hh \
	BpTimer.hh \
	PrintOnLevel.hh

CSOURCES=
OBJCSOURCES=
CPLUSSOURCES=\
	BpArray.cc \
	BpClass.cc \
	BpDict.cc \
	BpList.cc \
	BpObject.cc \
	BpString.cc \
	PrintOnLevel.cc

ifeq (`uname`,Linux)
#   BpTimer-Linux.cc
endif

INCLUDES=\
	-I. \
	-I../interfaces \
	-I$(PREFIX)/lib \
	-I$(PREFIX)/lib/bclib/interfaces \
	$(TARGET_INCLUDES)


LIBRARIES=bplib
bplib_OBJECTS=$(CSOURCES:.c=.o) $(OBJCSOURCES:.m=.o) $(CPLUSSOURCES:.cc=.o)
DOCUMENTATION=

PROGRAMS=
MANPAGES=

include $(MAKEDIR)/common
-include Makefile.depend

install::all
libraries::

#### Makefile                         -- 2004-01-20 09:30:49 -- pascal   ####
