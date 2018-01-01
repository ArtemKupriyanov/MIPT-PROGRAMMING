select maker, min(type) from Product
group by maker
having count(*) > 1 and count(distinct type) = 1
