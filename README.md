# AdventOfCode23

# Learning C++
I'm approaching this challenge with the goal of learning about C++. I'll be writing a few thoughts on my experience after completing each challenge. My goal is not to make fast or beautiful code, but rather explore the capabilities of C++.


### Day 1
Learning about `std` and printing. First encounter with strings in C++. Messed around with that a bit after completing the challenge. 

### Day 2
I'm finding out that most C code will work in C++. I challenged myself to actively use C++ strings and associated functions to solve the task. 


### Day 3
I ended up writing this in C-style. The problem is easily translated into scanning certain areas in a 2D array. I think the only reason this wouldn't compile on gcc is that I print the result using `cout`.
Next time I need to build a list in whatever form, I'll try to use std::vector::push_back, and work with the vector class instead.

### Day 4
The problem was solveable by looking at a single parsed line at a time. Perfect for using std::vector. I did get to use vector iterators and std::reduce. Tomorrow I will look for an opportunity to use a higher level function or an array function.


### Day 5
I did manage to create a lambda function today. They do not look pretty in C++, but I am happy to have made one.
Task 2 gave me the chance to work with vectors in a few ways. Iterators are not a good idea if you're pushing work to the vector you're looping through. It took a long time to figure out how to code this thing precisely.
