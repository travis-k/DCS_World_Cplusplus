local default_output_file = nil

function LuaExportStart()
	package.path  = package.path..";"..lfs.currentdir().."/LuaSocket/?.lua"
	package.cpath = package.cpath..";"..lfs.currentdir().."/LuaSocket/?.dll"
	socket = require("socket")
	host = "localhost"
	port = 8001
	c = socket.try(socket.connect(host, port)) -- connect to the listener socket
	c:setoption("tcp-nodelay",true) -- set immediate transmission mode
end

function LuaExportBeforeNextFrame()

end

function LuaExportAfterNextFrame()
	local t = LoGetModelTime()
	local o = LoGetSelfData()
	local tas = LoGetTrueAirSpeed()
	local alpha = LoGetAngleOfAttack()

	socket.try(c:send(string.format(
		"time = %.4f, 
		lat = %.4f, 
		long = %.4f, 
		alt = %.4f, 
		airspeed = %.4f,
		alpha = %.4f, 
		heading = %.4f, 
		pitch = %.4f, 
		bank = %.4f\n", 
		t, 
		name, 
		o.LatLongAlt.Lat, 
		o.LatLongAlt.Long, 
		o.LatLongAlt.Alt, 
		o.Heading, 
		o.Pitch, 
		o.Bank
		)))
end

function LuaExportStop()
	socket.try(c:send("quit")) -- to close the listener socket
	c:close()
end

function LuaExportActivityNextEvent(t)
	local tNext = t

	return tNext
end
