FROM debian:bookworm

ARG WP_CLI_VERSION=2.12.0

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates curl mariadb-client \
        php8.2-fpm php8.2-cli php8.2-mysql php8.2-curl php8.2-gd \
        php8.2-mbstring php8.2-xml php8.2-zip php8.2-intl \
    && rm -rf /var/lib/apt/lists/* \
    && curl -fsSL -o /usr/local/bin/wp \
        "https://github.com/wp-cli/wp-cli/releases/download/v${WP_CLI_VERSION}/wp-cli-${WP_CLI_VERSION}.phar" \
    && chmod +x /usr/local/bin/wp \
    && mkdir -p /run/php /usr/src/wordpress /var/www/html \
    && wp core download --path=/usr/src/wordpress --allow-root \
    && chown -R www-data:www-data /usr/src/wordpress /var/www/html

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf
COPY --chmod=755 tools/entrypoint.sh /usr/local/bin/entrypoint.sh

WORKDIR /var/www/html
EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["php-fpm8.2", "--nodaemonize"]
