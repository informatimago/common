MODULE=bplib
include $(MAKEDIR)/module

# We'll skip the test programs on OPENSTEP 4.2 since 
# the compiler has difficulties to compile them.
all clean cleanall distclean cvsclean depend install showvars:: 
	@case "`$(MAKEDIR)/distribution`" in \
	NEXTSTEP*) true ;;\
	*)         $(MAKE) -C tests $(MFLAGS) $@ ;;\
	esac

#### Makefile                         -- 2003-11-30 20:15:44 -- pascal   ####
