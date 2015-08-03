# Modules directory location from Makefile
MODULE_DIR = ./modules

# Imported source files and paths from modules
include $(MODULE_DIR)/usb/usb.mk
include $(MODULE_DIR)/version_information/version_information.mk

# List of all the module related files.
MODULES_SRC = $(USB_SRCS) \
              $(VERSIONINFO_SRCS)

# Required include directories
MODULES_INC = $(USB_INC) \
              $(VERSIONINFO_INC)
