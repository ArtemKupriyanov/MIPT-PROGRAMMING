select distinct Product.maker, Printer.price
from Product inner join Printer on Product.model = Printer.model
where (price in (select min(price) from Printer where color = 'y')) and (color = 'y')

