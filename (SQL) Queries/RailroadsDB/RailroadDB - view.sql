use RailroadDB
go

create view NationalTrains
as
select R_name from TrainRoutes R join
	(select R_id from 
		(select R_id, count(R_id) as cnt from StationsForRoute group by R_id) C
	where cnt = 7) S
on R.R_id = S.R_id
go

select * from NationalTrains