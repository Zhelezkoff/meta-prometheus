require promu.inc

################################################################################
#-------------------------------------------------------------------------------
# THINGS TO CONSIDER FOR EACH RELEASE:
# - SRC_URI (particularly "branch")
# - SRCREV
# - DEFAULT_PREFERENCE
#-------------------------------------------------------------------------------

SRC_URI = "git://github.com/prometheus/promu.git;branch=master;protocol=https"

#Tag: v0.17.0
SRCREV = "3912dec4ab83971903015cc7b2a8d8ff93b73910"


LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://src/github.com/prometheus/promu/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
