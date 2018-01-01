select maker
from(select maker, max(type) as type, count(distinct model) as model
from product
group by maker
having count(distinct type) = 1) as x
where (type = 'printer') or (model > 2 and type = 'pc')
