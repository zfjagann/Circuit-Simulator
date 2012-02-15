# These are phony targets since they don't actually create files with those names
.PHONY : clean realclean squeakyclean deleteBackups linecount depend

include Makefile.inc

dist: Makefile.dep $(OBJS)
	if [ ! -d $(DIST) ] ; then mkdir $(DIST) ; fi
	if [ ! -d $(DIST)/lib ] ; then mkdir $(DIST)/lib ; fi
	if [ ! -d $(DIST)/include ] ; then mkdir $(DIST)/include ; fi
	cp $(OBJS) $(DIST)/lib/
	cp $(GC_LIB)/* $(DIST)/lib/
	cp -r $(GC_INCLUDE)/* $(DIST)/include/
	cp -r $(CIRCUIT_LIBRARY)/* $(DIST)/include/
	cp $(DIST_FILES) $(DIST)/include/

$(EXE): Makefile.dep
	make --no-print-directory -f Makefile.real $(EXE)

# Cleans up the source directory's object files
# And files that were created automatically by flex and bison
clean:
	rm -f $(OBJS)

# Cleans up everything that was created at compile time
# Including the automatically created dependencies
realclean: clean
	rm -f 	main \
		Makefile.dep
	rm -rf $(DIST)

# Delete backup files (created automatically by my text editor)
deleteBackups:
	rm -f `find . | grep ".*~"`

# Deletes everthing realclean does, as well as backup files
squeakyclean: realclean deleteBackups

# Performs a line count of all the files i've written
linecount:
	wc -l $(ALL)

# Make the dependency file
# We need to have build flex and bison already, since we use those cpp files to
# build our dependencies.
Makefile.dep: $(SRCS)
	if [ ! -e Makefile.dep ] ; then touch Makefile.dep ; fi
	$(DEP) $(DEPFLAGS) -fMakefile.dep -- $(CXXFLAGS) -- $(SRCS) 2> /dev/null
	rm -f Makefile.dep.bak

# for convenience
depend: Makefile.dep
