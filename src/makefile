SRCS := $(shell find -name '*cpp')
BUILD_DIR := ../build
OBJSTMP := $(SRCS:%=$(BUILD_DIR)/%)
OBJS := $(OBJSTMP:.cpp=.o)

$(BUILD_DIR)/main: $(OBJS)
	echo $(OBJS)
	g++ $(OBJS) -o main
$(BUILD_DIR)/%.o: %.cpp
	echo "here"
	g++ -c $< -o $@
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

