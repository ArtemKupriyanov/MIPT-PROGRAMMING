select (select name from passenger where id_psg = t.id_psg) as name, cnt
from(select distinct pit.id_psg, count(*) as cnt
from pass_in_trip as pit
group by pit.id_psg, pit.place
having count(*) >= all (select count(*) as cnt
from pass_in_trip as pit
group by pit.id_psg, pit.place)) as t
