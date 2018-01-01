select (select min(trip_no) from trip) as min1,
(select min(trip_no) from trip where trip_no > (select min(trip_no) from trip)) as min2,
(select min(trip_no) from trip where trip_no > (select min(trip_no) from trip where trip_no > (select min(trip_no) from trip))) as min3,
(select max(trip_no) from trip where trip_no < (select max(trip_no) from trip where trip_no < (select max(trip_no) from trip))) as max3,
(select max(trip_no) from trip where trip_no < (select max(trip_no) from trip)) as max2,
(select max(trip_no) from trip) as max1
