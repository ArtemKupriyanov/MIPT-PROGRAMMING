with IncomeBefore as (
	select * from Income_o where date < cast('15April2001' as datetime)
), 
OutcomeBefore as (
	select * from Outcome_o where date < cast('15April2001' as datetime)
),
totalIncome as (
	select point, sum(inc) as totalInc from IncomeBefore group by point
),
totalOutcome as (
	select point, sum(out) as totalOut from OutcomeBefore group by point
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

