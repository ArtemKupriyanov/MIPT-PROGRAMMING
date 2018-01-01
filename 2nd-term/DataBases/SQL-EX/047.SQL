with makers as (
	select maker as mk, count(maker) as cnt from product group by maker
)
select row_number() over (order by cnt desc, maker, model) no, maker, model from makers join product on makers.mk = product.maker order by model

