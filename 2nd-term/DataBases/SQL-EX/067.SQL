with t as (
select count(trip_no) as trip_no, town_from, town_to
from trip
group by town_from, town_to
having count(trip_no) >= 
all (select count(trip_no)
from trip
group by town_from, town_to) )

select count(*)
from t

