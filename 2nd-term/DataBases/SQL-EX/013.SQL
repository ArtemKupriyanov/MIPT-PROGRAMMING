select avg(PC.speed) from PC inner join Product on (Product.model = PC.model and Product.maker = 'A')
