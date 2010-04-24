#******************************************************************************
#FILE:				$(COMMON)/bjlib/sources/Makefile
#LANGUAGE:			make
#SYSTEM:			UNIX
#USER-INTERFACE:	None
#DESCRIPTION
#	This is the makefile for the bjlib module.
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
#		$(MODULE)		bjlib, the name of this module.
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
#	1992-09-29 <PJB> Nouvelle version simplifiee.
#	1993-03-16 <PJB> Updated to use new common makedir.
#   2001-06-19 <PJB> Reorganized and simplified.
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
	bjobject.h \
	bjstring.h \
	bjstring_list.h \
	bjfile.h \
	bjarray.h \
	bjdict.h 


CSOURCES=\
	bjobject.c \
	bjstring.c \
	bjstring_list.c \
	bjstring_file.c \
	bjfile.c \
	bjarray.c \
	bjdict.c 

OBJCSOURCES=
CPLUSSOURCES=	

INCLUDES=\
	-I../sources \
	-I../interfaces \
	$(TARGET_INCLUDES)



LIBRARIES=bjlib
bjlib_OBJECTS=$(CSOURCES:.c=.o) $(OBJCSOURCES:.m=.o) $(CPLUSSOURCES:.cc=.o)
DOCUMENTATION=

PROGRAMS=
MANPAGES=

include $(MAKEDIR)/common
-include Makefile.depend

#### Makefile                         -- 2004-01-21 07:05:05 -- pascal   ####
