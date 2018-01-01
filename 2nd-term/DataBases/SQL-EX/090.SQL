select maker, model, type
from (select top ((select count(*) from product)-6) with ties model, maker, type
from (select top ((select count(*) from product)-3) with ties model, maker, type
from product
order by model desc) as x
order by model asc) as y
