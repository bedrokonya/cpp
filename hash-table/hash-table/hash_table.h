
#include <string>
#include <vector>

// Хеш-таблица, разрешающая коллизии методом цепочек.
class CHashTable {
public:
    CHashTable();
    ~CHashTable();

    
    // Проверка наличия ключа
    bool Has ( const std::string& key ) const;
    
    // Добавление ключа. Если число элементов становится больше размера table, то table расширяется.
    // Возврашает false, если элемент уже есть
    bool Add( const std::string& key );
    //Удаление ключа. Уменьшение таблицы не заложено.
    // Возвращает false, если элемента нет.
    bool Remove( const std::string& key );
    
private:
    // Элемент цепочки
    struct CListNode {
        std::string Key;
        CListNode* Next;
        CListNode( const std::string& key ) : Key ( key ), Next(0) {}
        ~CListNode() { delete Next; }
    };
    std::vector<CListNode*> table;
    size_t keysCount;
    
    int myHash( const std::string& key ) const;
    void rehash();
};