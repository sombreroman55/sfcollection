CC := g++
TARGET := sfas
CPPFLAGS := -DDEBUG # Add any #defines or such things here
CXXFLAGS := -ggdb
LDFLAGS := # Link any other libraries here
SRC_DIRS := src
BUILD_DIR := build
INCLUDE_DIRS := -I./src/
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cc))
OBJS := $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cc=.o)))
vpath %.cc $(SRC_DIRS)

# Build target
$(TARGET): $(OBJS) main.cc
	$(CC) $(INCLUDE_DIRS) $(CXXFLAGS) $^ -o $@

# Build object files
$(BUILD_DIR)/%.o: %.cc
	$(CC) $(INCLUDE_DIRS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)/*.o
	rm -f $(TARGET)
