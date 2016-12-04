# ---------------------------------------------------------------------------
# Имя проекта

NAME	= calk

# Настройки компилятора и линкера

CC      = sdcc
CFLAGS  = -I./include_sdcc -c --stack-auto
LFLAGS  = --code-loc 0x2100 --xram-loc 0x6000 --stack-auto --stack-loc 0x80 

# Настройки системы автоинкремента версии сборки

PROJECT  = $(shell type PROJECT)
VERSION  = $(shell type VERSION)
BUILD    = $(shell type BUILD)
TYPE     = $(shell type TYPE)

PROJNAME = ${PROJECT}-${VERSION}-${BUILD}-${TYPE}
TARBALL  = ${PROJNAME}.tar

# Настройки M3P

M3P		 = m3p
COMPORT	 = com3
COMLOG	 = $(COMPORT)_log.txt
BAUD	 = 9600	

# Каталоги с исходными текстами

SRC_DIR = SRC
UTILS_DIR = ./UTILS
export Path:=$(UTILS_DIR);$(Path)
# ---------------------------------------------------------------------------

all: simple

clean:
	del $(NAME).hex
	del $(NAME).bin
	del $(NAME).map
	del $(NAME).mem
	del $(NAME).lnk
	del pm3p_*.txt
	del com?_log.txt
	del $(TARBALL).gz
	del $(SRC_DIR)\*.asm
	del $(SRC_DIR)\*.rel
	del $(SRC_DIR)\*.rst
	del $(SRC_DIR)\*.sym
	del $(SRC_DIR)\*.lst 

load:
	$(M3P) lfile load.m3p


dist:
	tar -cvf $(TARBALL) --exclude=*.tar .
	gzip $(TARBALL)

term:
	$(M3P) echo $(COMLOG) $(BAUD)  openchannel $(COMPORT) +echo 0 term -echo bye


SIMPLE_SRC = \
$(SRC_DIR)/main.c \
$(SRC_DIR)/calc.c \
$(SRC_DIR)/fixedpoint.c \
$(SRC_DIR)/fixed_point_test.c \
$(SRC_DIR)/mem_ops.c \
$(SRC_DIR)/kb.c \
$(SRC_DIR)/lcd.c \
$(SRC_DIR)/max.c \
$(SRC_DIR)/din.c \
$(SRC_DIR)/sio.c\
$(SRC_DIR)/timer.c

SIMPLE_OBJ = $(SIMPLE_SRC:.c=.rel)

simple : $(SIMPLE_OBJ) makefile
	$(CC) $(SIMPLE_OBJ) -o $(NAME).hex $(LFLAGS)
	$(M3P) hb166 $(NAME).hex $(NAME).bin bye


$(SIMPLE_OBJ) : %.rel : %.c makefile
	$(CC) -c $(CFLAGS) $< -o $@  
