select 
(
select name 
from passenger 
where id_psg = pit.id_psg
) as name, 
sum(case when trip.time_out > trip.time_in then 24*60 - abs(datediff(mi, trip.time_in, trip.time_out)) 
else abs(datediff (mi, trip.time_in, time_out)) end) as time
from trip 
inner join pass_in_trip as pit on pit.trip_no = trip.trip_no
group by pit.id_psg
having sum(case when trip.time_out > trip.time_in then 24*60 - abs(datediff(mi, trip.time_in, trip.time_out)) 
else abs(datediff (mi, trip.time_in, time_out)) end) >= all (select sum(case when trip.time_out > trip.time_in then 24*60 - abs(datediff(mi, trip.time_in, trip.time_out)) else abs(datediff (mi, trip.time_in, time_out)) end) as time
from trip 
inner join pass_in_trip as pit on pit.trip_no = trip.trip_no
group by pit.id_psg)

