#include <stdio.h>
#include <stdlib.h>   
#include <time.h>     

int level;
int arrayFish[6];
int* cursor;

void initData();               // 初期データの設定
void printFishes();            // 魚の状態を表示
void decreaseWater(long elapsedTime); // 水の減少処理
int checkFishAlive();          // 魚の生存確認

int main(void) {
    long startTime = 0;
    long totalElapsedTime = 0;
    long prevElapsedTime = 0;
    int num;

    initData();        // 初期化処理
    cursor = arrayFish;

    startTime = clock();  // ゲーム開始時間を記録

    while (1) {
        printFishes();  // 現在の水槽状態を表示
        printf("何番水槽に水を入れますか？ ");
        scanf_s("%d", &num);


        // 入力チェック
        if (num < 1 || num > 6) {
            printf("\n入力値が間違っています。\n");
            continue;
        }

        // 総経過時間を計算
        totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
        printf("総経過時間 : %ld 秒\n", totalElapsedTime);

        // 最近の経過時間を計算
        long interval = totalElapsedTime - prevElapsedTime;
        printf("最近経過時間 : %ld 秒\n", interval);

        // 水を減らす処理
        decreaseWater(interval);
        prevElapsedTime = totalElapsedTime;

        // 選んだ水槽に対する処理
        if (cursor[num - 1] <= 0) {
            printf("%d 番魚はもう死にました。。水は要りません。\n", num);
        }
        else if (cursor[num - 1] + 1 <= 100) {
            printf("%d 番水槽に水を入れます。\n", num);
            cursor[num - 1] += 1;
        }

        // レベルアップ条件（20秒ごとに確認）
        if (totalElapsedTime / 20 > level - 1) {
            level++;
            printf("*** レベルアップ！既存 %d レベルから %d レベルにアップしました。***\n", level - 1, level);

            // 最終レベルに達したらゲーム終了
            if (level == 5) {
                printf("\n\nおめでとうございます！全てのレベルをクリアしました。ゲームを終了します。\n");
                exit(0);
            }
        }

        // 全ての魚が死んでいるか確認
        if (checkFishAlive() == 0) {
            printf("全ての魚が。。。(´;ω;｀)\n");
            exit(0);
        }
        else {
            printf("魚がまだ生きています！\n");
        }
    }

    return 0;
}

// 初期化関数
void initData() {
    level = 1;
    for (int i = 0; i < 6; i++) {
        arrayFish[i] = 100;
    }
}

// 水槽の状態を表示
void printFishes() {
    printf("%3d番 %3d番 %3d番 %3d番 %3d番 %3d番\n", 1, 2, 3, 4, 5, 6);
    for (int i = 0; i < 6; i++) {
        printf("  %3d ", arrayFish[i]);
    }
    printf("\n\n");
}

// 経過時間に応じて水を減らす処理
void decreaseWater(long elapsedTime) {
    for (int i = 0; i < 6; i++) {
        arrayFish[i] -= (level * 3 * (int)elapsedTime);
        if (arrayFish[i] < 0) {
            arrayFish[i] = 0;
        }
    }
}

// 生きている魚がいるか確認
int checkFishAlive() {
    for (int i = 0; i < 6; i++) {
        if (arrayFish[i] > 0) {
            return 1;
        }
    }
    return 0;
}
