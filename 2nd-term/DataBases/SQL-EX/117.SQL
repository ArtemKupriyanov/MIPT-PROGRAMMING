with t as (select distinct country, max(numguns)*5000 as ng, max(bore)*3000 as br, max(displacement) as dp
from classes as c
group by country)

select country, ng as maxv_val, 'numguns' as name
from t
where ng >= br and ng >= dp

union

select country, br, 'bore'
from t
where ng <= br and br >= dp

union

select country, dp, 'displacement'
from t
where dp >= br and ng <= dp
