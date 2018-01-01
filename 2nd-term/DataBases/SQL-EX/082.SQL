with newpc as(select row_number() over(order by code) as no, code, price
from pc)

select npc.code, (select avg(price) from newpc where no >= npc.no and no-5 <= npc.no ) as avgrpc
from newpc as npc
where npc.no + 4 < (select count(*) from pc)
