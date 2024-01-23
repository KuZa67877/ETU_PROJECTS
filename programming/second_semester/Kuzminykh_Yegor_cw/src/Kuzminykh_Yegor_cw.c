#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>

struct Png {
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

void terminate(char *text, struct Png *image) {
    puts(text);
    png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
    if (image->row_pointers) {
        for (int y = 0; y < image->height; y++)
            free(image->row_pointers[y]);
        free(image->row_pointers);
        free(image);
    }
    exit(-1);
}


void read_png_file(char *file_name, struct Png *image) {
    char header[8];

    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        terminate("Sorry, file don't opened\n", image);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        terminate("File does not have a PNG extension\n", image);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) {
        terminate("Error creating the PNG structure\n", image);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        terminate("Error creating the PNG structure\n", image);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        terminate("Error calling the png_init_io function\n", image);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        terminate("Error during read_image\n", image);
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (int y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}


void write_png_file(char *file_name, struct Png *image) {

    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        terminate("Error when opening the resulting file\n", image);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) {
        terminate("Error: png_create_write_struct failed\n", image);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        terminate("Error: png_create_info_struct failed\n", image);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        terminate("Error calling the png_init_io function\n", image);
    }

    png_init_io(image->png_ptr, fp);


    if (setjmp(png_jmpbuf(image->png_ptr))) {
        terminate("Error during writing header\n", image);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        terminate("Byte reading error\n", image);
    }

    png_write_image(image->png_ptr, image->row_pointers);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        terminate("Error during end of write\n", image);
    }

    png_write_end(image->png_ptr, NULL);

    for (int y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}

void check_coords(struct Png *image, int *x, int *y) {
    if (*x < 0) {
        *x = 0;
    }
    if (*x >= image->width) {
        *x = image->width - 1;
    }
    if (*y < 0) {
        *y = 0;
    }
    if (*y >= image->height) {
        *y = image->height - 1;
    }

}

void black_and_white(struct Png *image, int flag) {
    int x, y, sum;
    int count = png_get_channels(image->png_ptr, image->info_ptr);
    for (y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (x = 0; x < image->width; x++) {
            png_byte *ptr = &(row[x * count]);
            if (flag == 0) {
                sum = (ptr[0] + ptr[1] + ptr[2]) / 3;
            } else {
                sum = 0.36 * ptr[0] + 0.53 * ptr[1] + 0.11 * ptr[2];
            }
            for (int i = 0; i < 3; i++) {
                ptr[i] = sum;
            }
        }
    }
}

void crop(struct Png *image, int x_start, int y_start, int x_end, int y_end) {
    check_coords(image, &x_start, &y_start);
    check_coords(image, &x_end, &y_end);
    if (x_start <= 0 && y_start <= 0 && x_end <= 0 && y_end <= 0) {
        printf("Enter the correct coordinates\n");
        return;
    }
    if (x_start >= image->width - 1 && x_end >= image->width - 1 && y_start >= image->height - 1 &&
        y_end >= image->height - 1) {
        printf("Enter the correct coordinates\n");
        return;
    }
    png_bytep *new_pointers = (png_bytep *) malloc(sizeof(png_bytep) * (y_end - y_start));
    int count = png_get_channels(image->png_ptr, image->info_ptr);
    for (int y = y_start; y < y_end; y++) {
        png_byte *row = image->row_pointers[y];
        new_pointers[y - y_start] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
        memcpy(new_pointers[y - y_start], row + x_start * count, (x_end - x_start) * count);
    }
    image->row_pointers = new_pointers;
    image->height = y_end - y_start;
    image->width = x_end - x_start;
}

void inverse_circle(struct Png *image, int x0, int y0, int r) {
    check_coords(image, &x0, &y0);
    int count = png_get_channels(image->png_ptr, image->info_ptr);
    for (int y = y0 - r; y < y0 + r; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = x0 - r; x < x0 + r; x++) {
            if ((y - y0) * (y - y0) + (x - x0) * (x - x0) <= r * r) {
                if (x >= 0 && x < image->width && y >= 0 && y < image->height) {
                    png_byte *ptr = &(row[x * count]);
                    for (int i = 0; i < 3; i++) {
                        ptr[i] = 255 - ptr[i];
                    }
                }
            }
        }
    }
}

void inverse_square(struct Png *image, int x0, int y0, int x1, int y1) {
    int radius = (x1 - x0) / 2;
    int x = (x1 + x0) / 2;
    int y = (y1 + y0) / 2;
    inverse_circle(image, x, y, radius);
}

void change_pixel(struct Png *image, int x, int y, png_byte r, png_byte g, png_byte b, png_byte a) {
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) {
        return;
    }
    int count = png_get_channels(image->png_ptr, image->info_ptr);
    png_bytep ptr = image->row_pointers[y] + x * count;
    ptr[0] = r;
    ptr[1] = g;
    ptr[2] = b;
    if (count > 3) {
        ptr[3] = a;
    }
}

void draw_circle(struct Png *image, int x, int y, png_byte r, png_byte g, png_byte b, png_byte a, int thickness) {
    int radius = thickness / 2;
    for (int i = y - radius; i < y + radius; i++) {
        for (int j = x - radius; j < x + radius; j++) {
            if ((i - y) * (i - y) + (j - x) * (j - x) <= radius * radius) {
                change_pixel(image, j, i, r, g, b, a);
            }
        }
    }
}

void draw(struct Png *image, int x0, int y0, int x1, int y1, png_byte r, png_byte g, png_byte b, png_byte a,
          int thickness) {
    check_coords(image, &x0, &y0);
    check_coords(image, &x1, &y1);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        if (x0 >= 0 && x0 < image->width && y0 >= 0 && y0 < image->height) {
            draw_circle(image, x0, y0, r, g, b, a, thickness);
            change_pixel(image, x0, y0, r, g, b, a);
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }

    }
}

void print_info(struct Png *image) {
    printf("Information about the image:\n");
    printf("Image width: %d\n", image->width);
    printf("Image height: %d\n", image->height);
    printf("Image color type: %d\n", image->color_type);
    printf("Image bit depth: %d\n", image->bit_depth);
}

void print_help() {
    puts("Usage: [OPTIONS] [ARGUMENTS]\n");
    puts("OPTIONS:");
    puts("    --help, -h          Information about using the program");
    puts("   --black_and_white,-W Translating an image into black and white");
    puts("    --crop, -C          Cropping an image to a specified area");
    puts("    --draw, -D          Drawing a line");
    puts("    --inverse, -I       Inverting the image in a given circle\n");
    puts("ARGUMENTS:");
    puts("    --path, -P          Entering an image name to edit");
    puts("    --name, -N          Entering the name of the final image");
    puts("    --x0, -x            Coordinates of 1 point on Ox");
    puts("    --y0, -y            Coordinates of 1 point on the Oy");
    puts("    --x1, -w            Coordinates of 2 points on Ox");
    puts("    --y1, -z            Coordinates of 2 points on the Oy");
    puts("    --radius, -p        Circle radius length");
    puts("    --red, -r           Value for red (0 to 255)");
    puts("    --green, -g         Value for green (0 to 255)");
    puts("    --blue, -b          Value for blue (0 to 255)");
    puts("    --alpha, -a         Value for transparency (0 to 255)");
    puts("    --thickness, -t     Value for line thickness");
    puts("    --black, -B         Changing the algorithm for converting the image to black and white");
    puts("    --print, -i         Displaying information about the captured image");
}

struct Config {
    int x0;
    int x1;
    int y0;
    int y1;
    int red;
    int green;
    int blue;
    int alpha;
    int radius;
    int thickness;
    int black_and_white;
    int crop;
    int invert;
    int draw;
    int help;
    int black;
    int print;
};

int main(int argc, char **argv) {
    int rez = 0;
    char *path_to_file;
    char *name_file;
    struct Config config = {0, 0, 0, 0, 255, 0, 0, 255, -1, 1, 0,
                            0, 0, 0, 0, 0, 0};
    path_to_file = malloc(sizeof(char) * PATH_MAX);
    name_file = malloc(sizeof(char) * PATH_MAX);
    static struct option long_option[] = {
            {"help",            no_argument,       0, 'h'},
            {"x0",              required_argument, 0, 'x'},
            {"x1",              required_argument, 0, 'y'},
            {"y0",              required_argument, 0, 'w'},
            {"y1",              required_argument, 0, 'z'},
            {"radius",          required_argument, 0, 'p'},
            {"black_and_white", no_argument,       0, 'W'},
            {"black",           no_argument,       0, 'B'},
            {"crop",            no_argument,       0, 'C'},
            {"inverse",         no_argument,       0, 'I'},
            {"draw",            no_argument,       0, 'D'},
            {"red",             required_argument, 0, 'r'},
            {"green",           required_argument, 0, 'g'},
            {"blue",            required_argument, 0, 'b'},
            {"alpha",           required_argument, 0, 'a'},
            {"thickness",       required_argument, 0, 't'},
            {"path",            required_argument, 0, 'P'},
            {"name",            required_argument, 0, 'N'},
            {"print",           no_argument,       0, 'i'}
    };
    struct Png image;
    while ((rez = getopt_long(argc, argv, "hx:y:w:z:WCiDIN:P:r:g:b:a:t:p:B", long_option, NULL)) != -1) {
        switch (rez) {
            case 'h':
                config.help = 1;
                break;
            case 'x':
                config.x0 = atoi(optarg);
                break;
            case 'y':
                config.x1 = atoi(optarg);
                break;
            case 'w':
                config.y0 = atoi(optarg);
                break;
            case 'z':
                config.y1 = atoi(optarg);
                break;
            case 'p':
                config.radius = atoi(optarg);
                break;
            case 'W':
                config.black_and_white = 1;
                break;
            case 'r':
                config.red = atoi(optarg);
                break;
            case 'g':
                config.green = atoi(optarg);
                break;
            case 'b':
                config.blue = atoi(optarg);
                break;
            case 'a':
                config.alpha = atoi(optarg);
                break;
            case 't':
                config.thickness = atoi(optarg);
                break;
            case 'C':
                config.crop = 1;
                break;
            case 'I':
                config.invert = 1;
                break;
            case 'D':
                config.draw = 1;
                break;
            case 'P':
                strcpy(path_to_file, optarg);
                break;
            case 'N':
                strcpy(name_file, optarg);
                break;
            case 'B':
                config.black = 1;
                break;
            case 'i':
                config.print = 1;
                break;

        }
    }

    if (strstr(path_to_file, ".png") != NULL) {
        read_png_file(path_to_file, &image);
    } else {
        print_help();
        exit(0);
    }
    if (config.help != 0) {
        print_help();
    }
    if (config.crop == 1) {
        crop(&image, config.x0, config.y0, config.x1, config.y1);
    }
    if (config.invert == 1) {
        if (config.radius == -1) {
            inverse_square(&image, config.x0, config.y0, config.x1, config.y1);
        } else {
            inverse_circle(&image, config.x0, config.y0, config.radius);
        }
    }
    if (config.draw == 1) {
        draw(&image, config.x0, config.y0, config.x1, config.y1, config.red, config.green, config.blue, config.alpha,
             config.thickness);
    }
    if (config.black_and_white == 1) {
        black_and_white(&image, config.black);
    }
    if (config.print == 1) {
        print_info(&image);
    }
    if (strstr(name_file, ".png") != NULL) {
        write_png_file(name_file, &image);
    } else {
        write_png_file("new_file.png", &image);
    }
    return 0;
}
