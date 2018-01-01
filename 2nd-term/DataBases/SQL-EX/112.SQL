with notblack as (select 
(select 255*count(*) from utv where v_color = 'r') - sum(case when c = 'r' then b_vol else 0 end) as r,
(select 255*count(*) from utv where v_color = 'g') - sum(case when c = 'g' then b_vol else 0 end) as g,
(select 255*count(*) from utv where v_color = 'b') - sum(case when c = 'b' then b_vol else 0 end) as b
from (select *, (select v_color from utv where v_id = b_v_id) as c
from utb) as t)

select min(c) / 255 as c
from (select r as c
from notblack
union all
select g
from notblack
union all
select b
from notblack) as y
