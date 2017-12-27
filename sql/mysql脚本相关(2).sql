/*
SQLyog Ultimate v11.33 (32 bit)
MySQL - 5.7.20 : Database - wall
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`wall` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `wall`;

/*Table structure for table `tbl_statusdata` */

DROP TABLE IF EXISTS `tbl_statusdata`;

CREATE TABLE `tbl_statusdata` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `terminalId` char(20) DEFAULT NULL COMMENT '设备唯一id',
  `reportTime` datetime DEFAULT NULL COMMENT '上报时间',
  `writeTime` datetime DEFAULT NULL COMMENT '写表时间',
  `electricitys` int(11) DEFAULT '125' COMMENT '电流，界面系数0.01',
  `voltage` int(11) DEFAULT '125' COMMENT '电压，界面系数0.01',
  `electricResidue` int(11) DEFAULT '125' COMMENT '当前机器人剩余总电量，界面单位%',
  `robotStatus` int(11) DEFAULT '125' COMMENT '机器人当前状态0自动1手动2停止',
  `radarFront` int(11) DEFAULT '125' COMMENT '前雷达0正常1异常',
  `radarBack` int(11) DEFAULT '125' COMMENT '后雷达0正常1异常',
  `magnetismFront` int(11) DEFAULT '125' COMMENT '前磁导航0正常1异常',
  `magnetismBack` int(11) DEFAULT '125' COMMENT '后磁导航0正常1异常',
  `cardReader` int(11) DEFAULT '125' COMMENT '地标读卡器0正常1异常',
  `autoDoor` int(11) DEFAULT '125' COMMENT '自动门状态0正常1异常',
  `charger` int(11) DEFAULT '125' COMMENT '充电器状态0正常1异常',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8458 DEFAULT CHARSET=utf8;

/*Table structure for table `tbl_substationdata` */

DROP TABLE IF EXISTS `tbl_substationdata`;

CREATE TABLE `tbl_substationdata` (
  `dataId` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '数据自增id',
  `terminalId` char(20) NOT NULL COMMENT '设备唯一表示id',
  `reportTime` datetime NOT NULL COMMENT '数据上报时间',
  `writeTime` datetime NOT NULL COMMENT '数据写库时间',
  `pos` int(11) NOT NULL COMMENT '检测点位置',
  `sonPos` int(11) DEFAULT '-1' COMMENT '监测点子位置，默认-1表示没有子位置',
  `datatype` int(11) NOT NULL COMMENT '数据类型0开关状态1油位2红外3其它',
  `data` int(11) NOT NULL COMMENT '数据',
  `pictureType` int(11) NOT NULL COMMENT '图片类型0可见光1红外2其它',
  `pictureName` char(100) NOT NULL COMMENT '图片名称',
  PRIMARY KEY (`dataId`)
) ENGINE=InnoDB AUTO_INCREMENT=6977 DEFAULT CHARSET=utf8;

/*Table structure for table `tbl_users` */

DROP TABLE IF EXISTS `tbl_users`;

CREATE TABLE `tbl_users` (
  `userid` bigint(20) NOT NULL AUTO_INCREMENT,
  `createDate` datetime NOT NULL COMMENT '创建日期',
  `modifDate` datetime DEFAULT NULL COMMENT '修改日期',
  `userName` char(20) NOT NULL COMMENT '用户名',
  `userPwd` char(18) NOT NULL COMMENT '用户密码',
  `userAuth` int(11) NOT NULL DEFAULT '1' COMMENT '权限等级0管理员1普通2其它',
  PRIMARY KEY (`userid`,`userName`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

/*Table structure for table `tbl_userterminal` */

DROP TABLE IF EXISTS `tbl_userterminal`;

CREATE TABLE `tbl_userterminal` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `createDate` datetime NOT NULL COMMENT '添加日期',
  `modifDate` datetime DEFAULT NULL COMMENT '修改日期',
  `userid` bigint(20) NOT NULL COMMENT '用户表中用户id',
  `terminalId` char(20) NOT NULL COMMENT '设备唯一标识id',
  `terminalIp` char(20) NOT NULL COMMENT '工控机ip',
  `terminalPort` char(10) NOT NULL COMMENT '工控机prot',
  `cloudIp` char(20) NOT NULL COMMENT '云台Ip',
  `cloudPort` char(10) NOT NULL COMMENT '云台Port',
  `cloudUserName` char(50) NOT NULL COMMENT '云台用户名',
  `cloudUserPwd` char(30) NOT NULL COMMENT '云台登录密码',
  `ownerUnit` char(200) DEFAULT NULL COMMENT '设备使用单位',
  `remark` char(200) DEFAULT NULL COMMENT '设备备注信息',
  `posSize` int(11) DEFAULT NULL COMMENT '视觉监测点位置个数，不包含子位置',
  PRIMARY KEY (`id`,`terminalId`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
