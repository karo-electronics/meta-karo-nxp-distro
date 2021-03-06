SUMMARY = "An image with full multimedia, Machine Learning and Basler camera support"

require recipes-core/images/karo-image-ml.bb

REQUIRED_DISTRO_FEATURES = "x11 wayland"

IMAGE_INSTALL_append = " \
                        basler-camera-driver \
                        pylon \
                        python3-pypylon \
                        gentl-producer \
                        v4l-utils \
                        xauth \
"

IMAGE_INSTALL_append_mx8mp = " \
                        kernel-module-isp-vvcam \
                        imx8mp-modprobe-config \
                        basler-camera \
                        isp-imx \
                        packagegroup-fsl-gstreamer1.0-full \
                        packagegroup-imx-isp \
"
