SUMMARY = "An image with full multimedia and Machine Learning support"

require recipes-core/images/karo-image-weston.bb

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

TOOLCHAIN_TARGET_TASK_append = " \
        tensorflow-lite-staticdev \
"
