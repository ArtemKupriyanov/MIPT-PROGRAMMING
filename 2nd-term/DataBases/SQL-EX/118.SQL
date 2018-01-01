select name, convert(char(10), date, 120) as battle_dt,

convert(char(10),
(select min(election)
from (select case
when datename(weekday, firstapril) = 'monday'
then dateadd(dd, 1, firstapril)
when datename(weekday, firstapril) = 'tuesday'
then dateadd(dd, 7, firstapril)
when datename(weekday, firstapril) = 'wednesday'
then dateadd(dd, 6, firstapril)
when datename(weekday, firstapril) = 'thursday'
then dateadd(dd, 5, firstapril)
when datename(weekday, firstapril) = 'friday'
then dateadd(dd, 4, firstapril)
when datename(weekday, firstapril) = 'saturday'
then dateadd(dd, 3, firstapril)
when datename(weekday, firstapril) = 'sunday'
then dateadd(dd, 2, firstapril) end as election

from (select dateadd(dd, 1-datepart(dd, yr), dateadd(mm, 4-datepart(mm, yr), yr)) as firstapril
from (select b.date as yr union all
select dateadd(yyyy, 1, b.date) union all
select dateadd(yyyy, 2, b.date) union all
select dateadd(yyyy, 3, b.date) union all
select dateadd(yyyy, 4, b.date) union all
select dateadd(yyyy, 5, b.date) union all
select dateadd(yyyy, 6, b.date) union all
select dateadd(yyyy, 7, b.date) union all
select dateadd(yyyy, 8, b.date)) as nineyears
where (datepart(yyyy, yr) % 400 = 0) or (datepart(yyyy, yr) % 4 = 0 and datepart(yyyy, yr) % 100 <> 0)) as fapr) as oooh
where election >  b.date), 120) as election_date

from battles as b
