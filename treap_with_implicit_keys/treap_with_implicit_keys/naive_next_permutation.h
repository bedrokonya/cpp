
#include <algorithm>
#include <vector>

// Реализация “в лоб” на основе вектора и соответствующих stl-функций
class Vect : public InterfaceImplicitKeyTree {
private:
    std::vector<int> v_;
public:
    // Конструктор по умолчанию
    Vect() {}
    // Конструктор
    Vect(int cost) {
        v_.push_back(cost);
    }
    
    // Вставка элемента на позицию
    void Insert(int cost, int pos) {
        v_.push_back(0);
        for (size_t i = v_.size() - 1; i > pos; --i) {
            v_[i] = v_[i - 1];
        }
        v_[pos] = cost;
    }
    
    // Установка значения на позицию
    void SetUp(int cost, int pos) {
        v_[pos] = cost;
    }
    
    // Сумма на подотрезке
    int SumSegment(int l, int r) {
        int answer = 0;
        for (size_t i = l; i <= r; ++i)
            answer += v_[i];
        return answer;
    }
    
    // Следующая перестановка на подотрезке
    void NextPermutation(int l, int r) {
        std::next_permutation(v_.begin() + l, v_.begin() + r + 1);
    }
    
    void Print(std::vector<int> &ans) {
        for (size_t i = 0; i < v_.size(); i++) {
            ans.push_back(v_[i]);
            //std::cout << v_[i] << " ";
        }
        //std::cout << "\n";
    }
    
    /*void print() {
        if (v_.size() == 0)
            return;
        for (size_t i = 0; i < v_.size(); i++) {
            std::cout << v_[i] << " ";
        }
    } */
};
