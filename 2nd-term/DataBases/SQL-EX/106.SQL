
with temp as (select b_datetime, b_q_id, b_v_id, b_vol, row_number() over(order by b_datetime, b_q_id, b_v_id) as n
from utb)

select b_datetime, b_q_id, b_v_id, b_vol, 

cast(
(select
exp(sum(case when n % 2 <> 0 then log(cast(b_vol as float)) else 0 end))
/
exp(sum(case when n% 2 = 0 then log(cast(b_vol as float)) else 0 end))

from temp
where n <= t.n) as numeric(12, 8)) as sv

from temp as t
