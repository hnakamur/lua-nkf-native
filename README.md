# lua-nkf-native

This is a nkf C module for lua/luvit.
This module contains source code from nkf 2.1.2

## Build

run
```
./build.sh
```

## Sample Usage

```
local nkf = require("nkf")

local konnicihwa_sjis = "\130\177\130\241\130\201\130\191\130\205"
local konnicihwa_utf8 = "\227\129\147\227\130\147\227\129\171\227\129\161\227\129\175"
local konnichiwa_jis_base64 = "GyRCJDMkcyRLJEEkTxsoQg=="

print(nkf.nkf("-S -w", konnicihwa_sjis))
print(nkf.nkf("-W -j -MB", konnicihwa_utf8))
print(nkf.nkf("-m -w", "=?ISO-2022-JP?B?"..konnichiwa_jis_base64.."?="))
```

## TODO
* Add conditions for other OSes than mac in example.gyp.
* Check whether memory leaks exist.

## License

MIT license, for more info see [LICENSE](https://raw.github.com/hnakamur/luvit-c-module-example/master/LICENSE).

## Credits
Thanks a lot for [nkf project](http://sourceforge.jp/projects/nkf/).