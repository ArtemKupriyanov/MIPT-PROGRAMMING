select name, minutes 
from passenger
join (
select id_psg,sum(dur) as minutes 
from
(
select trip_no,
case
when  datediff(mi,time_out,time_in)> 0
then  datediff(mi,time_out,time_in)
else  datediff(mi,time_out,time_in)+1440
end dur  

from trip
) as x
join
(
select trip_no, id_psg 
from pass_in_trip
where id_psg in 
(select id_psg from pass_in_trip
group by id_psg
having  count(distinct place) = count (place)
)

) as y
on x.trip_no = y.trip_no
group by id_psg
)t
on t.id_psg=passenger.id_psg

