select maker, case
when sum(types) = 1 then 'laptop'
when sum(types) = 2 then 'pc'
when sum(types) = 3 then 'laptop/pc'
when sum(types) = 4 then 'printer'
when sum(types) = 5 then 'laptop/printer'
when sum(types) = 6 then 'pc/printer'
when sum(types) = 7 then 'laptop/pc/printer'
end
as types
from(select distinct maker, case when type = 'laptop' then 1 when type = 'pc' then 2 else 4 end as types
from product) as t
group by maker
