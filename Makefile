INCDIR   = include
SRCDIR   = src
SRCDIRS  = 
OBJDIR   = obj
BINDIR   = bin
LIBDIR   = lib
EXEFILE  = UpdatePML 





#Source Files to looks for
SOURCES := $(wildcard $(SRCDIRS:%=src/%/*.cpp)) $(wildcard src/*.cpp)



INCLUDES  = -Iinclude
LINKDIR   = -L$(LIBDIR)
LINKER    =  $(LINKDIR) 


CXX       = g++
CXXLIBS   =
LDLIBS    = $(LINKDIR)

CXXFLAGS  = -Wall $(INCLUDES) --std=c++11
LDFLAGS   = -std=c++11 $(LDLIBS)



#Target specific variables for Debug version.
DFLAG    = -DDEBUG
DBINDIR  =  $(BINDIR)/Debug
DOBJDIR  =  $(OBJDIR)/Debug
DEXE     =  $(DBINDIR)/$(EXEFILE)
DOBJECTS =  $(addprefix $(DOBJDIR)/,$(SOURCES:$(SRCDIR)/%.cpp=%.o))


#Target specific variables for Release version.
RFLAG    = -DNDEBUG
RBINDIR  =  $(BINDIR)/Release
ROBJDIR  =  $(OBJDIR)/Release
REXE     =  $(RBINDIR)/$(EXEFILE)
ROBJECTS  = $(addprefix $(ROBJDIR)/,$(SOURCES:src/%.cpp=%.o))


## Default build target Debug
Debug: $(DEXE)


$(DEXE) : $(DOBJECTS) | $(DBINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(DOBJDIR)/%.o: $(SRCDIR)/%.cpp | $(DOBJDIR)
	$(CXX) -o $@ -c $< $(DFLAG) $(CXXFLAGS)




Release: $(REXE)

$(REXE) : $(ROBJECTS) | $(RBINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(ROBJDIR)/%.o: $(SRCDIR)/%.cpp | $(ROBJDIR)
	$(CXX) -c -o $@ $< $(RFLAG) $(CXXFLAGS)


$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR) :
	mkdir $(BINDIR)


$(DBINDIR): | $(BINDIR)
	mkdir $(DBINDIR)

$(DOBJDIR): | $(OBJDIR)
	mkdir $(DOBJDIR) $(SRCDIRS:%=$(DOBJDIR)/%)


$(RBINDIR): | $(BINDIR)
	mkdir $(RBINDIR)

$(ROBJDIR): | $(OBJDIR)
	mkdir $(ROBJDIR) $(SRCDIRS:%=$(ROBJDIR)/%)


clean:
	rm -rf $(DOBJECTS) $(DEXE)

cleanDebug:
	rm $(DOBJECTS) $(DEXE)

cleanRelease:
	rm $(ROBJECTS) $(REXE)

## Include auto-generated dependencies rules
-include $(DOBJECTS:.o=.d)
