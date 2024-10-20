SRCS := $(shell find . -name '*cpp')
BUILD_DIR := ../build
OBJSTMP := $(SRCS:%=$(BUILD_DIR)/%)
OBJS := $(OBJSTMP:.cpp=.o)

$(BUILD_DIR)/main: $(OBJS)
	g++ -std=c++17 $(OBJS) -o main
$(BUILD_DIR)/%.o: %.cpp
	g++ -c $< -o $@
.PHONY: clean
clean:
	find $(BUILD_DIR) -name '*.o' -delete
