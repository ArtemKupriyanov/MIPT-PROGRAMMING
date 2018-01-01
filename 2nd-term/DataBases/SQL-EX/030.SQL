with M as 
(select point, date, NULL as Outcome, sum(inc) as income from income
group by point, date

union

select point, date, sum(out), NULL from Outcome
group by point, date )

select point, date, sum(Outcome) as Outcome, sum(income) as income
from M 
group by date, point
