#/bin/sh

arm-none-eabi-gcc \
    -mcpu=cortex-m0plus \
    -mthumb \
    -O0 \
    -fmessage-length=0 \
    -fsigned-char \
    -ffunction-sections \
    -fdata-sections \
    -Wall  \
    -g \
    -T /home/miles/projects/pes/kinetis/linux_sdk1.3/KSDK_1.3.0/platform/devices/MKL25Z4/linker/gcc/MKL25Z128xxx4_flash.ld \
    -Xlinker \
    --gc-sections \
    -Wl,-Map,"bubble_level_tpm_frdmkl25z.map" \
    -Xlinker \
    -z  \
    -Xlinker muldefs   \
    --specs=nano.specs          \
    -Wall  \
    -fno-common  \
    -ffunction-sections  \
    -fdata-sections  \
    -ffreestanding  \
    -fno-builtin  \
    -mapcs  \
    -Xlinker \
    -static  \
    -Xlinker \
    --defsym=__stack_size__=0x0400  \
    -Xlinker \
    --defsym=__heap_size__=0x0200 \
    -o "bubble_level_tpm_frdmkl25z.elf" \
    -Xlinker \
    --start-group  \
    ./utilities/fsl_debug_console.o \
    ./utilities/fsl_misc_utilities.o \
    ./utilities/print_scan.o  \
    ./startup/startup.o \
    ./startup/startup_MKL25Z4.o \
    ./startup/system_MKL25Z4.o  \
    ./source/accel.o \
    ./source/fsl_i2c_irq.o \
    ./source/fxos_api.o \
    ./source/main.o \
    ./source/mma8451_api.o  \
    ./board/board.o \
    ./board/gpio_pins.o \
    ./board/hardware_init.o \
    ./board/pin_mux.o  \
    /home/miles/projects/pes/kinetis/linux_sdk1.3/KSDK_1.3.0/lib/ksdk_platform_lib/kds/KL25Z4/debug/libksdk_platform.a \
    -lm \
    -lg \
    -lgcc \
    -lnosys \
    -Xlinker \
    --end-group

