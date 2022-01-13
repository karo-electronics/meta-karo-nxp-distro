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
        ${@bb.utils.contains('DISTRO_FEATURES','dhcpcd','dhcpcd','',d)} \
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
        nfs-utils \
        ntp \
        ntpdate \
        parted \
        ${@bb.utils.contains('DISTRO_FEATURES','pcie','pciutils','',d)} \
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

# create bootfs image file with every karo-image-* build
do_image_complete[depends] += "karo-image-bootfs:do_image_complete"

# create uuu.auto file for image

UUU_TEMPLATE_PATH_mx8mm = "uuu-templates/mx8mm"
UUU_TEMPLATE_PATH_mx8mn = "uuu-templates/mx8mn"
UUU_TEMPLATE_PATH_mx8mp = "uuu-templates/mx8mp"

addtask do_create_uuu_auto_script after do_image_complete before do_build

python do_create_uuu_auto_script() {
    def do_copyfile (src, destdir):
        import shutil

        bb.note("Copying %s to %s" % (src, destdir))
        shutil.copyfile(src, os.path.join(destdir, os.path.basename(src)))

    bb.note("DEPLOY_DIR_IMAGE='%s'" % d.expand("${DEPLOY_DIR_IMAGE}"))
    bb.note("BPN='%s'" % d.expand("${BPN}"))

    from string import Template

    machine = d.getVar('MACHINE')
    imxboot_target = d.getVar('IMXBOOT_TARGETS')
    image = d.getVar('BPN')

    uuu_template_path = d.expand("${THISDIR}/${UUU_TEMPLATE_PATH}/uuu.auto.template")
    img_dirname = d.expand("${DEPLOY_DIR_IMAGE}/${BPN}")
    uuu_auto_path = os.path.join(img_dirname, "uuu.auto")

    bb.utils.mkdirhier(img_dirname)

    f = open(uuu_template_path, 'r')
    uuu_template_string = f.read()

    try:
        with open(uuu_auto_path, 'w') as uuu_script:
            uuu_template = Template(uuu_template_string)
            uuu_auto = uuu_template.substitute(image=image, machine=machine, imxboot_target=imxboot_target)
            uuu_script.write(uuu_auto)
    except OSError:
        bb.fatal('Unable to open %s' % (uuu_auto_path))

    do_copyfile("%s/imx-boot-%s.bin-mfg-%s" % \
        (d.getVar('DEPLOY_DIR_IMAGE'), machine, imxboot_target), img_dirname)
    do_copyfile("%s/imx-boot-%s.bin-default-%s" % \
        (d.getVar('DEPLOY_DIR_IMAGE'), machine, imxboot_target), img_dirname)
    do_copyfile("%s/karo-image-bootfs-%s.ext4" % \
        (d.getVar('DEPLOY_DIR_IMAGE'), machine), img_dirname)
    do_copyfile("%s/%s-%s.ext4" % \
        (d.getVar('DEPLOY_DIR_IMAGE'), image, machine), img_dirname)
}

addtask do_clean_uuu_dir before do_clean

python do_clean_uuu_dir() {
    import glob

    for f in glob.glob(d.expand("${DEPLOY_DIR_IMAGE}/${BPN}/*")):
        bb.note("Removing %s" % f)
        os.remove(f)

    os.rmdir(d.expand("${DEPLOY_DIR_IMAGE}/${BPN}"))
}
