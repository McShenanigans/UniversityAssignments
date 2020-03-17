use Astronomy
go

drop procedure deletePlanet

create procedure deletePlanet(@Name varchar(50)) as
begin
	declare @id int
	select top 1 @id = P_id from (select P_id from Planets where P_name = @Name) C
	delete from Crews where M_id = (select top 1 M_id from (select M_id from Missions where P_id = @id) C)
	delete from Missions where P_id = @id
	delete from Satellites where P_id = @id
	delete from Planets where P_id = @id
end
go

select * from Planets
select * from Satellites
exec deletePlanet 'Lada'
select * from Planets
select * from Satellites
