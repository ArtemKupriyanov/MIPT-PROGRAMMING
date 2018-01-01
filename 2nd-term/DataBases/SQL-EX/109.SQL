with my as (select isnull(b_q_id, q_id) as id, isnull(q, 0) as q
from (select b_q_id, (sum(case when c = 'r' then b_vol else 0 end) + 
sum(case when c = 'g' then b_vol else 0 end) +
sum(case when c = 'b' then b_vol else 0 end)) as q
from (select *, (select v_color from utv where v_id = b_v_id) as c
from utb) as t
group by b_q_id) as t1 full join utq on b_q_id = q_id)

select (select q_name from utq where id = q_id) as name, (select count(*) from my where q = 765) as white, (select count(*) from my where q = 0) as  black
from my
where q = 0 or q = 765
