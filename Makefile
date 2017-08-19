# update:   19.08.2017
# Author:   Adam Allaf
#

CC = msp430-elf-gcc
DEBUG = mspdebug

MCU = msp430f5529

OBJDIR = obj
BINDIR = bin

#DEBUGINFO = -g
#ASM = -D_GNU_ASSEMBLER_

OPT = -O2


CFLAGS = $(OPT) $(ASM) -Wall $(DEBUGINFO) -mmcu=$(MCU)

BIN = $(MCU)_out.elf
OBJS = main.o

TARGET = msp430-project

all: $(TARGET)

msp430-project: dirs $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(BIN) $(addprefix $(OBJDIR)/,$(OBJS))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

dirs:
	+@[ -d ./$(OBJDIR) ] || mkdir $(OBJDIR)
	+@[ -d ./$(BINDIR) ] || mkdir $(BINDIR)

install: $(TARGET)
	$(DEBUG) tilib "prog $(BINDIR)/$(BIN)"

clean:
	@$(RM) $(BINDIR)/* $(OBJDIR)/*
	@rm -r $(BINDIR) $(OBJDIR)