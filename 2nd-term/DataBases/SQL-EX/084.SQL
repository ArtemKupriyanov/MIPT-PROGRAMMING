select (select name from company where id_comp = trip.id_comp) as name,
sum(case when datepart(dd, date) >= 1 and datepart(dd, date) <= 10 then 1 else 0 end) as '1-10',
sum(case when datepart(dd, date) >= 11 and datepart(dd, date) <= 20 then 1 else 0 end) as '11-20',
sum(case when datepart(dd, date) >= 21 and datepart(dd, date) <= 30 then 1 else 0 end) as '21-30'
from pass_in_trip as pit inner join trip on trip.trip_no = pit.trip_no
where convert(char(7), pit.date, 120) = '2003-04'
group by trip.id_comp
