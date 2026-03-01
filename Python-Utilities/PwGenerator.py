import random
import pathlib
path = pathlib.Path(__file__).parent / 'WordsList.txt'
file1 = open(path, 'r', encoding="utf-8")
Lines = file1.read().splitlines()


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

print(password)
    

    
