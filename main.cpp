/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:48 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/08 18:45:46 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "./containers/map.hpp"
	#include "./containers/stack.hpp"
	#include "./containers/vector.hpp"
#endif

int main(void)
{

// TESTING STACK
	
	ft::stack<int> stck;
	std::cout << "------------STACK-----------" << std::endl << std::endl;
	std::cout << "Is it empty ? " << (stck.empty() == 1 ? "yes." : "no.") << std::endl;
	std::cout << "Size of my stack before adding 3 values : " << stck.size() << std::endl;
	stck.push(42);
	stck.push(666);
	stck.push(21);
	std::cout << "Size of my stack after adding 3 values : " << stck.size() << std::endl;
	std::cout << "Values : " << std::endl;
    for (ft::stack<int> tst = stck; !tst.empty(); tst.pop())
		std::cout << tst.top() << std::endl;
	std::cout << "Is it empty ? " << (stck.empty() == 1 ? "yes." : "no.") << std::endl;

	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Testing operators" << std::endl;
	ft::stack<int> stck2;
	stck2.push(84);
	stck2.push(1337);
	stck2.push(2727);
	
	std::cout << "Operator : " << "<=" << std::endl;
	if (stck <= stck2)
		std::cout << "stack1 is <= than stack2" << std::endl;
	else
		std::cout << "stack1 is not <= than stack2" << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Operator : " << "<" << std::endl;
	if (stck < stck2)
		std::cout << "stack1 is < than stack2" << std::endl;
	else
		std::cout << "stack1 is not < than stack2" << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Operator : " << "==" << std::endl;
	if (stck == stck2)
		std::cout << "Both stacks are equal" << std::endl;
	else
		std::cout << "Both stacks are not equal" << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Operator : " << ">" << std::endl;
	if (stck > stck2)
		std::cout << "stack1 is > than stack2" << std::endl;
	else
		std::cout << "stack1 is not > than stack2" << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Operator : " << ">=" << std::endl;
	if (stck >= stck2)
		std::cout << "stack1 is >= than stack2" << std::endl;
	else
		std::cout << "stack 1 is not >= than stack2" << std::endl;

	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Operator : " << "!=" << std::endl;
	if (stck != stck2)
		std::cout << "Both stacks are differents" << std::endl;
	else
		std::cout << "Both stacks are equal" << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

// TESTING VECTOR

	std::cout << "-----------VECTOR-----------" << std::endl << std::endl;
	std::cout << std::endl;
	ft::vector<int>	vec;
	ft::vector<int>::iterator	vec_it;
	
	std::cout << "Is it empty ? " << (vec.empty() == 1 ? "yes." : "no.") << std::endl;
	std::cout << "Size of vector : " << vec.size() << std::endl;
	std::cout << "Max_size of vector : " << vec.max_size() << std::endl;
	std::cout << "Capacity of vector : " << vec.capacity() << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Using reserve on vector : " << std::endl;

	vec.reserve(918273645);
	std::cout << "Capacity of vector after reserve : " << vec.capacity() << std::endl;
	std::cout << "Using resize on vector : " << std::endl;
	vec.resize(16, 42);
	std::cout << "Size of vector after resize : " << vec.size() << std::endl;
	std::cout << "Capacity of vector after resize : " << vec.capacity() << std::endl;
	std::cout << "Front value : " << vec.front() << std::endl;
	std::cout << "Back value : " << vec.back() << std::endl;
	vec_it = vec.end();
	vec.insert(vec_it, 84);
	std::cout << std::endl;
	std::cout << "-------- Inserting a new value -------" << std::endl;

	std::cout << "Back value : " << vec.back() << std::endl;
	++vec_it;
	vec.insert(vec_it, 128);
	std::cout << "Back value : " << vec.back() << std::endl;
	std::cout << "Value of vector[vector.size() - 2] : " << vec[vec.size() - 2] << std::endl;
    std::cout << "Value of first element : " << vec.at(0) << std::endl;
    std::cout << "Value of last element : " << vec.at(vec.size() - 1) << std::endl;
	std::cout << std::endl;
	std::cout << "------- Testing all differents constructors ---------------------" << std::endl;

    ft::vector<int> prems;                                // empty vector of ints
    ft::vector<int> scnd (4,100);                       // four ints with value 100
    ft::vector<int> thrd (scnd.begin(),scnd.end());  // iterating through second
    ft::vector<int> fourth (thrd);                       // a copy of third
	std::cout << "All constructors correctly have been created." << std::endl;

    ft::vector<int> c;
    ft::vector<int> b;
    ft::vector<int>::iterator ft_it;
    ft::vector<int>::reverse_iterator rev_ft_it;
    ft::vector<int>::const_reverse_iterator const_rev_ft_it;
    ft::vector<int>::const_iterator const_ft_it;
	
    c.assign(16, 42);
    b.reserve(15);
    b.resize(16);
    b.clear();
    b.assign(16, 100);
	std::cout << std::endl;
    std::cout << "------------------------ Testing iterators ------------------------" << std::endl;
    
    ft_it = b.begin(); 
    b.insert(ft_it, 42);
    ft_it = b.begin(); 
    const_ft_it = b.begin();   
    std::cout << "Begin iterator : OK" << std::endl;
    std::cout << "Value of my it (begin): " << *(ft_it) << std::endl;
    std::cout << "Value of my const it (begin): " << *(const_ft_it) << std::endl;
    rev_ft_it = b.rbegin();
    const_rev_ft_it = b.rbegin();   
    std::cout << "Value of my it (rbegin): " << *(rev_ft_it) << std::endl;
    std::cout << "Value of my const it (rbegin): " << *(const_rev_ft_it) << std::endl;
    b.insert(ft_it, 666);
    ft_it = b.end(); 
    const_ft_it = b.end();   
    b.insert(ft_it, 666);
    rev_ft_it = b.rend(); 
    const_rev_ft_it = b.rend();   
    std::cout << "Value of my it (rend): " << *(rev_ft_it) << std::endl;
    std::cout << "Value of my const it (rend): " << *(const_rev_ft_it) << std::endl;
    std::cout << "End iterator : OK" << std::endl;
    std::cout << "Value of my it : " << *(ft_it) << std::endl;
    std::cout << "Value of my const it : " << *(const_ft_it) << std::endl;

    std::cout << "Value of last element of vector b: " << b.at(b.size() - 1) << std::endl;
    std::cout << "Value of last element of vector c : " << c.at(c.size() - 1) << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------ Testing size ------------------------" << std::endl;
    
    ft::vector<int> int_vec;
    ft::vector<char> char_vec;
    ft::vector<std::string> string_vec;
    
    int_vec.insert(int_vec.begin(), 42);
    int_vec.insert(int_vec.begin(), 420);
    int_vec.insert(int_vec.begin(), 4200);
    char_vec.insert(char_vec.begin(), 'a');
    char_vec.insert(char_vec.begin(), 'b');
    string_vec.insert(string_vec.begin(), "Hello");
    string_vec.insert(string_vec.begin(), "World");
    string_vec.insert(string_vec.begin(), "I am");
    string_vec.insert(string_vec.begin(), "Happy");
    
    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;
    
    std::cout << "max_size of char vector : " << char_vec.max_size() << std::endl;
    std::cout << "max_size of int vector : " << int_vec.max_size() << std::endl;
    std::cout << "max_size of string vector : " << string_vec.max_size() << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------ Testing resize ------------------------" << std::endl;

    char_vec.resize(420);
    int_vec.resize(4200);
    string_vec.resize(42000);
    
    std::cout << "resize of char vector : " << char_vec.size() << std::endl;
    std::cout << "resize of int vector : " << int_vec.size() << std::endl;
    std::cout << "resize of string vector : " << string_vec.size() << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------ Testing capacity ------------------------" << std::endl;

    std::cout << "capacity of char vector : " << char_vec.capacity() << std::endl;
    std::cout << "capacity of int vector : " << int_vec.capacity() << std::endl;
    std::cout << "capacity of string vector : " << string_vec.capacity() << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------ Testing empty before clear ------------------------" << std::endl;
    
    std::cout << "empty of char vector : " << char_vec.empty() << std::endl;
    std::cout << "empty of int vector : " << int_vec.empty() << std::endl;
    std::cout << "empty of string vector : " << string_vec.empty() << std::endl;
    
    char_vec.clear();
    int_vec.clear();
    string_vec.clear();
	std::cout << std::endl;
    std::cout << "------------------------ Testing empty after clear ------------------------" << std::endl;
    
    std::cout << "empty of char vector : " << char_vec.empty() << std::endl;
    std::cout << "empty of int vector : " << int_vec.empty() << std::endl;
    std::cout << "empty of string vector : " << string_vec.empty() << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------ Testing reserve before ------------------------" << std::endl;
    
    std::cout << "capacity of char vector : " << char_vec.capacity() << std::endl;
    std::cout << "capacity of int vector : " << int_vec.capacity() << std::endl;
    std::cout << "capacity of string vector : " << string_vec.capacity() << std::endl;
    
    char_vec.reserve(840);
    int_vec.reserve(8400);
    string_vec.reserve(84000);
	std::cout << std::endl;
    std::cout << "------------------------ Testing reserve after ------------------------" << std::endl;
    
    std::cout << "capacity of char vector : " << char_vec.capacity() << std::endl;
    std::cout << "capacity of int vector : " << int_vec.capacity() << std::endl;
    std::cout << "capacity of string vector : " << string_vec.capacity() << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------ Testing operator[] ------------------------" << std::endl;

    char_vec.insert(char_vec.begin(), 'X');
    int_vec.insert(int_vec.begin(), 727);
    string_vec.insert(string_vec.begin(), "TEST");
    
    std::cout << "char vector [0] : " << char_vec[0] << std::endl;
    std::cout << "int vector [0] : " << int_vec[0] << std::endl;
    std::cout << "string vector [0] : " << string_vec[0] << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------- Testing at before insert ------------------------" << std::endl;

    std::cout << "char vector [0] : " << char_vec.at(0) << std::endl;
    std::cout << "int vector [0] : " << int_vec.at(0) << std::endl;
    std::cout << "string vector [0] : " << string_vec.at(0) << std::endl;

    char_vec.insert(char_vec.begin(), 'Z');
    int_vec.insert(int_vec.begin(), 222);
    string_vec.insert(string_vec.begin(), "Bob the sponge");
	std::cout << std::endl;
    std::cout << "------------------------- Testing at afterinsert ------------------------" << std::endl;

    std::cout << "char vector [0] : " << char_vec.at(0) << std::endl;
    std::cout << "int vector [0] : " << int_vec.at(0) << std::endl;
    std::cout << "string vector [0] : " << string_vec.at(0) << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------- Testing front ------------------------" << std::endl;

    std::cout << "char vector front element : " << char_vec.front() << std::endl;
    std::cout << "int vector front element : " << int_vec.front() << std::endl;
    std::cout << "string vector front element : " << string_vec.front() << std::endl;
	std::cout << std::endl;
    std::cout << "------------------------- Testing back ------------------------" << std::endl;

    std::cout << "char vector Back element : " << char_vec.back() << std::endl;
    std::cout << "int vector Back element : " << int_vec.back() << std::endl;
    std::cout << "string vector Back element : " << string_vec.back() << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing assign before ------------------------" << std::endl;
    
    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;

    char_vec.assign(42, 'o');
    int_vec.assign(42, 420);
    string_vec.assign(42, "awa");
	std::cout << std::endl;
    std::cout << "------------------------- Testing assign after ------------------------" << std::endl;

    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing push_back before ------------------------" << std::endl;

    std::cout << "char vector : " << char_vec.at(char_vec.size() - 1) << std::endl;
    std::cout << "int vector : " << int_vec.at(int_vec.size() - 1) << std::endl;
    std::cout << "string vector : " << string_vec.at(string_vec.size() - 1) << std::endl;

    char_vec.push_back('W');
    int_vec.push_back(666);
    string_vec.push_back("Lorem Ipsum");
	std::cout << std::endl;
    std::cout << "------------------------- Testing push_back after ------------------------" << std::endl;

    std::cout << "char vector : " << char_vec.at(char_vec.size() - 1) << std::endl;
    std::cout << "int vector : " << int_vec.at(int_vec.size() - 1) << std::endl;
    std::cout << "string vector : " << string_vec.at(string_vec.size() - 1) << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing pop_back before ------------------------" << std::endl;

    std::cout << "char vector : " << char_vec.at(char_vec.size() - 1) << std::endl;
    std::cout << "int vector : " << int_vec.at(int_vec.size() - 1) << std::endl;
    std::cout << "string vector : " << string_vec.at(string_vec.size() - 1) << std::endl;

    char_vec.pop_back();
    int_vec.pop_back();
    string_vec.pop_back();
	std::cout << std::endl;
    std::cout << "------------------------- Testing pop_back after ------------------------" << std::endl;

    std::cout << "char vector : " << char_vec.at(char_vec.size() - 1) << std::endl;
    std::cout << "int vector : " << int_vec.at(int_vec.size() - 1) << std::endl;
    std::cout << "string vector : " << string_vec.at(string_vec.size() - 1) << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing insert before ------------------------" << std::endl;
  
    std::cout << "char vector : " << char_vec.at(0) << std::endl;
    std::cout << "int vector : " << int_vec.at(0) << std::endl;
    std::cout << "string vector : " << string_vec.at(0) << std::endl;

    char_vec.insert(char_vec.begin(), 'C');
    int_vec.insert(int_vec.begin(), 42424242);
    string_vec.insert(string_vec.begin(), "ewe");
	std::cout << std::endl;
	std::cout << "------------------------- Testing insert after ------------------------" << std::endl;

    std::cout << "char vector : " << char_vec.at(0) << std::endl;
    std::cout << "int vector : " << int_vec.at(0) << std::endl;
    std::cout << "string vector : " << string_vec.at(0) << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing erase ------------------------" << std::endl;

    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;

    char_vec.erase(char_vec.begin());
    int_vec.erase(int_vec.begin());
    string_vec.erase(string_vec.begin());

    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing swap before ------------------------" << std::endl;

    std::cout << "Value of last element of vector b: " << b.at(b.size() - 1) << std::endl;
    std::cout << "Value of last element of vector c : " << c.at(c.size() - 1) << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing swap after ------------------------" << std::endl;

    b.swap(c);
    std::cout << "Value of last element of vector b: " << b.at(b.size() - 1) << std::endl;
    std::cout << "Value of last element of vector c : " << c.at(c.size() - 1) << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------- Testing clear before ------------------------" << std::endl;

    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;
   
    char_vec.clear();
    int_vec.clear();
    string_vec.clear();
	std::cout << std::endl;
	std::cout << "------------------------- Testing clear after ------------------------" << std::endl;

    std::cout << "size of char vector : " << char_vec.size() << std::endl;
    std::cout << "size of int vector : " << int_vec.size() << std::endl;
    std::cout << "size of string vector : " << string_vec.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
// TESTING MAP

	std::cout << "-----------MAP-----------" << std::endl << std::endl;
	std::cout << std::endl;
	ft::map<char,int> first;
	first['a']=10;
	first['b']=20;
	first['c']=30;
	first['d']=40;
	std::cout << "Default constructor : OK " << std::endl; 
	ft::map<char,int> second (first.begin(),first.end());
	std::cout << "Range constructor : OK " << std::endl; 
	std::cout << "Copy constructor : OK " << std::endl; 
	ft::map<char,int> third (second);
	third = second;
	std::cout << "Overload operator = : OK" << std::endl;
	ft::map<std::string, std::string> test;
	ft::map<std::string, std::string>::iterator test_it;
	ft::map<std::string, std::string>::reverse_iterator rev_test_it;
	test.insert(ft::pair<std::string, std::string>("Hello", "World"));
	test.insert(ft::pair<std::string, std::string>("START", "END"));
	std::cout << std::endl;
	std::cout << "------------------------ Testing iterators ------------------------" << std::endl;
	test_it = test.begin();
	std::cout << std::endl;
	std::cout << "------------------------ Testing begin ------------------------" << std::endl;
	std::cout << "pair of elements : {" << test_it->first << "} {" << test_it->second << "} " << std::endl;
	test_it = test.end();
	--test_it;
	std::cout << std::endl;
	std::cout << "------------------------ Testing end ------------------------" << std::endl;
	std::cout << "pair of elements : {" << test_it->first << "} {" << test_it->second << "} " << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing rbegin ------------------------" << std::endl;
	rev_test_it = test.rbegin();
	std::cout << "pair of elements : {" << test_it->first << "} {" << test_it->second << "} " << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing rend ------------------------" << std::endl;
	rev_test_it = test.rend();
	--test_it;
	std::cout << "pair of elements : {" << test_it->first << "} {" << test_it->second << "} " << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing capacity before insert ------------------------" << std::endl;

	ft::map<int, std::string>               int_string;
	ft::map<std::string, std::string>       string_string;
	ft::map<char, char>                     char_char;
	ft::map<char, bool>                     char_bool;
	
	std::cout << " Are my containers empty ? " << std::endl << std::endl;
	std::cout << "int_string is empty? " << (int_string.empty() ? "yes" : "no" ) << std::endl; 
	std::cout << "string_string is empty? " << (string_string.empty() ? "yes" : "no" ) << std::endl; 
	std::cout << "char_char is empty? " << (char_char.empty() ? "yes" : "no" ) << std::endl; 
	std::cout << "char_bool is empty? " << (char_bool.empty() ? "yes" : "no" ) << std::endl << std::endl; 

	std::cout << " size of my containers " << std::endl << std::endl;
	std::cout << "int_string size: " << int_string.size() << std::endl; 
	std::cout << "string_string size: " << string_string.size() << std::endl; 
	std::cout << "char_char size: " << char_char.size() << std::endl; 
	std::cout << "char_bool size: " << char_bool.size() << std::endl << std::endl; 

	int_string.insert(ft::pair<int, std::string>(42, "insert pair"));
	string_string.insert(ft::pair<std::string, std::string>("pairleft", "pairright"));
	char_char.insert(ft::pair<char, char>('o', 'w'));
	char_bool.insert(ft::pair<char, bool>('o',false));
	std::cout << std::endl;
	std::cout << "------------------------ Testing capacity after insert ------------------------" << std::endl;
	
	std::cout << " Are my containers empty ? " << std::endl;
	std::cout << "int_string is empty? " << (int_string.empty() ? "yes" : "no" ) << std::endl; 
	std::cout << "string_string is empty? " << (string_string.empty() ? "yes" : "no" ) << std::endl; 
	std::cout << "char_char is empty? " << (char_char.empty() ? "yes" : "no" ) << std::endl; 
	std::cout << "char_bool is empty? " << (char_bool.empty() ? "yes" : "no" ) << std::endl;

	std::cout << " size of my containers " << std::endl << std::endl;
	std::cout << "int_string size: " << int_string.size() << std::endl; 
	std::cout << "string_string size: " << string_string.size() << std::endl; 
	std::cout << "char_char size: " << char_char.size() << std::endl; 
	std::cout << "char_bool size: " << char_bool.size() << std::endl << std::endl; 
	std::cout << std::endl;
	std::cout << "------------------------ Testing element access ------------------------" << std::endl;

	std::cout << " first index of my containers " << std::endl << std::endl;
	std::cout << "int_string " << int_string[42] << std::endl; 
	std::cout << "string_string " << string_string["pairleft"] << std::endl; 
	std::cout << "char_char " << char_char['o'] << std::endl; 
	std::cout << "char_bool " << char_bool['o'] << std::endl << std::endl; 
	std::cout << std::endl;
	std::cout << "------------------------ Testing modifiers ------------------------" << std::endl;
	
	int_string.insert(ft::pair<int, std::string>(43, "a"));
	int_string.insert(ft::pair<int, std::string>(44, "b"));
	int_string.insert(ft::pair<int, std::string>(45, "c"));
	int_string.insert(ft::pair<int, std::string>(46, "d"));
	int_string.insert(ft::pair<int, std::string>(47, "e"));
	int_string.insert(ft::pair<int, std::string>(48, "f"));
	int_string.insert(ft::pair<int, std::string>(49, "g"));
	
	string_string.insert(ft::pair<std::string, std::string>("test", "red"));
	string_string.insert(ft::pair<std::string, std::string>("lol", "white"));
	string_string.insert(ft::pair<std::string, std::string>("42", "blue"));
	string_string.insert(ft::pair<std::string, std::string>("nice", "green"));
	string_string.insert(ft::pair<std::string, std::string>("gg", "black"));
	
	char_char.insert(ft::pair<char, char>('w', 'w'));
	char_bool.insert(ft::pair<char, bool>('e',false));
	char_char.insert(ft::pair<char, char>('z', 'y'));
	char_bool.insert(ft::pair<char, bool>('f',true));
	char_char.insert(ft::pair<char, char>('x', 'w'));
	char_bool.insert(ft::pair<char, bool>('o',false));
	char_char.insert(ft::pair<char, char>('p', 'g'));
	char_bool.insert(ft::pair<char, bool>('z',true));
	std::cout << std::endl;
	std::cout << "------------------------ Testing size after insert ------------------------" << std::endl;

	std::cout << "int_string size: " << int_string.size() << std::endl; 
	std::cout << "string_string size: " << string_string.size() << std::endl; 
	std::cout << "char_char size: " << char_char.size() << std::endl; 
	std::cout << "char_bool size: " << char_bool.size() << std::endl << std::endl; 
	
	int_string.erase(int_string.begin());
	string_string.erase(string_string.begin());
	char_char.erase(char_char.begin());
	char_bool.erase(char_bool.begin());
	std::cout << std::endl;
	std::cout << "------------------------ Testing size after erase ------------------------" << std::endl;

	std::cout << "int_string size: " << int_string.size() << std::endl; 
	std::cout << "string_string size: " << string_string.size() << std::endl; 
	std::cout << "char_char size: " << char_char.size() << std::endl; 
	std::cout << "char_bool size: " << char_bool.size() << std::endl << std::endl; 

	int_string.clear();
	string_string.clear();
	char_char.clear();
	char_bool.clear();
	std::cout << std::endl;
	std::cout << "------------------------ Testing size after clear ------------------------" << std::endl;

	std::cout << "int_string size: " << int_string.size() << std::endl; 
	std::cout << "string_string size: " << string_string.size() << std::endl; 
	std::cout << "char_char size: " << char_char.size() << std::endl; 
	std::cout << "char_bool size: " << char_bool.size() << std::endl << std::endl; 

	ft::map<std::string, std::string>   map_a;
	ft::map<std::string, std::string>::iterator   map_a_it;
	ft::map<std::string, std::string>   map_b;
	ft::map<std::string, std::string>::iterator   map_b_it;

	std::cout << std::endl;
	std::cout << "------------------------ Testing swap before ------------------------" << std::endl;

	ft::map<char,int> foo,bar;
	foo['x']=100;
	foo['y']=200;
	bar['a']=11;
	bar['b']=22;
	bar['c']=33;
	std::cout << "foo contains:\n";
	for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	foo.swap(bar);
	std::cout << std::endl;
	std::cout << "------------------------ Testing swap after ------------------------" << std::endl;

	std::cout << "foo contains:\n";
	for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	std::cout << "------------------------ Testing key_comp ------------------------" << std::endl;

	ft::map<char,int> mymap;
	ft::map<char,int>::key_compare mycomp = mymap.key_comp();

		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;
		std::cout << "mymap contains:\n";
		char highest = mymap.rbegin()->first;	 // key value of last element
		ft::map<char,int>::iterator it = mymap.begin();
		do
			std::cout << it->first << " => " << it->second << std::endl;
		while ( mycomp((*it++).first, highest) );
	std::cout << std::endl;
	std::cout << "------------------------ Testing value_comp ------------------------" << std::endl;

	ft::map<char,int> test_map;
	test_map['x']=1001;
	test_map['y']=2002;
	test_map['z']=3003;
	std::cout << "test_map contains:\n";
	ft::pair<char,int> highest_pair = *test_map.rbegin();          // last element
	ft::map<char,int>::iterator it_val = test_map.begin();
	do {
		std::cout << it_val->first << " => " << it_val->second << '\n';
	} while ( test_map.value_comp()(*it_val++, highest_pair) );
	std::cout << std::endl;
	std::cout << "------------------------ Testing find ------------------------" << std::endl;

	ft::map<int, int>	ope_map;
	ft::map<int, int>::iterator	ope_map_ite;

	ope_map.insert(ft::pair<int, int>(42, 11238));
	ope_map.insert(ft::pair<int, int>(25, 88907));
	ope_map.insert(ft::pair<int, int>(125, 18));
	ope_map.insert(ft::pair<int, int>(16857, 132));
	ope_map.insert(ft::pair<int, int>(568, 18));
	ope_map.insert(ft::pair<int, int>(67568, 658));
	ope_map.insert(ft::pair<int, int>(5687, 5678));
	ope_map.insert(ft::pair<int, int>(64, 54754));
	ope_map.insert(ft::pair<int, int>(5623123, 56782));
	ope_map.insert(ft::pair<int, int>(213, 56754));
	ope_map.insert(ft::pair<int, int>(568, 5687));

	std::cout << " Searching element 42 " << std::endl << std::endl;
	ope_map_ite = ope_map.find(42);
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;
	ope_map_ite = ope_map.find(41232);
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing count ------------------------" << std::endl;

	std::cout << " Counting element 42 " << std::endl << std::endl;
	std::cout << "Occurence have been found " << ope_map.count(42) << " time in the map" << std::endl;
	
	std::cout << " Counting element 84 " << std::endl << std::endl;
	std::cout << "Occurence have been found " << ope_map.count(84) << " time in the map" << std::endl;
	
	std::cout << " Counting element 123897 " << std::endl << std::endl;
	std::cout << "Occurence have been found " << ope_map.count(123897) << " time in the map" << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing lower_bound ------------------------" << std::endl;

	std::cout << " Lower_bound for 184 " << std::endl << std::endl;
	ope_map_ite = ope_map.lower_bound(184);	
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;

	std::cout << " Lower_bound for 1 " << std::endl << std::endl;
	ope_map_ite = ope_map.lower_bound(1);	
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;


	std::cout << " Lower_bound for -1 " << std::endl << std::endl;
	ope_map_ite = ope_map.lower_bound(-1);	
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing upper_bound ------------------------" << std::endl;

	std::cout << " upper_bound for 184 " << std::endl << std::endl;
	ope_map_ite = ope_map.upper_bound(184);	
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;

	std::cout << " upper_bound for -1 " << std::endl << std::endl;
	ope_map_ite = ope_map.upper_bound(-1);	
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;

	std::cout << " upper_bound for 123 " << std::endl << std::endl;
	ope_map_ite = ope_map.upper_bound(123);	
	if (ope_map_ite == ope_map.end())
		std::cout << "unable to find value" << std::endl;
	else
		std::cout << "{" << ope_map_ite->first << "} {"<< ope_map_ite->second << "} "<< std::endl;
	std::cout << std::endl;
	std::cout << "------------------------ Testing equal_range ------------------------" << std::endl;

 	ft::map<char,int> equal_range_map;
	equal_range_map['a']=10;
	equal_range_map['b']=20;
	equal_range_map['c']=30;
	ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
	ret = equal_range_map.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	return (0);
}