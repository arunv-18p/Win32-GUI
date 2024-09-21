ROOT_DIR := $(CURDIR)

BUILD_DIR := $(ROOT_DIR)\\build

WIN32_GUI_FILE := $(BUILD_DIR)\\window.exe

WIN32_GUI_SOURCES := \
	$(ROOT_DIR)\\window.cpp \
	$(ROOT_DIR)\\utils\\gdi_utils.cpp \
	$(ROOT_DIR)\\utils\\win32_utils.cpp

WIN32_GUI_INCLUDES := \
	-I$(ROOT_DIR)\\include

WIN32_GUI_LIBS := \
	-lgdiplus \
	-luxtheme \
	-ldwmapi

.SILENT:

all: info clean win32_gui
	@echo status: Done

info:
	@echo  -----------------
	@echo ^|    Win32-GUI   ^|
	@echo ------------------

win32_gui:
	@echo status: Building Win32-GUI.exe
	@g++ -w $(WIN32_GUI_SOURCES) $(WIN32_GUI_INCLUDES) $(WIN32_GUI_LIBS) -o $(WIN32_GUI_FILE)
	@echo status: Executing Win32-GUI.exe
	"$(WIN32_GUI_FILE)"

clean:
	@echo status: Cleaning...
	del "$(WIN32_GUI_FILE)" 2>nul

.PHONY: all info win32_gui