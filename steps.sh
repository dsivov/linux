PATH=$PATH:/home/dmdb/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
KERNEL=kernel7
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs
sudo PATH=$PATH:/home/dmdb/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=/home/dmdb/DDPLAYER/KernelBuild modules_install
#sudo cp arch/arm/boot/zImage /home/dmdb/DDPLAYER/KernelBuild/root/boot/
#sudo cp arch/arm/boot/dts/*.dtb  /home/dmdb/DDPLAYER/KernelBuild/root/boot/
#sudo cp arch/arm/boot/dts/overlays/*.dtb* /home/dmdb/DDPLAYER/KernelBuild/root/boot/overlays/
#sudo cp arch/arm/boot/dts/overlays/README /home/dmdb/DDPLAYER/KernelBuild/root/boot/overlays/
sudo cp arch/arm/boot/dts/overlays/ddplayer-dac.dtbo ../Drivers/ddplayer-drivers/boot/overlays/ddplayer-dac.dtbo 
sudo cp ../KernelBuild/lib/modules/4.14.88-v7+/kernel/sound/soc/bcm/snd-soc-ddplayer-dac.ko ../Drivers/ddplayer-drivers/lib/modules/4.14.71+/kernel/sound/soc/bcm/
sudo cp ../KernelBuild/lib/modules/4.14.88-v7+/kernel/sound/soc/bcm/snd-soc-ddplayer-dac.ko ../Drivers/ddplayer-drivers/lib/modules/4.14.71-v7+/kernel/sound/soc/bcm/ 
cd ../Drivers/
sudo chown -R root:root *
sudo tar -zcvf ddplayer-driver.tar.gz *
git add ddplayer-driver.tar.gz
git commit -m "new version"
git push
