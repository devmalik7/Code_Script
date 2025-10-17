# PDF to Text Converter

This Python project automatically converts PDF files in a folder into plain text files using **PyPDF2**. Each PDF is processed page by page, and the extracted text is saved as a `.txt` file with the same name as the PDF.

---

## Features

- Automatically processes **all PDFs in the folder**.
- Skips PDFs with **no extractable text**.
- Handles errors gracefully and prints a **summary**.
- Creates `.txt` files named after the original PDF.

---

## Requirements

- Python 3.7 or higher
- PyPDF2 library

Install PyPDF2 with pip:

```bash
pip install PyPDF2
