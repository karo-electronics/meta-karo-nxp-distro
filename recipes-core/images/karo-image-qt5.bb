SUMMARY = "An image with qt5 support derived from fsl-image-qt5"

require recipes-core/images/karo-image-weston.bb

inherit populate_sdk_qt5

IMAGE_INSTALL_append = " \
    packagegroup-qt5-imx \
    tzdata \
"
