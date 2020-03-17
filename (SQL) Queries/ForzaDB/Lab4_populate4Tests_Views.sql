use ForzaHorizon
go

create view CarsView
as
select make, model from cars where modelYear between 1990 and 2020
go

create view playersTracksView
as
select p.Pname, t.T_name, t.lenght from tracks t, players p where t.T_type like 'rally' and p.P_id between 1 and 30
go

create view carOwnerships
as
select players.Pname, count(model) as owns from cars join players on cars.P_id = players.P_id group by Pname
go

insert into [Tables] values ('cars'), ('players'), ('races')
insert into [Views] values ('CarsView'), ('playersTracksView'), ('carOwnerships')

select * from [Tables]
select * from [Views]

insert into [Tests] values ('deleteTable100'),('insertTable1000'), ('insertTable100'), ('deleteTable1000'),('select_view')
insert into [TestViews] values (1,2), (1,1), (1,3)
insert into [TestTables] values
(1,1,100,1), (1,2,100,1), (1,3,100,1),
(2,1,1000,1),(2,2,1000,1),(2,3,1000,1),
(3,1,100,1),(3,2,100,1),(3,3,100,1),
(4,1,1000,1),(4,2,1000,1),(4,3,1000,1)
go

drop procedure insertRows_players
go

create procedure insertRows_players @TestID int as
declare @nrOfRows int
declare @newItem varchar(50)
declare @n int
declare @n1 int
select top 1 @nrOfRows = NoOfRows from TestTables where TestID = @TestID
select top 1 @n = P_id from players order by P_id desc
set @n1 = @n
while @n1 <= @nrOfRows + @n begin
	set @newItem = 'player' + convert(varchar(5), @n1)
	insert into players values (@newItem)
	set @n1 = @n1+1
end
go

drop procedure deleteRows_players
go

create procedure deleteRows_players @TestId int as
declare @nrOfRows int
select top 1 @nrOfRows = NoOfRows from TestTables where TestID = @TestId
delete top(@nrOfRows) from players where Pname like 'player%'
go

drop procedure insertRows_cars
go

create procedure insertRows_cars @TestId int as
declare @nrOfRows int
select @nrOfRows = NoOfRows from [TestTables] order by NoOfRows desc
declare @n int
declare @n1 int
select top 1 @n1 = C_id from cars order by C_id desc
declare @newItem varchar(50)
set @n = @n1
while @n < @nrOfRows + @n1 begin
	set @newItem = 'car' + convert(varchar(5), @n)
	insert into cars (C_id, make, P_id) values (@n, @newItem, 1)
	set @n = @n+1
end
go

drop procedure deleteRows_cars
go

create procedure deleteRows_cars @TestId int as
declare @nrOfRows int
select top 1 @nrOfRows = NoOfRows from [TestTables] where TestID = @TestId
delete top(@nrOfRows) from cars where make like 'car%'
go

drop procedure insertRows_races
go

create procedure insertRows_races @TestId int as
declare @nrOfRows int
select top 1 @nrOfRows = NoOfRows from [TestTables] where TestId = @TestId

declare @nrOFPlayers int
select top 1 @nrOfPlayers = P_id from players order by P_id desc
if @nrOFPlayers < @nrOfRows
	exec insertRows_players @nrOfRows

declare @nrOfTracks int
select top 1 @nrOfTracks = T_id from tracks order by T_id desc
while @nrOfTracks < @nrOfRows begin
	insert into tracks(T_id, T_name, lenght, T_type) values (@nrOfTracks+1,'track',1,'rally')
	set @nrOfTracks = @nrOfTracks+1
end

declare @n int
set @n = 1
while @n < @nrOfRows begin
	insert into races (P_id, T_id, score) values (@n,@n,-1)
	set @n = @n+1
end
go

drop procedure deleteRows_races
go

create procedure deleteRows_races @TestId int as
declare @nrOfRows int
select top 1 @nrOfRows = NoOfRows from [TestTables] where TestID = @TestId
delete top(@nrOfRows) from races where score = -1
go

drop procedure Test1000players
go

create procedure Test1000players as
declare @start datetime
declare @end datetime
declare @view datetime
set @start = getdate()
exec insertRows_players 5
exec deleteRows_players 11
set @end = getdate()
select * from playersTracksView
set @view  = getdate()
insert into TestRuns values ('add+remove+view 1000 players',@start, @view)
declare @id int
select top 1 @id=TestRunId from TestRuns where Description = 'add+remove+view 1000 players'
insert into TestRunTables values (@id,@id+1,@start,@end)
insert into TestRunViews values (@id,@id+1,@end,@view)
go

drop procedure Test100Cars
go

create procedure Test100Cars as
declare @start datetime
declare @end datetime
declare @view datetime
set @start = getdate()
exec insertRows_cars 7
exec deleteRows_cars 1
set @end = getdate()
select * from CarsView
set @view = getdate()
insert into Testruns values ('add+remove+view 100 cars',@start, @view)
declare @id int
select top 1 @id=TestRunId from TestRuns where Description = 'add+remove+view 100 cars'
insert into TestRunTables values (@id,@id+1,@start,@end)
insert into TestRunViews values (@id,@id+1,@end,@view)
go

drop procedure Test1000races
go

create procedure Test1000races as
declare @start datetime
declare @end datetime
declare @view datetime
set @start = getdate()
exec insertRows_races 6
exec deleteRows_races 12
set @end = getdate()
select * from carOwnerships
set @view = getdate()
insert into Testruns values ('add+remove+view 1000 races',@start, @view)
declare @id int
select top 1 @id=TestRunId from TestRuns where Description = 'add+remove+view 1000 races'
insert into TestRunTables values (@id,@id+1,@start,@end)
insert into TestRunViews values (@id,@id+1,@end,@view)
go

exec Test1000players
select* from TestRuns
select* from TestRunTables
select* from TestRunViews
select* from TestTables

exec Test1000races
select* from TestRuns
select* from TestRunTables
select* from TestRunViews
select* from TestTables

exec Test100cars
select* from TestRuns
select* from TestRunTables
select* from TestRunViews
select* from TestTables