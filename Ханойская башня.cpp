#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

const int TOWER_NUM = 3;

class Tower {
public:
    // конструктор и метод SetDisks нужны, чтобы правильно создать башни
    Tower(int disks_num) {
        FillTower(disks_num);
    }

    void SetDisks(int disks_num) {
        FillTower(disks_num);
    }

    int GetDisksNum() const {
        return disks_.size();
    }

    // перемещаем 1 диск с текущей башни на destination
    void MoveTopTo(Tower& destination) {
        int top_disk_num = disks_.size() - 1;
        try {
            destination.AddToTop(disks_[top_disk_num]);
        }
        catch (const invalid_argument& e) {
            cout << e.what() << '\n';
            throw;
        }

        disks_.pop_back();
    }

    // добавляем диск на верх собственной башни
    void AddToTop(int disk) {
        int top_disk_num = disks_.size() - 1;
        if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
            throw invalid_argument("Невозможно поместить большой диск на маленький");
        }
        else {
            disks_.push_back(disk);
        }
    }

    void MoveDisks(int disks_num, Tower& destination, Tower& buffer) {
        // наше условие завершения - не осталось больше дисков, чтобы перемещать их
        if (0 < disks_num) {
            // сначала отложим все диски, кроме верхнего, на дополнительный
            // стержень, используя destination в качестве буфера
            MoveDisks(disks_num - 1, buffer, destination);
            // переложим оставшийся самый большой диск в destination
            MoveTopTo(destination);
            // теперь нам нужно переложить диски, оказавшиеся в буфере,
            // в destination, используя изначальный стержжень, как буфер
            buffer.MoveDisks(disks_num - 1, destination, *this);
        }
    }

    void Print() {
        for (int i = 0; i < disks_.size(); i++) {
            cout << disks_[i] << " ";
        }
        cout << endl;
    }

private:
    vector<int> disks_;

    // используем приватный метод FillTower, чтобы избежать дубликации кода
    void FillTower(int disks_num) {
        for (int i = disks_num; i > 0; i--) {
            disks_.push_back(i);
        }
    }
};

void SolveHanoi(vector<Tower>& towers) {
    int disks_num = towers[0].GetDisksNum();
    towers[0].MoveDisks(disks_num, towers[2], towers[1]);
}
