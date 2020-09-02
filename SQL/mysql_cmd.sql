
mysql -uroot -p123456
SOURCE creat_table.sql

show databases like %es%

show create table RULES;
desc RULES;

drop index lmin_values on RULES;

alter database haha charset gbk

show create table RULES;

create view tv as select * from RULES;

--update会被执行
explain update RULES set alter_type='sdf' where min_values=0;

--视图中的值会被更改
select * from tv;

select * from RULES order by max_values desc;
select concat(device, parameter) from RULES; 
select * from RULES  where parameter like '%re';

-- 这里界面输入时要先将分割符改成//, 这应后面;会被当成文本处理，procedure才会被编译
DELIMITER //
create procedure procedure_test(in valve int, out ototal int)
BEGIN
    declare total int DEFAULT 5;
    select sum(max_values) + sum(min_values) into total from RULES where max_values > valve;
    select total into ototal;
END//
DELIMITER ;


set @total=1;
select sum(max_values) + sum(min_values) into @total from RULES where max_values > 1;
SELECT @total;

call procedure_test(2000,@total);
SELECT @total;

