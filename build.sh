#!/bin/bash
cd gba
make clean
make
cd ..
mkdir data
mv -f gba/gba_pkjb.gba data/gba_mb.gba
make -f Makefile.wii clean
make -f Makefile.wii
