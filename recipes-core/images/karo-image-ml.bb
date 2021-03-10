SUMMARY = "An image with full multimedia, basler camera and ML support"

require recipes-core/images/karo-image-basler.bb

OPENCV_PKGS_imxgpu = " \
        opencv-apps \
        opencv-samples \
        python3-opencv \
        python3-pygobject \
"

IMAGE_INSTALL_append = " \
        ${OPENCV_PKGS} \
        packagegroup-fsl-tools-gpu \
        packagegroup-fsl-tools-gpu-external \
        packagegroup-imx-ml \
        tzdata \
"

IMAGE_INSTALL_append_mx8mp = " \
        packagegroup-imx-isp \
"

TOOLCHAIN_TARGET_TASK_append = " \
        tensorflow-lite-staticdev \
"
