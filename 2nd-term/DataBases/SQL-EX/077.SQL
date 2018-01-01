with t as 
(select distinct count(distinct trip.trip_no) as cc, pit.date
from pass_in_trip as pit 
inner join trip on trip.trip_no = pit.trip_no
where trip.town_from = 'rostov'
group by trip.town_from, pit.date)

select cc, date
from t
where cc = (select max(cc) from t)

