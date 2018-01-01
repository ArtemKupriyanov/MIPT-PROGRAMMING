select count(*)
from (select maker, count(model) as c
from product
group by maker
having count(model) = 1) as x
