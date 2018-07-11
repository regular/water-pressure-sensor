ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino
AVR_TOOLS_DIR = /usr
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/cores/arduino
BOARDS_TXT = /usr/share/arduino/hardware/archlinux-arduino/avr/boards.txt
ARDUINO_VAR_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/variants
BOOTLOADER_PARENT = /usr/share/arduino/hardware/archlinux-arduino/avr/bootloaders
ARDUINO_PLATFORM_LIB_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/libraries

BOARD_TAG    = uno
BOARD_SUB		 = atmega328
ARDUINO_LIBS = EEPROM jeelib-master
MONITOR_PORT  = /dev/ttyUSB0
MONITOR_BAUDRATE = 57600
AVRDUDE_CONF = /etc/avrdude.conf

include /usr/share/arduino/Arduino.mk
