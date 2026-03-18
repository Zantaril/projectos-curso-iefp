import os
import requests
import secrets
from dotenv import load_dotenv
import basic_login


def authetication_two_fact():

    load_dotenv()

    TELEGRAM_BOT_TOKEN = (os.getenv("TELEGRAM_BOT_TOKEN") or "").strip()
    TELEGRAM_CHAT_ID = (os.getenv("TELEGRAM_CHAT_ID") or "").strip() 

    two_fa = f"{secrets.randbelow(10000):04d}"

    send_url = f"https://api.telegram.org/bot{TELEGRAM_BOT_TOKEN}/sendMessage"

    payload = {
        "chat_id":TELEGRAM_CHAT_ID,
        "text": f"O seu código secreto é: {two_fa}"
        }

    req = requests.post(send_url, json=payload, timeout= 10)


    login = input("Login feito com sucesso, introduzir código dois fatores: \n").strip()

    if login == two_fa:

        print("Autenticado com sucesso")
        return True

    else:

        print("Código errado. Prima enter para voltar a tentar o login.\n")
        input()
        basic_login.menu()
        return False

    

if __name__ == "__main__":
    authetication_two_fact()
  