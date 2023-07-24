#!/bin/bash

MYSQL_PROJECT=~/mysqlProject/mysql-server
AVID_PROJECT=~/mysqlProject/mysql-server/storage/avid/
patch ${MYSQL_PROJECT}/mysql-test/mysql-test-run.pl ${AVID_PROJECT}/mtr/mysql-test-run.patch

mkdir ${MYSQL_PROJECT}/mysql-test/suite/avid
mkdir ${MYSQL_PROJECT}/mysql-test/suite/avid/include
mkdir ${MYSQL_PROJECT}/mysql-test/suite/avid/t ${MYSQL_PROJECT}/mysql-test/suite/avid/r
cp -r ${AVID_PROJECT}/mtr/include/ ${MYSQL_PROJECT}/mysql-test/suite/avid/include/
cp -r ${AVID_PROJECT}/mtr/t/ ${MYSQL_PROJECT}/mysql-test/suite/avid/t/
cp -r ${AVID_PROJECT}/mtr/r/ ${MYSQL_PROJECT}/mysql-test/suite/avid/r/
