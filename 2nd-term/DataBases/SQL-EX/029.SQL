select t1.point, t1.date, inc, out 
from income_o t1 left join outcome_o t2 ON t1.point = t2.point 
and t1.date = t2.date 
union 

select t2.point, t2.date, inc, out 
from income_o t1 right join outcome_o t2 ON t1.point = t2.point 
and t1.date = t2.date

