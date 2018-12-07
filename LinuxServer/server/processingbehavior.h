#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/* Класс, задающий способ обработки сообщений сервером перед отправкой назад.
 * Реализованы классы Echo(сообщение не меняется) и SortAndSum (требование).
 * Для добавления другого способа надо создать наследника ProcessingBehavior
 * и создать его в конструкторе сервера
*/
class ProcessingBehavior
{
public:
    virtual std::string process(std::string message) const = 0;
    virtual ~ProcessingBehavior() {}
};

class Echo : public ProcessingBehavior
{
    std::string process(std::string message) const;
    ~Echo() {}
};

class SortAndSum : public ProcessingBehavior
{
    std::string process(std::string message) const;
    ~SortAndSum() {}
};
