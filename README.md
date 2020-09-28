# CSCI-103-Project-6-Filesystem
You will design and
implement a program that behaves very similarly to your Mac/Linux terminal or Windows cmd. In
order to do that, we need to create a filesystem. With this filesystem in place, you will be able to
execute some basic commands to interact with our CS103L terminal such as “cd” to change
directory, “rm” to delete a file or directory, “mkdir” to create a directory, “ls” to list all items in the
current directory, etc (see Section 5 for more commands that you can execute). For now, your
filesystem will only support managing directories and text files. In addition, we will keep all our
data in memory and you don’t actually have to read from or write to an “actual” file. In other
words, once you exit the program, all data in your filesystem will be deleted.

Under the hood, we will be using a doubly linked list. At this point, you should probably
have an idea of what it is. Compared to a singly linked list, a doubly linked list helps us in
multiple ways. For instance, 1). delete operation takes O(1) if the node to be deleted is given.
This is because all you need to do is adjusting the pointers of its next and prev nodes. The
information on these nodes can be retrieved directly from the node to be deleted itself. And 2).
traverse the list can be done both ways (top -> bottom, bottom -> top). However, to implement a
doubly linked list, you need to manage two pointers for each node. For more detail, check Unit
15. With that said, this data structure is perfect for our task.

In this assignment, you will practice and acquire the following skills:
● Dynamically memory allocation of structs and classes.
● Handling a great amount of pointers.
● Implementing multiple recursive functions.
● Creating a program using a doubly linked list as an underlying data structure.
