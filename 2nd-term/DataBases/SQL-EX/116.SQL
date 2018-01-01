select date_begin, date_finish
from (select row_number() over (order by date_begin) as n, *
from (select distinct b_datetime as date_begin
from utb
where dateadd(s, -1, b_datetime) not in (select b_datetime from utb) and dateadd(s, 1, b_datetime) in (select b_datetime from utb)) as start) as t1 inner join (select row_number() over (order by date_finish) as n, *
from (select distinct b_datetime as date_finish
from utb
where dateadd(s, 1, b_datetime) not in (select b_datetime from utb) and dateadd(s, -1, b_datetime) in (select b_datetime from utb)) as finish) as t2 on t1.n = t2.n
