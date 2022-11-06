TARGET_NAME = seistrace

SDIR = src
IDIR = include
TDIR = tests
MDIR = extern/mlib

ifeq ($(origin BUILD_TYPE), undefined)
	ODIR = release
else
	ODIR = $(BUILD_TYPE)
endif

TARGET := $(ODIR)/lib$(TARGET_NAME).so

CFLAGS := -I$(IDIR) -I$(MDIR) --std=c99 -Wall -Wextra -Wpedantic -fpic $(CFLAGS)
LDFLAGS = -shared

ifeq ($(BUILD_TYPE), debug)
	CFLAGS := -g -fsanitize=address -fsanitize=undefined $(CFLAGS)
else ifeq ($(BUILD_TYPE), gperftools)
	CFLAGS := -g -DWITHPERFTOOLS -O2 $(CFLAGS)
	LDFLAGS := $(LDFLAGS) -lprofiler
else
	CFLAGS := -O2 $(CFLAGS)
endif

SRC = $(wildcard $(SDIR)/*.c)
TSRC = $(wildcard $(TDIR)/*.c)
BTST = $(patsubst $(TDIR)/%.c, $(ODIR)/tests/%, $(TSRC))
DEP = $(wildcard $(IDIR)/*.h)
OBJ = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRC))

.PHONY: clean directories
all: directories $(TARGET)

$(ODIR)/%.o: $(SDIR)/%.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)

tests: directories $(BTST)
	$(shell LD_LIBRARY_PATH=$(ODIR) $(BTST))

$(ODIR)/tests/%: $(TDIR)/%.c $(TARGET) $(DEP)
	$(CC) $(CFLAGS) $< -o $@ -L$(ODIR) -l$(TARGET_NAME)

clean:
	@rm -rf $(ODIR)

directories: $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)/tests
