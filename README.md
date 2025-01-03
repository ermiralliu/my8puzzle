Initially an algorithms lab done in Java. The 50 move 4x4 puzzle required over 4 GB of RAM to be done.
In Java each object header is 12 to 16 bytes, so not space efficient at all.
So I switched to c++ which no memory overhead of this type.
Later I will add an SQL database to store the queue and set when they get over a certain size 
and threads to manage the saving and fetching the boards saved in the database