IMAGE_BASENAME = "karo-image-x11"
SUMMARY = "A very basic X11 image with a terminal"

IMAGE_FEATURES += " \
	       splash \
	       package-management \
	       x11-base \
"

LICENSE = "MIT"

inherit core-image distro_features_check

REQUIRED_DISTRO_FEATURES = "x11"

IMAGE_FSTYPES += "${@bb.utils.contains('FLASHTYPE',"emmc","ext4","",d)}"

QB_MEM = '${@bb.utils.contains("DISTRO_FEATURES", "opengl", "-m 512", "-m 256", d)}'

python extend_recipe_sysroot_append() {
    if d.getVar('DISTRO') != 'karo-x11':
        raise_sanity_error("cannot build 'karo-image-x11' with DISTRO '%s'" % d.getVar('DISTRO'), d)
}
