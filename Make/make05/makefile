# gets the list of all .c files in lib1/ into the variable, and the C files in lib2/ into lib2_SRCS 
lib1_SRCSib1_SRCS := $(wildcard lib1/*.c)
lib2_SRCS := $(wildcard lib2/*.c)

# Converts these to lists of object files using a substitution reference that changes .c to .o 
# and stores the results in lib1_OBJS and lib2_OBJS
lib1_OBJS := $(lib1_SRCS:.c=.o)
lib2_OBJS := $(lib2_SRCS:.c=.o)

.PHONY: all
all: $(lib1_OBJS) $(lib2_OBJS)

# Uses the built-in variable COMPILE.C to run a compiler that compiles a .c file into a .o file
%.o: %.c ; @$(COMPILE.C) -o $@ $<

# The makefile builds all the objects in lib1_OBJS and lib2_OBJS because they are prerequisites of all

# Alters the value of CPPFLAGS only for the file lib1/special.o
lib1/special.o: CPPFLAGS += -Wcomment

# Any .o files that are built in lib1/ will be built using the -fast command line option
lib1/%.o: CPPFLAGS += -fast
