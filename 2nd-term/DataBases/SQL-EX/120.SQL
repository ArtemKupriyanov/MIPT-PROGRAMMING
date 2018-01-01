with help as (select distinct pit.trip_no, trip.id_comp, trip.time_in, trip.time_out, pit.date
from pass_in_trip as pit inner join trip on trip.trip_no = pit.trip_no)

select (select name from company where id_comp = h.id_comp) as company,

cast(cast(sum(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end) as numeric(10,2)) / (select count(*) from help where id_comp = h.id_comp) as numeric(10,2)) as a_mean,

cast(exp(cast(sum(log(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end)) as numeric(10,5)) / (select count(*) from help where id_comp = h.id_comp)) as numeric(10,2)) as g_mean,

cast(sqrt(cast(sum(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end * case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end) as numeric(10,2)) / (select count(*) from help where id_comp = h.id_comp)) as numeric(10,2)) as q_mean,

cast((select count(*) from help where id_comp = h.id_comp) / sum(1 / cast(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end as numeric(10,5))) as numeric(10,2)) as h_mean

from help as h
group by h.id_comp

union all
select 'total',

cast(cast(sum(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end) as numeric(10,2)) / (select count(*) from help) as numeric(10,2)),

cast(exp(cast(sum(log(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end)) as numeric(10,4)) / (select count(*) from help)) as numeric(10,2)),

cast(sqrt(cast(sum(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end * case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end) as numeric(10,2)) / (select count(*) from help)) as numeric(10,2)),

cast((select count(*) from help) / sum(1 / cast(case when time_out > time_in
then 24*60 + datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
else datepart(hh, time_in)*60 + datepart(mi, time_in) - datepart(hh, time_out)*60 - datepart(mi, time_out)
end as numeric(10,5))) as numeric(10,2))
from help
