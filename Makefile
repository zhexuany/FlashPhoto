FLASH_PATH = ./FlashPhoto
MIA_PATH = ./Mia
PHOTO_PATH = ./libphoto
TEST_PATH = ./test
all: build

build:
	cd $(PHOTO_PATH); make
	cd $(FLASH_PATH); make
	cd $(MIA_PATH); make
	cd $(TEST_PATH); make

clean:
	cd $(PHOTO_PATH); make clean
	cd  $(TEST_PATH); make clean
	cd $(FLASH_PATH); make clean
	cd $(MIA_PATH); make clean
