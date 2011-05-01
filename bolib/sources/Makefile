#******************************************************************************
#FILE:				makefile
#LANGUAGE:			make
#SYSTEM:			UNIX
#USER-INTERFACE:	None
#DESCRIPTION
#	This is the makefile for the bolib module.
#
#	This makefile uses the following environment variables:
#
#		COMMON		the path to the common library directory, where makedir
#					is to be found.
#
#		TARGET		the name of the default target architecture. There must
#					be a $(COMMON)/makedir/$(TARGET) makefile include.
#
#AUTHORS
#	<PJB> Pascal J. Bourguignon
#MODIFICATIONS
#	1992/09/29 <PJB> Nouvelle version simplifiee.
#LEGAL
#    GPL
#    
#    Copyright Pascal Bourguignon 1992 - 2011
#    
#    This program is free software; you can redistribute it and/or
#    modify it under the terms of the GNU General Public License
#    as published by the Free Software Foundation; either version
#    2 of the License, or (at your option) any later version.
#    
#    This program is distributed in the hope that it will be
#    useful, but WITHOUT ANY WARRANTY; without even the implied
#    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#    PURPOSE.  See the GNU General Public License for more details.
#    
#    You should have received a copy of the GNU General Public
#    License along with this program; if not, write to the Free
#    Software Foundation, Inc., 59 Temple Place, Suite 330,
#    Boston, MA 02111-1307 USA
#******************************************************************************

INTERFACES=\
	BoArray.h \
	BoList.h \
	BoListNoRetain.h \
	BoObject.h \
	BoString.h \
	BoTimer.h 

CSOURCES=

OBJCSOURCES := \
	BoArray.m \
	BoListNoRetain.m \
	BoList.m \
	BoObject.m \
	BoString.m 

ifeq (`uname`,Darwin)
OBJCSOURCES += BoTimer.next.m
endif

ifeq (`uname`,Linux)
#OBJCSOURCES += BoTimer.posix.m
endif

CPLUSSOURCES=	


INCLUDES=\
	-I. \
	-I../interfaces \
	-I$(PREFIX)/lib/bclib/interfaces \
	$(TARGET_INCLUDES)


LIBRARIES=bolib
bolib_OBJECTS=$(CSOURCES:.c=.o) $(OBJCSOURCES:.m=.o) $(CPLUSSOURCES:.cc=.o)
DOCUMENTATION=

PROGRAMS=
MANPAGES=

include $(MAKEDIR)/common
-include Makefile.depend

install::all

#### Makefile                         -- 2004-01-20 09:30:38 -- pascal   ####

