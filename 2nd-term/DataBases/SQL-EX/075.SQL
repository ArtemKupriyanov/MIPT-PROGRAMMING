select ships.name,
ships.launched,

case 
when ships.launched is null 
then (select max(b1.name) 
from battles as b1 
where b1.date = (select max(b2.date) 
from battles as b2))

else
case
when ships.launched > (select max(b3.date) 
from battles as b3)
then null 

else
(select max(b4.name) 
from battles as b4 
where b4.date = (select min(b5.date) 
from battles as b5 
where datepart(yyyy, b5.date) >= ships.launched)) end end as battle
from ships

