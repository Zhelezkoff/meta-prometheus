SUMMARY = "Prometheus Pushgateway"
HOMEPAGE = "https://github.com/prometheus/pushgateway/"

do_compile[network] = "1"

SRC_URI:append = " file://pushgateway.service \
                   file://pushgateway \
"

B = "${UNPACKDIR}/build"

inherit go-mod

RDEPENDS:${PN}-dev += "bash"

DEPENDS = "promu-native"

GO_IMPORT = "github.com/prometheus/pushgateway"

# Go binaries produce unexpected effects that the Yocto QA mechanism doesn't
# like. We disable those checks here.
INSANE_SKIP:${PN} += "buildpaths"
INSANE_SKIP:${PN}-dev += "buildpaths"
INSANE_SKIP:${PN}-dbg += "buildpaths"
INSANE_SKIP:${PN} += "host-user-contaminated"

do_compile() {
    oe_runmake PROMU=${WORKDIR}/recipe-sysroot-native/usr/bin/promu build
}

do_install:append() {
    install -d ${D}/usr/sbin/
    install -m 0755 -g pushgateway -o pushgateway ${B}/src/${GO_IMPORT}/pushgateway ${D}/usr/sbin/pushgateway

    if [ "${VIRTUAL-RUNTIME_init_manager}" = "systemd" ]; then
        install -d ${D}${systemd_unitdir}/system/

        install -m 0644 ${UNPACKDIR}/pushgateway.service ${D}${systemd_unitdir}/system/pushgateway.service
    fi

    if [ "${VIRTUAL-RUNTIME_init_manager}" = "sysvinit" ]; then
        install -d ${D}${sysconfdir}/init.d/

        install -m 0755 ${UNPACKDIR}/pushgateway ${D}${sysconfdir}/init.d/pushgateway
    fi
}

# User
inherit useradd
# User pushgateway:pushgateway
USERADD_PACKAGES = "${PN}"
USERADD_PARAM:${PN} = "-g pushgateway -r -s /sbin/nologin pushgateway"
GROUPADD_PARAM:${PN} = "pushgateway"

# sysvinit
inherit update-rc.d
INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME = "pushgateway"
INITSCRIPT_PARAMS = "start 99 1 2 3 4 5 . stop 20 0 1 6 ."
RDEPENDS:${PN} += "initscripts"
CONFFILES:${PN} += "${sysconfdir}/init.d/pushgateway"

# systemd
inherit systemd
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE:${PN} = "pushgateway.service"
SYSTEMD_AUTO_ENABLE ?= "enable"
