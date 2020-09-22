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

VIRTUAL-RUNTIME_base-utils-hwclock = "util-linux-hwclock"

PREFERRED_PROVIDER_opencl-headers = "imx-gpu-viv"

VOLATILE_LOG_DIR = "no"
