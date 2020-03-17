use Astronomy
go

if object_id (N'dbo.showPlanets', N'IF') is not null
	drop function showStations
go

create function dbo.showPlanets(@N int)
returns table
as
return(
	select P_name from Planets P 
	join 
	(select P_id, cnt from Missions M 
		join 
		(select M_id, count(A_id) as cnt from Crews group by M_id) C 
		on M.M_id = C.M_id) C 
	on C.P_id = P.P_id
	where C.cnt > @N
);
go

select * from Astronomy.dbo.showPlanets(1)
