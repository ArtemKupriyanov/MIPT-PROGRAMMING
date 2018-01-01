select (select name from passenger where id_psg = t.id_psg) as name
from (select distinct id_psg
from pass_in_trip as pit inner join trip on pit.trip_no = trip.trip_no
where trip.time_out > trip.time_in and datename(weekday, date) = 'saturday') as t
