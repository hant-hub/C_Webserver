EXE_NAME := app

SRC_DIR := ./src
BUILD_DIR := ./build

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')


OBJ := $(SRC_FILES:%=$(BUILD_DIR)/%.o)
DEP := $(SRC_FILES:%=$(BUILD_DIR)/%.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))


CPPFLAGS := $(INC_FLAGS) -MMD -MP


$(BUILD_DIR)/$(EXE_NAME): $(OBJ) $(BUILD_DIR)/html
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/html: $(SRC_DIR)/html
	mkdir -p $@
	cp -a $</. $@/ 


.PHONY: clean print
print:
	echo $(OBJ)
	echo $(SRC_FILES)
	echo $(INC_DIRS)
clean:
	rm -r $(BUILD_DIR)


-include $(DEP)