TARGET = PSP-OSS
OBJS = main.o desktop.o iniparser.o startup.o Ram.o cursor.o unrarlib.o actions.o functions.o keyboard.o windows.o filebrowser.o startmenu.o irda.o usb.o wlan.o settings.o customskin.o \
	lib/OSSgraphics.o lib/OSSframebuffer.o codec/audio.o codec/mp3player.o codec/oggplayer.o codec/mikmodplayer.o \
	 lib/nlh.o lib/loadutil.o lib/stubs.o \



INCDIR = 
CFLAGS = -O3 -G0 -Wall -fno-strict-aliasing $(EXTRA_CFLAGS) $(shell freetype-config --cflags)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS) -c

LIBDIR =
LIBS = -lpspgu -lpng -ljpeg -lz -lpspumd -lpsppower -lpspusb -lpspusbstor -lpspaudiolib -lpspaudio \
	-lpsprtc -lpsputility  -lmad -lvorbisidec -lpspgum -lmikmod -lpspwlan \
	-lmmio $(shell freetype-config --libs) \
	-lpspdebug -lpsphprm_driver -lpsputility \
	-lpspsdk -lpspnet_apctl \
	-lm 

LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSP-OSS

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

oss: all kxploit
	cp -R PSP-OSS/EBOOT.PBP SYSTEM/PSP-OSS.elf