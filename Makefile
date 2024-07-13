#COMPILER
CXX      := -c++
#COMPILER FLAGS
CXXFLAGS :=  -Wall -g
#LINKER AND LIBRARIES FLAGS
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-window -lsfml-system
#NAME OF BUILD DIR
BUILD    := ./build
#NAME OF OBJECT'S DIR
OBJ_DIR  := $(BUILD)/objects
#NAME NAME OF APPS DIR
APP_DIR  := $(BUILD)/apps
#BUILD FILE NAME
TARGET   := DEFO
#NAME OF INCLUDE DIR
INCLUDE  := -Iinclude/
#FIND FILES IF ".cpp"
SRC      := $(wildcard *.cpp)
#OBJECTS FROM FILES
OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)

#BUILD METHOD
all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"