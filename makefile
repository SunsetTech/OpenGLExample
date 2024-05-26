PROJECT_NAME := Main

CC := g++
CFLAGS := -c -IHeaders -MMD -DGLM_ENABLE_EXPERIMENTAL
LDFLAGS := -lGL -lGLEW -lglfw
BUILD := Build
SOURCE := Source
SOURCES := $(shell find $(SOURCE) -name '*.cpp')
OBJECTS := $(patsubst $(SOURCE)/%,$(BUILD)/%,$(SOURCES:.cpp=.o))
NAME := $(PROJECT_NAME)


all: $(OBJECTS) $(NAME)

$(NAME): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.o: $(SOURCE)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo Scrub a dub dub...
	@rm -rf Build
	@rm -f *.so*
	@echo There! All clean! ^-^

.PHONY: print
print:
	@echo $(SOURCE)
	@echo $(SOURCES)
	@echo $(BUILD)
	@echo $(OBJECTS)

-include $(OBJECTS:.o=.d)
