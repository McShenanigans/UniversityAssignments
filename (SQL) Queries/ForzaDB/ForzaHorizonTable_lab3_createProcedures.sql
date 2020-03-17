use ForzaHorizon
go

/*creates a versionning table*/
create table VersionsStack(id int primary key, execProc nvarchar(50))
insert into VersionsStack(id, execProc) values (0,null)
go

create procedure popFromStack
as
begin
	declare @id int, @value nvarchar(50)
	select top 1 @id = id, @value = execProc from VersionsStack order by id desc
	if @id is null begin
		return
	end
	delete from VersionsStack where id=@id select @value
end
go

/*adds a new column 4-stars to stunts table*/
create procedure add4Stars
as
begin
	alter table stunts
	add fourStars int
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'add4Stars')
end
go

/* removes the 4-stars column from stunts table*/
create procedure remove4Stars
as
begin
	alter table stunts
	drop column fourStars
end
go

/*chenges the tipe of 4-stars column from int to float*/
create procedure modif4Stars
as
begin
	alter table stunts
	alter column fourStars float
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'modif4Stars')
end
go

/*undoes the modif4Stars procedures*/
create procedure modif4Stars_reverse
as
begin
	alter table stunts
	alter column fourStars int
end
go

/*creates a new table*/
create procedure createRammers
as
begin
	create table rammers(
		R_id int not null,
		R_name varchar(50) not null,
		Pid int not null,
		CNP varchar(50) not null
	)
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'createRammers')
end
go

/*adds a foreign key constraint for rammers table*/
create procedure connectRammer2Player
as
begin
	alter table rammers
	add constraint P_id foreign key(Pid) references players(P_id)
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'connectRammer2Player')
end
go

/*undoes connectRammers2Players*/
create procedure disconnectRammer
as
begin
	alter table rammers
	drop constraint P_id
end
go

/*Adds default constraint to rammers table*/
create procedure addDefaultContraint
as
begin
	alter table rammers
	add constraint D_name default 'Jackass' for R_name
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'addDefaultConstraint')
end
go

/*undoes addDefaultConstraint procedure*/
create procedure dropDefaultConstraint
as
begin
	alter table rammers
	drop constraint D_name
end
go

/*adds a primary key to rammers table*/
create procedure addPrimaryKey
as
begin
	alter table rammers
	add constraint P_name primary key(R_name)
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'addPrimaryKey')
end
go

/*undoes the addPrimaryKey procedure*/
create procedure dropPrimaryKey
as
begin
	alter table rammers
	drop constraint P_name
end
go

/*adds a candidate key to the rammers table*/
create procedure addCandidateKey
as
begin
	alter table rammers
	add constraint numConstr unique(CNP)
	declare @id int
	select top 1 @id = id from VersionsStack order by id desc
	insert into VersionsStack (id, execProc) values (@id + 1, 'addCandidateKey')
end
go

/*undoes the addCandidateKey procedure*/
create procedure dropCandidateKey
as begin
	alter table rammers
	drop constraint numConstr
end
go

/*undoes createRammers procedure*/
create procedure dropRammers
as
begin
	drop table rammers
	declare @cVersion int
end
go

create procedure restoreTable(@version int) as
Begin
	declare @cVersion int, @lastProc nvarchar(50)
	select top 1 @cVersion = id from VersionsStack order by id desc
	while @cVersion != 0 and @cVersion > @version
	begin
		select top 1 @lastProc = execProc from VersionsStack order by id desc
		if @lastProc = 'addCandidateKey' begin
			begin try
				exec dropCandidateKey
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		else if @lastProc = 'addPrimaryKey' begin
			begin try
				exec dropPrimaryKey
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		 else if @lastProc = 'addDefaultConstraint' begin
			begin try
				exec dropDefaultConstraint
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		else if @lastProc = 'connectRammer2Player' begin
			begin try
				exec disconnectRammer
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		else if @lastProc = 'createRammers' begin
			begin try
				exec dropRammers
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		else if @lastProc = 'modif4Stars' begin
			begin try
				exec modif4Stars_reverse
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		else if @lastProc = 'add4Stars' begin
			begin try
				exec remove4Stars
				exec popFromStack
			end try
			begin catch
				return
			end catch
		end
		select top 1 @cVersion = id from VersionsStack order by id desc
	end
	/*select @cVersion = sum(cVer) from versionningTable
	while @cVersion > @version
	begin
		begin try
			if @version < 7
			begin
				execute dropCandidateKey
			end
		end try
		begin catch
		end catch

		begin try
			if @version < 6
			begin
				execute dropPrimaryKey
			end
		end try
		begin catch
		end catch

		begin try
			if @version < 5
			begin
				execute dropDefaultConstraint
			end
		end try
		begin catch
		end catch

		begin try
			if @version < 4
			begin
				execute disconnectRammer
			end
		end try
		begin catch
		end catch

		begin try
			if @version < 3
			begin
				execute dropRammers
			end
		end try
		begin catch
		end catch

		begin try
			if @version < 2
			begin
				execute modif4Stars_reverse
			end
		end try
		begin catch
		end catch

		begin try
			if @version < 1
			begin
				execute remove4Stars
			end
		end try
		begin catch
		end catch

		select @cVersion = sum(cVer) from versionningTable
	end*/
End