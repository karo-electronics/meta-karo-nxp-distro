LICENSE = "MIT"

inherit core-image features_check rootfs-postprocess relative_symlinks

REQUIRED_DISTRO_FEATURES ??= ""

ROOTFS_POSTPROCESS_COMMAND_remove = " \
        rootfs_update_timestamp; \
        ${bb.utils.contains('DISTRO_FEATURES','read-only-rootfs','empty_var_volatile;','',d)} \
"

IMAGE_FEATURES_append = " tools-debug"

IMAGE_INSTALL_append = " \
        ${CORE_IMAGE_EXTRA_INSTALL} \
        alsa-utils-aplay \
        alsa-utils-amixer \
        alsa-utils-alsamixer \
        bash \
        canutils \
        coreutils \
        curl \
        dhcpcd \
        dosfstools \
        e2fsprogs \
        e2fsprogs-resize2fs \
        file \
        gdbserver \
        git \
        kmod \
        i2c-tools \
        ldd \
        less \
        libgpiod \
        libgpiod-tools \
        libstdc++ \
        ${@bb.utils.contains('DISTRO_FEATURES','wifi','linux-firmware-pcie8997','',d)} \
        lsof \
        mmc-utils \
        ncurses \
        ntp \
        ntpdate \
        parted \
        pciutils \
        rsync \
        strace \
        tcp-wrappers \
        tzdata \
        util-linux-fsck \
        util-linux-mkfs \
        util-linux-setterm \
        ${@bb.utils.contains('DISTRO_FEATURES','imx219','v4l-utils','',d)} \
        ${@bb.utils.contains('DISTRO_FEATURES','wifi','wpa-supplicant','',d)} \
"

CORE_IMAGE_EXTRA_INSTALL += "kernel-modules"
DEPENDS_append_mx6 = " u-boot-karo"
DEPENDS_append_mx8 = " imx-boot"

PREFERRED_PROVIDER_fdisk = "util-linux"

IMAGE_ROOTFS_SIZE ?= "${@bb.utils.contains('MACHINE_FEATURES',"nand",64*1024,128*1024,d)}"
IMAGE_ROOTFS_ALIGNMENT ?= "${@bb.utils.contains('MACHINE_FEATURES',"nand",128*1024,1024,d)}"
IMAGE_ROOTFS_EXTRA_SPACE ?= "${@bb.utils.contains('MACHINE_FEATURES',"nand",2*128*1024,0,d)}"

IMAGE_FSTYPES_remove = "tar.gz"
IMAGE_FSTYPES += "${@bb.utils.contains('MACHINE_FEATURES',"nand","ubi","",d)}"
IMAGE_FSTYPES += "${@bb.utils.contains('MACHINE_FEATURES',"emmc","ext4","",d)}"

MKUBIFS_ARGS ?= "-F -x zlib -m 2048 -e 126976 -c 256"
UBINIZE_ARGS ?= "-m 2048 -s 2048 -p 128KiB"
UBI_VOLNAME = "rootfs"
