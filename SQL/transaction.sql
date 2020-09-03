create table test(id int);


--mysql 事务锁主要通过事务版本号实现。

-- 事务中不会自动提交
set autocommit = 0;
--8.0 后的语法，查询用transaction_isolation
-- 8.0不同会话隔离级别也不同，所以要global，其他会话才能看见
--SET TRANSACTION ISOLATION LEVEL  READ UNCOMMITTED;
SET GLOBAL TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
--set transaction_isolation='read committed';
--set transaction_isolation='repeatable read';
--set transaction_isolation='serializable';

--这里执行事务是默认会设置到'repeatable-read'，时候
select @@transaction_isolation;
start transaction;

truncate test;
insert into test values(1),(2),(3);
update test set id = id * 2;
insert into test select sqrt(id) from test;
commit;

--在commit之前另外打开一个窗口,根据隔离程度可以看到不同内容

use test
select * from test;


--------
start transaction

--共享锁：全表被锁，其他客户端无法update，insert,delete，可以select， commit后解除
select * from test limit 5  lock in share mode;
commit
select * from test where id > 4 lock in share mode;
commit

--在commit之前另外打开一个窗口,根据隔离程度可以看到不同内容
use test
insert into test select sqrt(id) from test;



--排他锁：其他使用update，insert,delete，select ... for update查看时阻塞 仍然可以select
select * from test where id > 8 for update;
update test set id = id * 2 where id > 4;
commit