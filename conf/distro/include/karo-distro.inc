POKY_DISTRO ??= "poky"
require conf/distro/${POKY_DISTRO}.conf

DISTRO_FEATURES_DEFAULT_remove = " \
                                  argp \
                                  bluetooth \
                                  pcmcia \
                                  zeroconf \
                                  3g \
                                  nfc \
                                  ptest \
                                  x11 \
                                  wifi \
"

DISTRO_FEATURES_append = " \
                          dhcpcd \
                          ldconfig \
                          pam \
                          telnet-login \
"

DISTRO_FEATURES_append_mx8  = " dsi83"
DISTRO_FEATURES_append_qs8m = " csi-camera imx219 raspi-display"
DISTRO_FEATURES_append_qsxm = " basler csi-camera raspi-display"
DISTRO_FEATURES_append_qsxp = " basler csi-camera raspi-display"
DISTRO_FEATURES_append_tx8p = " lvds"

VIRTUAL-RUNTIME_base-utils-hwclock = "util-linux-hwclock"
VIRTUAL-RUNTIME_dev_manager ??= "udev"
VIRTUAL-RUNTIME_init_manager ?= "${@bb.utils.contains('DISTRO_FEATURES',"systemd","systemd","sysvinit",d)}"

PREFERRED_PROVIDER_opencl-headers = "imx-gpu-viv"

VOLATILE_LOG_DIR = "no"
