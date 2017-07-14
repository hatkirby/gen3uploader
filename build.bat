@echo off
cd gba
make clean
make
cd ..
@md data
mv -f gba/gba_pkjb.gba data/gba_mb.gba
make -f Makefile.wii clean
make -f Makefile.wii
pause
