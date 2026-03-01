'''

Small Decimal to Binary, Hexdecimal and Octal converter made for fun.

'''
def BinConverter():
    
    user_number = int(input("Choose an integer to convert into binary.\nR: "))

    starter_num = user_number

    if user_number == 0:
        print("0")
        return
    
    if user_number < 0:

        print("Please enter a non-negative integer.")
        return
    else:
        converted_bin = []

        while user_number != 0:

            next_bit = user_number % 2
            user_number //= 2
            
            converted_bin.append(next_bit)

        print(f"\n{starter_num} in Binary is: ",''.join(str(x) for x in converted_bin[::-1]))
    
   
def HexConverter():

    user_number = int(input("Choose an integer to convert into Hexdecimal.\nR: "))

    starter_num = user_number

    if user_number == 0: 
        print("0")
        return
    
    if user_number < 0:

        print("Please enter a non-negative integer.")
        return
    else:
        
        converted_hex = []

        hex_table = {10:'A', 11:'B', 12:'C', 13:'D', 14:'E', 15:'F'}

        while user_number != 0:

            next_set = user_number % 16
            user_number //= 16

            if next_set >= 10:
                next_set = hex_table[next_set]

            converted_hex.append(next_set)

        print(f"\n{starter_num} in Hexdecimal is: ",''.join(str(x) for x in converted_hex[::-1]))


def OctalConverter():

    user_number = int(input("Choose an integer to convert into Octal.\nR: "))

    starter_num = user_number

    if user_number == 0: 
        print("0")
        return

    if user_number < 0:

        print("Please enter a non-negative integer.")
        return
    else:
        converted_oct = []

        while user_number != 0:

            next_bit = user_number % 8
            user_number //= 8
            
            converted_oct.append(next_bit)

        print(f"\n{starter_num} in Octal is: ",''.join(str(x) for x in converted_oct[::-1]))
    

def main():
    
    converter_choice = input("\nInteger to Binary, Hexdecimal or Octal converter.\n" \
    "Choose a converter \n1.Binary \n2.Hexdecimal \n3.Octal\nR: ")
    
    if converter_choice not in ("1","2","3"):
        print("Choose one of the options.")
    else:
        match converter_choice:

            case "1": BinConverter()
            case "2": HexConverter()
            case "3": OctalConverter()
            case _: print("Choose a valid option.")

if __name__ == "__main__":
    main()
