require node-exporter.inc

################################################################################
#-------------------------------------------------------------------------------
# THINGS TO CONSIDER FOR EACH RELEASE:
# - SRC_URI (particularly "branch")
# - SRCREV
# - DEFAULT_PREFERENCE
#-------------------------------------------------------------------------------

SRC_URI = "git://github.com/prometheus/node_exporter.git;branch=release-1.9;protocol=https;destsuffix=${GO_SRCURI_DESTSUFFIX}"

remove_openbsd_init_script() {
	rm -rfv ${S}/src/${GO_IMPORT}/examples/openbsd-rc.d/node_exporter
}
do_patch[postfuncs] += "remove_openbsd_init_script"

#Tag: v1.9.0
SRCREV = "02afa5c53c36123611533f2defea6ccd4546a9bb"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/github.com/prometheus/node_exporter/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
