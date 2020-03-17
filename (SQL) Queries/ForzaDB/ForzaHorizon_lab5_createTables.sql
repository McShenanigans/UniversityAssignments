use ForzaHorizon
go

drop table races_1
drop table cars_1
drop table players_1


create table players_1(
	P_id int primary key identity,
	P_name varchar(50),
	P_ranking int unique
)

create table cars_1(
	C_id int primary key identity,
	C_make varchar(50),
	C_model varchar(50),
	C_year int
)

create table races_1(
	R_id int primary key identity,
	P_id int foreign key references players_1(P_id),
	C_id int foreign key references cars_1(C_id),
	R_seconds int
)