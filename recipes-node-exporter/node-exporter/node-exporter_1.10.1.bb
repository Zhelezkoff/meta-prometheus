require node-exporter.inc

################################################################################
#-------------------------------------------------------------------------------
# THINGS TO CONSIDER FOR EACH RELEASE:
# - SRC_URI (particularly "branch")
# - SRCREV
# - DEFAULT_PREFERENCE
#-------------------------------------------------------------------------------

SRC_URI = "git://github.com/prometheus/node_exporter.git;branch=release-1.10;protocol=https"

remove_openbsd_init_script() {
	rm -rfv ${S}/src/${GO_IMPORT}/examples/openbsd-rc.d/node_exporter
}
do_patch[postfuncs] += "remove_openbsd_init_script"

#Tag: v1.10.1
SRCREV = "fc328244fede80cde14dc0a8c5fc86f114525f29"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/github.com/prometheus/node_exporter/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
