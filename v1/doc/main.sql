

/* 创建数据库 */
create database dsf;

use dsf;

/* 创建黑名单表 */
CREATE TABLE `blacklist` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `id_card` varchar(64) NOT NULL,
    `name` varchar(20) NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7;


/* 创建客户端用户表 */
CREATE TABLE `user` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `name` varchar(20) NOT NULL,
    `password` varchar(20) NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7;
