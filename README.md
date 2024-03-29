# Relational DataBase Clone in C++

Disclaimer: This is not a production DB and is limited in capabilities in what it can do.
The goal of the project was to learn out the DB internals.
It should not be considered a replacement for a DB leave alone a replacement for SQLlite.

### Reason to work on this
I wanted to make my current knowledge of C++ by making something that is fun.
So relational DB is what we make.

The project is inspired from https://cstack.github.io/db_tutorial

This however just takes advantage of the C++ map stl library for storing data over the filesystem.

### What it does?

1) This is a append only database, which means deletes and updates are not supported yet.

2) This only supports one table for now, whose schema looks like
 * int id
 * string email
 * string username
 
 
3) A basic where clause is supported to query by ID.



### syntax

The front end of the DataBase is very naive and is a work in progress.

So far, we support REPL that works something like this:

```
db > insert 1 user1 email1
Executed.
db > select *
(1, user1, email1)
Executed.
db > insert 2 user2 email2
Executed.
db > select *
(1, user1, email1)
(2, user2, email2)
Executed.
db > select * where id = 2
(2, user2, email2)
Executed.
db > .exit
 
```

[Link to documentation](https://deepanshululla.com/SqlLiteClone/)




## Prerequisites

1. Conan the C++ package manager

2. Rspec the BDD test tool in Ruby

## setup

1. git clone <project>

2. run `make installDeps`

3. Run as you run your CMAKE project.


#### Todo

1. Create a Docker image for this.

2. Support updates and deletes.

PRs welcome!