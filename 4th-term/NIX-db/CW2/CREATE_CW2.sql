CREATE Database CW2
GO

USE CW2
GO

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

