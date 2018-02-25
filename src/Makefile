include sources.mk

#variables for lib
TARGET_FILE = project1
PRINT = KL25Z
PLATFORM=HOST#default platform if no platform is defined
LINKER_FILE = ../platform/MKL25Z128xxx4_flash.ld
CPU_KL25Z = cortex-m0plus
ARCH_KL25Z = armv6-m
FPU = fpv4-sp-d16
SPECS_KL25Z = nosys.specs

INCLUDES := -I ../inc/common/

INCLUDES_KL25Z = -I ../inc/common/ \
	     -I ../inc/CMSIS/ \
	     -I ../inc/KL25Z/

TEST_OBJFILES := $(SOURCES_TEST:.c=.o)
TEST_EXE := run_test
TEST_LIB := -lcmocka

#if platform is KL25Z
ifeq ($(PLATFORM),KL25Z)
$(warning KL25Z platform)
  CC = arm-none-eabi-gcc
  CFLAGS = -Wall -Werror -g -O0 -std=c99 -MMD -mcpu=$(CPU_KL25Z) \
  		 -mthumb -march=$(ARCH_KL25Z) -mfloat-abi=soft \
  		 -mfpu=$(FPU) --specs=$(SPECS_KL25Z) $(INCLUDES_KL25Z)
  CPPFLAGS = -DKL25Z -DPROJECT1 -D$(PRINT)
  LDFLAGS = -Wl,-Map=$(TARGET_FILE).map -T $(LINKER_FILE)
  OBJFILES = $(SOURCES_COMMON:.c=.o) $(SOURCES_KL25Z_C:.c=.o) $(SOURCES_KL25Z_S:.S=.o)
else ifeq ($(PLATFORM),$(filter $(PLATFORM),HOST BBB))# HOST or BBB
  $(warning HOST or BBB platform)
  ifeq ($(PLATFORM),HOST)
    CC= gcc
  else ifeq ($(PLATFORM),BBB)
    CC= arm-linux-gnueabihf-gcc
  endif
  CFLAGS += -Wall -Werror -g -O0 -std=c99 -MMD $(INCLUDES)
  CPPFLAGS += -DHOST -DPROJECT1 -DVERBOSE
  LDFLAGS += -Wl,-Map=$(TARGET_FILE).map
  OBJFILES += $(SOURCES_COMMON:.c=.o)
endif

%.o : %.c
	@echo "Building $@ object file from $?\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $? -o $@

%.asm : %.c
	@echo "Building $@ assembly file from $?\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) -S $< -o $@

%.i : %.c
	@echo "Building $@ preprocessed file from $?\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) -E $< -o $@

$(TARGET_FILE).elf : $(OBJFILES) $(SOURCES_MAIN:.c=.o)
	@echo "Linking together $^\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) $^ -o $@

.PHONY: build
build : $(TARGET_FILE).elf

.PHONY: test
test : $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE) : $(OBJFILES) $(TEST_OBJFILES)
	@echo "Creating test $@ by linking together $^\n"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) $^ $(TEST_LIB) -o $@

.PHONY: library
library : $(TARGET_FILE).a

$(TARGET_FILE).a : $(OBJFILES) $(SOURCES_MAIN:.c=.o)
	@echo "creating static library $@ from $^\n"
	ar rcs $@ $^

.PHONY: compile-all
compile-all: $(OBJFILES)

clean :
	rm -f *.o
	rm -f *.a
	rm -f *.d
	rm -f *.elf
	rm -f *.i
	rm -f *.map
	rm -f *.asm

upload:
	scp $(TARGET_FILE).elf root@192.168.7.2:/home/debian/bin
	ssh -o LocalCommand="cd /home/debian/bin" root@192.168.7.2
