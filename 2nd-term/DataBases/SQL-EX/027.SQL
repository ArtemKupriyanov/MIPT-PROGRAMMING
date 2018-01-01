select Product.maker, avg(PC.hd) from PC, Product 
where Product.model = Pc.model 
and Product.maker in 
(
select distinct maker from Product 
where Product.type = 'Printer'
) 
group by maker

