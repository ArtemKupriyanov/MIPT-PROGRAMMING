select name from ships where name like 'R%'
union
select ship from outcomes where ship like 'R%' and ship not in (select name from ships)

