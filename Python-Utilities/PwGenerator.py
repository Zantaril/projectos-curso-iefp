"""
exercício 4

Vamos criar um programa que gera uma palavra passe automaticamente através de X palavras 
contidas num ficheiro de texto(ficheiro tem 2405 palavras). 
X é 5 por defeito ou um número facultado pelo utilizador.

O programa tem que abrir o ficheiro com as palavras, ler 5 palavras das 2405 aleatoriamente, 
deve depois juntar as palavras com símbolos/números 
entre cada uma e por fim vai imprimir a palavra passe criada na consola.

"""
import random
import pathlib
path = pathlib.Path(__file__).parent / 'WordsList.txt'
file1 = open(path, 'r', encoding="utf-8")
Lines = file1.read().splitlines()


# Inserir cada elemento na password - DONE 
# Inserir numeros e simbolos entre cada palavra -  DONE
#Por cada palavra inserida na password insere
# um simbolo ou numero


password = []
numsSymb =["@", "£", "§", "¬", "€", ")", "(", "/", "&", "%", "$", "#",1,2,3,4,5,6,7,8,9,10,11,12,13]

while True:

    try:
        escolha = int(input("Quantas palavras quer na sua password(1 a 10):")) 
    except ValueError:
        print("\nIntruduza um valor válido\n")
        continue

    if escolha not in range(1,11):
        print("Inválido")
        escolha = int(input("Quantas palavras quer na sua password(1 a 10): \n"))
    else:
        password.extend(random.sample(Lines,escolha)) 
        password.extend(random.sample(numsSymb,escolha))  
        random.shuffle(password) 
        print()
    
    for i in password:
        print(i, end="")
    break

print("\n \n Enjoy your password!")

# TESTES TESTES
password=""
for i in range(escolha):
    password += Lines[random.randrange(len(Lines))]
    password += str(numsSymb[random.randrange(len(numsSymb))])

print(password)
    

    
