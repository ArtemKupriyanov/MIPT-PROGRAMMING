with cte as (select code, speed, ram, speed | ram as num_orig, speed | ram as working_level, 0 as cnt
from pc

union all
select code, speed, ram, num_orig, cast(working_level / 2 as smallint), case when working_level % 2 = 1 then cnt+1 else 0 end
from cte
where working_level > 0
)
 
select distinct code, speed, ram
from cte
where cnt = 4

