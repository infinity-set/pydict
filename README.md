# pydct - Python-Style Dictionary Implementation in C

## Overview

Welcome to the `pydct` repository! This C program provides a simple implementation of a Python-style dictionary, allowing key-value pair management using linked lists. It serves as a practical resource for understanding linked lists, memory management, and basic data structure implementation in the C programming language.

## Table of Contents

- [Why Use This Script](#why-use-this-script)
- [Prerequisites](#prerequisites)
- [Languages and Utilities Used](#languages-and-utilities-used)
- [Environments Used](#environments-used)
- [Data Structures](#data-structures)
- [Functions](#functions)
- [Usage](#usage)

## Why Use This Script

This project introduces a basic Python-style dictionary in C, providing insights into linked list implementation and key-value pair management. It's suitable for learners aiming to grasp fundamental concepts of memory management, pointers, and basic data structures in a dictionary context.

## Prerequisites

Before using this C program, ensure that you have the following:

- A C compiler installed on your system.
- Basic understanding of C programming, including linked lists and memory allocation concepts.
- Review: [Python List Class Implementation in C](https://github.com/infinity-set/pylst)

## Languages and Utilities Used

- **C**
- **Visual Studio Code**

[<img  alt="C Logo Icon" width="45px" src="https://upload.wikimedia.org/wikipedia/commons/1/18/C_Programming_Language.svg" />][C]
[<img alt="Visual Code Icon" width="45px" src="https://upload.wikimedia.org/wikipedia/commons/9/9a/Visual_Studio_Code_1.35_icon.svg" />][vscode]

[C]: https://learn.microsoft.com/en-us/cpp/c-language/
[vscode]: https://code.visualstudio.com/

## Environments Used

- **Windows**

[<img align="left" alt="Microsoft Icon" width="35px" src="https://upload.wikimedia.org/wikipedia/commons/3/34/Windows_logo_-_2012_derivative.svg" />][windows]

[windows]: https://www.microsoft.com/

<br /><br />

## Data Structures

### Dictionary Node Structure (`dict_node`)

- `char *key`: Pointer to the key string.
- `int key_length`: Length of the key.
- `int key_alloc`: Allocated memory for the key.
- `char *value`: Pointer to the value string.
- `int value_length`: Length of the value.
- `int value_alloc`: Allocated memory for the value.
- `struct dict_node *next`: Pointer to the next node.

### Python-Style Dictionary Structure (`pydict`)

- `dict_node *head`: Pointer to the head of the dictionary.
- `dict_node *tail`: Pointer to the tail of the dictionary.
- `int count`: Number of nodes in the dictionary.

## Functions

### `pydict_new()`

- Creates a new empty Python-style dictionary.
  - **Python syntax:** 
    ```python
    new_dict = {}
    ```

### `pydict_put(pydict *self, const char *key_string, const char *value_string)`

- Puts or updates a key-value pair in the Python-style dictionary.
  - **Python syntax:** 
    ```python
    existing_dict[key_string] = value_string
    ```

### `pydct_append(pydict *self, const char *key_string, const char *value_string)`

- Appends a new key-value pair to the Python-style dictionary.
  - **Python syntax:** 
    ```python
    existing_dict[key_string] = value_string
    ```

### `pydict_print(pydict *self)`

- Prints the contents of the Python-style dictionary.
  - **Python syntax:** 
    ```python
    print(existing_dict)
    ```

### `pydict_del(pydict *self)`

- Deletes the entire Python-style dictionary and frees memory.
  - **Python syntax:** 
    Note: Python handles memory management automatically, so no explicit deletion is required.

### `pydict_len(pydict *self)`

- Returns the length of the Python-style dictionary.
  - **Python syntax:** 
    ```python
    dict_length = len(existing_dict)
    ```

### `pydict_get(pydict *self, const char *key_string)`

- Gets the value associated with a key in the Python-style dictionary.
  - **Python syntax:** 
    ```python
    value = existing_dict.get(key_string)
    ```

### `pydict_find(pydict *self, const char *key_string)`

- Finds a node in the Python-style dictionary based on the key.
  - **Python syntax:** 
    ```python
    if key_string in existing_dict:
        # Node found
    ```


## Usage

The `main` function in the provided C code demonstrates the creation, appending, printing, and deletion of the Python-style dictionary (`pydict`).

Feel free to explore and modify the code according to your needs.

 <div align="center">
<br/>
<img src="https://github.com/infinity-set/pylst/assets/142350896/dcfc08e5-59c3-46c8-a5d3-ac15549b0ca2" height="100%" width="100%" alt="Main function code displayed in C"/>
<br />   
 </div>

 <div align="center">
<br/>
<img src="https://github.com/infinity-set/pylst/assets/142350896/8d99d582-8eb5-4c18-bebf-a391a9d9e64c" height="100%" width="100%" alt="Output of the execution displayed."/>
<br />   
 </div>

<br />

Feel free to explore and modify the code according to your needs.

#

⬅️ **[Home](https://github.com/infinity-set)**
