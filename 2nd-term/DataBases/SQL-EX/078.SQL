select name, 
convert(char(10), dateadd(dd, 1-datepart(dd, date), date), 120) as firstd, convert(char(10), dateadd(dd, -datepart(dd, dateadd(mm, 1, date)), dateadd(mm, 1, date)), 120) as lastd
from battles

