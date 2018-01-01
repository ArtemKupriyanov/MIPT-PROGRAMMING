with days as 
(select dateadd(day, a-1, '2003-04-01') as day
from 
(
select 1 as a 
union 
select 2 
union 
select 3 
union 
select 4 
union 
select 5 
union 
select 6 
union 
select 7
) as t)

select days.day, isnull(days2.qtv, 0)
from days left join 
(
select pit.date, count(distinct pit.trip_no) as qtv
from pass_in_trip as pit left join trip on trip.trip_no = pit.trip_no
where (trip.town_from = 'rostov') 
and (pit.date >= '2003-04-01') 
and (pit.date <= '2003-04-07')
group by pit.date) as days2 
on days.day = days2.date

