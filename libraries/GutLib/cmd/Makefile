#
# Makefile for the GutLib shared library
#
# $Author: kahle $
# $Date: 2008/06/10 08:47:27 $
# $Revision: 1.16 $
#

#library name
LIBNAME = GutLib

# Defaults
DEBUG = off
MVD = off
TEST = off

CXX           = 
HdrSuf	      = h
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o 

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS    := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

ifeq ($(DEBUG),on)
ROOTLIBS    := $(shell root-config --new --libs)
ROOTGLIBS    := $(shell root-config --new --glibs)
endif

# Linux with egcs (>= RedHat 5.2)
ifeq ($(ZARCH_TYPE),i386-suse63-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC -Wno-deprecated
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif
ifeq ($(ZARCH_TYPE),i386-suse72-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC -Wno-deprecated
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif
ifeq ($(ZARCH_TYPE),i586-suse82-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC -Wno-deprecated
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif
ifeq ($(ZARCH_TYPE),i586-sl3-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC -Wno-deprecated
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif
ifeq ($(ZARCH_TYPE),i586-sl4-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC -Wno-deprecated
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif
ifeq ($(ZARCH_TYPE),MacOSX)
CXX           = c++
CXXFLAGS      = -O -pipe -Wall
LD            = c++
LDFLAGS       = -O -Xlinker -bind_at_load -flat_namespace
# The SOFLAGS will be used to create the .dylib; the .so will
# be created separately
DllSuf        = dylib
SOFLAGS       = -dynamiclib -flat_namespace 
# -undefined suppress
endif

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) -lMinuit $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) -lMinuit $(SYSLIBS)

# Debug mode ?
ifeq ($(DEBUG),on)
	CXXFLAGS += -g
	CXXFLAGS += -DCF__DEBUG
endif

LIBRARIESDIR = $(GUTCODEDIR)/libraries
# set to test dir in test mode
ifeq ($(TEST),on)
	LIBRARIESDIR = $(GUTCODEDIR)/libraries-test
endif

OBJDIR        = $(LIBRARIESDIR)/GutLib/obj/$(ZARCH_TYPE)
DICTDIR       = $(LIBRARIESDIR)/GutLib/dict
USRINCS       += $(LIBRARIESDIR)/GutLib/inc/
USRSRC        += $(LIBRARIESDIR)/GutLib/src/
LIBDIR        = $(LIBRARIESDIR)/GutLib/lib/$(ZARCH_TYPE)

CXXFLAGS += -I$(USRINCS)
LDFLAGS += -I$(USRINCS)

KFRECONLIB := -L$(GUTCODEDIR)/kfrecon/lib/$(ZARCH_TYPE) -lkfrecon
KFRECONINCS := -I$(GUTCODEDIR)/kfrecon/inc/mvd
KFRECONINCS += -I$(GUTCODEDIR)/kfrecon/inc/mvd/vmp
KFRECONINCS += -I$(GUTCODEDIR)/kfrecon/inc/util
KFRECONINCS += -I$(GUTCODEDIR)/kfrecon/inc/vtx

#MVD mode including kfrecon
ifeq ($(MVD),on)
	LDFLAGS += $(KFRECONLIB)
	CXXFLAGS += $(KFRECONINCS)
	CXXFLAGS += -DCF__MVD
endif

SRCFILES = $(wildcard $(USRSRC)/*.$(SrcSuf))
HDRFILES = $(wildcard $(USRINCS)/*.h))
DICTFILES = $(addprefix $(DICTDIR)/, $(addsuffix Dict.$(SrcSuf), \
	    $(notdir $(basename $(HDRFILES)))))
OBJFILES = $(addprefix $(OBJDIR)/, $(addsuffix .$(ObjSuf), $(notdir $(basename $(SRCFILES))))) \
	   $(addprefix $(OBJDIR)/, $(addsuffix .$(ObjSuf), $(notdir $(basename $(DICTFILES)))))

#------------------------------------------------------------------

all:	dict lib

lib:	$(OBJFILES)
ifeq ($(ZARCH_TYPE),MacOSX)
# We need to make both the .dylib and the .so
	$(LD) $(SOFLAGS) $(GLIBS) $^ $(OutPutOpt) $(LIBDIR)/lib$(LIBNAME).$(DllSuf)
	$(LD) -bundle -undefined suppress -Wl,-x $(LDFLAGS) $^ \
	$(OutPutOpt) $(subst .$(DllSuf),.so,$(LIBDIR)/lib$(LIBNAME).$(DllSuf))
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $(GLIBS) \
	$^ $(OutPutOpt) $(LIBDIR)/lib$(LIBNAME).$(DllSuf)
	@echo "$@ done"	
endif

$(OBJDIR)/%.$(ObjSuf):	$(USRSRC)/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< -o $@	
$(OBJDIR)/%.$(ObjSuf):	$(DICTDIR)/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(OBJDIR)/%.$(ObjSuf):  $(USRINCS)/%.h

dict:	$(DICTFILES)

$(DICTDIR)/%Dict.$(SrcSuf): $(USRINCS)/%.h
ifeq ($(MVD),on)
	@echo -n "Generating dictionary $@...  "
	@rootcint -f $@	-c -p -I$(USRINCS) $(KFRECONINCS) $^ 
	@echo "done"
else
	@echo -n "Generating dictionary $@...  "
	@rootcint -f $@	-c -I$(USRINCS) $^ 
	@echo "done"
endif

clean:
	@rm -fv $(OBJDIR)/*.$(ObjSuf)

cleanall:	clean
	@rm -fv $(DICTDIR)/*.*
	@rm -fv $(LIBDIR)/*.$(DllSuf)

purge:
	@rm -fv $(USRSRC)/*~
	@rm -fv $(USRINCS)/*~
	@rm -fv ../*~

checkdirs: ../lib/$(ZARCH_TYPE) ../obj/$(ZARCH_TYPE) ../dict ../htmldoc

../lib/$(ZARCH_TYPE): ../lib
	mkdir -p $@

../obj/$(ZARCH_TYPE): ../obj
	mkdir -p $@

../lib:
	mkdir -p $@

../obj:
	mkdir -p $@

../exe:
	mkdir -p $@

../dict:
	mkdir -p $@

../htmldoc:
	mkdir -p $@

html:
	@echo "Generating HTML documentation ..."
	@root -b -q -l makehtml.C
	@echo "Done."

help:
	@echo ""
	@echo "Make the $(LIBNAME) shared library."
	@echo "Just type make."
	@echo ""
	@echo "Options available:"
	@echo "all       -> make shared library"
	@echo "clean     -> remove object files"
	@echo "cleanall  -> remove object files, dictionaries, the shared"
	@echo "             library and the HTML documentation"
	@echo "purge     -> remove backup files"
	@echo "html      -> make HTML documentation"
	@echo "checkdirs -> create necessary directories"
	@echo ""
	@echo "To create a debug version set DEBUG=on."
	@echo "E.g. 'make clean all DEBUG=on'"
	@echo ""
