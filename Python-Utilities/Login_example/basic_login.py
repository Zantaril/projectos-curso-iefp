import os
import json
import stdiomask
import hashlib
import secrets
import TELEBOT
import random

#  Gonçalo Fonseca pi06


DB_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "db_users.json")

def hot_and_cold():

    guess = random.randint(1, 10)
    attempts = 3

    while attempts != 0:
        print(f"You have {attempts} attempts left\n")
        numb_guess = int(input("Choose a number to guess from 1 to 10:\nR: "))

        if numb_guess == guess:
            print(f"You guessed it! The number was {guess}")
            return
        elif numb_guess < guess:
            print("Cold!")
        else:
            print("Hot!")

        attempts -= 1

    print(f"Out of attempts! The number was {guess}")



def carregar_users():
    if not os.path.exists(DB_FILE):
        return {}
    with open(DB_FILE, "r") as f:
        return json.load(f)

def salvar_users(users):
    with open(DB_FILE, "w") as f:
        json.dump(users, f, indent=2)

def limpar(pausa):
    if pausa == 1:
        input("\nPressionar para continuar")
    elif pausa == 2:
        input("\nPressionar para sair")
    os.system('cls' if os.name == 'nt' else 'clear')
    return True

def registar():

    print('\n--- Criar Nova Conta ---')
    users = carregar_users()
    username = input("Novo Utilizador: ").strip()

    if username in users:
        print("Erro: Utilizador já existe!")
        return limpar(1)

    password = stdiomask.getpass(prompt="Nova Password: ", mask=' ').strip()
    salt = secrets.token_hex(16)
    passwordhash = hashlib.sha256((password + salt).encode()).hexdigest()

    users[username] = {"salt": salt, "hash": passwordhash}
    salvar_users(users)

    print(f"Utilizador '{username}' criado com sucesso!")
    return limpar(1)


def login():

    print('\n--- Login ---')

    users = carregar_users()
    username = input("User Name: ").strip()
    password = stdiomask.getpass(prompt="Password: ", mask=' ').strip()

    user_data = users.get(username)
    if not user_data:
        return False

    salt = user_data.get('salt', '')
    hashed_db = user_data.get('hash', '')
    passwordhash = hashlib.sha256((password + salt).encode()).hexdigest()

    two_fa_valid =TELEBOT.authetication_two_fact()

    if two_fa_valid:
        hot_and_cold()

    return passwordhash == hashed_db
    

def menu():

    while True:

        limpar(0)
        print("1. Fazer Login\n2. Criar Conta\n3. Sair\n")
        
        opcao = input("\nEscolha uma opção: ")

        if opcao == '1':
            if login():
                print('\nBem-vindo!')
                limpar(2)
                break
            else:
                print('\nAcesso Negado!')
                limpar(1)
        elif opcao == '2':
            registar()
        elif opcao == '3':
            break
        else:
            print("Opção inválida.")
            limpar(1)


if __name__ == "__main__":
    menu()