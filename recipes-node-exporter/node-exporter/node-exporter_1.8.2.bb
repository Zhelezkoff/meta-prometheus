require node-exporter.inc

################################################################################
#-------------------------------------------------------------------------------
# THINGS TO CONSIDER FOR EACH RELEASE:
# - SRC_URI (particularly "branch")
# - SRCREV
# - DEFAULT_PREFERENCE
#-------------------------------------------------------------------------------

SRC_URI = "git://github.com/prometheus/node_exporter.git;branch=release-1.8;protocol=https"

#SRC_URI:append = " file://001-remove-bsd-1.8.2.patch;patchdir=src/${GO_IMPORT}"

#SRC_URI:append = " file://0001-Add-trimpath.patch;patchdir=src/${GO_IMPORT}"

remove_openbsd_init_script() {
	rm -rfv ${S}/src/${GO_IMPORT}/examples/openbsd-rc.d/node_exporter
}
do_patch[postfuncs] += "remove_openbsd_init_script"

#Tag: v1.8.2
SRCREV = "f1e0e8360aa60b6cb5e5cc1560bed348fc2c1895"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/github.com/prometheus/node_exporter/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
