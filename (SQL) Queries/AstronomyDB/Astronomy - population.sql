use Astronomy
go

delete from Crews
delete from Astronauts
delete from Missions
delete from Satellites
delete from Planets

insert into Astronauts (A_id, A_name, A_gender, A_birthday) values
(1,'Boris', 'male', '1950-05-15'),
(2,'Anatoly', 'male', '1960-06-07'),
(3,'Vadim', 'female', '1969-06-09')

select * from Astronauts

insert into Planets (P_id, P_name, P_description, P_distance) values
(1,'Lada', 'Contains reliable soviet technology', 1045106),
(2,'Astronomya', 'Contains valuable resources for space exploration', 945623),
(3,'Boiler', 'very hot - may boil blood. Cauntion is advised', 20654)

select * from Planets

insert into Satellites (S_id, P_id, S_name, S_diameter) values
(1,1,'Gopnik1', 1000),
(2,1,'Lada Mini', 1942),
(3,2,'Lentila', 1650),
(4,3,'The kitchen', 500)

select * from Satellites

insert into Missions (M_id, P_id, M_start, M_end) values
(1,1, '2015-03-05', '2016-05-01'),
(2,2, '2013-06-01', '2018-08-16'),
(3,3, '2018-01-26', '2020-01-16')

select * from Missions

insert into Crews (A_id, M_id) values
(1,1), (1,2), (1,3),
(2,2), (2,3),
(3,1), (3,3)

select * from Crews