with info as (select pit.id_psg, trip.town_from, dateadd(ss, datepart(ss, trip.time_out), dateadd(mi, datepart(mi, trip.time_out), dateadd(hh, datepart(hh, trip.time_out), pit.date))) as time
from pass_in_trip as pit inner join trip on pit.trip_no = trip.trip_no)

select (select name from passenger where id_psg = y.notmos) as name, count(*) as cnt
from (select id_psg as notmos
from (select id_psg, town_from, time
from info as i
where time <= all (select time from info where i.id_psg = id_psg)) as x
where town_from <> 'moscow') as y inner join pass_in_trip as pit2 on pit2.id_psg = y.notmos inner join trip on trip.trip_no = pit2.trip_no
where trip.town_to = 'moscow'
group by y.notmos
having count(*) > 1
