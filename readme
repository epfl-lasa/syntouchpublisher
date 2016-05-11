Installation
============

Install Cheetah USB rules:
--------------------------

In order to be able to read the Biotac data via the Cheetah SPI-USB board you first have to copy the udev rules:

1. Download the Cheetah SPI board drivers tp-usb-drivers-v2.10.zip from http://www.totalphase.com/products/cheetah_spi/ (Or find it in the driver folder)

2. Unzip the folder unzip tp-usb-drivers-v2.10.zip

3. Copy the udev rules sudo cp tp-usb-drivers-v2.10/linux/99-totalphase.rules /etc/udev/rules.d/

4. Go to /etc/udev/rules.d/ and change the permission chmode 644 99-totalphase.rules

Install the cheetah lib
-----------------------

1. Download the Appropriate API for your machine from http://www.totalphase.com/products/cheetah-api/ (Or find it in the driver folder)

2. Copy the library file (cheetah.dll or cheetah.so) from the downloaded zip. Paste the file into the Syntouch application folder (the bt_cheetah folder with biotac.h, biotac.c, etc.
files).

Test the bt_cheetah example
---------------------------
1. Go to /driver/bt_cheetah/bt_cheetah and run > ./bin/example
2. If everything is ok, you should see BioTac is found.


Install syntouchpublisher package:
----------------------------------
1. Copy the library file cheetah.so from downloaded zip to catkin_kin/devel/lib/ 
2. Catkin_make the syntouchpublisher package

Reference:
--------------
[link](http://www.syntouchllc.com/Products/BioTac/_media/BioTac_QuickStart_Guide.pdf)
