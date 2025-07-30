SUMMARY = "Prometheus Utility Tool"
HOMEPAGE = "https://github.com/prometheus/promu"

do_compile[network] = "1"

B = "${WORKDIR}/build"

inherit go-mod
inherit native

GO_IMPORT = "github.com/prometheus/promu"

do_compile() {
    chmod -R +w ${B}/.mod/
    oe_runmake build
    chmod -R +w ${B}/.mod/
}

do_install() {
    install -d ${D}${bindir}
    install bin/promu ${D}${bindir}/
}
