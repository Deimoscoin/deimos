
Debian
====================
This directory contains files used to package deimosd/deimos-qt
for Debian-based Linux systems. If you compile deimosd/deimos-qt yourself, there are some useful files here.

## deimos: URI support ##


deimos-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install deimos-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your deimos-qt binary to `/usr/bin`
and the `../../share/pixmaps/deimos128.png` to `/usr/share/pixmaps`

deimos-qt.protocol (KDE)

