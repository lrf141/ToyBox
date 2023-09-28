#!/bin/bash

MYSQL_PROJECT=~/mysqlProject/mysql-server
TOYBOX_PROJECT=~/mysqlProject/mysql-server/storage/toybox/
patch -R ${MYSQL_PROJECT}/mysql-test/mysql-test-run.pl < ${TOYBOX_PROJECT}/mtr/mysql-test-run.patch
rm -rf ${MYSQL_PROJECT}/mysql-test/suite/toybox
