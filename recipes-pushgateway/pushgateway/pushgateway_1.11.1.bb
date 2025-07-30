require pushgateway.inc

################################################################################
#-------------------------------------------------------------------------------
# THINGS TO CONSIDER FOR EACH RELEASE:
# - SRC_URI (particularly "branch")
# - SRCREV
# - DEFAULT_PREFERENCE
#-------------------------------------------------------------------------------

SRC_URI = "git://github.com/prometheus/pushgateway.git;branch=master;protocol=https"

#Tag: v1.11.1
SRCREV = "aff0d834b730375fc965135e3e2d17d15f82a76f"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/github.com/prometheus/pushgateway/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
