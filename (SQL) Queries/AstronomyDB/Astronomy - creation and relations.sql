use Astronomy
go

drop table Crews
drop table Missions
drop table Satellites
drop table Astronauts
drop table Planets

create table Astronauts(
	A_id int primary key,
	A_name varchar(50),
	A_gender varchar(10),
	A_birthday date
)

create table Planets(
	P_id int primary key,
	P_name varchar(50) unique,
	P_description varchar(900),
	P_distance int
)

create table Satellites(
	S_id int primary key,
	P_id int foreign key references Planets(P_id),
	S_name varchar(50),
	S_diameter int
)

create table Missions(
	M_id int primary key,
	P_id int foreign key references Planets(P_id),
	M_start date,
	M_end date,
)

create table Crews(
	A_id int foreign key references Astronauts(A_id),
	M_id int foreign key references Missions(M_id),
	constraint pk_crews primary key (A_id, M_id)
)