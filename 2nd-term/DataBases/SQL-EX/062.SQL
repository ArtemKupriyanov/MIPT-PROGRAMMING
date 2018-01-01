with sum_inc as (
select sum(inc) as sum_inc from income_o where date < '15april2001'),
sum_out as (
select sum(out) as sum_out from outcome_o where date < '15april2001'),
norm_sum_inc as (
select 0 as norm_sum_inc from sum_inc where sum_inc is null
union
select sum_inc as norm_sum_inc from sum_inc where sum_inc is not null),
norm_sum_out as (
select 0 as norm_sum_out from sum_out where sum_out is null
union
select sum_out as norm_sum_out from sum_out where sum_out is not null)
select norm_sum_inc - norm_sum_out from norm_sum_inc join norm_sum_out on 2 = 2

