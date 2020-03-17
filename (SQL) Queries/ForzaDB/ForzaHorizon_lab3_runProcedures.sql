use ForzaHorizon
go

select * from stunts
execute add4Stars
execute modif4Stars

execute restoreTable @version = 0

execute createRammers
select * from rammers
execute connectRammer2Player
execute addDefaultContraint
execute addPrimaryKey
execute addCandidateKey

execute restoreTable @version = 1

execute restoreTable @version = 2

select * from VersionsStack