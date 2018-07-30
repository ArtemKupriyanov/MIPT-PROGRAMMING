USE BDZ2
GO

CREATE TABLE Areas (AreaID int primary key, Area nvarchar(50), CostPerHour float)
CREATE TABLE Parking (ParkingNo int primary key, Address nvarchar(50), AreaID int, Num int)
CREATE TABLE Clients (ClientID int primary key, ClientsPersNum nvarchar(10), Surname nvarchar(max), Name nvarchar(max), PhoneNumber nvarchar(20))
CREATE TABLE Cars (CarID int primary key, RegNo nvarchar(10))
CREATE TABLE Tariffs (TariffID int primary key, Tariff nvarchar(max), CostPerMonth float)
CREATE TABLE TariffData (TariffID int, AreaID int, primary key(TariffID, AreaID))
CREATE TABLE Docs (DocID int primary key, Date_of_doc datetime, ClienID int, Total float)
CREATE TABLE Subscriptions (SubscrID int primary key, DocID int, CarID int, TariffID int, ValidityMonth date, Cost float)
CREATE TABLE ParkingData (ID int primary key, ParkingNo int, DateTime_of_scan datetime, RegNo nvarchar(10))

