Напишите lock-free очередь имени Michael и Scott
Оригинальная статья:
Maged Michael, Michael Scott - Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue Algorithms
Очередь должна быть шаблонной.
void lock_free_queue::enqueue(T item)   
bool lock_free_queue::dequeue(T& item)

Примечания

Утечки памяти недопустимы.
В деструкторе контейнера должна освобождаться занятая память: должны быть удалены узлы из списка очереди и узлы из списка на удаление.
