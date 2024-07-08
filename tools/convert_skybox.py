import sys
import os
from PIL import Image
from PIL.Image import Resampling

# Script created by Altiami
# Modified by Agent X.

out_dir = "skyboxes"

in_fn_id = sys.argv[1]
tile_count = 64
use_alt_tile_ratio = True
tile_len_ratio = 1 / 8 * 32 / 31 if use_alt_tile_ratio else 1 / 8

in_img = Image.open(f"{in_fn_id}")
if in_img.width > in_img.height:
    in_img = in_img.crop((
        (in_img.width - in_img.height) // 2,
        0,
        in_img.width - (in_img.width - in_img.height) // 2,
        in_img.height
    ))
elif in_img.width < in_img.height:
    in_img = in_img.crop((
        0,
        (in_img.height - in_img.width) // 2,
        in_img.width,
        in_img.height - (in_img.height - img_width) // 2
    ))
img_width = in_img.width
img_height = in_img.height
in_img = in_img.crop((0, 0, 2 * img_width, img_height + img_height * tile_len_ratio))
in_img.paste(in_img, (img_width, 0))
in_img.paste(
    in_img.crop((0, img_height - 1, in_img.width, img_height))
        .resize((in_img.width, in_img.height - img_height), Resampling.NEAREST),
    (0, img_height)
)

if not os.path.exists(out_dir):
    os.makedirs(out_dir)

for i in range(tile_count):
    x_t = i % 8
    y_t = i // 8
    separator = "\\" if os.name == "nt" else "/"
    in_img.crop((
            img_width * x_t // 8,
            img_height * y_t // 8,
            int(img_width * x_t // 8 + img_width * tile_len_ratio),
            int(img_height * y_t // 8 + img_height * tile_len_ratio)
        )).save(f"{out_dir}{separator}{os.path.basename(in_fn_id).split('.')[0]}.{f'{i:02}'}.rgba16.png", "PNG", optimize=True)
