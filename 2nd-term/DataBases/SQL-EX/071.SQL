select distinct maker 
from product 
where maker not in
(
select distinct maker 
from product
where model not in 
(select model 
from pc)
and (type='pc')
)
and maker in 
(select distinct maker 
from product
where (type='pc')
)

