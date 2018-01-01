select code, speed, ram, price, screen
from laptop
where
case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end * 2
<= 
case
when speed = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when ram <= price and ram <= screen
then ram
when price <= ram and price <= screen
then price
else screen
end
when ram = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when speed <= price and speed <= screen
then speed
when price <= speed and price <= screen
then price
else screen
end
when price = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when speed <= ram and speed <= screen
then speed
when ram <= speed and ram <= screen
then ram
else screen
end
when screen = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when speed <= ram and speed <= price
then speed
when ram <= speed and ram <= price
then ram
else price
end
end

and

case
when speed = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when ram <= price and ram <= screen
then ram
when price <= ram and price <= screen
then price
else screen
end
when ram = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when speed <= price and speed <= screen
then speed
when price <= speed and price <= screen
then price
else screen
end
when price = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when speed <= ram and speed <= screen
then speed
when ram <= speed and ram <= screen
then ram
else screen
end
when screen = case
when speed <= ram and speed <= price and speed <= screen
then speed
when ram <= speed and ram <= price and ram <= screen
then ram
when price <= speed and price <= ram and price <= screen
then price
else screen
end
then case
when speed <= ram and speed <= price
then speed
when ram <= speed and ram <= price
then ram
else price
end
end * 2
<=
case
when speed = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when ram >= price and ram >= screen
then ram
when price >= ram and price >= screen
then price
else screen
end
when ram = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when speed >= price and speed >= screen
then speed
when price >= speed and price >= screen
then price
else screen
end
when price = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when speed >= ram and speed >= screen
then speed
when ram >= speed and ram >= screen
then ram
else screen
end
when screen = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when speed >= ram and speed >= price
then speed
when ram >= speed and ram >= price
then ram
else price
end
end
and
case
when speed = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when ram >= price and ram >= screen
then ram
when price >= ram and price >= screen
then price
else screen
end
when ram = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when speed >= price and speed >= screen
then speed
when price >= speed and price >= screen
then price
else screen
end
when price = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when speed >= ram and speed >= screen
then speed
when ram >= speed and ram >= screen
then ram
else screen
end
when screen = case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
then case
when speed >= ram and speed >= price
then speed
when ram >= speed and ram >= price
then ram
else price
end
end * 2
<=
case
when speed >= ram and speed >= price and speed >= screen
then speed
when ram >= speed and ram >= price and ram >= screen
then ram
when price >= speed and price >= ram and price >= screen
then price
else screen
end
