'''

Gonçalo Fonseca PI06


'''

import tkinter as tk
import pathlib
import json
from tkinter.messagebox import showinfo

# FILE In
path_users = pathlib.Path(__file__).parent / 'user_database.json'
file1 = open(path_users, 'r', encoding="utf-8")
user_data = json.load(file1)

root = tk.Tk()
root.title("PI06 NEW USED CARS")
root.geometry("350x350")


frame = tk.Frame(root)
frame.place(relx=0.5, rely=0.5, anchor="center")

tk.Label(frame, text="Username:").pack(pady=2)
username_entry = tk.Entry(frame, bg="white", width=20)
username_entry.pack(pady=5)

tk.Label(frame, text="Password:").pack(pady=2)
password_entry = tk.Entry(frame, show="*", bg="white", width=20)
password_entry.pack(pady=5)

def register_user():

    reg_window = tk.Toplevel()
    reg_window.title("Register")
    reg_window.geometry("300x250")

    tk.Label(reg_window, text="Username:").pack(pady=5)
    reg_username = tk.Entry(reg_window, bg="white", width=20)
    reg_username.pack()

    tk.Label(reg_window, text="Password:").pack(pady=5)
    reg_password = tk.Entry(reg_window, show="*", bg="white", width=20)
    reg_password.pack()

    def save_user():

        new_user = {
            "username": reg_username.get().strip(),
            "password": reg_password.get().strip(),
            "admin": False
        }
        for user in user_data["USERBASE"]:
            if user["username"] == new_user["username"]:
                showinfo(message="Username already exists!")
                return
            
        user_data["USERBASE"].append(new_user)

        with open(path_users, "w", encoding="utf-8") as f:
            json.dump(user_data, f, indent=4, ensure_ascii=False)

        
        showinfo(message="Registered successfully!")
        reg_window.destroy()
      

    tk.Button(reg_window, text="Register", command=save_user).pack(pady=10)

def login():

    auth_user = username_entry.get().strip()
    auth_password = password_entry.get().strip()

    for user in user_data["USERBASE"]:
        if user["username"] == auth_user and user["password"] == auth_password:
            if user.get("admin"):
                showinfo(title="Log in successful", message=f"Welcome {auth_user}")
                stock_management()
            else:
                showinfo(title="Log in successful", message=f"Welcome {auth_user}")
                store_window()
            return
        
    showinfo(title="Log in failed", message="Incorrect user or password.")

tk.Button(frame, text="Log in", command=login).pack(side="left", pady=5)
tk.Button(frame, text="Register", command=register_user).pack(side="left", pady=5)

def save_button_clicked():

    new_car = {key: entry.get() for key, entry in entries.items()}

    user_data["Products"].append(new_car)

    with open(path_users, "w", encoding="utf-8") as f:
        json.dump(user_data, f, indent=4, ensure_ascii=False)

    showinfo(message="Saved Successfully!")

def stock_management():

    root.withdraw()
    stock_window = tk.Toplevel()
    stock_window.title("Stock manager")
    stock_window.geometry("600x600")

    global entries
    entries = {}

    designations = ["Brand", "Model", "Traction", "Kms", "Year", "License Plate", "Price"]

    top_frame = tk.Frame(stock_window)
    top_frame.pack(fill="x", pady=(10, 5))
    tk.Label(top_frame, font=("Arial", 16), text="Manage your cars here").pack()
    tk.Label(top_frame, font=("Arial", 13), text="Insert new car").pack(anchor="w", padx=20)

    grid_frame = tk.Frame(stock_window)
    grid_frame.pack(fill="x", padx=20)

    for index, field in enumerate(designations):
        row = (index // 3) * 2
        col = (index % 3) * 2

        tk.Label(grid_frame, text=field).grid(row=row, column=col, columnspan=2, sticky="w", padx=10)
        
        entry = tk.Entry(grid_frame, bg="white", width=20)
        entry.grid(row=row + 1, column=col, columnspan=2, sticky="w", padx=10, pady=(0, 10))
        entries[field] = entry

    tk.Button(grid_frame, text="Save Car", command=save_button_clicked).grid(
        row=5, column=0, columnspan=6, pady=10
    )

    bottom_frame = tk.Frame(stock_window)
    bottom_frame.pack(fill="x", padx=20, pady=10)
    tk.Label(bottom_frame, font=("Arial", 13), text="Search inventory").pack(anchor="w", padx=20)

    search_var = tk.StringVar()
    suggestion_list = tk.Listbox(bottom_frame, font=("Arial", 12))
    suggestion_list.pack(fill="x", padx=20)

    def show_car_list(filter_term=""):

        suggestion_list.delete(0, tk.END)
        
        for car in user_data["Products"]:
            display = f'{car.get("Brand")} {car.get("Model")} | {car.get("Traction")} | {car.get("Kms")}kms | {car.get("Year")} | {car.get("License Plate")} | {car.get("Price")}€'
            if filter_term.lower() in display.lower():
                suggestion_list.insert(tk.END, display)

    tk.Button(bottom_frame, text="Show inventory", command=lambda: show_car_list(search_var.get())).pack(side="left")
    
    def delete_car():
        selected = suggestion_list.curselection()
        if not selected:
            showinfo(message="No car selected!")
            return
        
        selected_text = suggestion_list.get(selected[0])
        license_plate = selected_text.split("|")[4].strip()

        for car in user_data["Products"]:
            if car.get("License Plate") == license_plate:
                user_data["Products"].remove(car)
                break

        with open(path_users, "w", encoding="utf-8") as f:
            json.dump(user_data, f, indent=4, ensure_ascii=False)

        showinfo(message="Car removed!")
        show_car_list()

    tk.Button(bottom_frame, text="Remove car", command=delete_car).pack(side="left")

    def exit_to_login():
        stock_window.destroy()
        root.deiconify()

    tk.Button(bottom_frame, text="Exit to login", command=exit_to_login).pack(side="right")

def store_window():

    root.withdraw()
    shop_window = tk.Toplevel()
    shop_window.title("PI06 NEW USED CARS")
    shop_window.geometry("900x800")

    tk.Label(shop_window, font=("Arial", 16), text="PI06 NEW USED CARS").pack(pady=10)

    search_var = tk.StringVar()
    search_entry = tk.Entry(shop_window, textvariable=search_var, font=("Arial", 12))
    search_entry.pack(anchor="w", fill="x", padx=20)

    checkboxes = {}

    checkbox_frame = tk.Frame(shop_window)
    checkbox_frame.pack(fill="both", expand=True, padx=20, pady=10)

    def show_cars(filter_term=""):

        for widget in checkbox_frame.winfo_children():
            widget.destroy()
        checkboxes.clear()

        for car in user_data["Products"]:
            display = f'{car.get("Brand")} {car.get("Model")} | {car.get("Traction")} | {car.get("Kms")}kms | {car.get("Year")} | {car.get("License Plate")} | {car.get("Price")}€'
            
            if filter_term.lower() in display.lower():
                var = tk.BooleanVar()
                tk.Checkbutton(checkbox_frame, text=display, variable=var, anchor="w").pack(fill="x")
                checkboxes[car.get("License Plate")] = var

    def buy_car():

        selected_plates = [plate for plate, var in checkboxes.items() if var.get()]
        
        if not selected_plates:
            showinfo(message="No car selected!")
            return
        
        user_data["Products"] = [car for car in user_data["Products"] if car.get("License Plate") not in selected_plates]
        
        with open(path_users, "w", encoding="utf-8") as f:
            json.dump(user_data, f, indent=4, ensure_ascii=False)
        
        showinfo(message=f"{len(selected_plates)} car(s) purchased!")
        show_cars()

    def exit_to_login():
        shop_window.destroy()
        root.deiconify()

    button_frame = tk.Frame(shop_window)
    button_frame.pack(pady=5)

    tk.Button(button_frame, text="Search", command=lambda: show_cars(search_var.get())).pack(side="left", padx=5)
    tk.Button(button_frame, text="Buy car", command=buy_car).pack(side="left", padx=5)
    tk.Button(button_frame, text="Exit to login", command=exit_to_login).pack(side="left", padx=5)

    show_cars()

tk.mainloop()