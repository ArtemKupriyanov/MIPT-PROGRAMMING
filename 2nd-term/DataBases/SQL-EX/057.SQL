with classesWithSunk as (
	select classes.class, ships.name from classes join ships on classes.class = ships.class join outcomes on ships.name = outcomes.ship where result = 'sunk'
	union 
	select class, ship as name from classes join outcomes on class = ship where result = 'sunk'
),
classesWithCountSunk as (
	select class, count(class) as cntSunk from classesWithSunk group by class
),
allShips as (
	select classes.class, name from classes join ships on classes.class = ships.class
	union
	select class, ship as name from classes join outcomes on class = ship
),
classesWithThreeShips as (
	select class, count(class) as cntShips from allShips group by class having count(class) >= 3
)
select classesWithCountSunk.class, cntSunk from classesWithThreeShips join classesWithCountSunk on classesWithCountSunk.class = classesWithThreeShips.class

