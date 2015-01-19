#
# Makefile for the cardmaker
#
# $Author: kahle $
# $Date: 2006/08/01 16:47:03 $
# $Revision: 1.7 $
#

# project name
PROJECT = logchecker

# Debug version
DEBUG = off
MVD = off
TEST = off

CXX           =
HdrSuf	      = h
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        = exe
DllSuf        = so
OutPutOpt     = -o

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# Linux with egcs (>= RedHat 5.2)
ifeq ($(ZARCH_TYPE),i386-suse63-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
endif
ifeq ($(ZARCH_TYPE),i386-suse72-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
endif
ifeq ($(ZARCH_TYPE),i586-suse82-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
endif
ifeq ($(ZARCH_TYPE),i586-sl3-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
endif
ifeq ($(ZARCH_TYPE),i586-sl4-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
endif
###
ifeq ($(ZARCH_TYPE),i586-sl5-linux)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
endif
###
ifeq ($(ZARCH_TYPE),MacOSX)
# MacOS X with cc (GNU cc 2.95.2)
CXX           = c++
CXXFLAGS      = -O -pipe -Wall
LD            = c++
LDFLAGS       = -O -Xlinker -bind_at_load -flat_namespace
# The SOFLAGS will be used to create the .dylib; the .so will
# be created separately
DllSuf        = dylib
SOFLAGS       = -dynamiclib -flat_namespace -undefined suppress
endif

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

OBJDIR	= ../obj
DICTDIR	= ../dict
USRINCS += ../inc/
USRSRC	+= ../src/
EXEDIR	= ../exe/$(ZARCH_TYPE)

CXXFLAGS += -I$(USRINCS)
LDFLAGS += -I$(USRINCS)

KFRECONLIB := -L$(GUTCODEDIR)/kfrecon/lib/$(ZARCH_TYPE) -lkfrecon
KFRECONINCS := -I$(GUTCODEDIR)/kfrecon/inc/mvd
KFRECONINCS += -I$(GUTCODEDIR)/kfrecon/inc/mvd/vmp
KFRECONINCS += -I$(GUTCODEDIR)/kfrecon/inc/util
KFRECONINCS += -I$(GUTCODEDIR)/kfrecon/inc/vtx

# GutLib
GUTLIBDIR = $(GUTCODEDIR)/libraries/GutLib
ifeq ($(TEST),on)
	GUTLIBDIR = $(GUTCODEDIR)/libraries/GutLib-test
endif
CXXFLAGS += -I$(GUTLIBDIR)/inc
LDFLAGS += -L$(GUTLIBDIR)/lib/$(ZARCH_TYPE) -lGutLib

# Debug mode
ifeq ($(DEBUG),on)
	CXXFLAGS += -g
	CXXFLAGS += -DCF__DEBUG
endif

#MVD mode including kfrecon
ifeq ($(MVD),on)
	LDFLAGS += $(KFRECONLIB)
	CXXFLAGS += $(KFRECONINCS)
	CXXFLAGS += -DCF__MVD
endif

SRCFILES = $(wildcard $(USRSRC)/*.$(SrcSuf))
HDRFILES = $(wildcard $(USRINCS)/*.h))
OBJFILES = $(addprefix $(OBJDIR)/, $(addsuffix .$(ObjSuf), $(notdir $(basename $(SRCFILES)))))

#------------------------------------------------------------------

all: exe

exe:	$(OBJFILES)
	$(LD) $(LDFLAGS) $(LIBS) \
	$^ $(OutPutOpt) $(EXEDIR)/$(PROJECT).$(ExeSuf)
	@echo "$@ done"

$(OBJDIR)/%.$(ObjSuf):  $(USRSRC)/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(OBJDIR)/%.$(ObjSuf):  $(DICTDIR)/%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(OBJDIR)/%.$(ObjSuf):  $(USRINCS)/%.h

dict:   $(DICTFILES)

#$(DICTDIR)/%Dict.$(SrcSuf): $(USRINCS)/%.h
#	@echo -n "Generating dictionary $@...  "
#	@rootcint -f $@ -c -I$(USRINCS) -I$(ZEVLIBDIR)/inc $^
#	@echo "done"

clean:
	@rm -fv $(OBJDIR)/*.$(ObjSuf)

cleanall:	clean
	@rm -fv $(DICTDIR)/*.*
	@rm -fv $(EXEDIR)/*.$(ExeSuf)
	@rm -frv ../htmldoc/*

purge:
	@rm -fv $(USRSRC)/*~
	@rm -fv $(USRINCS)/*~
	@rm -fv ../*~
	@rm -fv *~

checkdirs: ../exe/$(ZARCH_TYPE) ../obj/$(ZARCH_TYPE) ../dict ../htmldoc

../exe/$(ZARCH_TYPE): ../exe
	mkdir -p $@

../obj/$(ZARCH_TYPE): ../obj
	mkdir -p $@

../exe:
	mkdir -p $@

../obj:
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
	@echo "Make the $(PROJECT) executable"
	@echo "Just type make."
	@echo ""
	@echo "Options available:"
	@echo "all       -> make all"
	@echo "exe       -> make the executable"
	@echo "clean     -> remove object files"
	@echo "cleanall  -> remove object files, dictionaries and the HTML documentation"
	@echo "purge     -> remove backup files"
	@echo "html      -> make HTML documentation"
	@echo "checkdirs -> create necessary directories"
	@echo ""
	@echo "To create a debug version set DEBUG=on."
	@echo "In both cases make clean first."
	@echo "E.g. 'make clean all DEBUG=on'"
	@echo ""
