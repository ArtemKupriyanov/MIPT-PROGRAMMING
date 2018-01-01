With allShips as (
	Select name, numGuns, displacement from classes join ships on classes.class = ships.class
	Union
	Select ship as name, numGuns, displacement from classes join outcomes on ship = class
),
AllShips2 as (
	Select name as nm, numGuns as ng, displacement as dsp from classes join ships on classes.class = ships.class
	Union
	Select ship as nm, numGuns as ng, displacement as dsp from classes join outcomes on ship = class
)
Select name from allShips where numGuns >= all(select ng from allShips2 where dsp = displacement)

