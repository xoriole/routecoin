local m = Map("bitcoin", "Secret")
local s = m:section(TypedSection, "secret", "Secret")
s.anonymous = true
s:option(Value, "secret", "Secret")

return m