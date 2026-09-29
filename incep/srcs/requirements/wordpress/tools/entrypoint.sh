#!/bin/sh
# Install and configure WordPress on first start, then hand PID 1 to php-fpm.
set -eu

WP_PATH=/var/www/html

: "${DOMAIN_NAME:?DOMAIN_NAME is not set}"
: "${MYSQL_DATABASE:?MYSQL_DATABASE is not set}"
: "${MYSQL_USER:?MYSQL_USER is not set}"
: "${MYSQL_HOST:?MYSQL_HOST is not set}"
: "${WP_ADMIN_USER:?WP_ADMIN_USER is not set}"
: "${WP_USER:?WP_USER is not set}"

DB_PASSWORD="$(cat /run/secrets/db_password)"
# credentials.txt defines WP_ADMIN_PASSWORD and WP_USER_PASSWORD
. /run/secrets/credentials
: "${WP_ADMIN_PASSWORD:?WP_ADMIN_PASSWORD missing in credentials secret}"
: "${WP_USER_PASSWORD:?WP_USER_PASSWORD missing in credentials secret}"

# The subject forbids 'admin' / 'administrator' in the admin username.
case "$(echo "$WP_ADMIN_USER" | tr '[:upper:]' '[:lower:]')" in
    *admin*)
        echo "[wordpress] WP_ADMIN_USER must not contain 'admin'" >&2
        exit 1
        ;;
esac

wp() { command wp --allow-root --path="$WP_PATH" "$@"; }

# Populate the (initially empty) volume with the WordPress sources.
if [ ! -f "$WP_PATH/wp-load.php" ]; then
    echo "[wordpress] copying WordPress core into the volume"
    cp -a /usr/src/wordpress/. "$WP_PATH/"
fi

# Wait for MariaDB (bounded: gives up after 60 seconds).
i=0
until mariadb-admin ping -h "$MYSQL_HOST" -P "${MYSQL_PORT:-3306}" \
        -u "$MYSQL_USER" -p"$DB_PASSWORD" --silent >/dev/null 2>&1; do
    i=$((i + 1))
    if [ "$i" -ge 60 ]; then
        echo "[wordpress] MariaDB is unreachable, giving up" >&2
        exit 1
    fi
    sleep 1
done

if [ ! -f "$WP_PATH/wp-config.php" ]; then
    echo "[wordpress] generating wp-config.php"
    wp config create \
        --dbname="$MYSQL_DATABASE" \
        --dbuser="$MYSQL_USER" \
        --dbpass="$DB_PASSWORD" \
        --dbhost="$MYSQL_HOST:${MYSQL_PORT:-3306}" \
        --skip-check
fi

if ! wp core is-installed >/dev/null 2>&1; then
    echo "[wordpress] installing site https://$DOMAIN_NAME"
    wp core install \
        --url="https://$DOMAIN_NAME" \
        --title="${WP_TITLE:-Inception}" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --skip-email
fi

if ! wp user get "$WP_USER" --field=ID >/dev/null 2>&1; then
    echo "[wordpress] creating user '$WP_USER'"
    wp user create "$WP_USER" "$WP_USER_EMAIL" \
        --role="${WP_USER_ROLE:-author}" \
        --user_pass="$WP_USER_PASSWORD"
fi

chown -R www-data:www-data "$WP_PATH"

echo "[wordpress] ready"
exec "$@"
