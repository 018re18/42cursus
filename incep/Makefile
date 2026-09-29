NAME        := inception

SRCS_DIR    := srcs
ENV_FILE    := $(SRCS_DIR)/.env
ENV_EXAMPLE := $(SRCS_DIR)/.env.example
COMPOSE     := docker compose -f $(SRCS_DIR)/docker-compose.yml -p $(NAME)

# 42 login, only used to generate srcs/.env the first time (make LOGIN=wil).
LOGIN       ?= rookuma

# Read lazily from srcs/.env, so they are valid once the file is generated.
# DATA_PATH can be overridden from the shell (e.g. DATA_PATH=/tmp/x make).
env_value    = $(shell sed -n 's/^$(1)=//p' $(ENV_FILE) 2>/dev/null)
DOMAIN_NAME  = $(call env_value,DOMAIN_NAME)
DATA_PATH   ?= $(call env_value,DATA_PATH)

SECRETS_DIR := secrets
SECRETS     := $(SECRETS_DIR)/db_password.txt \
               $(SECRETS_DIR)/db_root_password.txt \
               $(SECRETS_DIR)/credentials.txt

# 24 random alphanumeric characters
RANDPW      = LC_ALL=C tr -dc 'A-Za-z0-9' < /dev/urandom | head -c 24

all: up

up: setup
	$(COMPOSE) up -d --build

build: setup
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

setup: env secrets data

env: $(ENV_FILE)

# Generated once from the template; later edits to srcs/.env are kept.
$(ENV_FILE):
	@sed 's/__LOGIN__/$(LOGIN)/g' $(ENV_EXAMPLE) > $@
	@echo "generated $@ for login '$(LOGIN)'"

data: env
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
hosts: env
	@grep -q "[[:space:]]$(DOMAIN_NAME)$$" /etc/hosts \
		|| echo "127.0.0.1 $(DOMAIN_NAME)" | sudo tee -a /etc/hosts

# -------------------------------------------------------------- cleanup ----

# Stop and remove containers and the network.
clean: down

# Also remove images, volumes and the persisted data on the host.
fclean:
	-$(COMPOSE) down --rmi all --volumes --remove-orphans
	@if [ -d "$(DATA_PATH)" ]; then \
		rm -rf $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress 2>/dev/null \
		|| sudo rm -rf $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress; \
	fi

re: fclean all

.PHONY: all up build down start stop restart ps logs setup env data secrets hosts clean fclean re
