require pushgateway.inc

################################################################################
#-------------------------------------------------------------------------------
# THINGS TO CONSIDER FOR EACH RELEASE:
# - SRC_URI (particularly "branch")
# - SRCREV
# - DEFAULT_PREFERENCE
#-------------------------------------------------------------------------------

SRC_URI = "git://github.com/prometheus/pushgateway.git;branch=master;protocol=https"

#Tag: v1.11.2
SRCREV = "ace6bf252df95246501059f17ace076f1081144e"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/github.com/prometheus/pushgateway/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
