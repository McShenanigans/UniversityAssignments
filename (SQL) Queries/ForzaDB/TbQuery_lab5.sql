use ForzaHorizon
go

insert into cars_1 (C_make, C_model, C_year)
values ('Ford', 'Mustang GT350R', 2016),
('Chevrolet', 'Camaro ZR1', 2015),
('Dodge', 'Challenger SRT Demon', 2016),
('AMC', 'Rebel', 1970),
('Dacia', 'Lodgy', 2015),
('Ford', 'mustang', 2006),
('Ford', 'mustang', 1999)

declare @id int

select top 1 @id = C_id from cars_1 order by C_id desc
while @id < 1000 begin
		if @id % 7 = 0
			insert into cars_1 values ('Ford', 'mustang', 2013)
		else
			insert into cars_1 values ('Chevy', 'camaro', 2010)
		select top 1 @id = C_id from cars_1 order by C_id desc
end

select * from cars_1

begin try
	drop table cars_1_copy
end try
begin catch
end catch

create table cars_1_copy(
	C_id int primary key identity,
	C_make varchar(50),
	Cmodel varchar(50),
	C_year int
)

insert into cars_1_copy (C_make, Cmodel, C_year)
values ('Ford', 'Mustang GT350R', 2016),
('Chevrolet', 'Camaro ZR1', 2015),
('Dodge', 'Challenger SRT Demon', 2016),
('AMC', 'Rebel', 1970),
('Dacia', 'Lodgy', 2015),
('Ford', 'mustang', 2006),
('Ford', 'mustang', 1999)

select top 1 @id = C_id from cars_1_copy order by C_id desc
while @id < 1000 begin
		if @id % 7 = 0
			insert into cars_1_copy values ('Ford', 'mustang', 2013)
		else
			insert into cars_1_copy values ('Chevy', 'camaro', 2010)
		select top 1 @id = C_id from cars_1_copy order by C_id desc
end

select * from cars_1_copy

if exists (select name from sys.indexes where name = N'N_idx_Cmodel')
	drop index N_idx_Cmodel on cars_1_copy
go

create nonclustered index N_idx_Cmodel on cars_1_copy(Cmodel)
go



select * from cars_1 where C_model = 'mustang'
select * from cars_1_copy where Cmodel = 'mustang'