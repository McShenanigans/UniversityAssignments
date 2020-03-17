use ForzaHorizon
go

insert into players (Pname)
values ('TeHash007'), ('GigiMos'), ('Edi_Flinstone')

insert into cars (make, model, modelYear, color, P_id)
values ('Ford', 'Mustang GT350R', 2016, 'red', 1),
('Chevrolet', 'Camaro ZR1', 2015, 'yellow', 1),
('Dodge', 'Challenger SRT Demon', 2018, 'red', 2),
('AMC', 'Rebel', 1970, 'white', 3),
('Dacia', 'Lodgy', 2015, null, 3)

insert into tracks (t_name,lenght,T_type)
values ('The Goliath', 25, 'road'),
('The Gauntlet', 19, 'rally'),
('The Collossus', 30,'road'),
('The Marathon', 17, 'street'),
('The Titan', 19, 'off-road')

insert into showcases (SC_name)
values ('The Halo Experience'),
('The Delta Wing'),
('Horizon Motocross'),
('The Flying Scotsman'),
('Behemoth'),
('The Racing Dacia'),
('Trabant Mania')

insert into stunts (S_type, oneStar, twoStars, threeStars)
values ('danger zone', 140, 200, 250),
('drift zone', 20000, 40000, 50000),
('danger zone', 100, 140, 200),
('spped trap', 200, 275, 350),
('speed zone', 140, 160, 200)

insert into participated (SC_id, P_id, P_time, P_score)
values (1, 1, 5.35, 13000),
(2,1,4.32, 16000),
(3,2,3.12, 10000)

insert into stuntRuns (S_id, P_id, score, rating)
values (1,2,54000,3),
(2,2,24000,1),
(3,2,36000, 1)

insert into races (P_id, T_id, R_time, score)
values (1,1,7.5,60000),
(2,1,8.3, 48000),
(1,2,9.7,70000),
(2,2,16.3, 15000),
(3,1,10.2, 19950)

insert into beautySpots (BS_name) values
('Uffington White Horse'),
('Whitewater Falls'),
('Mortimer Gardens'),
('Arthurs Seat')

insert into visited (BS_id, P_id) values
(1,1), (1,2), (1,3), (2,2), (2,1), (3,3)

insert into clothes (P_id, C_type, C_color) values 
(1, 'Tshirt', 'red'), (1, 'Jeans', 'blue'), (1, 'Trianers', 'black'), (1, 'Pea coat', 'black'),
(2, 'Shirt', 'white'), (2, 'Cargo pants', 'green'), (2, 'slicks', 'red'),
(3, 'Tshirt', 'blue'), (3, 'Jeans', 'black'), (2, 'trainers', 'white')

insert into accessories (P_id, A_type, A_color) values
(1, 'glasses', 'smoked'),
(2, 'hat', 'red'), (2, 'glasses', 'pink')

select * from cars
select * from players
select * from tracks
select * from showcases
select * from stunts
select * from participated
select * from stuntRuns
select * from races
select * from beautySpots
select * from visited
select * from accessories
select * from clothes

/*updates distance to 15 to all rally/road tracks with length <= 20*/
update tracks
set lenght=15 where lenght<=20 and T_type like 'r%'
select * from tracks

/*sets color to green to all Lamborghinis, yellow cars and white cars*/
update cars
set color='green' where color in ('yellow', 'white') or make='Lamborghini'
select * from cars

/*sets name to "fred Flinstone" to all players with id between 3 and 4*/
update players
set Pname='Fred Flintone' where P_id between 3 and 4
select * from players

/*deletes all cars with no color*/
delete from cars 
where color is null
select * from cars

/*deletes all showcases that end with "Dacia" or that start with "Trabant"*/
delete from showcases
where SC_name like '%Dacia' or SC_name like 'Trabant%'
select * from showcases

/*a*/
/*union of all showcases that start with The or that end with th and all rally tracks*/
select distinct SC_name from showcases where SC_name like 'The%' or SC_name like '%th'
union
select T_name as SC_name from tracks where T_type = 'rally'

/*union off all road tracks and all danger zones and drift zones*/
select distinct T_name from tracks where T_type='road'
union all
select S_type from stunts where S_type = 'danger zone' or S_type = 'drift zone'

/*b*/
/*top 2 players with a score > 10000 in stuntRuns and that got a score of ... in schowcase participations*/
select top 2 P_id from stuntRuns where score > 10000
intersect
select P_id from participated where P_score in (5000, 10000, 6500, 13000)

/*top 2 players with cars that got over 20000 points in races*/
select top 2 P_id from cars
intersect
select P_id from races where score > 20000

/*c*/
/*all non-rally and non-offroad tracks with length < 20, ordered in descending order by name*/
select T_name from tracks where T_type not in ('rally', 'off-road')
except
select T_name from tracks where lenght<20
order by T_name desc

/*all distinct cars made before 2000 and that are made by AMC or Chevrolet, ordered ascending by make*/
select distinct make, model from cars where modelYear < 2000
except
select make, model from cars where make not in ('AMC', 'Chevrolet')
order by make asc

/*d*/
/*all distinct tracks on which players who visited beautyspots raced on*/
select distinct T_name, T_type from tracks
inner join races on tracks.T_id = races.T_id
inner join visited on visited.P_id = races.P_id

/*all distinct players that raced and that have done stunts*/
select distinct races.P_id from races
full join stuntRuns
on races.P_id = stuntRuns.P_id

/*all distinct players that participated in showcases and that visited beautyspots*/
select distinct participated.P_id from participated
left join visited
on participated.P_id = visited.P_id

/*all players that wear both clothes and accessories*/
select distinct clothes.P_id from clothes
right join accessories
on clothes.P_id = accessories.P_id

/*e*/
/*all cars that were driven in races and got over 25000 points*/
select make, model, modelYear from cars
where cars.P_id in (
	select P_id from races 
	where score > 25000
)

/*all cars whose owners wear glasses and have participated in showcases*/
select make, model, modelYear from cars
where cars.P_id in ( 
	select P_id from participated 
	where P_id in (
		select P_id from accessories 
		where A_type = 'glasses'
	)
)

/*f*/
/*all players who own a Mustang*/
select P_id from players where exists (select P_id from cars where model like 'Mustang%')

/*all playres that got over 20000 points in races*/
select P_id from players where exists (select P_id from races where score > 20000)

/*g*/
/*all Fords*/
select make1, model1, modelYear1 from (
	select make as make1, model as model1, modelYear as modelYear1 
	from cars 
	where make = 'Ford') as cars1

/*all tracks with length > 20*/
select Tname, Ttype from (
	select T_name as Tname, T_type as Ttype 
	from tracks 
	where lenght > 20) as tracks1

/*h*/
/*number of cars of each model*/
select count(C_id), model from cars
group by model

/*avrage length of road and street tracks*/
select avg(lenght), T_type from tracks
group by T_type having T_type in ('road', 'street')

/*total score of each player that wears a hat*/
select sum(score), P_id from races
group by P_id having P_id in (select P_id from accessories where A_type = 'hat')

/*max race score of players with over 50000 points in stuntRuns*/
select max(score), P_id from races
group by P_id having P_id in (select P_id from stuntRuns where score > 50000)

/*i*/
/*all stuntRuns scores that are lower than the lowest score in races*/
select score from stuntRuns
where score < all (select score from races)
/*RW (aggragate): all stuntRuns scores that are lower than the lowest score in races*/
select score from stuntRuns
where score < all (select min(score) from races)

/*all the participations scores that are lower than all race scores of on track 1*/
select P_score from participated
where P_score < all (select score from races where T_id = 1)
/*RW (not in): all the participations scores that are lower than all race scores of on track 1*/
select P_score from participated
where P_score < all (select score from races where T_id not in (2,3,4,5,6,7,8,10,9))

/*all colors which's color coresponds to the owner's tshirt color*/
select color from cars
where color = any (select C_color from clothes where C_type = 'Tshirt')
/*RW (not in): all colors which's color coresponds to the owner's tshirt color*/
select color from cars
where color = any (select C_color from clothes where C_type not in ('Jeans', 'Shirt', 'trainers', 'Pea coat', 'Cargo pants', 'slicks', 'Trainers'))

/*all stuntRuns scores greater than the highest score required for a 3-star stunt rating*/
select P_id from stuntRuns
where score > any (select threeStars from stunts)
/*RW (aggregate): all stuntRuns scores greater than the highest score required for a 3-star stunt rating*/
select P_id from stuntRuns
where score > any (select max(threeStars) from stunts)