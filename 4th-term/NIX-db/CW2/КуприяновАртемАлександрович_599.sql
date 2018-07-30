--1) ничего обычного
declare @param int
set @param = 1
select NewsID, Date_of_comments, Comment 
from News_comments
where Comment_UserID = @param

--2) ничего обычного
select News.Level_ID, count(distinct News.News_txt) as uniqueNews, count(distinct News.UserID) as uniqueUsers  
from 
News
inner join
Visibility_levels
on News.Level_ID = Visibility_levels.Level_id
group by News.Level_ID

--3) находим топ1 юзеров. Находим их подписчиков. Считаем количество таких подписчиков
--для каждого юзера
select top1user.Comment_UserID as UserId, count(*) as cnt from
(
select Top 1 with ties Comment_UserID, count(*) as cnt from News_comments
group by Comment_UserID
order by cnt desc
) as top1user
inner join
Subscriptions
on Subscriptions.SubsID = top1user.Comment_UserID
group by top1user.Comment_UserID

--4) нужные нам новости = все новости - новости, под которыми были комментарии
--после 01.10.16
select ResponceTable.NewsID from
(
select News.*, PosID, Date_of_comments, Comment_UserID, Comment from  
News
inner join
News_comments
on News.NewsID = News_comments.NewsID
except
select News.*, PosID, Date_of_comments, Comment_UserID, Comment from  
News
inner join
News_comments
on News.NewsID = News_comments.NewsID
where Date_of_comments > '20161001'
) as ResponceTable

--5) вычитать из User_Properties декартово на Properties - неверно. Там лежат не все пользователи
--в users лежат все пользователи, поэтому вычитаю из users декартово на propiertes
select Users.UserID, Properties.PropID
from Properties, Users

except

select User_Properties.UserID, User_Properties.PropID
from User_Properties

--6) опять же, есть пользователи, которые ничего не опубликовали
select ResponceTable.UserID from
(
	--которые все-таки что-то опубликовали
	select News.UserID, count(*) as cnt_news from News
	group by  News.UserID
	having count(*) < 3
	union
	--которые ничего не опубликовали
	select InUsersNotInNews.*, 0 as cnt_news from
	(
		select Users.UserID from Users
		except
		select News.UserID from News
	) as InUsersNotInNews
) as ResponceTable

--7) не понял формулировка. Вывел пользователей, которые подписаны хотя бы на 1 с новостями 
select distinct Subscriptions.UserID from 
Subscriptions
inner join
(
--пользователи, которые публиковали новости
select News.UserID as SubWithNews from News
) as NeedSubs
on Subscriptions.SubsID = NeedSubs.SubWithNews

--8)
declare @userid int, @subsid int
set @userid = 1
set @subsid = 2
if
(
select count(*) 
from Subscriptions
where Subscriptions.UserID = @userid and Subscriptions.SubsID = @subsid
) > 0
begin
select 'this pair already exists' as answer
end
else
begin
insert into Subscriptions values (@userid, @subsid)
end

--9)
select T1.UserID, T1.cnt_news, count(T2.UserID) as Rating from
(
select News.UserID, count(*) as cnt_news from News
	group by  News.UserID
	having count(*) < 3
	union
	select InUsersNotInNews.*, 0 as cnt_news from
	(
		select Users.UserID from Users
		except
		select News.UserID from News
	) as InUsersNotInNews
) as T1
inner join
(
select News.UserID, count(*) as cnt_news from News
	group by  News.UserID
	having count(*) < 3
	union
	select InUsersNotInNews.*, 0 as cnt_news from
	(
		select Users.UserID from Users
		except
		select News.UserID from News
	) as InUsersNotInNews
) as T2
on T1.cnt_news >= T2.cnt_news
group by T1.UserID, T1.cnt_news

--10)
declare @step int
set @step = 1
select floor(ResponceTable.cnt_comments / @step)*@step as from_,
floor(ResponceTable.cnt_comments / @step + 1)*@step as to_,
count(*) as cnt_in
from
(
select News.NewsID, count(*) as cnt_comments from 
News
inner join
News_comments
on News.NewsID = News_comments.NewsID
group by News.NewsID
) as ResponceTable
group by floor(ResponceTable.cnt_comments / @step)*@step,
floor(ResponceTable.cnt_comments / @step + 1)*@step