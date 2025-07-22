#include <stdio.h>
#include <stdlib.h>   
#include <time.h>     

int level;
int arrayFish[6];
int* cursor;

void initData();               // �����f�[�^�̐ݒ�
void printFishes();            // ���̏�Ԃ�\��
void decreaseWater(long elapsedTime); // ���̌�������
int checkFishAlive();          // ���̐����m�F

int main(void) {
    long startTime = 0;
    long totalElapsedTime = 0;
    long prevElapsedTime = 0;
    int num;

    initData();        // ����������
    cursor = arrayFish;

    startTime = clock();  // �Q�[���J�n���Ԃ��L�^

    while (1) {
        printFishes();  // ���݂̐�����Ԃ�\��
        printf("���Ԑ����ɐ������܂����H ");
        scanf_s("%d", &num);


        // ���̓`�F�b�N
        if (num < 1 || num > 6) {
            printf("\n���͒l���Ԉ���Ă��܂��B\n");
            continue;
        }

        // ���o�ߎ��Ԃ��v�Z
        totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
        printf("���o�ߎ��� : %ld �b\n", totalElapsedTime);

        // �ŋ߂̌o�ߎ��Ԃ��v�Z
        long interval = totalElapsedTime - prevElapsedTime;
        printf("�ŋߌo�ߎ��� : %ld �b\n", interval);

        // �������炷����
        decreaseWater(interval);
        prevElapsedTime = totalElapsedTime;

        // �I�񂾐����ɑ΂��鏈��
        if (cursor[num - 1] <= 0) {
            printf("%d �ԋ��͂������ɂ܂����B�B���͗v��܂���B\n", num);
        }
        else if (cursor[num - 1] + 1 <= 100) {
            printf("%d �Ԑ����ɐ������܂��B\n", num);
            cursor[num - 1] += 1;
        }

        // ���x���A�b�v�����i20�b���ƂɊm�F�j
        if (totalElapsedTime / 20 > level - 1) {
            level++;
            printf("*** ���x���A�b�v�I���� %d ���x������ %d ���x���ɃA�b�v���܂����B***\n", level - 1, level);

            // �ŏI���x���ɒB������Q�[���I��
            if (level == 5) {
                printf("\n\n���߂łƂ��������܂��I�S�Ẵ��x�����N���A���܂����B�Q�[�����I�����܂��B\n");
                exit(0);
            }
        }

        // �S�Ă̋�������ł��邩�m�F
        if (checkFishAlive() == 0) {
            printf("�S�Ă̋����B�B�B(�L;��;�M)\n");
            exit(0);
        }
        else {
            printf("�����܂������Ă��܂��I\n");
        }
    }

    return 0;
}

// �������֐�
void initData() {
    level = 1;
    for (int i = 0; i < 6; i++) {
        arrayFish[i] = 100;
    }
}

// �����̏�Ԃ�\��
void printFishes() {
    printf("%3d�� %3d�� %3d�� %3d�� %3d�� %3d��\n", 1, 2, 3, 4, 5, 6);
    for (int i = 0; i < 6; i++) {
        printf("  %3d ", arrayFish[i]);
    }
    printf("\n\n");
}

// �o�ߎ��Ԃɉ����Đ������炷����
void decreaseWater(long elapsedTime) {
    for (int i = 0; i < 6; i++) {
        arrayFish[i] -= (level * 3 * (int)elapsedTime);
        if (arrayFish[i] < 0) {
            arrayFish[i] = 0;
        }
    }
}

// �����Ă��鋛�����邩�m�F
int checkFishAlive() {
    for (int i = 0; i < 6; i++) {
        if (arrayFish[i] > 0) {
            return 1;
        }
    }
    return 0;
}
