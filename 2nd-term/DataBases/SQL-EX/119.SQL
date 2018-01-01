select convert(char(4), b_datetime, 120) as year, sum(b_vol) as cnt
from utb
group by convert(char(4), b_datetime, 120)
having count(distinct b_datetime) > 10

union all

select convert(char(7), b_datetime, 120) as year, sum(b_vol) as cnt
from utb
group by convert(char(7), b_datetime, 120)
having count(distinct b_datetime) > 10

union all

select convert(char(10), b_datetime, 120) as year, sum(b_vol) as cnt
from utb
group by convert(char(10), b_datetime, 120)
having count(distinct b_datetime) > 10
