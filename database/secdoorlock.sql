-- phpMyAdmin SQL Dump
-- version 4.2.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 07-Dez-2014 às 00:35
-- Versão do servidor: 10.0.15-MariaDB-log
-- PHP Version: 5.6.3

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
-- Estrutura da tabela `accesslog`
--

CREATE TABLE IF NOT EXISTS `accesslog` (
`id` int(11) NOT NULL,
  `tagid_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `created` datetime NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Extraindo dados da tabela `accesslog`
--

INSERT INTO `accesslog` (`id`, `tagid_id`, `user_id`, `created`) VALUES
(3, 1, 1, '2014-12-07 00:34:00');

-- --------------------------------------------------------

--
-- Estrutura da tabela `tagids`
--

CREATE TABLE IF NOT EXISTS `tagids` (
`id` int(11) NOT NULL,
  `tagid` varchar(20) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Extraindo dados da tabela `tagids`
--

INSERT INTO `tagids` (`id`, `tagid`, `created`, `modified`) VALUES
(1, '53E693F4', '2014-12-06 23:56:40', '2014-12-06 23:56:40');

-- --------------------------------------------------------

--
-- Estrutura da tabela `tagids_users`
--

CREATE TABLE IF NOT EXISTS `tagids_users` (
`id` int(11) NOT NULL,
  `tagid_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Extraindo dados da tabela `tagids_users`
--

INSERT INTO `tagids_users` (`id`, `tagid_id`, `user_id`, `created`, `modified`) VALUES
(1, 1, 1, NULL, NULL);

-- --------------------------------------------------------

--
-- Estrutura da tabela `users`
--

CREATE TABLE IF NOT EXISTS `users` (
`id` int(11) NOT NULL,
  `username` varchar(80) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(100) NOT NULL,
  `role` varchar(20) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Extraindo dados da tabela `users`
--

INSERT INTO `users` (`id`, `username`, `password`, `email`, `role`, `created`, `modified`) VALUES
(1, 'admin', 'fe5e5ea150d426c46dc86baca9b0c9fee7bcbb12', 'admin@nfcunlocker.com', 'admin', '2014-12-06 21:12:08', '2014-12-06 21:12:08'),
(2, 'teste', 'f87d7a2d778b1f417ddcd7ea325c8a8a21a4db76', 'teste1@votaminas.com', 'user', '2014-12-06 21:14:20', '2014-12-06 21:14:20');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `accesslog`
--
ALTER TABLE `accesslog`
 ADD PRIMARY KEY (`id`), ADD KEY `tagid_id` (`tagid_id`), ADD KEY `user_id` (`user_id`);

--
-- Indexes for table `tagids`
--
ALTER TABLE `tagids`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `tagids_users`
--
ALTER TABLE `tagids_users`
 ADD PRIMARY KEY (`id`), ADD KEY `FK_tagids_tagsids_users` (`tagid_id`), ADD KEY `FK_users_tagsids_users` (`user_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `accesslog`
--
ALTER TABLE `accesslog`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `tagids`
--
ALTER TABLE `tagids`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `tagids_users`
--
ALTER TABLE `tagids_users`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- Constraints for dumped tables
--

--
-- Limitadores para a tabela `accesslog`
--
ALTER TABLE `accesslog`
ADD CONSTRAINT `TAGID_ACCESS` FOREIGN KEY (`tagid_id`) REFERENCES `tagids` (`id`),
ADD CONSTRAINT `USERID_ACCESS` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

--
-- Limitadores para a tabela `tagids_users`
--
ALTER TABLE `tagids_users`
ADD CONSTRAINT `FK_tagids_tagsids_users` FOREIGN KEY (`tagid_id`) REFERENCES `tagids` (`id`),
ADD CONSTRAINT `FK_users_tagsids_users` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
