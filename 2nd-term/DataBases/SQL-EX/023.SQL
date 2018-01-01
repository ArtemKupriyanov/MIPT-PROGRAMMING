select distinct maker
from product t1 join pc t2 on t1.model = t2.model
where (speed >= 750) and maker in
( 
select maker
from product t1 join laptop t2 on t1.model=t2.model
where (speed >=750)
)

