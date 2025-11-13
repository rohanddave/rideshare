#!/usr/bin/make -f

#-------------------------------------------------------------------------------
# 1. Setting up necessary variables for the build process
#-------------------------------------------------------------------------------

# The compilers that we will be using (we will only use g++)
CC := gcc
CXX := g++

# Common library path
COMMON_DIR := ../common

# $(wildcard *.h) finds all file names with patterns (random string + ".h")
HDRS := $(wildcard *.h)
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)		# replaces .cpp extension to .o (e.g., main.cpp -> main.o)
				# and stores the names to OBJS

# $(wildcard DriverServer*.h) finds all file names with patterns ("DriverServer" + random string + ".h")
SVR_HDRS := $(wildcard DriverServer*.h)
SVR_SRCS := $(wildcard DriverServer*.cpp)
SVR_OBJS := $(SVR_SRCS:.cpp=.o)

# $(wildcard DriverClient*.h) finds all file names with patterns ("DriverClient" + random string + ".h")
CLNT_HDRS := $(wildcard DriverClient*.h)
CLNT_SRCS := $(wildcard DriverClient*.cpp)
CLNT_OBJS := $(CLNT_SRCS:.cpp=.o)

# $(filter-out X Y Z, A) removes X Y and Z from A if X Y Z are found in A
CMN_HDRS := $(filter-out $(SVR_HDRS) $(CLNT_HDRS), $(HDRS))
CMN_SRCS := $(filter-out $(SVR_SRCS) $(CLNT_SRCS), $(SRCS))
CMN_OBJS := $(CMN_SRCS:.cpp=.o)

# Common library objects from ../common/
COMMON_OBJS := $(COMMON_DIR)/Socket.o $(COMMON_DIR)/ServerSocket.o

# -Wall prints: all warnings
# -std=c++11: use of C++11
CFLAGS := -Wall -std=c++11

# -pthread: use of posix threads (necessary to use std::thread or pthreads)
LFLAGS := -pthread

# we are building two target binaries: server and client
TARGET := server client

#-------------------------------------------------------------------------------
# 2. What to build and how to build them
#-------------------------------------------------------------------------------

# The build rules are defined as follows:
# target : prerequisite files
#	How to build the target
# 1. Make program will first check whether the target exists in the folder.
# 2. If not it will check for prerequisite files.
# 3. If the prerequisite files all exist in the folder the program will execute
#    the next line to build the target.
# 4. If any of the prerequisite file does not exist, the program will look for 
#    rules to create the prerequisite file: it will look for rules where the
#    prerequisite file is the target.


# "all:" is the starting point of the build process unless specified otherwise.
# 1. The make program will look for targets (i.e., server and client) to build
# 2. If the target is not found in the folder it will look for
#    rules to build the target (it will look for "server: xxx" and "client: xxx"
#    which should define the rules to build the server and the client)

all: server client

debug: DFLAGS := -ggdb -DDEBUG
debug: server client

# Build common library first
$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.cpp
	$(MAKE) -C $(COMMON_DIR)

# "server:" defines rules to build the server.
# 1. To build the server binary we need compiled object files for the server.
#    We defined them above and the necessary object files are:
#    - $(SVR_OBJS) that includes all DriverServer* object files and
#    - $(CMN_OBJS) that include all common object files (like DriverSocket)
#    - $(COMMON_OBJS) that include Socket and ServerSocket from ../common/
# 2. The next line $(CXX) $(LFLAGS) -o $@ $^ defines how to create server
#    binary. This line translates to
#
#      g++ -pthread -o server DriverServerMain.o DriverServerStub.o ... DriverSocket.o ... ../common/Socket.o ...
#
#    $@ is a macro for the string behind the colon (i.e., server).
#    $^ is a macro for all the string after the colon (i.e., $(SVR_OBJS) $(CMN_OBJS) $(COMMON_OBJS))

server: $(SVR_OBJS) $(CMN_OBJS) $(COMMON_OBJS)
	$(CXX) $(LFLAGS) -o $@ $^

# This rule defines how to build the server specific object files.
# To build object files, corresponding source code files (i.e., cpp and h files) are
# necessary.
# Since we will have all the files the build command will be executed
#   g++ -Wall -std=c++11 -c DriverServerMain.cpp DriverServerStub.cpp ...

$(SVR_OBJS): $(SVR_SRCS) $(SVR_HDRS)
	$(CXX) $(CFLAGS) $(DFLAGS) -c $(SVR_SRCS)


# Same applies to the client program (when DriverClientMain.cpp exists).
client: $(CLNT_OBJS) $(CMN_OBJS) $(COMMON_OBJS)
	$(CXX) $(LFLAGS) -o $@ $^

$(CLNT_OBJS): $(CLNT_SRCS) $(CLNT_HDRS)
	$(CXX) $(CFLAGS) $(DFLAGS) -c $(CLNT_SRCS)


# This rule compiles the common source code into object files.
# This includes DriverSocket and other files that are shared between server and client
$(CMN_OBJS): $(CMN_SRCS) $(CMN_HDRS)
	$(CXX) $(CFLAGS) $(DFLAGS) -c $(CMN_SRCS)

# This defines how you will clean up the compiled files.
# You can type "make clean" in the command line to delete all compiled files
# which include .o files and the compiled binary.

clean:
	rm -rf *.o server client

# This indicates "clean" is not a target file to build but rather a
# special command.

.PHONY: clean debug all

