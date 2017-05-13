#include <cassert>

template <typename TYPE>
class CPtrOwner {
    TYPE *ptr;
public:
    // Конструктор. Получает во владение переданный ему указатель.
    // Предполагаемое использование: CPtrOwner<CSomeInstance> instancePtr( new CSomeInstance() );
    explicit CPtrOwner( TYPE* _ptr = 0 ) :
        ptr(_ptr) {}
    
    // Деструктор. Удаляет владеемый объект оператором delete
    ~CPtrOwner() {
        delete ptr;
    }
    
    // Операция присваивания.
    const CPtrOwner<TYPE>& operator = ( TYPE* other ) {
        if (ptr == other)
            return *ptr;
        delete ptr;
        ptr = other;
        return *ptr;
    }
    
    // Разрушает владеемый объект и зануляет указатель.
    // Можно вызывать даже для нулевого указателя на объект.
    void Release() {
        delete ptr;
        ptr = 0;
    }
    
    // Отстраняет от владения объектом, не удаляя его.
    // Возвращает указатель на владеемый объект. Может вернуть 0.
    TYPE* Detach() {
        TYPE ptr_ = ptr;
        ptr = 0;
        return ptr_;
    }
    
    // Метод явной проверки на равенство указателя нулю.
    // Возвращает true, если указатель равен нулю, и false в противном случае
    bool IsNull() const {
        return ptr == 0;
    }
    
    // Возвращает указатель на владеемый объект. Может вернуть ноль.
    TYPE* Ptr() {
        return ptr;
    }
    // Возвращает константный указатель на владеемый объект. Может вернуть ноль.
    const TYPE* Ptr() const {
        return Ptr();
    }
    
    // Возвращает указатель на владеемый объект.
    // С помощью assert проверяет на неравенство указателя нулю.
    TYPE* SafePtr() {
        assert(Ptr() != 0);
        return Ptr();
    }
    // Возвращает константный указатель на владеемый объект.
    // С помощью assert проверяет на неравенство указателя нулю.
    const TYPE* SafePtr() const {
        return SafePtr();
    }
    
    // Операция неявного приведения типа к указателю на владеемый объект.
    // Может вернуть нулевой указатель.
    operator TYPE* () {
        return Ptr();
    }
    operator const TYPE* () const {
        return Ptr();
    }
    
    // Операция разыменования указателя.
    // Проверяет на неравенство указателя нулю с помощью assert
    TYPE& operator * () {
        return *SafePtr();
    }
    const TYPE& operator * () const {
        return *SafePtr();
    }
    
    // Операция доступа к члену.
    // Проверяет на неравенство указателя нулю с помощью assert
    TYPE* operator -> () {
        return SafePtr();
    }
    const TYPE* operator -> () const {
        return SafePtr();
    }
};