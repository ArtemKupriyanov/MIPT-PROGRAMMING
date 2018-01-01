select distinct Classes.class
from Classes inner join Ships on (classes.class = ships.name)
union
select distinct Classes.class
from Classes inner join Outcomes on (classes.class = Outcomes.ship)

