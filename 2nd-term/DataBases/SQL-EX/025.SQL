select distinct maker 
from Product 
where model in ( 
select model from PC 
where ram = ( 
  select Min(ram) from PC 
  ) 
and speed = ( 
  select max(speed) from PC 
  where ram = ( 
   select Min(ram) from PC 
   ) 
  ) 
) 
and 
maker in ( 
select maker from Product 
where type='printer' 
)
