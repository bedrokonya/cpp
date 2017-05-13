#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <cctype>
#include <string>
#include "assert.h"
#include <map>

// Даны а, буква х и натуральное число k. Вывести, есть ли
// в язые L слова, содержащие ровно k букв х.

// Класс обработки регулярного выражения.
class Regular_expression_processing {
private:
    std::string _expression;
    char _needed_symbol;
    int _desired_number_of_symbol;

    
    // Класс "Конечный автомат"
    class Finite_state_machine {
    public:
        // Создает конечный автомат с двумя состояниями(начальным и завершающим) из одного символа
        Finite_state_machine() {}
        Finite_state_machine(char letter) {
            _initial_state = new State();
            _initial_state->_is_it_initial = true;
            _initial_state->append.push_back(letter);
            State* finite_state = new State();
            finite_state->_is_it_finite = true;
            _initial_state->following_states.push_back(finite_state);
            finite_states.push_back(finite_state);
            
        }
        // класс "Состояние"
        class State {
        public:
            State() {
                _is_it_finite = false;
                _is_it_initial = false;
            }
            
            bool _is_it_initial; // начальное?
            bool _is_it_finite; // конечное?
            std::vector<State*> following_states; // Состояния, в которые можно прийти из текущего
            std::vector<char> append; // Символы, по которым пойдем в следующие состояния
        };
        
        State* _initial_state;
        std::vector<State*> finite_states;
    };
    
    std::set<Finite_state_machine::State*> used;
    std::map<Finite_state_machine::State*, int> previous_number_of_symbols;
public:
    Regular_expression_processing(std::string expression, char sym, int n) {
        _expression = expression;
        _needed_symbol = sym;
        _desired_number_of_symbol = n;
    }
    
    // Операция '.'
    void concatenation(Regular_expression_processing::Finite_state_machine* first_FSM, Finite_state_machine* second_FSM) {
        // Проверяем, что нам передали не нулевые указатели.
        assert(first_FSM != nullptr && second_FSM != nullptr);
        // Говорим начальному состоянию второго автомата, что оно боьше не начальное.
        second_FSM->_initial_state->_is_it_initial = false;
        
        for (size_t i = 0; i < first_FSM->finite_states.size(); i++) {
            // Все конечные состояния первого автомата больше не конечные.
            first_FSM->finite_states[i]->_is_it_finite = false;
            // Каждому конечному состоянию первого автомата сообщаем о том,
            // что у него появилось новое следующее за ним состояние,
            // а именно -- начальное состояние второго автомата.
            first_FSM->finite_states[i]->following_states.push_back(second_FSM->_initial_state);
            // Не забываем добавить эпсилон-переходы
            first_FSM->finite_states[i]->append.push_back('1');
            // Говорим первому автомату о том, что у него теперь совершенно новые конечные состояния,
            // а именно -- конечные состояния второго автомата.
            first_FSM->finite_states.clear();
            first_FSM->finite_states = second_FSM->finite_states;
        }
        return;
    }
    
    // Операция '+'
    Finite_state_machine* addition(Finite_state_machine* first_FSM, Finite_state_machine* second_FSM) {
        // Проверяем, что нам передали не нулевые указатели.
        assert(first_FSM != nullptr && second_FSM != nullptr);
        // Говорим начальным состояниям первого и второго автомата, что они больше не начальные.
        first_FSM->_initial_state->_is_it_initial = false;
        second_FSM->_initial_state->_is_it_initial = false;
        // Заводим новый автомат, состоящий из одного состояния.
        Finite_state_machine* new_FSM = new Finite_state_machine();
        new_FSM->_initial_state = new Finite_state_machine::State();
        // Проставляем все поля нужным образом
        new_FSM->_initial_state->_is_it_initial = true;
        new_FSM->_initial_state->following_states.push_back(first_FSM->_initial_state);
        new_FSM->_initial_state->append.push_back('1');
        new_FSM->_initial_state->following_states.push_back(second_FSM->_initial_state);
        new_FSM->_initial_state->append.push_back('1');
        // Не забудем сообщить новому автомату о конечных состояниях старых автоматов.
        for (size_t i = 0; i < first_FSM->finite_states.size(); i++) {
            new_FSM->finite_states.push_back(first_FSM->finite_states[i]);
        }
        for (size_t i = 0; i < second_FSM->finite_states.size(); i++) {
            new_FSM->finite_states.push_back(second_FSM->finite_states[i]);
        }
        return new_FSM;
    }
    
    //Операция '*'
    Finite_state_machine* kleene_star(Finite_state_machine* old_FSM) {
        // Заведем новый автомат, состоящий из одного состояния.
        Finite_state_machine* new_FSM = new Finite_state_machine();
        new_FSM->_initial_state = new Finite_state_machine::State();
        new_FSM->_initial_state->_is_it_initial = true;
        new_FSM->_initial_state->_is_it_finite = true;
        new_FSM->finite_states.push_back(new_FSM->_initial_state);
        // Говорим "старому" начальному состоянию, что оно больше не начальное.
        old_FSM->_initial_state->_is_it_initial = false;
        for (size_t i = 0; i < old_FSM->finite_states.size(); i++) {
            old_FSM->finite_states[i]->_is_it_finite = false;
            old_FSM->finite_states[i]->following_states.push_back(new_FSM->_initial_state);
            old_FSM->finite_states[i]->append.push_back('1');
        }
        new_FSM->_initial_state->following_states.push_back(old_FSM->_initial_state);
        new_FSM->_initial_state->append.push_back('1');
        return new_FSM;
    }
    
    // Строит конечный(недетерменированный) автомат по регулярному выражению в постфиксной нотации
    // ab+c.aba.*.bac.+.+*
    Finite_state_machine* convert_regular_expression_to_FSM () {
        std::stack<Finite_state_machine*> stack_of_machines;
        char letter;
        for (size_t i = 0; i < _expression.size(); i++) {
            letter = _expression[i];
            if (letter == ' '){
                continue;
            }
            if (letter == 'a' || letter == 'b' || letter == 'c') {
                Finite_state_machine* m = new Finite_state_machine(letter);
                stack_of_machines.push(m);
            }
            else {
                switch (letter) {
                    case '.': {
                        assert(stack_of_machines.size() >= 2);
                        Finite_state_machine* first_FSM = stack_of_machines.top();
                        stack_of_machines.pop();
                        Finite_state_machine* second_FSM = stack_of_machines.top();
                        stack_of_machines.pop();
                        concatenation(second_FSM, first_FSM);
                        stack_of_machines.push(second_FSM);
                        break;
                    }
                    case '+': {
                        assert(stack_of_machines.size() >= 2);
                        Finite_state_machine* first_FSM = stack_of_machines.top();
                        stack_of_machines.pop();
                        Finite_state_machine* second_FSM = stack_of_machines.top();
                        stack_of_machines.pop();
                        Finite_state_machine* new_FSM = addition(second_FSM, first_FSM);
                        stack_of_machines.push(new_FSM);
                        break;
                    }
                    case '*': {
                        assert(stack_of_machines.size() >= 1);
                        Finite_state_machine* FSM = stack_of_machines.top();
                        stack_of_machines.pop();
                        Finite_state_machine* new_FSM = kleene_star(FSM);
                        stack_of_machines.push(new_FSM);
                        break;
                    }
                    default: {
                        throw std::runtime_error("Invalid expression!");
                    }
                }
            }
        }
        if (stack_of_machines.size() == 1) {
            return stack_of_machines.top();
        }
        else {
            throw std::runtime_error("Invalid expression!");
        }
    }
    
    bool dfs_for_finding_the_answer(Finite_state_machine::State* initial, int counter) {
        if (previous_number_of_symbols.count(initial) == 0) {
            previous_number_of_symbols.insert(std::make_pair(initial, counter));
        }
        else {
            previous_number_of_symbols[initial] = counter;
        }
        
        // Если счетчик насчитал нужное количество определенной буквы
        if (counter == _desired_number_of_symbol) {
            used.insert(initial);
            // И если мы пришли в терминальную вершину
            if (initial->_is_it_finite) {
                // то завершаемся, ибо мы нашли слово в данном языке,
                // которое подходит под все требования
                return true;
            } else {
                // Если мы еще не пришли в терминальную вершину
                for (size_t i = 0; i < initial->following_states.size(); i++) {
                    if (initial->append[i] != _needed_symbol && used.count(initial->following_states[i]) == 0) {
                        if(dfs_for_finding_the_answer(initial->following_states[i], counter))
                            return true;
                    }
                }
            }
        } else {
            // Если счетчик еще не насчитал нужное нам количество
            for (size_t i = 0; i < initial->following_states.size(); i++) {
                if (initial->append[i] == _needed_symbol) {
                    if(dfs_for_finding_the_answer(initial->following_states[i], counter + 1))
                        return true;
                } else {
                    if (previous_number_of_symbols.count(initial->following_states[i]) == 0 ||
                        previous_number_of_symbols[initial->following_states[i]] < counter) {
                        if(dfs_for_finding_the_answer(initial->following_states[i], counter))
                            return true;
                    }
                }
            }
        }
        return false;
    }
    
    

};

//ab+c.aba.*.bac.+.+* a 2

//acb..bab.c.*.ab.ba.+.+*a. a 0
int main() {
    std::string expression;
    char needed_symbol;
    int desired_number_of_symbol;
    bool answer;
    std::cin >> expression >> needed_symbol >> desired_number_of_symbol;
    Regular_expression_processing* r = new Regular_expression_processing(expression, needed_symbol, desired_number_of_symbol);
    answer = r->dfs_for_finding_the_answer(r->convert_regular_expression_to_FSM()->_initial_state, 0);
    if (answer == false) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES";
    }
    
    return 0;
}