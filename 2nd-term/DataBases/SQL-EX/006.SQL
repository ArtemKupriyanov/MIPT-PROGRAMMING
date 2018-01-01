select distinct Product.maker, Laptop.speed
from Product right join Laptop on (Product.model = Laptop.model)
where Laptop.hd >= 10 and 
type in (select type from Product where type = 'laptop')

