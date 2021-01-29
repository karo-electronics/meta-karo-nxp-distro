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

DISTRO_FEATURES_append_qs8m = " csi-camera imx219 raspi-display"
DISTRO_FEATURES_append_tx8m = " dsi83"

VIRTUAL-RUNTIME_base-utils-hwclock = "util-linux-hwclock"
VIRTUAL-RUNTIME_dev_manager ??= "udev"
VIRTUAL-RUNTIME_init_manager ?= "${@bb.utils.contains('DISTRO_FEATURES',"systemd","systemd","sysvinit",d)}"

PREFERRED_PROVIDER_opencl-headers = "imx-gpu-viv"

VOLATILE_LOG_DIR = "no"
