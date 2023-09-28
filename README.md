# Toybox

Simple Storage Engine for MySQL

## How to build

### Clone mysql-server from github
```bash
$ git clone git@github.com:mysql/mysql-server.git
$ cd mysql-server
```

### Clone this repository
```bash
mysql-server/$ cd storage/
mysql-server/storage$ git clone git@github.com:lrf141/toybox.git
```

### Build with MySQL Server
```bash
mysql-server$ mkdir build && cd $_
mysql-server/build$ cmake ../ -DCMAKE_BUILD_TYPE=Debug -DWITH_BOOST=./boost -DDOWNLOAD_BOOST=1
```

### (Optional) Run mysql-test-run
```bash
mysql-server/storage/toybox$ ./mtr/setup-test.sh
mysql-server/storage/toybox$ cd ../../build/mysql-test
mysql-server/build/mysql-test$ ./mtr --suite toybox
```

### Run with rr-debugger
```bash
mysql-server/storage/toybox$ sudo sysctl -w kernel.perf_event_paranoid=1
mysql-server/storage/toybox$ ./mtr/setup-test.sh
mysql-server/storage/toybox$ cd ../../build/mysql-test
mysql-server/build/mysql-test$ ./mtr --suite toybox --rr
```

### (Optional) Run unit test
```
mysql-server/build$ ./runtime_output_directory/toybox_tests 
```

### (Deprecated) Install/Uninstall Plugin
```sql
mysql> INSTALL PLUGIN toybox SONAME 'ha_toybox.so';

mysql> UNINSTALL PLUGIN toybox;
```
