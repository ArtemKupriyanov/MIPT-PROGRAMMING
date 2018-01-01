with ourpass as (
select distinct pt.id_psg from pass_in_trip join pass_in_trip as pt on pass_in_trip.id_psg = pt.id_psg and pass_in_trip.place = pt.place and (pass_in_trip.trip_no <> pt.trip_no or pass_in_trip.date <> pt.date))
select name from ourpass join passenger on ourpass.id_psg = passenger.id_psg

