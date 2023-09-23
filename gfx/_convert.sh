#!/bin/bash

gfx2next -bitmap-y -pal-none -pal-file=base.pal menu.png

tail -c +16384 menu.nxi > menu.nxi.tmp
rm -f menu.nxi
head -c 49152 menu.nxi.tmp > menu.nxi
rm -f menu.nxi.tmp
