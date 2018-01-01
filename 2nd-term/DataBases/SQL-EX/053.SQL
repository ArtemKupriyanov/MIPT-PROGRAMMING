With classesOfBb as (
	Select * from classes where type = 'bb'
)
Select cast(avg(cast(numGuns as float)) as decimal(12,2)) from classesOfBb

