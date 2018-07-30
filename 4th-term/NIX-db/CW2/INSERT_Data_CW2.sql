Drop table Users
Drop table Subscriptions
Drop table User_Properties 
Drop table Properties
Drop table Visibility_levels
Drop table News
Drop table News_comments

CREATE TABLE Users (UserID int primary key, Grp int NOT NULL)

CREATE TABLE User_Properties 
(
	UserID int, PropID int, Value nvarchar(100) NOT NULL, Level_ID int NOT NULL, 
	primary key(UserID, PropID)
)

CREATE TABLE Properties (PropID int primary key, Property nvarchar(50) NOT NULL)

CREATE TABLE Visibility_levels (Level_id int primary key, Level nvarchar(max) NOT NULL)

CREATE TABLE Subscriptions (UserID int, SubsID int, primary key(UserID, SubsID))

CREATE TABLE News 
(
	NewsID int primary key, UserID int not NULL, Date_of_news datetime not NULL, 
	Level_ID int not NULL, News_txt nvarchar(max) NOT NULL
)

CREATE TABLE News_comments 
(
	NewsID int, PosID int, Date_of_comments datetime not NULL, Comment_UserID int not NULL, Comment nvarchar(max) not NULL,
	primary key (NewsID, PosID)
)

INSERT INTO Visibility_levels
VALUES 
(1,N'Под замком'),
(2,N'Показывать друзьям'),
(3,N'Показывать друзьям и друзьям друзей'),
(4,N'Показывать всем')

INSERT INTO Users
VALUES
(1,0), (2,0), (3,0), (4,0), (5,0), (6,0), (7,0), (8,1), (9,1), (10,1)

INSERT INTO Properties
VALUES 
(1,N'Surname'), (2,N'Name'), (3,N'Date_of_Birth'), (4,N'Group_name'), (5,N'Home_town')

INSERT INTO User_properties VALUES
(1,1,N'Ivanov',4),
(1,2,N'Ivan',4),
(1,3,N'19960501',4),
(1,5,N'Dolgoprudny',4),
(2,1,N'Petrova',4),
(2,2,N'Svetlana',4),
(2,3,N'19961015',2),
(2,5,N'Moscow',2),
(3,1,N'Sidorov',3),
(3,2,N'Konstantin',3),
(4,3,N'19931218',4),
(5,1,N'Test',1),
(5,2,N'Test',1),
(5,3,N'19900101',1),
(5,5,N'New York',1),
(6,1,N'Homyakov',4),
(6,2,N'Sergei',4),
(6,3,N'19951215',2),
(7,1,N'Svetlova',2),
(7,2,N'Tatyana',2),
(7,3,N'19970916',3),
(7,5,N'Sankt-Peterburgh',4),
(8,4,N'Nix SQL',4),
(9,4,N'Nix OOP',4),
(10,4,N'MIPT',4)

INSERT INTO Subscriptions VALUES
(1,2), (1,3), (1,5), (1,7), (1,8), (1,10), (2,1), (2,3),
(3,4), (4,2), (5,6), (6,7), (6,10), (7,9), (7,10)

INSERT INTO News VALUES
(1,1,'20160901',4,N'Привет всем! Я зарегистрировался'),
(2,8,'20160920',4,N'Здравствуйте! С 29.09.16 мы начинаем занятия по SQL. Присоединиться могут все желающие'),
(3,9,'20160921',4,N'Здравствуйте! С 22.09.16 мы начинаем занятия по ООП. Присоединиться могут все желающие'),
(4,7,'20161001',2,N'А я сделала первое домашнее задание по техкурсу!!!')

INSERT INTO News_comments VALUES
(2,1,'20160920',1,N'Я хочу посещать, но я только первый курс. Можно ли мне ходить?'),
(2,2,'20160920',8,N'Ограничений на курс нет. Можно приходить всем'),
(2,3,'20160920',1,N'Спасибо! Приду!'),
(3,1,'20160921',7,N'Если я не умею программировать на С++, то можно ли прийти?'),
(3,2,'20160921',9,N'Конечно!'),
(3,3,'20160921',7,N'Спасибо за ответ!'),
(3,4,'20160922',3,N'Я не смог прийти на первое занятие, можно ли еще записаться на курс?'),
(3,5,'20160922',9,N'Да, Вам отправлены логин и пароль к кабинету'),
(4,1,'20161001',6,N'А у меня не получается 3-я задача, но я сейчас еще подумаю и сделаю.'),
(4,2,'20161002',6,N'Ура! Тоже сдал'),
(4,3,'20161002',7,N'Молодец!')