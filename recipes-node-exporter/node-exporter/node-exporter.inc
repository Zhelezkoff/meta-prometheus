SUMMARY = "Prometheus Node Exporter"
HOMEPAGE = "https://github.com/prometheus/node_exporter"

do_compile[network] = "1"

SRC_URI:append = " file://node_exporter"

B = "${WORKDIR}/build"

inherit go-mod

RDEPENDS:${PN}-dev += "bash"

DEPENDS = "promu-native"

GO_IMPORT = "github.com/prometheus/node_exporter"

# Go binaries produce unexpected effects that the Yocto QA mechanism doesn't
# like. We disable those checks here.
INSANE_SKIP:${PN} += "buildpaths"
INSANE_SKIP:${PN}-dev += "buildpaths"
INSANE_SKIP:${PN}-dbg += "buildpaths"
INSANE_SKIP:${PN} += "host-user-contaminated"

FILES:${PN} = "\
   ${systemd_unitdir}/system/node_exporter.service \
   ${systemd_unitdir}/system/node_exporter.socket \
   ${sysconfdir}/sysconfig/node_exporter \
   ${localstatedir}/lib/node_exporter/textfile_collector\
   ${sysconfdir}/init.d/node_exporter \
   /usr/sbin/node_exporter \
"

do_compile() {
    chmod -R +w ${B}/.mod/
    oe_runmake PROMU=${WORKDIR}/recipe-sysroot-native/usr/bin/promu build
    chmod -R +w ${B}/.mod/
}

do_install:append() {
    install -d ${D}/usr/sbin/
    install -m 0755 -g node_exporter -o node_exporter ${B}/src/${GO_IMPORT}/node_exporter ${D}/usr/sbin/node_exporter

    if [ "${VIRTUAL-RUNTIME_init_manager}" = "systemd" ]; then
        install -d ${D}${systemd_unitdir}/system/

        install -m 0644 ${S}/src/${GO_IMPORT}/examples/systemd/node_exporter.service ${D}${systemd_unitdir}/system/node_exporter.service
        install -m 0644 ${S}/src/${GO_IMPORT}/examples/systemd/node_exporter.socket ${D}${systemd_unitdir}/system/node_exporter.socket

        install -d ${D}${sysconfdir}/sysconfig
        install -m 0644 ${S}/src/${GO_IMPORT}/examples/systemd/sysconfig.node_exporter ${D}${sysconfdir}/sysconfig/node_exporter
    fi

    if [ "${VIRTUAL-RUNTIME_init_manager}" = "sysvinit" ]; then
        install -d ${D}${sysconfdir}/init.d/

        install -m 0755 ${WORKDIR}/node_exporter ${D}${sysconfdir}/init.d/node_exporter
    fi

    install -d -g node_exporter -o node_exporter ${D}${localstatedir}/lib/node_exporter/textfile_collector
}

# User
inherit useradd
# User node_exporter:node_exporter
USERADD_PACKAGES = "${PN}"
USERADD_PARAM:${PN} = "-g node_exporter -r -s /sbin/nologin node_exporter"
GROUPADD_PARAM:${PN} = "node_exporter"

# sysvinit
inherit update-rc.d
INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME = "node_exporter"
INITSCRIPT_PARAMS = "start 99 1 2 3 4 5 . stop 20 0 1 6 ."
RDEPENDS:${PN} += "initscripts"
CONFFILES:${PN} += "${sysconfdir}/init.d/node_exporter"

# systemd
inherit systemd
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE:${PN} = "node_exporter.service node_exporter.socket"
SYSTEMD_AUTO_ENABLE ?= "enable"
