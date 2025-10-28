# Pharmaceutical Management System (C++ / BST)

Console program to manage drugs using a Binary Search Tree (BST) keyed by drug ID.  
Each drug stores a linked list of manufacturing products (name + quantity).  
Includes save/load to a flat file.

## Core Features
- Add a drug (ID, label, unit price, category, products list)
- Display all drugs (in-order BST traversal)
- Search and show a drug by ID
- Add products to an existing drug
- Remove a product from a drug
- Find and display all drugs that use a given product
- Replace a product name across all drugs
- Category view: group drugs by category (secondary BST over categories)
- Persist to file and reload
- Delete a drug by ID
- Delete all drugs in a category (clears category BST + inner drug trees)
- Clear the data file

## Data Structures
- `Tree` = BST of `Drug` by `ID`
- `List` = singly linked list of `Product { name, quantity }`
- `categoryTree` = BST keyed by `category` string; each node holds a `Tree` of drugs in that category

## Menu (enum `choic`)
1. Add a new drug  
2. Display all drugs  
3. Search for a drug by ID  
4. Add a product to a drug  
5. Remove a product from a drug  
6. Search & display drugs by product name  
7. Replace a product in all drugs  
8. Manage categories  
9. Save drugs to file  
10. Load drugs from file  
11. Delete a drug by ID  
12. Delete all drugs in a category  
13. Clear file  
0. Exit

## Build & Run

### Windows (MinGW g++)
```bash
g++ -std=c++17 -O2 -Wall main.cpp -o pharma.exe
pharma.exe
