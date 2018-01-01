select distinct p.maker
from product as p

except

select distinct p.maker
from product as p
where (p.type = 'pc') and (p.model not in (select model from pc))

