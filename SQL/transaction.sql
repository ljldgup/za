create table test(id int);

set autocommit = 0;

set tx_isolation='READ-UNCOMMITTED';
--set tx_isolation='read-committed';
--set tx_isolation='repeatable-read';
--set tx_isolation='serializable';

select @@tx_isolation;
start transaction;
truncate test;
insert into test values(1),(2),(3);
update from test set id = id * 2
insert into test select sqrt(id) from test;
commit


--------
start transaction

--共享锁：全表被锁，其他客户端无法update，insert,delete，可以select， commit后解除
select * from test limit 5  lock in share mode;
commit
select * from test where id > 4  lock in share mode;
commit

--排他锁：其他使用update，insert,delete，select ... for update查看时阻塞 仍然可以select
select * from test where id > 8 for update;
update test set id = id * 2 where id > 4;
commit