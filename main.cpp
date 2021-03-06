#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>

class destruct_memory
{
    std::vector<int*> vec;
public:
    void push()
    {
        for(int i =0; i <= 1000000; i++)
        {
            vec.push_back(new int(i));
        }
    }
};

class normal_memory
{
    std::vector<int*> vec;
public:
    ~normal_memory()
    {
        for(auto i : vec)
        {
            delete i;
        }
        std::cout << "work" << std::endl;

    }
    void push()
    {
        for(int i =0; i <= 1000000; i++)
        {
            vec.push_back(new int(i));
        }
    }
};

class Myexception : public std::exception
{
    float data;
    const char* error;
public:
    Myexception(const char *error, float data): error(error), data(data)
    {
    }
    float getData() const
    {return data;}
    const char* getError() const
    {return error;}
    const char * what() const noexcept override
    {return error;}
};

float SQRT(const float& ob)
{
    if (ob<0)
        throw Myexception("Negative value", ob);
    else
    {
        return sqrt(ob);
    }

}

int main()
{
    //#3
    std::cout << "--------------------------------bad------------------------------"<< std::endl;
    destruct_memory z;
    z.push();
    std::cout << "--------------------------------good------------------------------"<< std::endl;
    normal_memory z1;
    z1.push();
    // #2
    float x;
    std::cout << "x= ";
    std::cin >> x;
    try
    {
        std::cout<< SQRT(x) << std::endl;
    }
    catch(Myexception& e)
    {
        std::cout << e.what() << " " << e.getData() << std::endl;

    }

    //#1
    //out_of_range
    std::vector<int> test(4);
    try
    {
        test.at(5);
    }
    catch (std::out_of_range& e)
    {
        std::cout << e.what() << std::endl;
    }
    //length_error
    try
    {
        test.resize(-5);
    }
    catch (std::length_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    // invalid argument
    std::string str = "word";

    try
    {
        std::cout << std::stoi(str) << std::endl;
    }
    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
    //bad_cast
    struct my
    {
        virtual ~my() {};
        int k;
    };
    struct my1
    {
        virtual ~my1() {};
        std::string i;
    };
    my1 test_5;
    try
    {
        auto test_4 = dynamic_cast<my&>(test_5);
    }
    catch (std::bad_cast& e)
    {
        std::cout << e.what() << std::endl;
    }
    //bad_alloc
    char* str_1;
    int k =1;
    try
    {
        while (k)
        {
            str_1 = new char[10000000000000];
        }
    }
    catch(std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}
