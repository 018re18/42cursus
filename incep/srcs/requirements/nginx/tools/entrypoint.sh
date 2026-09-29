#!/bin/sh
# Create a self-signed certificate and the site config, then hand PID 1 to nginx.
set -eu

: "${DOMAIN_NAME:?DOMAIN_NAME is not set}"
: "${NGINX_PORT:?NGINX_PORT is not set}"
: "${WP_PORT:?WP_PORT is not set}"

SSL_DIR=/etc/nginx/ssl

if [ ! -f "$SSL_DIR/inception.crt" ] || [ ! -f "$SSL_DIR/inception.key" ]; then
    echo "[nginx] generating self-signed certificate for $DOMAIN_NAME"
    openssl req -x509 -nodes -newkey rsa:2048 -days 365 \
        -keyout "$SSL_DIR/inception.key" \
        -out "$SSL_DIR/inception.crt" \
        -subj "/C=JP/L=Tokyo/O=42/CN=$DOMAIN_NAME" \
        -addext "subjectAltName=DNS:$DOMAIN_NAME" 2>/dev/null
    chmod 600 "$SSL_DIR/inception.key"
fi

# ":<port>" appended to HTTP_HOST, empty for the default HTTPS port.
if [ "$NGINX_PORT" = 443 ]; then HOST_PORT=""; else HOST_PORT=":$NGINX_PORT"; fi

sed -e "s/__DOMAIN_NAME__/$DOMAIN_NAME/g" \
    -e "s/__HOST_PORT__/$HOST_PORT/g" \
    -e "s/__NGINX_PORT__/$NGINX_PORT/g" \
    -e "s/__WP_PORT__/$WP_PORT/g" \
    /etc/nginx/templates/inception.conf.template > /etc/nginx/conf.d/inception.conf

nginx -t
exec "$@"
