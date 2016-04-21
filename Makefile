FLASH_PATH = ./FlashPhoto
MIA_PATH = ./Mia
PHOTO_PATH = ./libphoto

all: build

build:
	cd $(PHOTO_PATH); make
	cd $(FLASH_PATH); make

clean:
	cd $(PHOTO_PATH); make clean
	cd $(FLASH_PATH); make clean
