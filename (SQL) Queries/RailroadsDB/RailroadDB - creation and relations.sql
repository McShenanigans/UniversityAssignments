use RailroadDB
go

create table TrainType(
	TT_id int primary key identity,
	decription varchar(50)
)

create table Stations(
	S_id int primary key identity,
	S_name varchar(50) unique
)

create table Trains(
	T_id int primary key identity,
	T_type int foreign key references TrainType(TT_id),
	T_name varchar(50)
)

create table TrainRoutes(
	R_id int primary key identity,
	T_id int foreign key references Trains(T_id),
	R_name varchar(50) unique,
)

create table StationsForRoute(
	R_id int foreign key references TrainRoutes(R_id),
	S_id int foreign key references Stations(S_id),
	constraint pk_sfr primary key(R_id, S_id),
	ArrivalTime time,
	DepartureTime time
)