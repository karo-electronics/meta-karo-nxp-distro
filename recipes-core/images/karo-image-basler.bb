SUMMARY = "An image with full multimedia and basler camera support"

require recipes-core/images/karo-image-weston.bb

REQUIRED_DISTRO_FEATURES = "x11 wayland"

IMAGE_INSTALL_append = " \
                        basler-camera-driver \
                        pylon \
                        python3-pypylon \
                        gentl-producer \
                        xauth \
"

IMAGE_INSTALL_append_mx8mp = " \
                        kernel-module-isp-vvcam \
                        basler-camera \
                        isp-imx \
                        packagegroup-fsl-gstreamer1.0-full \
"
