FILES_libgbm-imx_mx8_append = " ${libdir}/libgbm.so.1"

do_install_append_mx8() {
        ln -sf libgbm_viv.so ${D}${libdir}/libgbm.so.1
}
