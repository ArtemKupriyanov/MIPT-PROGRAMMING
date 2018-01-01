select distinct maker from Product left join PC on (Product.model = PC.model)  where PC.speed >= 450
