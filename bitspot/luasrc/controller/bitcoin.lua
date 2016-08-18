--[[
	LuCI configuration interface for Bitcoin Payment
	
	Copyright (C) 2009 ePoint Systems Ltd
	Author: Sandip Pandey
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
]]--

module("luci.controller.bitcoin", package.seeall)

function index()
	entry({"admin", "bitcoin"}, call("users"), "Bitcoin").index = true
	--entry({"admin", "bitcoin", "status"}, call("action_main"), "Management")
	--entry({"admin", "bitcoin", "whitelist"}, form("epoint/whitelist"), "Whitelist")
	entry({"admin", "bitcoin", "users"}, call("users"), "Users").index = true	
	entry({"admin", "bitcoin", "secret"},cbi("epoint/secret"), "Secret")
end

function action_main()
	require("nixio.fs")
	require("luci.util")

	local file = "/etc/epoint/tariffs"
	local content = luci.http.formvalue("content")
	if content then
		nixio.fs.writefile(file,
			string.gsub(luci.http.formvalue("content"), "\r", ""))
	end
	content = nixio.fs.readfile(file)
	luci.template.render("epoint/tariff-editor", {
		content = content })

end

function users()
	luci.template.render("epoint/users", {
		content = "Secret" })
end
