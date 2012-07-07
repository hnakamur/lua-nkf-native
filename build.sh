#!/bin/bash
gyp nkf.gyp --depth=. -f make --generator-output=./out
V=1 make -C out
cp out/out/Default/nkf.so ./
