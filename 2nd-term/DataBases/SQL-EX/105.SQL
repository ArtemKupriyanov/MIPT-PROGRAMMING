select maker, model, row_number() over(order by maker, model) as a,

(select q
from (select row_number() over(order by maker) as q, maker
from product group by maker) as t1
where maker = p.maker) as b,

(select min(q)
from (select row_number() over(order by maker, model) as q, maker
from product) as t2
where maker = p.maker) as c,

(select max(q)
from (select row_number() over(order by maker, model) as q, maker
from product) as t3
where maker = p.maker) as d

from product as p
