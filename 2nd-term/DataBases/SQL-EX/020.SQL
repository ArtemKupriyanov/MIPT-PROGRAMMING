select maker, count(distinct model)
from product
where type='PC'
group by maker having count(model)>=3
