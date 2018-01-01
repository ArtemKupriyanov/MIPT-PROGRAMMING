with s as (
select classes.country, outcomes.battle
from outcomes  
join ships on (outcomes.ship = ships.name) 
join classes on (ships.class = classes.class)

union

select classes.country, outcomes.battle
from outcomes
join classes on (outcomes.ship= classes.class)
)
select distinct classes.country, battles.name
from classes, battles
where classes.country not in (select country
from s
where (classes.country = country) 
and (battles.name = battle))

