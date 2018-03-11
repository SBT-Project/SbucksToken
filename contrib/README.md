
Debian
====================
This directory contains files used to package sbuckstokend/sbuckstoken-qt
for Debian-based Linux systems. If you compile sbuckstokend/sbuckstoken-qt yourself, there are some useful files here.

## sbuckstoken: URI support ##


sbuckstoken-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install sbuckstoken-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sbuckstokenqt binary to `/usr/bin`
and the `../../share/pixmaps/sbuckstoken128.png` to `/usr/share/pixmaps`

sbuckstoken-qt.protocol (KDE)

