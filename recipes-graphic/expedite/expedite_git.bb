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
#   COPYING-PLAIN
#   COPYING
#
LICENSE = "CUSTOM"
LIC_FILES_CHKSUM = "file://COPYING-PLAIN;md5=f59cacc08235a546b0c34a5422133035 \
                    file://COPYING;md5=d70bc65d46237e4ef386beebe7d0fe5b"

SRC_URI = "git://git.enlightenment.org/tools/expedite.git;protocol=https"

# Modify these as desired
PV = "1.11.99+git${SRCPV}"
SRCREV = "ffa005ea3de26b4219f32c285cb1665bb1366163"

S = "${WORKDIR}/git"

# NOTE: unable to map the following pkg-config dependencies: evil
#       (this is based on recipes that have previously been built and packaged)
DEPENDS = "efl"

# NOTE: if this software is not capable of being built in a separate build directory
# from the source, you should replace autotools with autotools-brokensep in the
# inherit line
inherit pkgconfig autotools

# Specify any options you want to pass to the configure script using EXTRA_OECONF:
EXTRA_OECONF = ""
