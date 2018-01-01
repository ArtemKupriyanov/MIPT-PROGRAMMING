With AllBbShips as (
	Select distinct name, cast(numGuns as float) ng from classes join ships on classes.class = ships.class where type = 'bb'
	Union
	Select distinct ship as name, cast(numGuns as float) ng from classes join outcomes on class = ship where type = 'bb'
)
Select cast(avg(ng) as decimal(12,2)) from allBbShips

