select (select name from company as a1 where a1.id_comp = c19.id_comp) as company_name,
(select y.ccc
from (select sum(r.cnt) as ccc, r.id_comp
from (select count(distinct pit.trip_no) as cnt, tr.id_comp, (select name from company as a1 where a1.id_comp = tr.id_comp) as company_name, pit.date
from pass_in_trip as pit inner join trip as tr on pit.trip_no = tr.trip_no inner join company as ccc on ccc.id_comp = tr.id_comp
group by tr.id_comp, pit.date) as r
group by r.id_comp) as y
where y.id_comp = c19.id_comp) as flights,
count(distinct tr19.plane) as planes, count(distinct pit19.id_psg) as diff_psngrs,
count(pit19.id_psg) as total_psngrs
from pass_in_trip as pit19 inner join trip as tr19 on pit19.trip_no = tr19.trip_no inner join company as c19 on tr19.id_comp = c19.id_comp
group by c19.id_comp
