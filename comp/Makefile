CC := g++
TARGET := sfcc
CPPFLAGS := # Add any #defines or such things here
CXXFLAGS := -ggdb
LDFLAGS := # Link any other libraries here
SRC_DIRS := src/frontend src/ds src/preproccessor src/optimizer src/backend src
BUILD_DIR := build
INCLUDE_DIRS := -I./src/frontend/ -I./src/ds/ -I./src/preproccessor/ -I./src/optimizer/ -I./src/backend/
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cc))
OBJS := $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cc=.o)))
vpath %.cc $(SRC_DIRS)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(INCLUDE_DIRS) $(CXXFLAGS) $^ -o $@

# Build object files
$(BUILD_DIR)/%.o: $(SRCS)
	$(CC) $(INCLUDE_DIRS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)/*.o
