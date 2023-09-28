#!/bin/bash

gfx2next -bitmap-y -pal-none -pal-file=base.pal dialog.png

tail -c +16384 dialog.nxi > dialog.nxi.tmp
rm -f dialog.nxi
head -c 49152 dialog.nxi.tmp > dialog.nxi
rm -f dialog.nxi.tmp

gfx2next -bitmap-y -pal-none -pal-file=base.pal menu.png

tail -c +16384 menu.nxi > menu.nxi.tmp
rm -f menu.nxi
head -c 49152 menu.nxi.tmp > menu.nxi
rm -f menu.nxi.tmp
