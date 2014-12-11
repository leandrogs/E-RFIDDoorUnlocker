-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Dec 11, 2014 at 03:53 PM
-- Server version: 5.6.17
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `secdoorlock`
--
CREATE DATABASE IF NOT EXISTS `secdoorlock` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `secdoorlock`;

-- --------------------------------------------------------

--
-- Table structure for table `accesslogs`
--

CREATE TABLE IF NOT EXISTS `accesslogs` (
  `id` int(11) NOT NULL,
  `tagid_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `created` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `tagids`
--

CREATE TABLE IF NOT EXISTS `tagids` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tagid` varchar(20) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `tagids`
--

INSERT INTO `tagids` (`id`, `tagid`, `created`, `modified`) VALUES
(1, '53E693F4', '2014-12-06 23:56:40', '2014-12-06 23:56:40');

-- --------------------------------------------------------

--
-- Table structure for table `tagids_users`
--

CREATE TABLE IF NOT EXISTS `tagids_users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tagid_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_tagids_tagsids_users` (`tagid_id`),
  KEY `FK_users_tagsids_users` (`user_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `tagids_users`
--

INSERT INTO `tagids_users` (`id`, `tagid_id`, `user_id`, `created`, `modified`) VALUES
(1, 1, 1, '2014-12-11 14:21:52', '2014-12-11 14:21:52');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(80) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(100) NOT NULL,
  `role` varchar(20) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `username`, `password`, `email`, `role`, `created`, `modified`) VALUES
(1, 'admin', 'fe5e5ea150d426c46dc86baca9b0c9fee7bcbb12', 'admin@nfcunlocker.com', 'admin', '2014-12-11 13:31:10', '2014-12-11 13:31:10');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `tagids_users`
--
ALTER TABLE `tagids_users`
  ADD CONSTRAINT `FK_tagids_tagsids_users` FOREIGN KEY (`tagid_id`) REFERENCES `tagids` (`id`),
  ADD CONSTRAINT `FK_users_tagsids_users` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
