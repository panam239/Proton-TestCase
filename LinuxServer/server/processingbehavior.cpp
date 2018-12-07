#include "processingbehavior.h"

bool isDigit(char ch) {
    return (ch > '0' && ch < '9');
}

std::string Echo::process(std::string message) const
{
    return message;
}

std::string SortAndSum::process(std::string message) const
{
    std::string::iterator msgIter = message.begin();
    std::vector<unsigned int> numbers;
    std::string strNumber;
    unsigned int sum = 0;
    while (msgIter != message.end()) {
        if(isDigit(*msgIter))
            strNumber += *msgIter;
        else if(strNumber.size() > 0)
        {
            unsigned int number = std::stoul(strNumber);
            numbers.push_back(number);
            sum += number;
            strNumber.clear();
        }
        ++msgIter;
    }
    if(strNumber.size() > 0)
    {
        unsigned int number = std::stoul(strNumber);
        numbers.push_back(number);
        sum += number;
    }
    std::cout << "numbers" << numbers.size() << "sum "<< sum << std::endl;
    strNumber.clear();
    if(numbers.size() > 0) {
        std::sort(numbers.begin(), numbers.end());
        std::vector<unsigned int>::iterator numIter = numbers.begin();
        while(numIter != numbers.end())
        {
            strNumber += std::to_string(*numIter);
            strNumber += ' ';
            ++numIter;
        }
        strNumber.pop_back();
        strNumber.push_back('\n');
    } else
        strNumber += "No numbers\n";
    strNumber += std::to_string(sum);
    std::cout << "result: " << strNumber;
    return strNumber;
}
