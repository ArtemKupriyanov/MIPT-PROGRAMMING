with r as(
select country, class
from classes
where country = 'russia')
select *
from r

union

select country, class 
from classes
where (select count(*) 
from r) = 0

