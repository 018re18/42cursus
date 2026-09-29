#!/bin/sh
# Initialise the database on first start, then hand PID 1 over to mariadbd.
set -eu

DATADIR=/var/lib/mysql
MARKER="$DATADIR/.inception_initialized"

: "${MYSQL_DATABASE:?MYSQL_DATABASE is not set}"
: "${MYSQL_USER:?MYSQL_USER is not set}"

DB_PASSWORD="$(cat /run/secrets/db_password)"
DB_ROOT_PASSWORD="$(cat /run/secrets/db_root_password)"

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld "$DATADIR"

if [ ! -d "$DATADIR/mysql" ]; then
    echo "[mariadb] creating system tables"
    mariadb-install-db --user=mysql --datadir="$DATADIR" \
        --skip-test-db --auth-root-authentication-method=normal >/dev/null
fi

if [ ! -f "$MARKER" ]; then
    echo "[mariadb] creating database '$MYSQL_DATABASE' and user '$MYSQL_USER'"
    mariadbd --user=mysql --datadir="$DATADIR" --bootstrap --skip-networking <<EOF
USE mysql;
FLUSH PRIVILEGES;
DELETE FROM mysql.global_priv WHERE User='';
DROP DATABASE IF EXISTS test;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
ALTER USER '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF
    touch "$MARKER"
    chown mysql:mysql "$MARKER"
    echo "[mariadb] initialisation done"
fi

exec "$@"
