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
#   LICENSE.LibRaw.pdf
#   LICENSE.CDDL
#   COPYRIGHT
#
SUMMARY = "LibRaw - raw image decoder"
DESCRIPTION = "LibRaw is a library for reading RAW files obtained from digital photo cameras (CRW/CR2, NEF, RAF, DNG, and others). " 

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LibRaw.pdf;md5=73b68a59b155f15cf1738d8c7fe5bf4a \
                    file://LICENSE.CDDL;md5=786f31583aef7862dabd13e78addd669 \
                    file://LICENSE.LGPL;md5=68ad62c64cc6c620126241fd429e68fe \
                    file://COPYRIGHT;md5=342cc298b1d5db74b6fb703001e5020a"

SRC_URI = "http://www.libraw.org/data/LibRaw-${PV}.tar.gz \
    file://libraw-gcc6.patch \
   "
# Thanks to archlinux guys libraw-gcc6.patch

SRC_URI[md5sum] = "456626300777209def1ea784910f326a"
SRC_URI[sha256sum] = "92b0c42c7666eca9307e5e1f97d6fefc196cf0b7ee089e22880259a76fafd15c"

S = "${WORKDIR}/LibRaw-${PV}"

# NOTE: unable to map the following pkg-config dependencies: lcms2
#       (this is based on recipes that have previously been built and packaged)
# NOTE: the following library dependencies are unknown, ignoring: jasper
#       (this is based on recipes that have previously been built and packaged)
DEPENDS = "libjpeg-turbo"

# NOTE: if this software is not capable of being built in a separate build directory
# from the source, you should replace autotools with autotools-brokensep in the
# inherit line
inherit pkgconfig autotools native

BBCLASSEXTEND = "native"
# Specify any options you want to pass to the configure script using EXTRA_OECONF:
EXTRA_OECONF = ""

PROVIDES += "libraw"

EXTRA_OECONF = " \
    --disable-examples \
"
