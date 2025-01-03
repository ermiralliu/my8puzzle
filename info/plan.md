Since the Set lookup needs to be faster, it will have it's own database, which only has byte arrays.
Not even byte arrays, they'll be a single long.

Point Lookups (Finding a single row by ID): 
The performance difference between ordered and unordered IDs for point lookups 
(e.g., SELECT * FROM MyTable WHERE id = 123;) is usually less significant, 
especially if you have an index on the ID column. 
The database can quickly locate the row in the index, 
regardless of whether the IDs are ordered.

So we can just increment the id directly after giving the current id to another thread to check if it's contained 
and save to Queue table.
And sends the query to insert checked element to SET too.
These are done almost synchronously, so no problem i guess.

Meanwhile another thread fetches from the database and adds to a potential_box (that has the same box nr as the one we're working on currently).
We keep a count of items in the database

<!-- And another thread adds the set to the SET table  -->