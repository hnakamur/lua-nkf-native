local nkf = require("nkf")

local konnicihwa_sjis = "\130\177\130\241\130\201\130\191\130\205"
local konnicihwa_utf8 = "\227\129\147\227\130\147\227\129\171\227\129\161\227\129\175"
local konnichiwa_jis_base64 = "GyRCJDMkcyRLJEEkTxsoQg=="

assert(nkf.convert("-S -w", konnicihwa_sjis) == konnicihwa_utf8)
assert(nkf.convert("-W -s", konnicihwa_utf8) == konnicihwa_sjis)

assert(nkf.convert("-W -j -MB", konnicihwa_utf8) == konnichiwa_jis_base64)
assert(nkf.convert("-m -w", "=?ISO-2022-JP?B?"..konnichiwa_jis_base64.."?=") ==
  konnicihwa_utf8)
