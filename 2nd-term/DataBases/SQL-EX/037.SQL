select My.class
from ( select Classes.*, Ships.name
from Classes inner join Ships on (Classes.class = Ships.class)
UNIon
select Classes.*, Outcomes.ship
from Classes inner join Outcomes on (Classes.class = Outcomes.ship) ) as My
group by class
having count(*) = 1

