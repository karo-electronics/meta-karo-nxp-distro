SUMMARY = "An image with qt5 support derived from fsl-image-qt5"

require karo-image.inc
require dynamic-layers/qt5-layer/recipes-fsl/images/fsl-image-qt5.bb

bluetooth_pkg = "${@bb.utils.contains('DISTRO_FEATURES','bluethooth','','packagegroup-tools-bluetooth',d)}"

CORE_IMAGE_EXTRA_INSTALL_remove = "${@bb.utils.contains('DISTRO_FEATURES','bluethooth','','packagegroup-tools-bluetooth',d)}"

# qt creator needs openssh
IMAGE_FEATURES += "ssh-server-openssh"
