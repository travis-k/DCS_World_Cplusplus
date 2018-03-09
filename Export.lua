local default_output_file = nil

function LuaExportStart()
	-- default_output_file = io.open(lfs.writedir().."/Logs/Export.log", "w")
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
	local name = LoGetPilotName()
	local o = LoGetSelfData();
	local ind_airspeed = LoGetIndicatedAirSpeed();
	local radar_altitude = LoGetAltitudeAboveGroundLevel();
	local angular_velocities = LoGetAngularVelocity();
	local accel_body = LoGetAccelerationUnits()

	-- if default_output_file then
	-- 	  default_output_file:write(string.format("t = %.4f, name = %s, latitude = %.4f, longitude = %.4f, altitude = %.4f, heading = %.4f, pitch = %.4f, bank = %.4f, indicated_airspeed = %0.4f, radar_altitude = %0.4f, gyro_x = %0.4f, gyro_y = %0.4f, gyro_z = %0.4f, accel_x = %0.4f, accel_y = %0.4f, accel_z = %0.4f\n", t, name, o.LatLongAlt.Lat, o.LatLongAlt.Long, o.LatLongAlt.Alt, o.Heading, o.Pitch, o.Bank, ind_airspeed, radar_altitude, angular_velocities.x, angular_velocities.y, angular_velocities.z, accel_body.x, accel_body.y, accel_body.z))
	-- end
	socket.try(c:send(string.format("t = %.4f, name = %s, latitude = %.7f, longitude = %.7f, altitude = %.4f, heading = %.4f, pitch = %.4f, bank = %.4f, indicated_airspeed = %0.4f, radar_altitude = %0.4f, gyro_x = %0.4f, gyro_y = %0.4f, gyro_z = %0.4f, accel_x = %0.4f, accel_y = %0.4f, accel_z = %0.4f\n", t, name, o.LatLongAlt.Lat, o.LatLongAlt.Long, o.LatLongAlt.Alt, o.Heading, o.Pitch, o.Bank, ind_airspeed, radar_altitude, angular_velocities.x, angular_velocities.y, angular_velocities.z, accel_body.x, accel_body.y, accel_body.z)))
end

function LuaExportStop()
   -- if default_output_file then
	  -- default_output_file:close()
	  -- default_output_file = nil
   -- end
	socket.try(c:send("quit")) -- to close the listener socket
	c:close()
end

function LuaExportActivityNextEvent(t)
	local tNext = t

	return tNext
end