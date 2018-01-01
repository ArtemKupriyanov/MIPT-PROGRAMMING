select (select name from company where id_comp = x.id_comp) as name, trip_no, date
from (select row_number() over(order by pit.date, trip.time_out, pit.id_psg) no, trip.trip_no, pit.date, trip.id_comp
from pass_in_trip as pit inner join trip on trip.trip_no = pit.trip_no
where convert(char(7), pit.date, 120) = '2003-04' and trip.town_from = 'rostov') as x
where no = 5
