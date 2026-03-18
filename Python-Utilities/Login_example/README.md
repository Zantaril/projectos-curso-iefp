# basic_login

Sistema de autenticação seguro em Python com verificação a dois fatores via Telegram, seguido de um mini-jogo de adivinhar números.

## Descrição

O projeto implementa um sistema de login com três camadas de segurança:

1. **Autenticação por password** — as passwords são armazenadas com hash SHA-256 e salt aleatório, nunca em texto simples.
2. **Autenticação de dois fatores (2FA)** — após o login, é enviado um código de 4 dígitos para o Telegram do utilizador via bot.
3. **Mini-jogo** — só após passar as duas camadas anteriores é que o utilizador acede ao jogo *Hot and Cold*.

## Estrutura do Projeto

```
basic_login/
├── basic_login.py       # Lógica principal: menu, login, registo
├── TELEBOT.py           # Autenticação 2FA via Telegram Bot API
├── db_users.json        # Base de dados de utilizadores (gerada automaticamente)
├── .env                 # Variáveis de ambiente (não incluído no repositório)
├── .env.example         # Exemplo de configuração do .env
└── README.md
```

## Instalação

### Pré-requisitos

- Python 3.8+
- Conta no Telegram e um bot criado via [@BotFather](https://t.me/BotFather)

### 1. Clonar o repositório

```bash
git clone https://github.com/teu-utilizador/basic_login.git
cd basic_login
```

### 2. Instalar dependências

```bash
pip install requests python-dotenv stdiomask
```

### 3. Configurar variáveis de ambiente

Copia o ficheiro de exemplo e preenche com os teus dados:

```bash
cp .env.example .env
```

Edita o `.env`:

```
TELEGRAM_BOT_TOKEN=o_teu_token_aqui
TELEGRAM_CHAT_ID=o_teu_chat_id_aqui
```

> Para obter o `CHAT_ID`, envia uma mensagem ao teu bot e acede a:  
> `https://api.telegram.org/bot<TOKEN>/getUpdates`

### 4. Executar

```bash
python basic_login.py
```

## Como Funciona

1. No menu principal, escolhe **Criar Conta** para registar um novo utilizador.
2. Faz **Login** com as tuas credenciais.
3. Um código de 4 dígitos será enviado para o teu Telegram — introduz-o para continuar.
4. Após autenticação bem-sucedida, o mini-jogo inicia.

## Tecnologias Utilizadas

- `hashlib` + `secrets` — hashing seguro de passwords com salt
- `Telegram Bot API` — envio de códigos 2FA
- `python-dotenv` — gestão segura de variáveis de ambiente
- `stdiomask` — input de password sem mostrar caracteres no terminal
