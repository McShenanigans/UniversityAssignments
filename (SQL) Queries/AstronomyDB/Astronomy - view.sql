use Astronomy
go

create view PlanetsView
as
select P_name, S_cnt, M_cnt from Planets P join (
	select S.P_id, S_cnt, M_cnt from (select P_id, count(S_id) as S_cnt from Satellites group by P_id) S join
	(select P_id, count(M_id) as M_cnt from Missions group by P_id) M on S.P_id = M.P_id
) J on P.P_id = J.P_id
go

select * from PlanetsView