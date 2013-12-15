#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#--- Outputs & Inputs ----#
include target.mk

#---- Setting ----#
CPPUTEST_WARNINGFLAGS = -Wall -W -Werror -pedantic-errors\
                        -Wcast-qual -Wcast-align -Wwrite-strings\
                        -Wconversion -Wfloat-equal -Wpointer-arith
CPPUTEST_CXXFLAGS += -include tests/PreIncludeFiles.h
LD_LIBRARIES = -lpthread -lboost_thread-mt -lboost_system-mt

CPPUTEST_USE_EXTENSIONS = Y

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
