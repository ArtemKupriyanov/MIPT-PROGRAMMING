select (select q_name from utq where q_id = ras.q_id) as q_name
from (select b_q_id as q_id, sum(case when cr = 'r' then b_vol else 0 end) as r, sum(case when cr = 'g' then b_vol else 0 end) as g, sum(case when cr = 'b' then b_vol else 0 end) as b
from (select b_v_id as id, (select v_color from utv where p.b_v_id = v_id) as cr
from (select b_v_id, sum(b_vol) as c
from utb
group by b_v_id) as p
where c = 255) as pusto inner join utb on pusto.id = b_v_id
group by b_q_id) as ras
where r = 255 and g = 255 and b = 255
