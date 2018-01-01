with temp as(select isnull(i.point, o.point) as point, isnull(i.date, o.date) as date, i.inc, o.out
from income_o as i full join outcome_o as o on i.date = o.date and i.point = o.point)

select t.point, t.date as dp, case when t.out is null then t.date else

(select min(day) as min_date
from
(select dateadd(dd, 1, t.date) as day
union all
select dateadd(dd, 2, t.date)
union all
select dateadd(dd, 3, t.date)
union all
select dateadd(dd, 1, (select min(temp.date) from temp where date > t.date and dateadd(dd, 1, temp.date) not in (select date from outcome_o where point = t.point) and datename(weekday, dateadd(dd, 1, date)) <> 'sunday'))
) as dat
where (dat.day not in (select date from outcome_o where point = t.point)) and (datename(weekday, day) <> 'sunday'))

end as di
from temp as t
where t.inc is not null
