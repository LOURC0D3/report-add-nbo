#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t read_file(char* filename) {
    FILE* file = fopen(filename, "rb");
    uint32_t number;
    
    if (file == NULL) {
        printf("파일 열기 실패: %s\n", filename);
        exit(1);
    }

    size_t read_size = fread(&number, 1, sizeof(uint32_t), file);
    if (read_size != sizeof(uint32_t)) {
        printf("파일 읽기 실패 - 형식이 올바르지 않습니다. : %s\n", filename);
        exit(1);
    }

    fclose(file);

    uint32_t converted_number = 
        ((number << 24) & 0xFF000000) | 
        ((number << 8)  & 0x00FF0000) | 
        ((number >> 8)  & 0x0000FF00) | 
        ((number >> 24) & 0x000000FF);

    return converted_number;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("syntax : add-nbo <file1> <file2>\n");
        printf("sample : add-nbo a.bin b.bin\n");
        return -1;
    }

    uint32_t number1 = read_file(argv[1]);
    uint32_t number2 = read_file(argv[2]);
    uint32_t sum = number1 + number2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", number1, number1, number2, number2, sum, sum);
    return 0;
}
