select hd from PC
group by hd
having count(hd) > 1
