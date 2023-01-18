#Makefile

#Macros
PROJ_NAME := tle-ping
CXX := g++
SRC_DIR := src
INC_DIR := header-files
BUILD_DIR := outputs
OBJ_DIR := obj

#.cpp .hpp .o files
SRCSXX := $(wildcard $(SRC_DIR)/*.cpp)
HDRSXX := $(wildcard $(INC_DIR)/*.hpp)
OBJS := $(patsubst %.cpp,%.o, $(SRCSXX))
#OBJS := $(subst %.cpp, %.o, $(subst src, obj, $(SRCSXX)))

#Flags for compiler
CC_FLAGS := -c 		\
			-w 		\
			-Wall	\
			-ansi	\
			-pedantic

#Project dependences
PROJ_DEP := -std=c++11   \
			-std=gnu++11


all: directories $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@echo "Building binary using G++ linker \033[94m$@\033[0m ..."
	$(CXX) $^ -o $(BUILD_DIR)/$@ $(PROJ_DEP)
	@echo "Finish building binary in \033[94m$(BUILD_DIR)/$@\033[0m"
	@echo ' '
	@rm $(SRC_DIR)/*.o

%.o: %.cpp
	@echo "Building target using G++ Compiler $@ ..."
	$(CXX) -O0 -g -c $^ -o $@ -I $(INC_DIR)
#	$(CXX) $< $(CC_FLAGS) -o S@
	@echo "\033[94m$@ Finish compilation\033[0m"

directories:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)/* $(SRC_DIR)/*.o $(BUILD_DIR)
