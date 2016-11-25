# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# NOTE: multiple licenses have been detected; if that is correct you should separate
# these in the LICENSE value using & if the multiple licenses all apply, or | if there
# is a choice between the multiple licenses. If in doubt, check the accompanying
# documentation to determine which situation is applicable.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   LICENSE.txt
#   examples/TinyRenderer/LICENSE.txt
#   examples/ThirdPartyLibs/openvr/LICENSE
#   data/kuka_lwr/meshes_arm/COPYRIGHT
#
SUMMARY = "bullet"
DESCRIPTION = "A 3D Collision Detection and Rigid Body Dynamics Library for games and animation"
LICENSE = "custom ZLIB"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=74f06ab3011994d1b43d71ecbb42a7cf \
                    file://examples/TinyRenderer/LICENSE.txt;md5=e493b4cc970724fe3e57031f7d6ab9fc \
                    file://examples/ThirdPartyLibs/openvr/LICENSE;md5=3f0ba432004f9cf11d8186503a8bd3d7 \
                    file://data/kuka_lwr/meshes_arm/COPYRIGHT;md5=2e93d905885ec840715733c6912284d5"

SRC_URI = "https://github.com/bulletphysics/bullet3/archive/${PV}.tar.gz"
SRC_URI[md5sum] = "194cf1ef1eeb7fa9ac7dc580219d3c8b"
SRC_URI[sha256sum] = "6e157c0b50373bc0e860de27f06397827bb28a4205bc568ae79d76a0f919ed62"

S = "${WORKDIR}/${BPN}3-${PV}"

# NOTE: unable to map the following CMake package dependencies: NumPy
DEPENDS = "virtual/libgl ttf-dejavu graphviz python doxygen"

inherit cmake python-dir

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
EXTRA_OECMAKE = ""

