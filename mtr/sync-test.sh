#!/bin/bash -eu

if [ $# -ne 3 ]; then
  exit 1;
fi

MYSQL_PROJECT=~/mysqlProject/mysql-server
MYSQL_TEST_SUITE_AVID=${MYSQL_PROJECT}/mysql-test/suite/avid/
AVID_PROJECT=~/mysqlProject/mysql-server/storage/avid/
TEST_CASE=$1

cp -f -i ${AVID_PROJECT}/mtr/t/${TEST_CASE}.test ${MYSQL_TEST_SUITE_AVID}/t/${TEST_CASE}.test
cp -f -i ${AVID_PROJECT}/mtr/r/${TEST_CASE}.result ${MYSQL_TEST_SUITE_AVID}/r/${TEST_CASE}.result
