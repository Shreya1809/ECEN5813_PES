#!/bin/sh
scripts/pem_start.sh &
arm-none-eabi-gdb -tui -x scripts/commands_to_flash_and_debug

