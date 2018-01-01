select code, point, date, out
from(select convert(char(7), o.date, 120) as month
from outcome as o
group by convert(char(7), o.date, 120)
having (select sum(out) from outcome where convert(char(7), o.date, 120) = convert(char(7), date, 120)) >= all (select sum(out) from outcome group by convert(char(7), date, 120))) as mos inner join outcome on mos.month = convert(char(7), date, 120) 

