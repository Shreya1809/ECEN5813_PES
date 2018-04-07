include sources.mk

#default platform if no platform is defined
PLATFORM := HOST

# Common settings
TARGET_FILE := project
# Kinetis likes gnu99 instead of c99
CFLAGS := -Wall -Werror -g -O0 -std=gnu99 -MMD -DPROJECT3 -DVERBOSE
# Need to follow this recommendation for portable specifier widths
# https://stackoverflow.com/questions/1403074/printf-with-sizeof-on-32-vs-64-platforms-how-do-i-handle-format-code-in-platfor
# But just disabling format warning/error as workaround for now
CFLAGS += -Wno-format
INCLUDES := -I inc/common/
OBJFILES := $(SOURCES_COMMON:.c=.o)
LDFLAGS := -Wl,-no-wchar-size-warning,-Map=$(TARGET_FILE).map

# Test Settings
TEST_OBJFILES := $(SOURCES_TEST:.c=.o)
TEST_EXE := run_test
TEST_LIB := -lcmocka

# Only using variables if value used more than once in makefile

# Old original KL25Z settings
# Some settings different than kinetis, so not using these
#CPU_KL25Z = cortex-m0plus
#ARCH_KL25Z = armv6-m
#FPU = fpv4-sp-d16
#SPECS_KL25Z = nosys.specs

#if platform is KL25Z
ifeq ($(PLATFORM),KL25Z)
$(warning KL25Z platform)
  CC := arm-none-eabi-gcc
  OBJCOPY := arm-none-eabi-objcopy
  OBJFILES += $(SOURCES_KL25Z_C:.c=.o) $(SOURCES_KL25Z_S:.S=.o)
  INCLUDES += \
	-I inc/CMSIS/ \
	-I inc/KL25Z/
# Probably don't need all of these, but not removing yet, since produces different .elf
  CFLAGS += \
    -DCPU_MKL25Z128VLK4 \
	-DKL25Z \
	-mcpu=cortex-m0plus \
	-mthumb \
	-O0 \
	-fmessage-length=0 \
	-fsigned-char \
	-ffunction-sections \
	-fdata-sections \
	-fno-common \
	-ffreestanding \
	-fno-builtin \
	-mapcs
  LDFLAGS += \
	-T platform/MKL25Z128xxx4_flash.ld \
    --specs=nano.specs \
    -Xlinker --gc-sections \
    -Xlinker --defsym=__stack_size__=0x0400 \
    -Xlinker --defsym=__heap_size__=0x0200
# Note -lg points to libg.a which is the debugging version of libc.a from arm.
# -lg and -nosys both needed together to find _exit symbol
  LDLIBS := -lg -lnosys
else ifeq ($(PLATFORM),$(filter $(PLATFORM),HOST BBB))
  $(warning HOST or BBB platform)
  ifeq ($(PLATFORM),HOST)
    CC := gcc
  else ifeq ($(PLATFORM),BBB)
    CC := arm-linux-gnueabihf-gcc
  endif
endif

%.o : %.c
	@echo "Building $@ object file from $^\n"
	$(CC) $(CFLAGS) $(INCLUDES) -MF$(^:.c=.d) -c $^ -o $@

# This rule is not required, since automatic processing of .S file
# produces a (sometimes)identical .elf
# Although now we're seeing some differences with latest $(CFLAGS)
%.o : %.S
	@echo "Building $@ object file from $^\n"
	$(CC) $(CFLAGS) -MF$(^:.S=.d) -c $^ -o $@

%.asm : %.c
	@echo "Building $@ assembly file from $^\n"
	$(CC) $(CFLAGS) -S $< -o $@

%.i : %.c
	@echo "Building $@ preprocessed file from $^\n"
	$(CC) $(CFLAGS) -E $< -o $@

$(TARGET_FILE).elf : $(OBJFILES) $(SOURCES_MAIN:.c=.o)
	@echo "Linking together $^\n"
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $^ $(LDLIBS) -o $@

.PHONY: build
build : $(TARGET_FILE).elf

.PHONY: test
test : $(TEST_EXE)
	./$(TEST_EXE)

# Todo - can probably remove includes from linker command
$(TEST_EXE) : $(OBJFILES) $(TEST_OBJFILES)
	@echo "Creating test $@ by linking together $^\n"
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $^ $(TEST_LIB) -o $@

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

ifeq ($(PLATFORM),KL25Z)
upload: $(TARGET_FILE).srec
	$(warning KL25Z platform upload)
	echo uploading $^
	cp $^ /media/$(USER)/FRDM-KL25Z
else ifeq ($(PLATFORM),$(filter $(PLATFORM),HOST BBB))# HOST or BBB
upload: $(TARGET_FILE).elf
	$(warning HOST or BBB platform)
	# If this doesn't work, try the following command
	# sudo dhclient enx544a16e6786e
	# https://groups.google.com/forum/#!topic/beagleboard/a6PiVmnL_OU

	# Having trouble CD-ing to directory after SSH connection,
	# so just copying to /root instead of /home/debian/bin
	scp $(TARGET_FILE).elf root@192.168.7.2:/root
	ssh -o LocalCommand="cd /home/debian/bin" root@192.168.7.2
endif

