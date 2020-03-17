use RailroadDB
go

if object_id (N'dbo.showStations', N'IF') is not null
	drop function showStations
go

create function dbo.showStations(@R int)
returns table
as
return(
	select S_name from Stations S join
		(select S_id from 
			(select S_id, count(S_id) as cnt from StationsForRoute group by S_id) C
		where cnt > @R) C 
	on S.S_id = C.S_id
);
go

select * from RailroadDB.dbo.showStations(4)