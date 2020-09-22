SUMMARY = "A very basic Wayland image with Weston desktop and terminal"

require karo-image.inc

IMAGE_FEATURES_append = " \
                         hwcodecs \
                         package-management \
                         splash \
                         ssh-server-dropbear \
"

REQUIRED_DISTRO_FEATURES = "wayland"

CORE_IMAGE_BASE_INSTALL_append = " \
                                  clutter-1.0-examples \
                                  glmark2 \
                                  gtk+3-demo \
                                  weston \
                                  weston-init \
                                  weston-examples \
"

IMAGE_INSTALL_append = " \
                        gst-examples \
                        libdrm \
                        libdrm-tests \
                        libdrm-kms \
"

QB_MEM = '${@bb.utils.contains("DISTRO_FEATURES", "opengl", "-m 512", "-m 256", d)}'

python extend_recipe_sysroot_append() {
    if d.getVar('DISTRO') != 'karo-wayland':
        raise_sanity_error("cannot build 'karo-image-weston' with DISTRO '%s'" % d.getVar('DISTRO'), d)
}
