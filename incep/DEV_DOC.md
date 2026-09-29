# Developer documentation

## Set up the environment from scratch

### Prerequisites

- A Linux virtual machine (e.g. Debian) with:
  - Docker Engine and the Docker Compose v2 plugin (`docker compose version`)
  - `make`, `sudo`
- Your user in the `docker` group (`sudo usermod -aG docker $USER`, then log in again).

### Configuration files

| File | Purpose |
|------|---------|
| `srcs/.env` | Non-secret settings: `LOGIN`, `DOMAIN_NAME`, `DATA_PATH`, database name/user, WordPress title, user names and e-mails. Edit `LOGIN`, `DOMAIN_NAME` and `DATA_PATH` to match your login. |
| `srcs/docker-compose.yml` | Services, named volumes, network and secrets. |
| `srcs/requirements/*/conf/` | `50-server.cnf` (MariaDB), `www.conf` (php-fpm pool), `inception.conf.template` (nginx vhost). |

The WordPress admin user name must not contain `admin`; the WordPress entrypoint refuses to start
otherwise.

### Secrets

`make` generates any missing file in `secrets/` with 24 random alphanumeric characters:

```
secrets/db_password.txt        # MariaDB user password     -> mariadb, wordpress
secrets/db_root_password.txt   # MariaDB root password     -> mariadb
secrets/credentials.txt        # WP_ADMIN_PASSWORD=...     -> wordpress
                               # WP_USER_PASSWORD=...
```

You can also write them by hand before the first `make` (keep `credentials.txt` in
`KEY=value` form, and avoid quotes in passwords). `secrets/` is in `.gitignore`: never commit it.
Compose mounts each file at `/run/secrets/<name>` in the containers that list it.

## Build and launch

```sh
make hosts    # once: 127.0.0.1 <DOMAIN_NAME> in /etc/hosts
make          # = make up: secrets + data dirs + docker compose up -d --build
```

The Makefile wraps `docker compose -f srcs/docker-compose.yml -p inception`. Other targets:

| Target | Command |
|--------|---------|
| `build` | `docker compose build` |
| `up` | `docker compose up -d --build` |
| `down` / `clean` | `docker compose down` |
| `start` / `stop` / `restart` | same-named compose commands |
| `ps` / `logs` | `docker compose ps` / `docker compose logs -f` |
| `fclean` | `docker compose down --rmi all --volumes`, then removes `$(DATA_PATH)/{mariadb,wordpress}` |
| `re` | `fclean` then `all` |

`DATA_PATH` can be overridden for local testing, e.g. `DATA_PATH=/tmp/inception make`.

### Startup sequence

1. **mariadb**: on an empty volume, `mariadb-install-db` creates the system tables. It then
   runs a bootstrap SQL script that sets the root password, creates `$MYSQL_DATABASE` and
   `$MYSQL_USER`, and writes a marker file `.inception_initialized`. Finally it `exec`s `mariadbd`.
   The healthcheck (`mariadb-admin ping`) marks it healthy.
2. **wordpress** starts once mariadb is healthy. It copies the WordPress core (downloaded at image
   build time into `/usr/src/wordpress`) into the empty volume and waits up to 60 s for the
   database. Then it runs `wp config create`, `wp core install` (admin user) and
   `wp user create` (second user), and `exec`s `php-fpm8.2 --nodaemonize`.
3. **nginx** generates a self-signed certificate for `$DOMAIN_NAME` if none exists, renders the
   vhost template, checks it with `nginx -t`, and `exec`s `nginx -g 'daemon off;'`.

Each step is skipped if it has already been done, so restarting a container is safe.

## Manage containers and volumes

```sh
docker compose -f srcs/docker-compose.yml -p inception ps
docker exec -it mariadb mariadb -u wpuser -p wordpress      # SQL shell (password: secrets/db_password.txt)
docker exec -it wordpress wp user list --allow-root         # WP-CLI
docker exec -it nginx nginx -T                              # dump the active nginx config
docker network inspect inception                            # the 3 containers on one bridge
docker volume ls                                            # mariadb_data, wordpress_data
docker volume inspect wordpress_data                        # shows device=/home/<login>/data/wordpress
docker image ls | grep inception                            # mariadb, wordpress, nginx images
```

After editing a Dockerfile or a file in `conf/` or `tools/`, run `make` again: Compose rebuilds
and recreates only the changed services.

Quick TLS check:

```sh
openssl s_client -connect <DOMAIN_NAME>:443 -tls1_2 </dev/null | grep Protocol   # accepted
openssl s_client -connect <DOMAIN_NAME>:443 -tls1_1 </dev/null                   # rejected
```

## Where the data lives and how it persists

| Volume | Mounted at | Host directory |
|--------|-----------|----------------|
| `mariadb_data` | `/var/lib/mysql` (mariadb) | `/home/<login>/data/mariadb` |
| `wordpress_data` | `/var/www/html` (wordpress, and read-only in nginx) | `/home/<login>/data/wordpress` |

Both are **named volumes** using the `local` driver with `type: none, o: bind, device: …`, so
Docker manages them by name but stores their content in the host directory. The Makefile creates
these directories before `docker compose up`.

- `make stop`, `make down`, rebuilding images, or a container crash: **data is kept**.
- `make fclean` (or `make re`): volumes and host directories are deleted, and the next `make`
  re-installs a fresh site. `sudo` may be requested because MariaDB files belong to the
  container's `mysql` user.

The TLS certificate is kept inside the nginx container and regenerated when the container is
recreated.
