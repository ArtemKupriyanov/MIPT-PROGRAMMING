select distinct My1.ship
from Outcomes as My1 inner join Battles as My2 on (My2.name = My1.battle)
where (My1.result = 'damaged') and exists ( select Outcomes.ship
from Outcomes inner join Battles on (Battles.name = Outcomes.battle)
where (My1.ship = Outcomes.ship) and (Battles.date > My2.date) )

