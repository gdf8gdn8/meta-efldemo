SUMMARY = "EFL"
LICENSE = "MIT & BSD & LGPL-2.1"
LIC_FILES_CHKSUM = "file://COPYING;md5=7289b9073819c9ee98b6f688df9717e8"

DEPENDS_class-native = "freetype-native libxext-native libpng-native jpeg-native tiff-native libfribidi-native glib-2.0-native dbus-native openssl-native librsvg-native"
DEPENDS = "udev libxkbcommon libinput virtual/libiconv tslib curl glib-2.0 gnutls pkgconfig zlib jpeg openssl libsndfile1 cairo dbus libexif librsvg freetype libpng tiff   fontconfig libfribidi giflib udev  efl-native util-linux libunwind efl-native"
# 
inherit efl gettext pkgconfig

BBCLASSEXTEND = "native"

PROVIDES += "ecore edje eet eeze efreet eina eio embryo emotion ethumb evas eldbus"

# we don't have bullet for physics
# You have chosen to disable physics support. This disables lots of
# core functionality and is effectively never tested. You are going
# to find features that suddenly don't work and as a result cause
# a series of breakages. This is simply not tested so you are on
# your own in terms of ensuring everything works if you do this
EXTRA_OECONF = " \
    --enable-i-really-know-what-i-am-doing-and-that-this-will-probably-break-things-and-i-will-fix-them-myself-and-send-patches-abb \
"
EXTRA_OECONF_append_class-target = " \
    --with-edje-cc=${STAGING_BINDIR_NATIVE}/edje_cc \
    --with-eolian-gen=${STAGING_BINDIR_NATIVE}/eolian_gen \
    --with-eolian-cxx=${STAGING_BINDIR_NATIVE}/eolian_cxx \
    --with-elua=${STAGING_BINDIR_NATIVE}/elua \
    --with-elm-prefs-cc=${STAGING_BINDIR_NATIVE}/elm_prefs_cc \
    --with-eldbus-codegen=${STAGING_BINDIR_NATIVE}/eldbus-codegen \
    --with-eet-eet=${STAGING_BINDIR_NATIVE}/eet \
    --enable-static \
"
EXTRA_OECONF_append_class-native = " \
    --disable-fontconfig \
    --disable-audio \
    --disable-physics \
    --disable-multisense \
    --disable-cserve \
    --disable-libeeze \
    --with-x11=none \
    --disable-image-loader-bmp \
    --disable-image-loader-eet \
    --disable-image-loader-generic \
    --disable-image-loader-gif \
    --disable-image-loader-ico \
    --disable-image-loader-jp2k \
    --disable-image-loader-pmaps \
    --disable-image-loader-psd \
    --disable-image-loader-tga \
    --disable-image-loader-wbmp \
    --disable-image-loader-webp \
    --disable-image-loader-xpm \
    --disable-image-loader-tgv \
    --disable-image-loader-dds \
    --disable-spectre \
    --disable-poppler \
    --disable-libraw \
"
# eglfs -> sucking freescale virvante driver
# eglfs need hwcomposer.h ?
PACKAGECONFIG ?= " fb  gstreamer1 pulseaudio luajit ${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'wayland', '', d)} ${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'x11', '', d)} ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}"
PACKAGECONFIG_class-native = "luajit"

# gs is broken!? so we can't configure spectre :(
PACKAGECONFIG[libspectre] = "--enable-spectre,--disable-spectre"
PACKAGECONFIG[physics] = "--enable-physics,--disable-physics,bullet"
# gs is broken!? so we can't configure poppler :(
PACKAGECONFIG[poppler] = "--enable-poppler,--disable-poppler"
PACKAGECONFIG[libraw] = "--enable-libraw,--disable-libraw,libraw"
PACKAGECONFIG[wayland] = "--enable-wayland --enable-wayland-ivi-shell,--disable-wayland --disable-wayland-ivi-shell,wayland"
PACKAGECONFIG[egl] = "--enable-egl,--disable-egl,virtual/egl"
# sort of tri-state
PACKAGECONFIG[opengl-full] = "--with-opengl=full,,virtual/libgl"
PACKAGECONFIG[opengl-es] = "--with-opengl=es,,virtual/libgles2"
PACKAGECONFIG[opengl-none] = "--with-opengl=none,,"
# be aware when enabling this for efl-native, we don't provide gcc-native so you need to make
# sure that all your builders have g++ which supports -std=gnu++11
PACKAGECONFIG[c++11] = "--enable-cxx-bindings,--disable-cxx-bindings"
PACKAGECONFIG[gstreamer] = "--enable-gstreamer,--disable-gstreamer,gstreamer"
PACKAGECONFIG[gstreamer1] = "--enable-gstreamer1,--disable-gstreamer1,gstreamer1.0 gstreamer1.0-plugins-base"
PACKAGECONFIG[pulseaudio] = "--enable-pulseaudio,--disable-pulseaudio,pulseaudio"
PACKAGECONFIG[systemd] = "--enable-systemd,--disable-systemd,systemd"
PACKAGECONFIG[luajit] = "--disable-lua-old,--enable-lua-old,luajit"
PACKAGECONFIG[lua-old] = "--enable-lua-old,--disable-lua-old,lua"
PACKAGECONFIG[avahi] = "--enable-avahi,--disable-avahi,avahi"

# needs android sdk
PACKAGECONFIG[eglfs] = "--enable-eglfs --with-opengl=es,--disable-eglfs,virtual/libgles2"


PACKAGECONFIG[fb] = "--enable-fb,--disable-fb,tslib"

PACKAGECONFIG[x11] = ",--with-x11=none,virtual/libx11 libxext libxdamage libxrender libxcursor libxcomposite libxinerama libxrandr libxtst libxscrnsaver"
# currently we don't provide doxygen-native
PACKAGECONFIG[doc] = "--enable-doc,--disable-doc,doxygen-native"

do_install_append() {
    # don't ship precompiled lua files
    rm -f ${datadir}/elua/*/*.luac
}


#ALLOW_EMPTY_ecore = "1"
#RDEPENDS_ecore = "ecore-audio ecore-input-evas ecore-input ecore-imf-evas ecore-imf ecore-file ecore-con ecore-ipc ecore-x ecore-evas"
RDEPENDS_efl = "cairo"
#python populate_packages_prepend () {
#    for plugin_type in "engines loaders savers".split():
#        bb.note( "splitting packages for evas %s..." % plugin_type )
#        basedir = d.expand( '${libdir}/evas/modules/%s' % plugin_type)#
#
#        do_split_packages(d, basedir, '^(.*)',
#        output_pattern = 'evas-' + plugin_type[:-1] + "-%s",
#        description = 'Evas module %s',
#        allow_dirs=True, recursive=False, extra_depends="" )
#
#        plugin_type = "cserve2"
#        bb.note( "splitting packages for evas %s..." % plugin_type )
#        basedir = d.expand( '${libdir}/evas/%s/loaders' % plugin_type)#
#
#        do_split_packages(d, basedir, '^(.*)',
#        output_pattern = 'evas-' + plugin_type + "-%s",
#        description = 'Evas csever2 loader module %s',
#        allow_dirs=True, recursive=False, extra_depends="" )
#}

#PACKAGES += "evas-loader-png evas-engine-software-generic evas-engine-fb"
#PACKAGES_DYNAMIC += "^evas-engine-.* ^evas-loader-.* ^evas-saver-.* ^evas-cserve2-.*"
FILES_${PN} += " \
    ${systemd_system_unitdir}/* \
    ${libdir}/* \
    ${datadir}/* \
    ${bindir}/edje_player \
    ${bindir}/eeze_* \
    ${bindir}/efreetd* \
    ${bindir}/ethumb* \
    ${bindir}/elu* \
"

FILES_${PN}-dbg += " \
    ${libdir}/*/*/.debug \
"
FILES_${PN}-dev += " \
    ${libdir}/cmake \
    ${libdir}/*/*/*/*/module.la \
    ${libdir}/*/*/*/*/*/module.la \
    ${libdir}/ethumb*/*/*/*/module.la \
    ${libdir}/eeze*/*/*/*/*/module.la \
    ${libdir}/edje*/*/*/*/module.la \
    ${libdir}/emotion/modules/gstreamer1/*/module.la \
    ${datadir}/gdb/auto-load \
    ${datadir}/eo/gdb \
    ${bindir}/eldbus-codegen \
    ${bindir}/*_cc ${bindir}/*_decc \
    ${bindir}/edje_* \
    ${bindir}/eet* \
    ${bindir}/diffeet* \
    ${bindir}/vieet \
    ${bindir}/eina* \
"
