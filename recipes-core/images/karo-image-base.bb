SUMMARY = "A console-only image for Ka-Ro electronics TX modules"

require karo-image.inc

DISTRO_FEATURES_append = " busybox-crond"

IMAGE_LINGUAS_append = " de-de"

IMAGE_FEATURES_append = " splash ssh-server-openssh"
IMAGE_INSTALL_append_karo-base = " udev"

python extend_recipe_sysroot_append() {
    if d.getVar('DISTRO') != 'karo-base':
        raise_sanity_error("cannot build 'karo-image-base' with DISTRO '%s'" % d.getVar('DISTRO'), d)
}
