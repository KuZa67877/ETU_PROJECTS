import PIL
import numpy as np
import math
from PIL import Image, ImageDraw


def pentagram(img, x, y, r, thickness, color):
    line_color = (color[0], color[1], color[2])
    draw = ImageDraw.Draw(img)
    coordinates = ((x-r,y-r),(x+r,y+r))
    draw.ellipse(coordinates, outline = tuple(color), width=thickness)
    coords = []
    for i in range(0,6):
        phi = (math.pi/5)*(2*i+3/2)
        
        node_i = (int(x+r*math.cos(phi)),int(y+r*math.sin(phi)))
        
        coords.append(node_i)
    for i in range(0, 5):
        draw.line((coords[i], coords[(i + 2) % 5]), fill=line_color, width=thickness)
    return img


def swap(img, x0,y0,x1,y1,width):
    new_image = img.copy()
    img1= img.crop((x0, y0, x0+width, y0+width))
    img1=img1.rotate(270)
    img2= img.crop((x1, y1, x1+width, y1+width))
    img2=img2.rotate(270)
    new_image.paste(img2,(x0,y0))
    new_image.paste(img1,(x1,y1))
    new_image = new_image.rotate(270)
    return new_image

def avg_color(img, x0, y0, x1, y1):
    new_image = img.copy()
    coord_x= img.size[0]
    coord_y=img.size[1]
    for x in range(x0,x1+1):
        for y in range(y0,y1+1):
            colors=[0,0,0]
            #перебор всех точек и проверка их на вхождение в изображение
            coordinats=[(x+1,y),(x-1,y),(x+1,y+1),(x+1,y-1),(x-1,y+1),(x-1,y-1),(x,y+1),(x,y-1)]
            for i in range(len(coordinats)):
                if (not(0 <= coordinats[i][0] <= coord_x)) or (not(0 <= coordinats[i][1] <= coord_y)):
                    coordinats.pop(i)
                    i-=1
            count_pixels=len(coordinats)
            for i in range(len(coordinats)):
                old_pixel = img.getpixel(coordinats[i])
                colors[0]+=old_pixel[0]
                colors[1]+=old_pixel[1]
                colors[2]+=old_pixel[2]
            new_color =  (int(colors[0]/count_pixels), int(colors[1]/count_pixels),int(colors[2]/count_pixels))
            new_image.putpixel((x,y),new_color)

    return new_image
