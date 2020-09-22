FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

do_install_append () {
    rm -rvf ${D}${sysconfdir}/default/volatiles
}
