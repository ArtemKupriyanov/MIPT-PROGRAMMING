with shipsInBattle as (
select distinct ship, displacement, numGuns from classes join ships on classes.class = ships.class join outcomes on name = ship where battle = 'Guadalcanal'
union
select distinct ship, displacement, numGuns from classes join outcomes on classes.class = outcomes.ship where battle = 'Guadalcanal'
)
select * from shipsInBattle
union
select ship, NULL as displacement, NULL as numGuns from outcomes where battle = 'Guadalcanal' and ship not in (select ship from shipsInBattle)

