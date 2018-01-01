select distinct A.Country, Cast(avg(bore * bore * bore/2) as decimal(10,2)) as weight from
	(select Country, Ships.name, bore from Classes join Ships on
	(Classes.Class = Ships.Class)
	union
	select Classes.Country, Outcomes.Ship, Classes.Bore from Classes join Outcomes on (Outcomes.Ship = Classes.Class)
where Outcomes.Ship not in (select distinct Name from Ships)) as A
group by Country

