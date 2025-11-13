import os
from PIL import Image

def batch_resize_images(input_folder, output_folder, target_width, target_height):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    # Process only JPG, JPEG, PNG files
    for filename in os.listdir(input_folder):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg')):
            input_path = os.path.join(input_folder, filename)
            output_path = os.path.join(output_folder, filename)
            try:
                with Image.open(input_path) as img:
                    img_resized = img.resize((target_width, target_height))
                    img_resized.save(output_path)
                    print(f"Resized: {filename}")
            except Exception as e:
                print(f"Error processing {filename}: {e}")

# Example usage
# batch_resize_images("input_folder_path", "output_folder_path", 800, 600)
