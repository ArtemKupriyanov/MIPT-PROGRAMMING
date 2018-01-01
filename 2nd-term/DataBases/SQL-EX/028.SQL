with MyT as ( 
select B_Q_ID, sum(B_VOL)*1.0 as dye 
from utB 
group by B_Q_ID 

union 

select Q_ID, 0 
from utQ 
where Q_ID NOT IN ( 
select B_Q_ID from utB 
) 
) 
select cast(avg(dye) as numeric(6, 2)) from MyT
