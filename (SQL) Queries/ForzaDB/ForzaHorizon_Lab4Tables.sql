use ForzaHorizon
go
/*
drop table TestRunTables_lab4
drop table TestTables_lab4
drop table Testviews_lab4
drop table TestRunViews_lab4
drop table Tables_lab4
drop table Tests_lab4
drop table Views_lab4
drop table TestRuns_lab4
*/

create table Tables_lab4(
	TableID int primary key,
	T_Name varchar(50)
)

create table Tests_lab4(
	TestID int primary key,
	Test_Name varchar(50)
)

create table Views_lab4(
	ViewID int primary key,
	V_Name varchar(50)
)

create table TestRuns_lab4(
	TestRunID int primary key,
	TR_Description varchar(50),
	StartAt date,
	EndAt date
)

create table TestRunTables_lab4(
	TestRunID int foreign key references TestRuns_lab4(TestRunID),
	TableID int foreign key references Tables_lab4(TableID),
	constraint pk_TestRunTables_lab4 primary key (TestRunID, TableID),
	StartAt date,
	EndAt date
)

create table TestTables_lab4(
	TestID int foreign key references Tests_lab4(TestID),
	TableID int foreign key references Tables_lab4(TableID),
	constraint pk_TestTables_lab4 primary key (TestID, TableID),
	StartAt date,
	EndAt date
)

create table TestViews_lab4(
	TestID int foreign key references Tests_lab4(TestID),
	ViewID int foreign key references Views_lab4(ViewID),
	constraint pk_TestViews_lab4 primary key (TestID, ViewID)
)

create table TestRunViews_lab4(
	TestRunID int foreign key references TestRuns_lab4(TestRunID),
	ViewID int foreign key references Views_lab4(ViewID),
	constraint pk_TestRunViews_lab4 primary key (TestRunID, ViewID),
	StartAt date,
	EndAt date
)