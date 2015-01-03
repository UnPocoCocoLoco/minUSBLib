CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld -v
CP      = arm-none-eabi-objcopy
OD      = arm-none-eabi-objdump
  
CFLAGS  =  -I./ -c -fno-common -O1 -g -mcpu=cortex-m3 -mthumb
LFLAGS  = -Tstm32.ld -nostartfiles
CPFLAGS = -O ihex
ODFLAGS = -S

NAME = main
SCRIPT = stm32.ld
OBJ = core_cm3.o init.o stm32f10x_usb.o usb_desc.o usb_com.o usb_aux.o
INC = core_cm3.h stm32f10x.h usb_aux.h stm32f10x_usb.h macros.h

all: test

clean:
	-rm $(NAME).lst $(NAME).o $(NAME).elf $(NAME).lst $(NAME).hex

test: $(NAME).elf
	@ echo "....copying"
	$(CP) $(CPFLAGS) $(NAME).elf $(NAME).hex
	$(OD) $(ODFLAGS) $(NAME).elf > $(NAME).lst

$(NAME).elf: $(NAME).o $(SCRIPT) $(OBJ) $(INC)
	@ echo "...linking"
	$(LD) $(LFLAGS) -o $(NAME).elf $(NAME).o $(OBJ)
	
%.o: %.c
	@ echo "..compiling"
	$(CC) $(CFLAGS) ./$<
