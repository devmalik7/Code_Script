import tkinter as tk
import requests

def get_joke():
    """Fetch a random joke from JokeAPI and display it."""
    url = "https://v2.jokeapi.dev/joke/Any"
    try:
        response = requests.get(url)
        data = response.json()

        if data["type"] == "single":
            joke = data["joke"]
        else:
            joke = f"{data['setup']}\n\n{data['delivery']}"

        joke_text.config(state=tk.NORMAL)
        joke_text.delete(1.0, tk.END)
        joke_text.insert(tk.END, joke)
        joke_text.config(state=tk.DISABLED)
    except Exception as e:
        joke_text.config(state=tk.NORMAL)
        joke_text.delete(1.0, tk.END)
        joke_text.insert(tk.END, f"Error fetching joke:\n{e}")
        joke_text.config(state=tk.DISABLED)

root = tk.Tk()
root.title("Random Joke Generator")
root.geometry("500x300")
root.config(bg="#fafafa")

title = tk.Label(root, text="Random Joke Generator", font=("Helvetica", 16, "bold"), bg="#fafafa")
title.pack(pady=10)

joke_text = tk.Text(root, wrap=tk.WORD, font=("Helvetica", 12), bg="#fff", height=8, width=55)
joke_text.pack(padx=10, pady=10)
joke_text.config(state=tk.DISABLED)

next_button = tk.Button(root, text="Next Joke", command=get_joke, font=("Helvetica", 12, "bold"), bg="#4CAF50", fg="white")
next_button.pack(pady=10)

get_joke()

root.mainloop()
