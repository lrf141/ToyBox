#!/bin/bash

MYSQL_PROJECT=~/mysqlProject/mysql-server
TOYBOX_PROJECT=~/mysqlProject/mysql-server/storage/toybox/
PATCH_LINE=`cat ${MYSQL_PROJECT}/mysql-test/mysql-test-run.pl | head -n 2 | tail -n 1 | sed -e "s/^.\{2\}//"`
PATCH=`echo "${PATCH_LINE}" | awk '{print $1}'`
PATCH_STATUS=`echo "${PATCH_LINE}" | awk '{print $2}'`
if [ "${PATCH}" != "patch" ] && [ "${PATCH_STATUS}" != "true" ]; then
  patch ${MYSQL_PROJECT}/mysql-test/mysql-test-run.pl ${TOYBOX_PROJECT}/mtr/mysql-test-run.patch
fi

mkdir ${MYSQL_PROJECT}/mysql-test/suite/toybox
mkdir ${MYSQL_PROJECT}/mysql-test/suite/toybox/include
mkdir ${MYSQL_PROJECT}/mysql-test/suite/toybox/t ${MYSQL_PROJECT}/mysql-test/suite/toybox/r
cp -r ${TOYBOX_PROJECT}/mtr/include ${MYSQL_PROJECT}/mysql-test/suite/toybox/
cp -r ${TOYBOX_PROJECT}/mtr/t/ ${MYSQL_PROJECT}/mysql-test/suite/toybox/
cp -r ${TOYBOX_PROJECT}/mtr/r/ ${MYSQL_PROJECT}/mysql-test/suite/toybox/
