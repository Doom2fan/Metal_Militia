CC = gdcc-cc
LD = gdcc-ld
ML = gdcc-makelib
COM_FLAGS = --bc-target=ZDoom
CC_FLAGS = $(COM_FLAGS) -DDEBUG

SOURCEDIRECTORY = C_Source

INCDIR = $(SOURCEDIRECTORY)/inc
SRCDIR = $(SOURCEDIRECTORY)/src
OBJDIR = $(SOURCEDIRECTORY)/obj
LIBDIR = $(OBJDIR)/lib

ACSDIR = PK7_Source/acs

all: $(OBJDIR) $(ACSDIR) $(ACSDIR)/METLMILT.bin

cleanall:
	rm -rf $(OBJDIR) $(ACSDIR)

$(OBJDIR):
	@mkdir "$(OBJDIR)"
	@mkdir "$(OBJDIR)/lib"

$(ACSDIR):
	@mkdir "$(ACSDIR)"

## ===========================================
##
## Libs
##
## ===========================================
$(LIBDIR)/libc.ir:
	$(ML) $(COM_FLAGS) -c -o $@ libc

$(LIBDIR)/libGDCC.ir:
	$(ML) $(COM_FLAGS) -c -o $@ libGDCC

## ===========================================
##
## METLMILT.bin
##
## ===========================================
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.ir)

$(OBJDIR)/%.ir: $(SRCDIR)/%.c
	$(CC) $(CC_FLAGS) -i$(INCDIR) -i$(SRCDIR) -c $< -o $@

$(ACSDIR)/METLMILT.bin: $(LIBDIR)/libc.ir $(LIBDIR)/libGDCC.ir $(OBJ)
	$(LD) $(COM_FLAGS) $^ -o $@