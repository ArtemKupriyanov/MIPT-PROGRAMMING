﻿drop table Areas
drop table Parking
drop table Clients
drop table Cars
drop table Tariffs
drop table TariffData
drop table Docs
drop table Subscriptions
drop table ParkingData

CREATE TABLE Areas (AreaID int primary key, Area nvarchar(50), CostPerHour float)
CREATE TABLE Parking (ParkingNo int primary key, Address nvarchar(50), AreaID int, Num int)
CREATE TABLE Clients (ClientID int primary key, ClientsPersNum nvarchar(10), Surname nvarchar(max), Name nvarchar(max), PhoneNumber nvarchar(20))
CREATE TABLE Cars (CarID int primary key, RegNo nvarchar(10))
CREATE TABLE Tariffs (TariffID int primary key, Tariff nvarchar(max), CostPerMonth float)
CREATE TABLE TariffData (TariffID int, AreaID int, primary key(TariffID, AreaID))
CREATE TABLE Docs (DocID int primary key, Date_of_doc datetime, ClienID int, Total float)
CREATE TABLE Subscriptions (SubscrID int primary key, DocID int, CarID int, TariffID int, ValidityMonth date, Cost float)
CREATE TABLE ParkingData (ID int primary key, ParkingNo int, DateTime_of_scan datetime, RegNo nvarchar(10))

INSERT INTO Areas VALUES
(1,'Area 1',40),
(2,'Area 2',80),
(3,'Area 3',120),
(4,'Area 4',250)

INSERT INTO Parking VALUES
(1,'Street 1',1,10),
(2,'Street 2',1,20),
(3,'Street 5',2,50),
(4,'Street 6',2,60),
(5,'Street 9',3,100),
(6,'Street 10',3,5),
(7,'Street 13',4,10),
(8,'Street 14',4,20)

INSERT INTO Tariffs VALUES
(1,'Easy',8000),
(2,'Medium',16000),
(3,'Hard',24000),
(4,'Super Hard',50000)

INSERT INTO TariffData VALUES
(1,1),
(2,1),
(2,2),
(3,1),
(3,2),
(3,3),
(4,1),
(4,2),
(4,3),
(4,4)

INSERT INTO Clients VALUES 
(1,'zp190rt','Smith','John','8-800-650-05-43'),
(2,'xt67e8r','Ivanov','Maxim','8-800-112-45-15'),
(3,'96rt1we','Nosoff','Grace','8-800-777-77-88'),
(4,'4xp9jr5','Kim','Yen','8-800-982-16-95')

INSERT INTO Cars VALUES
(1,'A190AA190'),
(2,'A010BC777'),
(3,'T777AO99'),
(4,'C555CC777'),
(5,'C725AE190'),
(6,'B999BB777')

INSERT INTO Docs VALUES
(1,'20160825',1,8000),
(2,'20160826',2,16000),
(3,'20160827',4,90000),
(4,'20160915',2,32000),
(5,'20160920',3,24000),
(6,'20160925',4,50000),
(7,'20161001',1,16000),
(8,'20161029',3,50000)

INSERT INTO Subscriptions VALUES
(1,1,1,1,'20160901',8000),
(2,2,2,2,'20160901',16000),
(3,3,4,1,'20160901',8000),
(4,3,4,1,'20161001',8000),
(5,3,4,3,'20161101',24000),
(6,3,5,4,'20160901',50000),
(7,4,2,2,'20161001',16000),
(8,4,2,2,'20161101',16000),
(9,5,3,3,'20161001',24000),
(10,6,5,4,'20161001',50000),
(11,7,1,2,'20161101',16000),
(12,8,3,4,'20161101',50000)

INSERT INTO ParkingData VALUES
(1,1,'20160901 10:00:00','A190AA190'),
(2,1,'20160901 10:00:00','A010BC777'),
(3,1,'20160901 10:00:00','T777AO99'),
(4,1,'20160901 15:00:00','A190AA190'),
(5,1,'20160901 15:00:00','A010BC777'),
(6,1,'20160901 15:00:00','C555CC777'),
(7,1,'20160901 15:00:00','T777AO99'),
(8,1,'20160901 18:00:00','A190AA190'),
(9,2,'20160902 12:00:00','A190AA190'),
(10,2,'20160902 12:00:00','A010BC777'),
(11,2,'20160902 15:00:00','A010BC777'),
(12,2,'20160902 15:00:00','B999BB777'),
(13,2,'20160902 15:00:00','C725AE190'),
(14,2,'20160902 19:00:00','A190AA190'),
(15,2,'20160902 19:00:00','B999BB777'),
(16,3,'20160903 15:00:00','B999BB777'),
(17,3,'20160903 15:00:00','C555CC777'),
(18,3,'20160903 15:00:00','C725AE190'),
(19,4,'20160904 13:30:00','T777AO99'),
(20,4,'20160904 13:30:00','A010BC777'),
(21,5,'20160905 16:00:00','B999BB777'),
(22,5,'20160905 16:00:00','C555CC777'),
(23,5,'20160906 9:00:00','B999BB777'),
(24,5,'20160906 9:00:00','C555CC777'),
(25,5,'20160906 10:00:00','B999BB777'),
(26,5,'20160906 10:00:00','C555CC777'),
(27,6,'20160909 15:00:00','A010BC777'),
(28,7,'20160910 12:00:00','A010BC777'),
(29,1,'20160915 12:00:00','A010BC777'),
(30,1,'20160915 12:00:00','C555CC777'),
(31,2,'20160916 10:00:00','A010BC777'),
(32,2,'20160916 10:00:00','B999BB777'),
(33,2,'20160916 10:00:00','C725AE190'),
(34,3,'20160918 15:00:00','B999BB777'),
(35,3,'20160918 15:00:00','C555CC777'),
(36,3,'20160918 20:00:00','A190AA190'),
(37,3,'20160918 20:00:00','C725AE190'),
(38,3,'20160918 20:00:00','B999BB777'),
(39,4,'20160919 12:30:00','T777AO99'),
(40,4,'20160919 12:30:00','B999BB777'),
(41,4,'20160919 12:30:00','A010BC777'),
(42,4,'20160919 19:30:00','T777AO99'),
(43,4,'20160919 19:30:00','A010BC777'),
(44,4,'20160919 19:30:00','B999BB777'),
(45,5,'20160920 12:00:00','B999BB777'),
(46,5,'20160920 12:00:00','C555CC777'),
(47,5,'20160920 13:00:00','C725AE190'),
(48,6,'20160924 12:00:00','C725AE190'),
(49,6,'20160924 12:00:00','C555CC777'),
(50,6,'20160924 18:00:00','A010BC777'),
(51,6,'20160924 18:00:00','C725AE190'),
(52,6,'20160924 18:00:00','C555CC777'),
(53,7,'20160925 14:00:00','A010BC777'),
(54,7,'20160925 14:00:00','B999BB777'),
(55,7,'20160925 15:00:00','C555CC777'),
(56,8,'20160928 14:00:00','A190AA190'),
(57,8,'20160928 15:00:00','A190AA190'),
(58,1,'20161001 9:00:00','A010BC777'),
(59,1,'20161001 9:00:00','T777AO99'),
(60,1,'20161001 9:00:00','A190AA190'),
(61,2,'20161002 12:00:00','A010BC777'),
(62,2,'20161002 12:00:00','B999BB777'),
(63,2,'20161002 12:00:00','C725AE190'),
(64,3,'20161003 15:00:00','C555CC777'),
(65,3,'20161003 15:00:00','A190AA190'),
(66,3,'20161003 15:00:00','C725AE190'),
(67,3,'20161003 15:00:00','B999BB777'),
(68,3,'20161003 17:00:00','C555CC777'),
(69,3,'20161003 17:00:00','C725AE190'),
(70,3,'20161003 17:00:00','B999BB777'),
(71,4,'20161005 11:35:00','T777AO99'),
(72,4,'20161005 11:35:00','B999BB777'),
(73,4,'20161005 11:35:00','A010BC777'),
(74,4,'20161005 12:00:00','T777AO99'),
(75,4,'20161005 12:00:00','B999BB777'),
(76,5,'20161006 16:40:00','B999BB777'),
(77,5,'20161006 17:00:00','C555CC777'),
(78,6,'20161009 18:00:00','A010BC777'),
(79,7,'20161010 13:45:00','A010BC777'),
(80,7,'20161010 13:45:00','C555CC777'),
(81,7,'20161010 18:45:00','A010BC777'),
(82,8,'20161012 15:00:00','A190AA190'),
(83,5,'20161020 12:00:00','B999BB777'),
(84,5,'20161020 12:00:00','C555CC777'),
(85,5,'20161020 12:00:00','C725AE190'),
(86,4,'20161021 18:00:00','T777AO99'),
(87,4,'20161021 18:00:00','A010BC777'),
(88,4,'20161021 18:20:00','T777AO99'),
(89,6,'20161024 12:00:00','A010BC777'),
(90,6,'20161024 12:00:00','C725AE190'),
(91,6,'20161024 13:15:00','C725AE190'),
(92,7,'20161025 15:00:00','B999BB777'),
(93,7,'20161025 15:00:00','A010BC777'),
(94,7,'20161025 15:30:00','B999BB777'),
(95,8,'20161028 15:00:00','C725AE190'),
(96,8,'20161028 16:00:00','C725AE190'),
(97,8,'20161112 15:00:00','A190AA190'),
(98,8,'20161113 11:00:00','C725AE190'),
(99,8,'20161113 18:00:00','C725AE190'),
(100,8,'20161113 20:00:00','C725AE190')

--1
--комментарий преподавателя:
--Значит, что сгруппировать нужно по зоне и по месяцу на который куплен абонемент.
--Независимо от даты счета – имеется в виду, что неважно, когда выписан счет, главное, на какой месяц куплен абонемент.
select AreaID, month(ValidityMonth) as month_, count(SubscrID) as cnt, sum(Cost) as sum_ from 
Subscriptions
inner join
TariffData
on TariffData.TariffID = Subscriptions.TariffID
group by AreaID, month(ValidityMonth)

--2
select ResponceTableForJoin.*, Parking.Num from
(
select ParkingNo, date_, hour_, COUNT(*) as cnt_now from
(
select distinct ParkingNo, convert(date, DateTime_of_scan) as date_,
datepart(hour, DateTime_of_scan) as hour_, RegNo 
from 
ParkingData
) as ResponceTableForGroupBy
group by ParkingNo, date_, hour_
) as ResponceTableForJoin
inner join
Parking
on Parking.ParkingNo = ResponceTableForJoin.ParkingNo
--3  знаю, что можно сделать много проще, но так проверено=)
--по поводу формулировки - считаю рейтинг как на лекциях (т.е. если 2 строки равны по рейтингу
--, то присваиваю им максимальное значение). Из последней лекции я понял именно это...
select TableForRating1.ParkingNo, TableForRating1.cntRegNO, count(TableForRating2.ParkingNo) as Rating from
(
select ParkingNo, count(RegNo) as cntRegNO from
(
select distinct ParkingNo, RegNo 
from ParkingData
) as distinctRegNo
group by ParkingNo
) as TableForRating1
inner join
(
select ParkingNo, count(RegNo) as cntRegNO from
(
select distinct ParkingNo, RegNo 
from ParkingData
) as distinctRegNo
group by ParkingNo
) as TableForRating2
on
TableForRating1.cntRegNO <= TableForRating2.cntRegNO
group by TableForRating1.ParkingNo, TableForRating1.cntRegNO

--4) Ноября в данных нет(  => в таблице одно нули, потому что никто ничего не оплачивал
select Clients.ClientID, isnull(sum(cost), 0) as costOnMonth from 
Clients
left join
(
select Subscriptions.DocID, Cost, Date_of_doc, ClienID as ClientID from
Subscriptions
inner join
Docs
on Subscriptions.DocID = Docs.DocID
where convert(date, Date_of_doc) >= '20161101' and convert(date, Date_of_doc) <= '20161130'
) as Tright
on Clients.ClientID = Tright.ClientID
group by Clients.ClientID

--5)
select TariffID from Tariffs
except
select TariffID from 
Docs
inner join
Subscriptions
on Docs.DocID = Subscriptions.DocID
where Date_of_doc >= '20161001'

--6) все уникальные покупки абониментов - покупки после сентября = покупки до сентября включительно
--???
--PROFIT
select distinct Cars.CarID, ClientID from
Cars
inner join
(
select Subscriptions.*, Date_of_doc, ClienID as ClientID, Total from
Subscriptions
inner join
Docs
on Docs.DocID = Subscriptions.DocID
) as T1
on Cars.CarID = T1.CarID 
except
select distinct Cars.CarID, ClientID from
Cars
inner join
(
select Subscriptions.*, Date_of_doc, ClienID as ClientID, Total from
Subscriptions
inner join
Docs
on Docs.DocID = Subscriptions.DocID
) as T1
on Cars.CarID = T1.CarID
where ValidityMonth > '20161001'

--7)
select ScheduledPark.*, AreasDescr.AreaSize, cast(ScheduledParking as float) /AreasDescr.AreaSize as AreaLoad from
(
select Areas.AreaID, count(*) as ScheduledParking from
Areas
inner join
(
select TariffData.TariffID, AreaID from
(
select * from Subscriptions
where ValidityMonth >= '20161101' and ValidityMonth <= '20161130'
) as T1
inner join
TariffData
on T1.TariffID = TariffData.TariffID
) as SubsInNovember
on Areas.AreaID = SubsInNovember.AreaID
group by Areas.AreaID
) as ScheduledPark

inner join
(
select Areas.AreaID, sum(Parking.Num) as AreaSize from
Areas
inner join
Parking
on Areas.AreaID = Parking.AreaID
group by Areas.AreaID
) as AreasDescr
on ScheduledPark.AreaID = AreasDescr.AreaID
order by AreaLoad desc

--8) 1ый запрос: все купившие абонимент - купившие абонимент и зафиксированные парконом = 
--купившие абонимент, но не зафиксированные парконом
--2ой запрос: Зафиксированные парконом - купившие абонимент и зафиксированные парконом =
--зафиксированные парконом, но не купившие абонимент
select * from Subscriptions

--9)
declare @date date
set @date = '20160901'
select ParkonDetected.RegNo, ParkonDetected.ParkingNo, @date as DateDetected from
(
	select distinct ParkingNo, RegNo from ParkingData
	where convert(date, ParkingData.DateTime_of_scan) = @date
) as ParkonDetected 
left join
(
	select Parking.ParkingNo, Q.RegNo from 
	(
		select T.AreaID, T.ValidityMonth, Cars.RegNo from
		(
			select Subscriptions.*, TariffData.AreaID from 
			Subscriptions
			inner join
			TariffData
			on Subscriptions.TariffID = TariffData.TariffID
		) as T
		inner join
		Cars
		on T.CarID = Cars.CarID
	) as Q
	inner join
	Parking
	on Q.AreaID = Parking.AreaID
	where month(@date) = month(Q.ValidityMonth)
) as HaveAccessInPark
on ParkonDetected.ParkingNo = HaveAccessInPark.ParkingNo
and ParkonDetected.RegNo = HaveAccessInPark.RegNo
where HaveAccessInPark.ParkingNo is null or HaveAccessInPark.RegNo is null

--10)


--11)
declare @regno nvarchar(10)
set @regno = 'B190AE190'
if (select count(*) from Cars where Cars.RegNo = @regno) > 0
begin
select 'yes'
end
else
begin
declare @CarId int
set @CarId = (select count(*) from Cars) + 1 
insert into Cars values (@CarId, @regno)
end

--12)
declare @CarId int
declare @ClientId int
declare @monthNo nvarchar(2)

set @CarId = 1
set @ClientId = 3
set @monthNo = '9'

if (
select count(*) from 
Subscriptions
inner join
Docs
on Subscriptions.DocID = Docs.DocID
where month(Subscriptions.ValidityMonth) = @monthNo
and ClienID = @ClientId and CarID = @CarId
) > 0
select 'yes'
else
select 'no'

--13)
declare @CarId int
declare @ClientId int
declare @TarffId int
declare @monthNo nvarchar(2)

set @CarId = 1
set @ClientId = 1
set @TarffId = 1
set @monthNo = '12'

insert into Docs values (
(select count(*) + 1 from Docs),
(select getdate()),
@ClientId,
(select CostPerMonth from Tariffs where TariffID = @TarffId)
)

insert into Subscriptions values (
(select count(*) + 1 from Subscriptions),
(select count(*) from Docs), -- без +1, потому что абонимент был добавлен и имеет в Docs последнюю строчку
@CarId,
@TarffId,
(select '2016' + @monthNo + '01'),
(select CostPerMonth from Tariffs where TariffID = @TarffId)
)

--14) нипанятна
update Docs
set Docs.Total = 
(
select Docs.DocID, sum(Subscriptions.Cost) as NewTotal from 
Docs
inner join
Subscriptions
on Docs.DocID = Subscriptions.DocID
where 
group by Docs.DocID



--15)
--drop table #RespPark
--drop table #checkNullTable

select * into #RespPark
from (select top(1) ParkingNo from Parking) as T --занес несколько строк
--сделаем еще одну временную таблицу для проверки есть ли вообще такой тариф
select * into #checkNullTable from	
(
	select top(1) Tariffs.* from
	(
		select T.TariffID from
		(
			select TariffData.*, Parking.ParkingNo from 
			TariffData
			inner join
			Parking
			on TariffData.AreaID = Parking.AreaID
		) as T
		where ParkingNo in (select * from #RespPark)
		group by T.TariffID
		having count(ParkingNo) = (select count(*) from #RespPark)
	) as T
	inner join
	Tariffs
	on T.TariffID = Tariffs.TariffID
	order by Tariffs.CostPerMonth
) as M

if (select count(*) from #checkNullTable) > 0
select * from #checkNullTable
else
select 'no solutions'