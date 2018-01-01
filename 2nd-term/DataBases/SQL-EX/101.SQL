with new as (select *, case when color = 'n' then 1 else 0 end + (select count(color) from printer where code < p.code and color = 'n') as g
from printer as p)

select code, model, color, type, price, (select max(model) from new where g = n.g) as max_model, (select count(distinct type) from new where g = n.g) as distct_types, (select avg(price) from new where g = n.g) as avg_price
from new as n
