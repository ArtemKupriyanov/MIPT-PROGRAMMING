select distinct battle 
from(
select battle, ship, country 
from outcomes, ships, classes
where (ships.class = classes.class) 
and (outcomes.ship = ships.name) 

union

select battle, ship, country 
from outcomes, classes
where ship in
(select class 
from classes) 
and (classes.class = ship)
) as x1
group by battle, country
having count(ship) >= 3

