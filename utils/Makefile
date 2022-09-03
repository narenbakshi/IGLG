TARGET = probe_out
TARGET2 = analyze_out
TARGET3 = responses_out



CC = gcc
CFLAGS = -lnanomsg -I/usr/include/libxml2 -lxml2 -lsqlite3 -std=c99 -lczmq -lzmq -lpaho-mqtt3a -w

OUTDIR = ./bin
DATADIR = ./data
SUBDIR = ./middleware/nanoMsg ./middleware/pahomqtt ./middleware/zeroMq utils factory
DIR_OBJ = ./obj


INCS = $(wildcard probe.h $(foreach fd, $(SUBDIR), $(fd)/*.h))
SRCS = $(wildcard probe.c $(foreach fd, $(SUBDIR), $(fd)/*.c))

INCS2 = $(wildcard analyze.h $(foreach fd, $(SUBDIR), $(fd)/*.h))
SRCS2 = $(wildcard analyze.c $(foreach fd, $(SUBDIR), $(fd)/*.c))

INCS3 = $(wildcard responses.h $(foreach fd, $(SUBDIR), $(fd)/*.h))
SRCS3 = $(wildcard responses.c $(foreach fd, $(SUBDIR), $(fd)/*.c))



NODIR_SRC = $(notdir $(SRCS))
OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:c=o)) # obj/xxx.o obj/folder/xxx .o

OBJS2 = $(addprefix $(DIR_OBJ)/, $(SRCS2:c=o)) # obj/xxx.o obj/folder/xxx .o
OBJS3 = $(addprefix $(DIR_OBJ)/, $(SRCS3:c=o)) # obj/xxx.o obj/folder/xxx .o

 
LIBS = -lnanomsg -lxml2 -lsqlite3 -std=c99 -lczmq -lzmq -lpaho-mqtt3a
LIB_DIRS = -I/usr/include/libxml2





PHONY := $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(OUTDIR)/$@ $(OBJS) $(LIB_DIRS) $(LIBS)

$(DIR_OBJ)/%.o: %.c $(INCS)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $< $(INC_DIRS)



PHONY := $(TARGET2)
$(TARGET2): $(OBJS2)
	$(CC) -o $(OUTDIR)/$@ $(OBJS2) $(LIB_DIRS) $(LIBS)

$(DIR_OBJ)/%.o: %.c $(INCS2)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $< $(INC_DIRS)



PHONY := $(TARGET3)
$(TARGET3): $(OBJS3)
	$(CC) -o $(OUTDIR)/$@ $(OBJS3) $(LIB_DIRS) $(LIBS)

$(DIR_OBJ)/%.o: %.c $(INCS3)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $< $(INC_DIRS)

PHONY := all
all: $(TARGET) $(TARGET2) $(TARGET3)


PHONY += clean
clean:
	rm -rf $(OUTDIR)/* $(DATADIR)/* $(DIR_OBJ)/*

PHONY += echoes
echoes:
	@echo "INC files: $(INCS)"
	@echo "SRC files: $(SRCS)"
	@echo "OBJ files: $(OBJS)"
	@echo "LIB files: $(LIBS)"
	@echo "INC DIR: $(INC_DIRS)"
	@echo "LIB DIR: $(LIB_DIRS)"

.PHONY = $(PHONY)
