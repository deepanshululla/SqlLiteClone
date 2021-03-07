# Relational DataBase Clone in C++

Disclaimer: This is not a production DB and is limited in capabilities in what it can do.
The goal of the project was to learn out the DB internals.
It should not be considered a replacement for a DB leave alone a replacement for SQLlite.

### Reason to work on this
I wanted to make my current knowledge of C++ by making something that is fun.
So relational DB is what we make.

The project is inspired from https://cstack.github.io/db_tutorial


### What it does?

1) This is a append only database, which means deletes and updates are not supported yet.

2) This only supports one table for now, whose schema looks like
 * int id
 * string email
 * string username
 
 
3) A basic where clause is supported to query by ID.


