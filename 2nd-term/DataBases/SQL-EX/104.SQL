
with t as (select * 
from (select 1 a1 union all select 2 union all select 3 union all select 4 union all select 5 union all select 6 union all select 7 union all select 8 union all select 9 union all select 10) as x1,
(select 1 a2 union all select 2 union all select 3 union all select 4 union all select 5 union all select 6 union all select 7 union all select 8 union all select 9 union all select 10) as x2,
(select 1 a3 union all select 2 union all select 3 union all select 4 union all select 5 union all select 6 union all select 7 union all select 8 union all select 9 union all select 10) as x3)

select class, replace('bc-x', 'x', cast(100*(a1-1) + 10*(a2-1) + a3 as char(4))) as num
from t cross join classes
where type = 'bc' and (100*(a1-1) + 10*(a2-1) + a3 <= numguns)

