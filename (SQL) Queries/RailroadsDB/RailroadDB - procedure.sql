use RailroadDB
go

create procedure AddStation(@station int, @route int, @arrival time, @departure time) as
begin
	if exists (select * from Stations where S_id = @station) begin
		if exists (select * from TrainRoutes where R_id = @route) begin
			begin try
				insert into StationsForRoute(R_id, S_id, ArrivalTime, DepartureTime)
				values (@route, @station, @arrival, @departure)
			end try
			begin catch
				update StationsForRoute
				set ArrivalTime = @arrival, DepartureTime = @departure
				where R_id = @route and S_id = @station
			end catch
		end
	end
end

select * from StationsForRoute
exec AddStation 7, 1, '19:30', '19:40'
exec AddStation 7, 1, '20:30', '20:40'