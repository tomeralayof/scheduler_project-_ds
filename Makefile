BUILD_ALL = find ../ds/$(DS) -type f -name Makefile -execdir make all \;
BUILD_RELEASE_ALL = find ../ds/$(DS) -type f -name Makefile -execdir make release \;
BUILD_DEBUG_ALL = find ../ds/$(DS) -type f -name Makefile -execdir make debug \;
BUILD_TEST = find ../ds/$(DS) -type f -name Makefile -execdir make test \;
BUILD_CLEAN = find ../ds/$(DS) -type f -name Makefile -execdir make clean \;


buildall:
	$(BUILD_ALL)

releaseall:
	$(BUILD_RELEASE_ALL)
	
debugall:
	$(BUILD_DEBUG_ALL)

buildtest:
	$(BUILD_TEST)
	
cleanall:
	$(BUILD_CLEAN)
	

