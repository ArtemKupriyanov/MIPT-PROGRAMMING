select speed, avg(price) from PC
group by (speed)
having (speed > 600)

