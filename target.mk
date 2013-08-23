#---- Outputs ----#
COMPONENT_NAME = subsumption

#--- Inputs ----#
CPPUTEST_HOME = cpputest
CPP_PLATFORM = gcc
PROJECT_HOME_DIR = .
SCRIPT_DIR = $(PROJECT_HOME_DIR)/scripts

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src\
	$(PROJECT_HOME_DIR)/src/agent\
	$(PROJECT_HOME_DIR)/src/environment\
	$(PROJECT_HOME_DIR)/src/util\

TEST_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/tests\
	$(PROJECT_HOME_DIR)/tests/agent\
	$(PROJECT_HOME_DIR)/tests/environment\
	$(PROJECT_HOME_DIR)/tests/util\

INC_DIRS = \
	$(PROJECT_HOME_DIR)/include\
	$(PROJECT_HOME_DIR)/include/agent\
	$(PROJECT_HOME_DIR)/include/environment\
	$(PROJECT_HOME_DIR)/include/util\
	$(PROJECT_HOME_DIR)/mocks\

INCLUDE_DIRS = \
	$(CPPUTEST_HOME)/include\
	$(PROJECT_HOME_DIR)/tests\
	${INC_DIRS}

MOCKS_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/mocks\
	$(PROJECT_HOME_DIR)/mocks/agent\
	$(PROJECT_HOME_DIR)/mocks/environment\
	$(PROJECT_HOME_DIR)/mocks/util\
