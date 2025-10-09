#Scans a directory and removes temporary files (.tmp, .log, .bak, etc.).

import os
import argparse

TEMP_EXTENSIONS = [".tmp", ".log", ".bak", ".temp", ".old"]

def clean_temp_files(directory):
    removed = 0
    for root, _, files in os.walk(directory):
        for file in files:
            if any(file.lower().endswith(ext) for ext in TEMP_EXTENSIONS):
                path = os.path.join(root, file)
                try:
                    os.remove(path)
                    print(f"🧹 Removed: {path}")
                    removed += 1
                except Exception as e:
                    print(f"⚠️ Could not remove {path}: {e}")
    print(f"\n✅ Done! Removed {removed} temporary files.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Remove temporary files from a directory.")
    parser.add_argument("directory", help="Path to clean (e.g., . or /path/to/folder)")
    args = parser.parse_args()
    clean_temp_files(args.directory)

