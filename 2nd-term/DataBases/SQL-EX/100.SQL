select isnull(ii.date, oo.date) as date, isnull(ii.n, oo.n) as n, ii.point, ii.inc, oo.point, oo.out
from
(select date, point, (select count(*) from income where income.date = i.date and income.code <= i.code) as n, inc
from income as i) as ii
full join
(select date, point, (select count(*) from outcome where outcome.date = o.date and outcome.code <= o.code) as n, out
from outcome as o) as oo on ii.date = oo.date and ii.n = oo.n
