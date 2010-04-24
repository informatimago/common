#******************************************************************************
#FILE:				makefile
#LANGUAGE:			make
#SYSTEM:			UNIX
#USER-INTERFACE:	None
#DESCRIPTION
#	This is the makefile for the BpRIB module.
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
#	Copyright Pascal J. Bourguignon 1992 - 1992
#	All rights reserved.
#	This program may not be included in any commercial product without the 
#	author written permission. It may be used freely for any non-commercial 
#	purpose, provided that this header is always included.
#******************************************************************************


MAKEDIR			=	$(COMMON)/makedir
PROJECT			=	$(COMMON)/cplusplus/bprib/tests
PROGRAM			=	ribtest

include $(MAKEDIR)/common
include $(MAKEDIR)/target$(TARGET)


CSOURCES		= 
CPLUSSOURCES	= \
	ribtest.cc
OBJECTS			= \
	ribtest.o
INCLUDES		= \
	-I. \
	-I../interfaces \
	-I$(COMMON)/cplusplus/bprib/interfaces \
	-I$(COMMON)/cplusplus/bplib/interfaces \
	-I$(COMMON)/c/bclib/interfaces \
	$(TARGET_INCLUDES)
LIBRARIES		= \
	$(COMMON)/cplusplus/libraries/libbprib.a \
	$(COMMON)/cplusplus/libraries/libbplib.a \
	$(COMMON)/c/libraries/libbclib.a \
	$(TARGET_LIBRARIES)

CFLAGS=$(TARGET_CFLAGS)  -arch m68k -arch i486 -arch hppa -arch sparc 
CPLUSFLAGS=$(TARGET_CPLUSFLAGS)  -arch m68k -arch i486 -arch hppa -arch sparc 


ribtest:makefile ribtest.o $(LIBRARIES)
	cc++ $(CPLUSFLAGS) -o ribtest ribtest.o $(LIBRARIES)

ribtest.o::ribtest.cc $(COMMON)/cplusplus/bprib/interfaces/BpRIB.hh

test:../sources/ribtest.csh ../../bin/ribtest ../sources/ribtest.reference
	-rm ../sources/ribtest.output
	cd ../sources ; ribtest.csh
	cd ../sources ; diff ribtest.reference ribtest.output

clean::
	- rm ../../bin/ribtest *.output


# For $(MAKEDIR)/library :
#	A library subdirectory must contain the following directories:
#		./objects.$(TARGET)	the target directory,
#		./sources			the sources directory,
#		./interfaces		the interfaces directory,
#	The module library will be put in $(PROJECT)/libraries/lib$(MODULE).a
#	Input variables are:
#		$(PROJECT)		the "project" directory containing the "libraries" 
#						directory and the module directories;
#		$(LIBRARY)		the name of the library;
#		$(CSOURCES)		the list of C sources in ../sources/;
#		$(CPLUSSOURCES)	the list of C++ sources in ../sources/;
#		$(OBJECTS)		the list of .o files in the object directory;
#		$(INCLUDES)		the list of includes -I options to compile the module;
#	Output:
#		$(PROJECT)/libraries/lib$(LIBRARY).a	the compiled library.


#END makefile




#### Makefile                         -- 2004-01-17 16:39:39 -- pascal   ####
