import os
import PyPDF2

folder_path = os.path.dirname(os.path.abspath(__file__))

total_pdfs = 0
converted = 0
skipped = 0
failed = 0

for filename in os.listdir(folder_path):
    if filename.lower().endswith('.pdf'):
        total_pdfs += 1
        pdf_file_path = os.path.join(folder_path, filename)
        txt_file_path = os.path.join(folder_path, f"{os.path.splitext(filename)[0]}.txt")
        
        try:
            with open(pdf_file_path, 'rb') as file:
                reader = PyPDF2.PdfReader(file)
                text = ''
                for page in reader.pages:
                    page_text = page.extract_text()
                    if page_text:
                        text += page_text + '\n'
            
            if text.strip():
                with open(txt_file_path, 'w', encoding='utf-8') as f:
                    f.write(text)
                print(f"✅ Converted '{filename}' to '{os.path.basename(txt_file_path)}'")
                converted += 1
            else:
                print(f"⚠ Skipped '{filename}': no text found")
                skipped += 1
        
        except Exception as e:
            print(f"❌ Failed to convert '{filename}': {e}")
            failed += 1

print("\n--- Summary ---")
print(f"Total PDFs found: {total_pdfs}")
print(f"Converted: {converted}")
print(f"Skipped (no text): {skipped}")
print(f"Failed: {failed}")
print("Processing complete.")
