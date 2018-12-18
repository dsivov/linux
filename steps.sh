PATH=$PATH:/home/dmdb/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
KERNEL=kernel7
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs
#sudo PATH=$PATH:/home/dmdb/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=/home/dmdb/Rasp/Volumio_my/build/build/ddplayer/root/ modules_install
#sudo cp arch/arm/boot/zImage /home/dmdb/Rasp/Volumio_my/build/build/ddplayer/root/boot/dImage
#sudo cp arch/arm/boot/dts/*.dtb  /home/dmdb/Rasp/Volumio_my/build/build/ddplayer/root/boot/
#sudo cp arch/arm/boot/dts/overlays/*.dtb* /home/dmdb/Rasp/Volumio_my/build/build/ddplayer/root/boot/overlays/
#sudo cp arch/arm/boot/dts/overlays/README /home/dmdb/Rasp/Volumio_my/build/build/ddplayer/root/boot/overlays/
