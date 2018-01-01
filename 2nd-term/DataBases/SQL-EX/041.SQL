with max_pc as (
	select cast(pc.code as varchar(15)) as code,
	cast(pc.model as varchar(15)) as model,
	cast(pc.speed as varchar(15)) as speed,
	cast(pc.ram as varchar(15)) as ram,
	cast(pc.hd as varchar(15)) as hd,
	cast(pc.cd as varchar(15)) as cd,
	cast(pc.price as varchar(15)) as price
	from pc where code in (select max(code) from pc)
)
select chr, value from max_pc
unpivot (value for chr in (model, speed, ram, hd, cd, price)) AS unpvt

