create database dsf;
use dsf;
create table user (
    id int primary key not null auto_increment,
    name varchar(20) not null,
    password varchar(20) not null
)engine=innodb auto_increment=0 default charset=utf8;

insert into user(id, name, password) values(1, 'lxh', '123');
insert into user(id, name, password) values(2, 'xcg', '345');
insert into user(id, name, password) values(3, 'nwk', '123');