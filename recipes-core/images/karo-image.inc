LICENSE = "MIT"

inherit core-image distro_features_check

DISTROOVERRIDES =. "karo-minimal:karo-base:karo-x11:karo-wayland"

IMAGE_FEATURES += "tools-debug"

IMAGE_INSTALL = "\
              packagegroup-core-boot \
              ${CORE_IMAGE_EXTRA_INSTALL} \
              alsa-utils-aplay \
              alsa-utils-amixer \
              alsa-utils-alsamixer \
              bash \
              canutils \
              coreutils \
              dhcpcd \
              dosfstools \
              e2fsprogs \
              file \
              gdbserver \
              kmod \
              i2c-tools \
              ldd \
	      less \
              libstdc++ \
              lsof \
              mmc-utils \
	      ncurses \
              ntp \
              ntpdate \
              parted \
              rsync \
              strace \
              tzdata \
              util-linux-fsck \
              util-linux-mkfs \
              util-linux-setterm \
"

CORE_IMAGE_EXTRA_INSTALL += "kernel-modules"
CORE_IMAGE_EXTRA_INSTALL_mx6 += "u-boot-karo"
#CORE_IMAGE_EXTRA_INSTALL_mx8 += "imx-boot"

PREFERRED_PROVIDER_fdisk = "util-linux"
PREFERRED_PROVIDER_virtual/bootloader = "u-boot-karo"
PREFERRED_PROVIDER_virtual/kernel = "linux-karo"

IMAGE_ROOTFS_SIZE ?= "${@bb.utils.contains('FLASHTYPE',"nand",32*1024,128*1024,d)}"
IMAGE_ROOTFS_ALIGNMENT ?= "${@bb.utils.contains('FLASHTYPE',"nand",128*1024,1024,d)}"
IMAGE_ROOTFS_EXTRA_SPACE ?= "${@bb.utils.contains('FLASHTYPE',"nand",2*128*1024,0,d)}"

IMAGE_FSTYPES_remove = "tar.gz"
IMAGE_FSTYPES += "tar.bz2"
IMAGE_FSTYPES += "${@bb.utils.contains('FLASHTYPE',"nand","ubi","",d)}"
IMAGE_FSTYPES += "${@bb.utils.contains('FLASHTYPE',"emmc","ext4","",d)}"

MKUBIFS_ARGS ?= "-F -x zlib -m 2048 -e 126976 -c 256"
UBINIZE_ARGS ?= "-m 2048 -s 2048 -p 128KiB"
UBI_VOLNAME = "rootfs"

ROOT_HOME ?= "/root"
