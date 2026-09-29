# User documentation

## Services provided

| Service     | Role                                                              | Reachable from          |
|-------------|-------------------------------------------------------------------|-------------------------|
| `nginx`     | HTTPS web server (TLS 1.2 / 1.3), the only entry point            | `https://rookuma.42.fr` (port 443) |
| `wordpress` | The WordPress site, executed by php-fpm                           | internal only (port 9000) |
| `mariadb`   | Database holding posts, users and settings                        | internal only (port 3306) |

Data is kept in `/home/rookuma/data/` on the host, so it survives restarts.

## Start and stop

Run these from the repository root:

```sh
make          # build (if needed) and start everything
make stop     # stop the containers, nothing is deleted
make start    # start them again
make down     # remove the containers (the website and database are kept)
```

`make fclean` deletes **everything**, including the website and database. Only use it
to reset the project.

## Access the website

1. The first time, make the domain point to this machine: `make hosts`
   (this adds `127.0.0.1 rookuma.42.fr` to `/etc/hosts`).
2. Open <https://rookuma.42.fr>. The certificate is self-signed, so the browser shows a
   warning: accept it to continue.
3. The administration panel is at <https://rookuma.42.fr/wp-admin>.

Plain HTTP (port 80) is not served.

## Credentials

Passwords are generated automatically by `make` on the first run and stored in `secrets/`
(this folder is never committed to git):

| File                          | Contains                                                    |
|-------------------------------|-------------------------------------------------------------|
| `secrets/credentials.txt`     | `WP_ADMIN_PASSWORD` (user `siteowner`) and `WP_USER_PASSWORD` (user `writer`) |
| `secrets/db_password.txt`     | password of the database user `wpuser`                      |
| `secrets/db_root_password.txt`| password of the MariaDB `root` account                      |

User names and e-mail addresses are in `srcs/.env`.

To read the admin password: `cat secrets/credentials.txt`.

Passwords are only applied when the site is created for the first time. After that, change a
WordPress password from the admin panel (*Users → Profile*). To start over with new passwords,
delete the files in `secrets/` and run `make re` (this erases the site).

## Check that everything runs

```sh
make ps                      # all three containers should be "Up", mariadb "(healthy)"
make logs                    # live logs, Ctrl-C to quit
docker logs wordpress        # should end with "[wordpress] ready"
curl -kI https://rookuma.42.fr   # should answer HTTP/1.1 200
```

If a container keeps restarting, `docker logs <name>` shows the reason.
