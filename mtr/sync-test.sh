#!/bin/bash -eu

if [ $# -ne 3 ]; then
  exit 1;
fi

MYSQL_PROJECT=~/mysqlProject/mysql-server
MYSQL_TEST_SUITE_TOYBOX=${MYSQL_PROJECT}/mysql-test/suite/toybox/
TOYBOX_PROJECT=~/mysqlProject/mysql-server/storage/toybox/
TEST_CASE=$1

cp -f -i ${TOYBOX_PROJECT}/mtr/t/${TEST_CASE}.test ${MYSQL_TEST_SUITE_TOYBOX}/t/${TEST_CASE}.test
cp -f -i ${TOYBOX_PROJECT}/mtr/r/${TEST_CASE}.result ${MYSQL_TEST_SUITE_TOYBOX}/r/${TEST_CASE}.result
