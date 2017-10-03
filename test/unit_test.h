// unit_test.h
//
// Tiago de Lima <tiago.delima@univ-artois.fr>
// 29 sep 2017
//
// Unit tests.

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using Test = std::pair< std::string, bool >;
using TestVector = std::vector< Test >;

//! Runs one test.
bool run_one_test( Test test )
{
    if( !test.second )
    {
        std::cout << std::endl;
        std::cout << test.first << " FAILED!";
        return false;
    }

    return true;
}

//! Runs all tests. 
int run_tests( std::string name, const TestVector & test_vec)
{
    std::cout << "Testing " << name << "... ";

    unsigned int num_fail { 0 };
    for( Test test : test_vec )
    {
        if( !run_one_test( test ) )
        {
            ++num_fail;
        }
    }

    if( num_fail > 0 )
    {
        std::cout << std::endl;
        std::cout << "Failures: " << num_fail << std::endl;
    }
    else
    {
        std::cout << "OK!" << std::endl;
    }
    return num_fail;
}
