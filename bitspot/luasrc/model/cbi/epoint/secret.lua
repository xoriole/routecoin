local m = Map("epoint", "ePoint Secret")
local s = m:section(NamedSection, "secret", "ePoint Secret")
s.addremove = false

s.optional = false
s:option(Value, "secret", "Secret")

return m
