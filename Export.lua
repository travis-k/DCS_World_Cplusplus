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

	-- UDPport = 49001
	-- u = socket.try(socket.udp())
	-- u:setpeername(host, UDPport)

end

function LuaExportBeforeNextFrame()

end

function LuaExportAfterNextFrame()
	local t = LoGetModelTime()
	local name = LoGetPilotName()
	local o = LoGetSelfData()
	local IndicatedAirSpeed = LoGetIndicatedAirSpeed()
	local AltitudeAboveSeaLevel = LoGetAltitudeAboveSeaLevel()
	local AltitudeAboveGroundLevel = LoGetAltitudeAboveGroundLevel()
	local AngularVelocity = LoGetAngularVelocity()
	local AccelerationUnits = LoGetAccelerationUnits()
	local VectorVelocity = LoGetVectorVelocity()



	-- if default_output_file then
	-- 	  default_output_file:write(string.format("t = %.4f, name = %s, latitude = %.4f, longitude = %.4f, altitude = %.4f, heading = %.4f, pitch = %.4f, bank = %.4f, indicated_airspeed = %0.4f, radar_altitude = %0.4f, gyro_x = %0.4f, gyro_y = %0.4f, gyro_z = %0.4f, accel_x = %0.4f, accel_y = %0.4f, accel_z = %0.4f\n", t, name, o.LatLongAlt.Lat, o.LatLongAlt.Long, o.LatLongAlt.Alt, o.Heading, o.Pitch, o.Bank, ind_airspeed, radar_altitude, angular_velocities.x, angular_velocities.y, angular_velocities.z, accel_body.x, accel_body.y, accel_body.z))
	-- end

	-- "t = %.4f, name = %s, latitude = %.7f, longitude = %.7f, altitude = %.4f, heading = %.4f, pitch = %.4f, bank = %.4f, indicated_airspeed = %0.4f, radar_altitude = %0.4f, gyro_x = %0.4f, gyro_y = %0.4f, gyro_z = %0.4f, accel_x = %0.4f, accel_y = %0.4f, accel_z = %0.4f,  pos_x = %0.4f,  pos_y = %0.4f,  pos_z = %0.4f,  vel_x = %0.4f,  vel_y = %0.4f,  vel_z = %0.4f \n", t, name, o.LatLongAlt.Lat, o.LatLongAlt.Long, o.LatLongAlt.Alt, o.Heading, o.Pitch, o.Bank, ind_airspeed, radar_altitude, angular_velocities.x, angular_velocities.y, angular_velocities.z, accel_body.x, accel_body.y, accel_body.z, o.Position.x, o.Position.y, o.Position.z, velocity.x, velocity.y, velocity.z

	-- socket.try(c:send(string.format("Time=%.3f, name=%s \n", t,name)))
	-- socket.try(c:send(string.format("Vind_keas=%.3f \n", IndicatedAirSpeed*1.94384)))
	-- socket.try(c:send(string.format("Norml=%.3f, Axial=%.3f, Side=%.3f \n", AccelerationUnits.y, AccelerationUnits.x*-1, AccelerationUnits.z*-1)))
	-- socket.try(c:send(string.format("Q=%.3f, P=%.3f, R=%.3f \n", AngularVelocity.z, AngularVelocity.x, AngularVelocity.y*-1)))
	-- socket.try(c:send(string.format("Pitch=%.3f, Roll=%.3f, Hding=%.3f \n", o.Pitch*57.2958, o.Bank*57.2958, o.Heading*57.2958)))
	-- socket.try(c:send(string.format("Lat=%.7f, Lon=%.7f, Alt=%.3f, RAlt=%.3f \n", o.LatLongAlt.Lat, o.LatLongAlt.Long, AltitudeAboveSeaLevel*3.28084, AltitudeAboveGroundLevel*3.28084)))
	-- socket.try(c:send(string.format("Pos_E=%.3f, Pos_U=%.3f, Pos_S=%.3f \n", o.Position.z, o.Position.y, o.Position.x*-1))) 
	-- socket.try(c:send(string.format("Vel_E=%.3f, Vel_U=%.3f, Vel_S=%.3f \n", VectorVelocity.z, VectorVelocity.y, VectorVelocity.x*-1))) 


	socket.try(c:send(string.format("Time=%.3f, name=%s, Vind_keas=%.3f, Norml=%.3f, Axial=%.3f, Side=%.3f, Q=%.3f, P=%.3f, R=%.3f, Pitch=%.3f, Roll=%.3f, Hding=%.3f, Lat=%.7f, Lon=%.7f, Alt=%.3f, RAlt=%.3f, Pos_E=%.3f, Pos_U=%.3f, Pos_S=%.3f, Vel_E=%.3f, Vel_U=%.3f, Vel_S=%.3f \n", t,name,IndicatedAirSpeed*1.94384,AccelerationUnits.y, AccelerationUnits.x*-1, AccelerationUnits.z*-1,AngularVelocity.z, AngularVelocity.x, AngularVelocity.y*-1,o.Pitch*57.2958, o.Bank*57.2958, o.Heading*57.2958,o.LatLongAlt.Lat, o.LatLongAlt.Long, AltitudeAboveSeaLevel*3.28084, AltitudeAboveGroundLevel*3.28084,o.Position.z, o.Position.y, o.Position.x*-1,VectorVelocity.z, VectorVelocity.y, VectorVelocity.x*-1)))


end

function LuaExportStop()
   -- if default_output_file then
	  -- default_output_file:close()
	  -- default_output_file = nil
   -- end
	socket.try(c:send("quit")) -- to close the listener socket
	c:close()
	-- u:close()
end

function LuaExportActivityNextEvent(t)
	local tNext = t

	return tNext
end