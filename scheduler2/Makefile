CC:= gcc #compiler
CPICFLAGS:= -fPIC -ansi -pedantic-errors -Wall -Wextra #compiler flags with PIC
CFLAGS:= -ansi -pedantic-errors -Wall -Wextra #compiler flag for tests purpose
RELEASE= -O3 -DNDEBUG #compiler optimization flags
LDFLAGS:= -shared
DEBUG:= -g -DDEBUG #debug flags

SRCS_TST := $(wildcard *_test.c) #all files have _test.c
SRCS_LIB := $(filter-out $(SRCS_TST),$(wildcard *.c)) #all c files exept of *_test.c
OBJS_LIB := $(SRCS_LIB:.c=.o) #object files without test
OBJS_TST := $(SRCS_TST:.c=.o) #test object files

DEPENDENCY=scheduler

DEPENCENCY_1:=pq2
DEPENCENCY_2:=task

VLG = valgrind --leak-check=yes --track-origins=yes #valgrind 

OS_RUN_TIME_RELEASE = -L $(PATH_RELEASE) -Wl,rpath=$(PATH_RELEASE)
OS_RUN_TIME_DEBUG = -L $(PATH_DEBUG) -Wl,rpath=$(PATH_DEBUG)


all: release debug
	$(MAKE) -C ../$(DEPENCENCY_1) $(MAKE) -C ../$(DEPENCENCY_2)
###########################release###########################
PATH_OBJ_RELEASE = ../obj/release
PATH_RELEASE = ../libs/release	
LIB_RELEASE = ../libs/release/lib$(DEPENDENCY).so #name file and location

release: $(LIB_RELEASE)

$(LIB_RELEASE): $(PATH_OBJ_RELEASE)/$(DEPENDENCY).o
	$(CC) $(LDFLAGS) -o $@ $^ 

$(PATH_OBJ_RELEASE)/$(DEPENDENCY).o: $(SRCS_LIB)
	$(CC) -c $(OS_RUN_TIME_RELEASE) $(CPICFLAGS) $(RELEASE) $< -o $@	
	
###########################debug###########################
PATH_OBJ_DEBUG = ../obj/debug
PATH_DEBUG = ../libs/debug
LIB_DEBUG = ../libs/debug/lib$(DEPENDENCY).so

debug: $(LIB_DEBUG)

$(LIB_DEBUG): $(PATH_OBJ_DEBUG)/$(DEPENDENCY).o
	$(CC) $(LDFLAGS) -o $@ $^ 

$(PATH_OBJ_DEBUG)/$(DEPENDENCY).o: $(SRCS_LIB)
	$(CC) -c $(OS_RUN_TIME_DEBUG) $(CPICFLAGS) $(DEBUG) $< -o $@	
###########################test###########################
TESTS_TARGET:= a.out

test: $(TESTS_TARGET)
	./$(TESTS_TARGET)	
	
$(TESTS_TARGET): $(LIB_DEBUG) $(OBJS_TST)
	$(CC) $(FLAGS) $(DEBUG) -o $@ $(SRCS_TST) $< $(PATH_DEBUG)/libpq2.so $(PATH_DEBUG)/libheap.so $(PATH_DEBUG)/libvector.so $(PATH_DEBUG)/libtask.so $(PATH_DEBUG)/libuid.so

###########################vlg###########################
vlg: $(TESTS_TARGET)
	$(VLG) ./$(TESTS_TARGET)

###########################clean & phony###########################	
clean: 
	rm -f $(TESTS_TARGET) $(PATH_OBJ_RELEASE)/*.o $(PATH_OBJ_DEBUG)/*.o $(LIB_RELEASE) $(LIB_DEBUG)

.PHONY: clean all

# $< copy the string that is the first dependency
# $@ is a shortcut for the target (the blue text of the current segment)
 













