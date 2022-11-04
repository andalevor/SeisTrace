TARGET = libseistrace.so

SDIR = src
IDIR = include
MLIB_DIR = extern/mlib

ifeq ($(origin BUILD_TYPE), undefined)
	ODIR = release
else
	ODIR = $(BUILD_TYPE)
endif

TARGET := $(ODIR)/$(TARGET)

CFLAGS := -I$(IDIR) -I$(MLIB_DIR) --std=c99 -Wall -Wextra -Wpedantic -fpic $(CFLAGS)
LDFLAGS = -lm -shared

ifeq ($(BUILD_TYPE), debug)
	CFLAGS := -g -fsanitize=address -fsanitize=undefined $(CFLAGS)
else ifeq ($(BUILD_TYPE), gperftools)
	CFLAGS := -g -DWITHPERFTOOLS -O2 $(CFLAGS)
	LDFLAGS := $(LDFLAGS) -lprofiler
else
	CFLAGS := -O2 $(CFLAGS)
endif

SRC = $(wildcard $(SDIR)/*.c)
DEP = $(wildcard $(IDIR)/*.h)
OBJ = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRC))

.PHONY: clean directories
all: directories $(TARGET)

$(ODIR)/%.o: $(SDIR)/%.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)

clean:
	@rm -rf $(ODIR)

directories: $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
