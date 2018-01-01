with t as (
select income.point as ipt, income.code as ic, inc, out, income.date as id, outcome.point as opt, outcome.code as oc, outcome.date as od from income full join outcome on income.point = outcome.point and income.date = outcome.date where income.point is null or outcome.point is null),
t1 as (
select * from t where opt is null),
t2 as (
select * from t where ipt is null)
select ipt, id, 'inc' as type, sum(inc) as money_sum from t1 group by ipt, id
union
select opt, od, 'out' as type, sum(out) as money_sum from t2 group by opt, od

