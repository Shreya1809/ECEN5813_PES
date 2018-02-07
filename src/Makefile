include sources.mk

#variables for lib
TARGET_FILE = project1
PRINT = KL25Z
PLATFORM = HOST #default platform if no platform is defined
LINKER_FILE = ../platform/MKL25Z128xxx4_flash.ld
CPU_KL25Z = cortex-m0plus
ARCH_KL25Z = armv6-m		
FPU = fpv4-sp-d16
SPECS_KL25Z = nosys.specs 

INCLUDES := -I ../inc/Common/

INCLUDES_KL25Z = -I ../inc/Common/ \
	     -I ../inc/CMSIS/ \
	     -I ../inc/KL25Z/


#default platform host
ifeq ($(PLATFORM), HOST)
CC= gcc
CFLAGS += -Wall -Werror -g -O0 -std=c99 $(INCLUDES)
CPPFLAGS += -DHOST -DPROJECT1 -DVERBOSE
LDFLAGS += -Wl,-Map=$(TARGET_FILE).map
OBJFILES += $(SOURCES_COMMOM:.c=.o)

#if platform is Beaglebone
else ifeq ($(PLATFORM),BBB)
CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -Werror -g -O0 -std=c99 $(INCLUDES)
CPPFLAGS = -DBBB -DPROJECT1 -D VERBOSE
LDFLAGS = -Wl,-Map=$(TARGET_FILE).map
OBJFILES = $(SOURCES:.c=.o)

#if platform is KL25Z
else ifeq ($(PLATFORM),KL25Z)
CC = arm-none-eabihf-gcc
CFLAGS = -Wall -Werror -g -O0 -std=c99 -mcpu=$(CPU_KL25Z) \
		 -mthumb -march=$(ARCH_KL25Z) -mfloat-abi=soft \
		 -mfpu=$(FPU) --specs=$(SPECS_KL25Z) $(INCLUDES_KL25Z)
CPPFLAGS = -DKL25Z -DPROJECT1 -D$(PRINT)
LDFLAGS = -Wl,-Map=$(TARGET_FILE).map -T $(LINKER_FILE)
OBJFILES = $(SOURCES_KL25Z:.c=.o) $(SOURCES_KL25Z_S:.S=.o)

endif

%.o : %.c 
	@echo "Building $? file from $@\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

%.asm : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -S $< -o $@

%.i : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -E $< -o $@

build : $(OBJFILES)
	@echo "Building $< file and linking it\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJFILES) -o $(TARGET_FILE).elf

clean : 
	rm -f *.o
	rm -f project1.elf
	rm -f *.i
	rm -f *.map
	rm -f *.asm

upload:
	scp $(TARGET_FILE).elf root@192.168.7.2:/home/debian/bin
	ssh root@192.168.7.2
	cd /home/debian/bin
