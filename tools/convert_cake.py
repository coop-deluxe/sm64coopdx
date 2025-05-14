from PIL import Image
import os

def split_image(image_path, output_folder, slice_width=80, slice_height=20):
    # Open the image
    image = Image.open(image_path)
    width, height = image.size
    
    # Ensure output folder exists
    os.makedirs(output_folder, exist_ok=True)
    
    slice_count = 0
    
    # Loop to create slices
    for y in range(0, height, slice_height):
        for x in range(0, width, slice_width):
            # Define the bounding box (left, upper, right, lower)
            box = (x, y, x + slice_width, y + slice_height)
            slice_img = image.crop(box)
            
            # Save slice
            slice_filename = os.path.join(output_folder, f"cake_end_texture_{slice_count}.png")
            slice_img.save(slice_filename)
            slice_count += 1
    
    print(f"Image split into {slice_count} slices and saved in '{output_folder}'.")

# Example usage
split_image("cake.png", "output_slices")
