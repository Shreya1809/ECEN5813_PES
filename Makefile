include sources.mk

TARGET_FILE := project1
#default platform if no platform is defined
PLATFORM := HOST

#LINKER_FILE := platform/MKL25Z128xxx4_flash.ld
LINKER_FILE := link.ld
CPU_KL25Z = cortex-m0plus
ARCH_KL25Z = armv6-m
FPU = fpv4-sp-d16
SPECS_KL25Z = nosys.specs

CFLAGS := -Wall -Werror -g -O0 -std=c99 -MMD -DPROJECT1 -DVERBOSE

INCLUDES := -I inc/common/

INCLUDES_KL25Z := \
	-I inc/CMSIS/ \
	-I inc/KL25Z/

OBJFILES := $(SOURCES_COMMON:.c=.o)

TEST_OBJFILES := $(SOURCES_TEST:.c=.o)
TEST_EXE := run_test
TEST_LIB := -lcmocka

#LDFLAGS=--specs=nano.specs -Wl,--gc-sections,-Map,$(TARGET).map,-Tlink.ld
#
#%.o: %.c
#	$(CC) -c $(ARCHFLAGS) -o $@ $<
#
#$(TARGET).elf: $(OBJ)
#	$(LD) $(ARCHFLAGS) $(LDFLAGS) -o $@ $(OBJ)

#if platform is KL25Z
ifeq ($(PLATFORM),KL25Z)
$(warning KL25Z platform)
  CC := arm-none-eabi-gcc
  OBJCOPY := arm-none-eabi-objcopy
  #OBJFILES += $(SOURCES_KL25Z_C:.c=.o) $(SOURCES_KL25Z_S:.S=.o)
  OBJFILES += $(SOURCES_KL25Z_C:.c=.o)
  INCLUDES += $(INCLUDES_KL25Z)
  ARCHFLAGS := -mthumb -mcpu=cortex-m0plus
  #ARCHFLAGS := -mthumb -mcpu=$(CPU_KL25Z) \
  #		 -march=$(ARCH_KL25Z) -mfloat-abi=soft \
  #		 -mfpu=$(FPU) --specs=$(SPECS_KL25Z)
  CFLAGS += -DKL25Z $(ARCHFLAGS)
  #CFLAGS = -Wall -Werror -g -O0 -std=c99 -MMD -mcpu=$(CPU_KL25Z) \
  #		 -mthumb -march=$(ARCH_KL25Z) -mfloat-abi=soft \
  #		 -mfpu=$(FPU) --specs=$(SPECS_KL25Z) $(INCLUDES_KL25Z)
  #CPPFLAGS = -DKL25Z -DPROJECT1
  #LDFLAGS = -Wl,-Map=$(TARGET_FILE).map -T $(LINKER_FILE)
  LDFLAGS := --specs=nano.specs -Wl,--gc-sections,-Map,$(TARGET).map,-T$(LINKER_FILE)
else ifeq ($(PLATFORM),$(filter $(PLATFORM),HOST BBB))# HOST or BBB
  $(warning HOST or BBB platform)
  ifeq ($(PLATFORM),HOST)
    CC= gcc
  else ifeq ($(PLATFORM),BBB)
    CC= arm-linux-gnueabihf-gcc
  endif
  # Not using HOST flag anywhere yet
  #CFLAGS += -DHOST
  LDFLAGS += -Wl,-Map=$(TARGET_FILE).map
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
# Can enable capturing all matches with **/*.ext in bash with
#  shopt -s globstar
# Fish prefers **.ext, otherwise it misses files in current directory
# Can compromise with some redundancy
	rm -f **/*.o *.o
	rm -f **/*.a *.a
	rm -f **/*.d *.d
	rm -f **/*.elf *.elf
	rm -f **/*.i *.i
	rm -f **/*.map *.map
	rm -f **/*.asm *.asm
	rm -f **/*.srec *.srec

$(TARGET_FILE).srec : $(TARGET_FILE).elf

%.srec: %.elf
	$(OBJCOPY) -O srec $< $@

upload: $(TARGET_FILE).srec
ifeq ($(PLATFORM),KL25Z)
	$(warning KL25Z platform upload)
	echo uploading $^
	cp $^ /media/$(USER)/FRDM-KL25Z
else ifeq ($(PLATFORM),$(filter $(PLATFORM),HOST BBB))# HOST or BBB
	$(warning HOST or BBB platform)
	scp $(TARGET_FILE).elf root@192.168.7.2:/home/debian/bin
	ssh -o LocalCommand="cd /home/debian/bin" root@192.168.7.2
endif


