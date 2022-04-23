#include <iostream>

int G1[10][10];
int G2[10][10];
int V1[10][10];
int V2[10][10];

std::string name1, name2;
void Initial();
void Show(int, bool);
void GamerInit(int);
void SetPosition(int, int, int, int, int);
bool Validate(int, int, int, int, int, int);

int main()
{
    Initial();
    GamerInit(0);
    GamerInit(1);
}

void Show(int num, bool b=true) {
    system("cls");
    std::cout << " ";
    // Номера столюцов
    for (int i = 0; i < 10; i++) 
        std::cout << " " << i;
    std::cout << "\n";

    for (int y = 0; y < 10; y++) {
        // Номера строк
        std::cout << y << " ";
        for (int x = 0; x < 10; x++) {
            if ((num == 0 ? G1[x][y] : G2[x][y]) == 0) std::cout << (char)0xB0 << (char)0xB0;
            if ((num == 0 ? G1[x][y] : G2[x][y]) == 1) std::cout << (char)0xDB << (char)0xDB;
            if ((num == 0 ? G1[x][y] : G2[x][y]) == 2) std::cout << (char)0xCE << (char)0xCE;
        }
        std::cout << std::endl;
    }
}

void SetPosition(int x1, int y1, int x2, int y2, int num) {
    for (int x = x1; x <= x2; x++) 
        for (int y = y1; y <= y2; y++) 
            (num == 0 ? G1[x][y] : G2[x][y]) = 1;
}

void GamerInit(int num) {
    int x1, x2, y1, y2;   
    Show(num, false);
    for (int size = 1; size < 5; size++) {        
        for (int count = 1; count <= 5 - size; count++) {
            std::cout << "Player " << (num == 0 ? name1 : name2) << "\n";
            std::cout << "Set the coordinates (x,y) of the head of the "<< count << " ship size " << size<< ": ";
            std::cin >> x1 >> y1;

            if (size > 1) {
                std::cout << "Set the coordinates of the stern of the ship: ";
                std::cin >> x2 >> y2;
            }
            else {
                x2 = x1;
                y2 = y1;
            }

            if (x1 > x2 || y1 > y2) {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            // Проверяем валидность кординат
            if (!Validate(x1, y1, x2, y2, size, num)) {
                std::cout << "Invalid coordinate!\n";
                count--;
            }
            else {
                SetPosition(x1, y1, x2, y2, num);
                // Выводим карту
                Show(num, false);
            }
        }
    }
}
bool Validate(int x1, int y1, int x2 , int y2, int size, int num) {
    bool result = (x1 >= 0 && x1 < 10) && (y1 >= 0 && y1 < 10) && 
                  (x2 >= 0 && x2 < 10) && (y2 >= 0 && y2 < 10) && 
                  (x1 == x2 || y1 == y2);
    if (!result) {
        std::cout << "Fist check invalid\n";
        return result;
    }

    // Проверяем длинну
    result = result && ((x2 - x1) == (size - 1) || (y2 - y1) == (size - 1));
    if (!result) {
        std::cout << "len chek invalid\n";
        std::cout << x2 << "\t" << x1 << "\n";
        std::cout << y2 << "\t" << y1 << "\n";
        std::cout << size << "\n";
        return result;
    }

    // Проверяем что там нет коробля
    for (int x=x1; (x <= x2) && result; x++)
        for (int y = y1; (y <= y2) && result; y++) {
            result = result && ((num == 0 ? G1[x][y] : G2[x][y]) == 0);
        }
    if (!result) {
        std::cout << "Pocition ocuped\n";
        return result;
    }
    return result;
}

void Initial() {
    for (int y=0;y<10;y++)
        for (int x = 0; x < 10; x++) {
            G1[x][y] = 0;
            G2[x][y] = 0;
            V1[x][y] = 0;
            V2[x][y] = 0;
        }
    std::cout << "Enter the name of the first player: ";
    std::cin >> name1;
    std::cout << "Enter the name of the second player: ";
    std::cin >> name2;
}