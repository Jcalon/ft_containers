# ft_containers

Reimplementation of vector, stack and map in C++.

### How does containers work?

`stack`  
Stack is a LIFO container. It can be built with other containers, such as list. We'll use a private property that will be a container (list by default), but it can be specified during instanciation.

`vector`  
Vector work with a dynamic array: new T[size]. _container is the array containing objects. _container_size is the size of _container in memory. _container_length is the number of elements in the array.

`map`  
Map is an associative array (key => value). It cannot have two pairs with the same key. We can use std::pair to store a pair key/value. It's implemented using a `red black tree`.

