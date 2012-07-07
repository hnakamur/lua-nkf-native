local string = require("string")
local table = require("table")

function rep(str)
  local buf = {}
  local len = string.len(str)
  local i = 1
  while i <= len do
    local b = string.byte(str, i)
    local ch = (0x20 <= b and b < 0x7f) and
      string.char(b) or string.format("\\%03d", b)
    table.insert(buf, ch)
    i = i + 1
  end
  return table.concat(buf, "")
end

for line in io.lines() do
  print(rep(line))
end
