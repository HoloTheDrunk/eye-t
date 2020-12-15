from PIL import ImageFont, ImageDraw, Image, ImageOps
from os import listdir, mkdir, path
from time import sleep


def save(letter, i, address , font):
    image = Image.new('RGB', (28, 28))
    draw = ImageDraw.Draw(image)
    width = font.getsize(letter)[0]
    height = font.getsize(letter)[1]
    draw.text((14 - int(width/2) , 14 - int(height/2) - 3 ), letter, font=font)
    image = ImageOps.invert(image)
    image.save(address)

def get_font(filename):
    return ImageFont.truetype("fonts/" + filename, 32)

def save_letter(letter, fonts):
    l =chr(letter)
    if not path.exists("set/" + str(letter)):
        mkdir("set/" + str(letter))
    for i in range(len(fonts)):
        save(l, i, "set/"+ str(letter) + "/" +str(i) + ".jpg" , fonts[i])


def main():
    fonts = listdir("fonts")
    for i in range(len(fonts)):
        fonts[i] = get_font(fonts[i])

    if not path.exists("set"):
        mkdir("set")
    for i in range(33, 126):
        try:
            print("Generating files for ", i,"->",chr(i), "..." )
            save_letter(i, fonts)
        except:
            print ("Error for character ", i)
        sleep(0.1)


if __name__ == "__main__":
    main()
