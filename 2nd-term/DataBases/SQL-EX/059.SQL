with totalIncome as (
	select point, sum(inc) as totalInc from income_o group by point
),
totalOutcome as (
	select point, sum(out) as totalOut from outcome_o group by point
)
select totalIncome.point, 
case
when totalInc is not NULL and totalOut is not NULL
then totalInc - totalOut
when totalInc is NULL and totalOut is not NULL
then -totalOut
when totalInc is not NULL and totalOut is NULL
then totalInc
else 0
end totalInc
from totalIncome full join totalOutcome on totalIncome.point = totalOutcome.point

