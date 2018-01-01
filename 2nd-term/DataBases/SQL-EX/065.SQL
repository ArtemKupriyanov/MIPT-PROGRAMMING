select row_number() 
over(order by maker, 
case 	when type = 'pc' then 1
 		when type = 'laptop' then 2 
		else 3 end), 
case 	when type = 'pc' then maker
		when type = 'laptop'
then case
when 'pc' in (select type from product where maker = z.maker)
then ''
else maker end
else
case 
when 'pc' in 
(select type 
from product 
where maker = z.maker)
or 'laptop' in 
(select type 
from product 
where maker = z.maker)
then ''
else maker
end  end as maker, type
from product as z
group by maker, type

