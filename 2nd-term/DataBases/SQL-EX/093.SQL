select (select name from company where id_comp = x.id_comp) as company, sum(time) as time
from (select sum(case when time_in > time_out then abs(datediff(mi, time_in, time_out)) else 24*60 - abs(datediff(mi, time_in, time_out)) end) as time, id_comp, date
from (select max(trip.time_in) as time_in, max(trip.time_out) as time_out, trip.id_comp, date
from pass_in_trip as pit2 inner join trip on trip.trip_no = pit2.trip_no
group by pit2.date, trip.id_comp, trip.trip_no) as t
group by date, id_comp) as x
group by id_comp
