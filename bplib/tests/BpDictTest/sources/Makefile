#******************************************************************************
#FILE:				$(COMMON)/bplib/tests/BpDictTest/sources/Makefile
#LANGUAGE:			make
#SYSTEM:			UNIX
#USER-INTERFACE:	None
#DESCRIPTION
#	This is the Makefile to build the BpDict Test program.
#
#	This Makefile uses the following environment variables:
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
#		$(MODULE)		BpDictTest, the name of this module.
#
#	Output:
#
#		$(PREFIX)/bin/$(PROGRAM)	the executable.
#
#AUTHORS
#	<PJB> Pascal J. Bourguignon
#MODIFICATIONS
#	1993-03-16 <PJB> Creation.
#   2001-06-19 <PJB> Reorganized & simplified.
#LEGAL
#	Copyright Pascal J. Bourguignon 1993 - 2001
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

INTERFACES=

CSOURCES=
OBJCSOURCES=
CPLUSSOURCES=\
	BpDictTest.cc

INCLUDES=\
	-I. \
	-I../interfaces \
	-I$(PREFIX)/lib \
	-I$(PREFIX)/lib/bplib/interfaces \
	-I$(PREFIX)/lib/bclib/interfaces \
	$(TARGET_INCLUDES)


LIBRARIES=
DOCUMENTATION=

PROGRAMS=BpDictTest
BpDictTest_OBJECTS=$(CSOURCES:.c=.o) $(OBJCSOURCES:.m=.o) $(CPLUSSOURCES:.cc=.o)
BpDictTest_LIBRARIES=\
	$(PREFIX)/lib/bplib/libraries/libbplib.a \
	$(PREFIX)/lib/bclib/libraries/libbclib.a \
	$(TARGET_LIBRARIES)
BpDictTest_LD=$(CCPLUS)

include $(MAKEDIR)/common
-include Makefile.depend

#### Makefile                         -- 2003-12-03 20:35:08 -- pascal   ####
