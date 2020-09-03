select user,host,Shutdown_priv from mysql.user;
desc  mysql.user;
create user 'ljl'@'localhost' identified by '123123';
--on 后面是数据库和表
GRANT ALL ON *.* TO 'ljl'@'localhost';
flush privileges;
SHOW GRANTS FOR 'ljl'@'localhost';
REVOKE SELECT ON *.* FROM ljl@'localhost';
SHOW GRANTS FOR 'ljl'@'localhost';
drop user 'ljl'@'localhost';