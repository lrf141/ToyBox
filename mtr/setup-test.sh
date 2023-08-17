#!/bin/bash

MYSQL_PROJECT=~/mysqlProject/mysql-server
TOYBOX_PROJECT=~/mysqlProject/mysql-server/storage/toybox/
patch ${MYSQL_PROJECT}/mysql-test/mysql-test-run.pl ${TOYBOX_PROJECT}/mtr/mysql-test-run.patch

mkdir ${MYSQL_PROJECT}/mysql-test/suite/toybox
mkdir ${MYSQL_PROJECT}/mysql-test/suite/toybox/include
mkdir ${MYSQL_PROJECT}/mysql-test/suite/toybox/t ${MYSQL_PROJECT}/mysql-test/suite/toybox/r
cp -r ${TOYBOX_PROJECT}/mtr/include ${MYSQL_PROJECT}/mysql-test/suite/toybox/
cp -r ${TOYBOX_PROJECT}/mtr/t/ ${MYSQL_PROJECT}/mysql-test/suite/toybox/
cp -r ${TOYBOX_PROJECT}/mtr/r/ ${MYSQL_PROJECT}/mysql-test/suite/toybox/
