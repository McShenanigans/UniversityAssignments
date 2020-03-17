use ForzaHorizon
go

drop view JoinedView
go

create view JoinedView
as
select p.P_name, c.C_make, c.C_model
from cars_1 c inner join races_1 r on c.C_id = r.C_id inner join players_1 p on p.P_id = r.P_id
where C_year between 1990 and 2020 and P_ranking < 50
go

select * from JoinedView

if exists (select name from sys.indexes where name = N'N_idx_CYear')
	drop index N_idx_CYear on cars_1
go

create nonclustered index N_idx_CYear on cars_1(C_year)
go

if exists (select name from sys.indexes where name = N'N_idx_PRanking')
	drop index N_idx_PRanking on players_1
go

create nonclustered index N_idx_PRanking on players_1(P_ranking)
go

select * from JoinedView