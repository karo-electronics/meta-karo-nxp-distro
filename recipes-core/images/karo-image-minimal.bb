SUMMARY = "A minimal Linux system without graphics support."

require karo-image.inc 

inherit rootfs-postprocess

IMAGE_LINGUAS = ""
IMAGE_FEATURES_remove = "tools-debug"

IMAGE_ROOTFS_MAXSIZE ?= "${@bb.utils.contains('MACHINE_FEATURES',"nand","65536","",d)}"

python extend_recipe_sysroot_append() {
    bb.note("IMAGE_FEATURES[read-only-rootfs]='%s'" % bb.utils.filter('IMAGE_FEATURES','read-only-rootfs',d))
    if bb.utils.contains('IMAGE_FEATURES','read-only-rootfs',False,True,d):
        bb.error("IMAGE_FEATURES=%s" % d.getVar('IMAGE_FEATURES'))
        raise_sanity_error("IMAGE_FEATURES is missing the 'read-only-rootfs' feature", d)

    if d.getVar('DISTRO') != 'karo-minimal':
        raise_sanity_error("cannot build karo-image-minimal with '%s' DISTRO" % d.getVar('DISTRO'), d)
}
