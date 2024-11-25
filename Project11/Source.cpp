#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

class ArraySizeException : public std::exception 
{
public:
    const char* what() const noexcept override 
    {
        return "Array size is not 4x4.";
    }
};

class ArrayDataException : public std::exception 
{
private:
    std::string message;
public:
    explicit ArrayDataException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class ArrayValueCalculator 
{
public:
    static int doCalc(const std::vector<std::vector<std::string>>& array)
    {
        
        if (array.size() != 4) 
        {
            throw ArraySizeException();
        }

        for (const auto& row : array) {
            if (row.size() != 4) 
            {
                throw ArraySizeException();
            }
        }

        int sum = 0;

        
        for (size_t i = 0; i < array.size(); ++i) 
        {
            for (size_t j = 0; j < array[i].size(); ++j) 
            {
                try 
                {
                   
                    sum += std::stoi(array[i][j]);
                }
                catch (const std::invalid_argument&) 
                {
                    throw ArrayDataException("Invalid data at cell [" +
                        std::to_string(i) + "][" +
                        std::to_string(j) + "]");
                }
                catch (const std::out_of_range&)
                {
                    throw ArrayDataException("Out-of-range value at cell [" +
                        std::to_string(i) + "][" +
                        std::to_string(j) + "]");
                }
            }
        }

        return sum;
    }
};

int main()
{
    
    std::vector<std::vector<std::string>> array = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    try
    {
        int result = ArrayValueCalculator::doCalc(array);
        std::cout << "Sum of array elements: " << result << std::endl;
    }
    catch (const ArraySizeException& e) 
    {
        std::cerr << "ArraySizeException: " << e.what() << std::endl;
    }
    catch (const ArrayDataException& e) 
    {
        std::cerr << "ArrayDataException: " << e.what() << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}