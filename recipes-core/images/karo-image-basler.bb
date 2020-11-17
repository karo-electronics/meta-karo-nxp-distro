SUMMARY = "An image with full multimedia and basler camera support"

require recipes-core/images/karo-image-weston.bb

REQUIRED_DISTRO_FEATURES = "x11 wayland"

IMAGE_INSTALL_append = " \
                        basler-camera-driver \
                        pylon \
                        python3-pypylon \
                        gentl-producer \
                        kernel-module-isp-vvcam \
                        basler-camera \
                        isp-imx \
                        xauth \
                        packagegroup-fsl-gstreamer1.0-full \
"
