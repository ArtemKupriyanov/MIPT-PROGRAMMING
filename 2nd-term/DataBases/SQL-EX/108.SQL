select a.a, b.b, c.c
from (select distinct cast(b_vol as int) as a from utb) as a inner join (select distinct cast(b_vol as int) as b from utb) as b on a.a < b.b inner join (select distinct cast(b_vol as int) as c from utb) as c on b.b < c.c
where (a.a + b.b > c.c and b.b + c.c > a.a and c.c + a.a > b.b) and (1 = case when a.a < c.c and b.b < c.c and a.a*a.a + b.b*b.b >= c.c*c.c then 1 when b.b < a.a and c.c < a.a and b.b*b.b + c.c*c.c >= a.a*a.a then 1 when c.c < b.b and a.a < b.b and c.c*c.c + a.a*a.a > b.b*b.b then 1 else 0 end)
