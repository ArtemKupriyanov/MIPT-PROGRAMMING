select up, down, side, cast(sqrt(side*side - (down-up)*(down-up)/4)/2 as numeric(10, 2)) as rad
from (select distinct cast(b_vol as int) as up from utb) as a
inner join (select distinct cast(b_vol as int) as down from utb) as b on up < down,
(select distinct cast(b_vol as int) as side from utb) as c
where up + down = 2*side
