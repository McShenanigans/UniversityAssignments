use RailroadDB
go

insert into Stations (S_name) values
('Brasov'), ('Baicoi'), ('Cluj-Napoca'), ('Iasi'), ('Oradea'), ('Bacau'), ('Onesti')

select * from Stations

insert into TrainType (decription) values
('Regio'), ('Inter-regio'), ('Personal')

select * from TrainType

insert into Trains (T_type, T_name) values
(1, 'R10746'), (2, 'IR1746'), (2, 'IR1902'), (1, 'R10239'), (3, 'P696969')

select * from Trains

insert into TrainRoutes (T_id, R_name) values
(1,'Brasov -> Cluj-Napoca'),(2, 'National 1'),(3, 'National 2'),(4, 'Cluj-Napoca -> Bacau'),(5, 'Baicon -> Iasi')

select * from TrainRoutes

insert into StationsForRoute (R_id, S_id, ArrivalTime, DepartureTime) values
(2,1,'8:42:00','8:52:00'), (2,2,'9:42:00','9:52:00'), (2,3,'10:42:00','10:52:00'), (2,4,'11:42:00','11:52:00'), (2,5,'12:42:00','12:52:00'), (2,6,'13:42:00','13:52:00'), (2,7,'14:42:00','14:52:00'),
(3,1,'10:12:00','10:22:00'), (3,2,'11:12:00','11:22:00'), (3,3,'12:12:00','12:22:00'), (3,4,'13:12:00','13:22:00'), (3,5,'14:12:00','14:22:00'), (3,6,'15:12:00','15:22:00'), (3,7,'16:12:00','16:22:00'),
(1,1,'14:30:00','14:40:00'), (1,6,'15:30:00','15:40:00'), (1,3,'16:30:00','16:40:00'),
(4,3,'9:15:00','9:25:00'), (4,2,'10:15:00','10:25:00'), (4,7,'11:15:00','11:25:00'),(4,6,'12:15:00','12:25:00'),
(5,2,'7:42:00','7:52:00'), (5,1,'8:42:00','8:52:00'), (5,3,'9:42:00','9:52:00'), (5,4,'10:42:00','10:52:00')

select * from StationsForRoute