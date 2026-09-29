NAME        := inception

SRCS_DIR    := srcs
ENV_FILE    := $(SRCS_DIR)/.env
COMPOSE     := docker compose -f $(SRCS_DIR)/docker-compose.yml -p $(NAME)

# Values are read from srcs/.env; DATA_PATH can be overridden from the shell.
LOGIN       := $(shell sed -n 's/^LOGIN=//p' $(ENV_FILE))
DOMAIN_NAME := $(shell sed -n 's/^DOMAIN_NAME=//p' $(ENV_FILE))
DATA_PATH   ?= $(shell sed -n 's/^DATA_PATH=//p' $(ENV_FILE))
export DATA_PATH

SECRETS_DIR := secrets
SECRETS     := $(SECRETS_DIR)/db_password.txt \
               $(SECRETS_DIR)/db_root_password.txt \
               $(SECRETS_DIR)/credentials.txt

# 24 random alphanumeric characters
RANDPW      = LC_ALL=C tr -dc 'A-Za-z0-9' < /dev/urandom | head -c 24

all: up

up: secrets data
	$(COMPOSE) up -d --build

build: secrets data
	$(COMPOSE) build

down:
	$(COMPOSE) down

start:
	$(COMPOSE) start

stop:
	$(COMPOSE) stop

restart:
	$(COMPOSE) restart

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs -f

# ---------------------------------------------------------------- setup ----

data:
	@mkdir -p $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress

secrets: $(SECRETS)

$(SECRETS_DIR)/db_password.txt $(SECRETS_DIR)/db_root_password.txt:
	@mkdir -p $(SECRETS_DIR)
	@$(RANDPW) > $@
	@chmod 600 $@
	@echo "generated $@"

$(SECRETS_DIR)/credentials.txt:
	@mkdir -p $(SECRETS_DIR)
	@printf 'WP_ADMIN_PASSWORD=%s\nWP_USER_PASSWORD=%s\n' "$$($(RANDPW))" "$$($(RANDPW))" > $@
	@chmod 600 $@
	@echo "generated $@"

# Point the domain to the local machine (needs sudo, run once).
hosts:
	@grep -q "[[:space:]]$(DOMAIN_NAME)$$" /etc/hosts \
		|| echo "127.0.0.1 $(DOMAIN_NAME)" | sudo tee -a /etc/hosts

# -------------------------------------------------------------- cleanup ----

# Stop and remove containers and the network.
clean: down

# Also remove images, volumes and the persisted data on the host.
fclean:
	$(COMPOSE) down --rmi all --volumes --remove-orphans
	@if [ -d "$(DATA_PATH)" ]; then \
		rm -rf $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress 2>/dev/null \
		|| sudo rm -rf $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress; \
	fi

re: fclean all

.PHONY: all up build down start stop restart ps logs data secrets hosts clean fclean re
