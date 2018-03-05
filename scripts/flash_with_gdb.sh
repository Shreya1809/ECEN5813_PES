#!/bin/sh
scripts/pem_start.sh &
arm-none-eabi-gdb -x scripts/commands_to_flash_only

