use Faculty;
go

drop database ForzaHorizon;
go

create database ForzaHorizon
go
use ForzaHorizon
go

create table players(
	P_id int primary key identity,
	Pname varchar(50)
)

create table tracks(
	T_id int primary key identity,
	T_name varchar(50),
	lenght int,
	T_type varchar(50)
)

create table beautySpots(
	BS_id int primary key identity,
	BS_name varchar(50)
)

create table clothes(
	Cl_id int primary key identity,
	P_id int foreign key references players(P_id),
	C_type varchar(50),
	C_color varchar(50)
)

create table accessories(
	A_id int primary key identity,
	P_id int foreign key references players(P_id),
	A_type varchar(50),
	A_color varchar(50)
)

create table stunts(
	S_id int primary key identity,
	S_type varchar(50),
	oneStar int,
	twoStars int,
	threeStars int
)

create table showcases(
	SC_id int primary key identity,
	SC_name varchar(50)
)

create table cars(
	C_id int primary key identity,
	make varchar(50),
	model varchar(50),
	modelYear int,
	color varchar(50),
	P_id int foreign key references players(P_id)
)

create table races(
	P_id int foreign key references players(P_id),
	T_id int foreign key references tracks(T_id),
	R_time float,
	score float,
	constraint pk_races primary key(P_id, T_id)
)

create table stuntRuns(
	S_id int foreign key references stunts(S_id),
	P_id int foreign key references players(P_id),
	constraint pk_stuntRuns primary key (S_id, P_id),
	score int,
	rating int check(rating = 1 or rating = 2 or rating = 3 or rating = 0)
)

create table visited(
	BS_id int foreign key references beautySpots(BS_id),
	P_id int foreign key references players(P_id),
	constraint pk_visited primary key (BS_id, P_id),
	V_date date
)

create table participated(
	SC_id int foreign key references showcases(SC_id),
	P_id int foreign key references players(P_id),
	constraint pk_participated primary key (SC_id, P_id),
	P_time float,
	P_score int
)
