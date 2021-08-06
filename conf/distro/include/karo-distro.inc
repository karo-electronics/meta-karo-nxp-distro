POKY_DISTRO ??= "poky"
require conf/distro/${POKY_DISTRO}.conf

POKY_DEFAULT_DISTRO_FEATURES_remove = " \
                                       largefile \
                                       opengl \
                                       ptest \
                                       vulkan \
                                       wayland \
"

DISTRO_FEATURES_DEFAULT_remove = " \
                                  3g \
                                  argp \
                                  bluetooth \
                                  nfc \
                                  pcmcia \
                                  wifi \
                                  x11 \
                                  zeroconf \
"

DISTRO_FEATURES_append = " \
                          alternatives-symlinks-relative \
                          dhcpcd \
                          ldconfig \
                          pam \
                          telnet-login \
"

DISTRO_FEATURES_append_mx8  = " dsi83"
DISTRO_FEATURES_append_tx8m = " pcie"
DISTRO_FEATURES_append_qs8m = " csi-camera imx219 raspi-display tc358867"
DISTRO_FEATURES_append_qsxm = " basler csi-camera pcie raspi-display tc358867"
DISTRO_FEATURES_append_qsxp = " basler csi-camera pcie raspi-display tc358867"
DISTRO_FEATURES_append_tx8p = " lvds"

VIRTUAL-RUNTIME_base-utils-hwclock = "util-linux-hwclock"
VIRTUAL-RUNTIME_dev_manager ?= "udev"
VIRTUAL-RUNTIME_init_manager ?= "${@bb.utils.contains('DISTRO_FEATURES',"systemd","systemd","sysvinit",d)}"

PREFERRED_PROVIDER_opencl-headers = "imx-gpu-viv"

VOLATILE_LOG_DIR = "no"

# mask out sysvinit recipes from meta-imx layer
BBMASK += ".*/meta-imx/.*/sysvinit/.*"

# mask out bbappend from devil since it's fetch gives 404
BBMASK += ".*/meta-imx/meta-sdk/recipes-graphics/devil/devil_%.bbappend"

# mask out recipe breaking the weston desktop without systemd
BBMASK += ".*/meta-imx/meta-bsp/recipes-graphics/wayland/weston-init.bbappend"
