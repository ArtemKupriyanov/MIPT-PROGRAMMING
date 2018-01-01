select distinct classes.class from classes join ships on classes.class = ships.class join outcomes on name = ship where result = 'sunk'
union
select distinct class from classes join outcomes on class = ship where result = 'sunk'

