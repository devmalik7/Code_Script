#Displays EXIF metadata for an image (camera, GPS, date, etc.)

from PIL import Image, ExifTags
import argparse

def view_exif(image_path):
    try:
        image = Image.open(image_path)
        exif_data = image._getexif()
        if not exif_data:
            print("❌ No EXIF metadata found.")
            return

        print(f"📸 EXIF Data for: {image_path}\n")
        for tag, value in exif_data.items():
            tag_name = ExifTags.TAGS.get(tag, tag)
            print(f"{tag_name:25}: {value}")
    except Exception as e:
        print(f"⚠️ Error reading EXIF data: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="View EXIF metadata of an image.")
    parser.add_argument("image", help="Path to the image file")
    args = parser.parse_args()
    view_exif(args.image)