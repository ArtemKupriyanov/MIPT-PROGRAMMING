select (select q_name from utq where t.b_q_id = q_id) as name, r
from (select b_q_id,
sum(case when c = 'r' then b_vol else 0 end) as r,
sum(case when c = 'g' then b_vol else 0 end) as g,
sum(case when c = 'b' then b_vol else 0 end) as b
from (select *, (select v_color from utv where v_id = b_v_id) as c
from utb) as t
group by b_q_id) as t
where r > 0 and r < 255 and r = g and g = b and b = r
