select ships.name
from ships inner join classes on classes.class = ships.class
where (case when classes.numguns = 8 then 1 else 0 end) +
(case when classes.bore = 15 then 1 else 0 end) +
(case when classes.displacement = 32000 then 1 else 0 end) +
(case when classes.type = 'bb' then 1 else 0 end) +
(case when ships.launched = 1915 then 1 else 0 end) +
(case when classes.class = 'kongo' then 1 else 0 end) +
(case when classes.country = 'usa' then 1 else 0 end) > 3
