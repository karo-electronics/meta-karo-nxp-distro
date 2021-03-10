SUMMARY = "A very basic Wayland image with Weston desktop and terminal"

require karo-image.inc

IMAGE_FEATURES_append = " \
                         hwcodecs \
                         package-management \
                         splash \
                         ssh-server-openssh \
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
                        ${@bb.utils.contains('DISTRO_FEATURES', 'x11 wayland', 'weston-xwayland xterm', '', d)} \
"

QB_MEM = '${@bb.utils.contains("DISTRO_FEATURES", "opengl", "-m 512", "-m 256", d)}'
