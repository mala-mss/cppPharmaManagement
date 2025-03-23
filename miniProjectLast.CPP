#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;
// A pharmaceutical laboratory has decided to automate the management of information on the drugs it
// produces by leveraging dynamic data structures. To achieve this, a binary search tree (BST) will be used,
// where each node represents a drug. This approach ensures efficient search, insertion, and deletion
// operations based on a drug's unique identifier (an integer). Each drug is characterized by the following
// attributes: a unique number (integer), a label (character string), a unit price (real), a category (character
// string), and a linked list of product (name and quantity) required for its manufacture.
// Work requested:
// Develop a C++ program that should allow, from a menu, to :

enum choic
{
    addDrug = 1,
    display = 2,
    search = 3,
    addProduct = 4,
    RemoveProduct = 5,
    SearchNdDisplayDrugByProductName = 6,
    ReplaceProdInAllDrugs = 7,
    ManageCategories = 8,
    SaveDrugsInFile = 9,
    LoadDrugFromFile = 10,
    DeleteDrugById = 11,
    DeleteallDrugsInCategory = 12,
    Clear_File=13
};
// Part 1:

// 1) Enter the information (number, label, price, and category) of a drug and insert it into the drug
// tree.
struct Product
{
    string name;
    int quantity;
};

struct Node
{
    Product prod;
    Node *next = NULL;
};
typedef Node *List;

struct Drug
{
    int ID;
    string label;
    float unitPrice;
    string category;
    List products = NULL;
};

struct TreeNode
{
    Drug element;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
};
typedef TreeNode *Tree;

void addToList(List &list, Product product)
{
    List p = new Node();
    p->prod = product;
    p->next = list;
    list = p;
}

List addProducts()
{
    List products = NULL;
    cout << "How many products make this drug? \t";
    int numProducts;
    cin >> numProducts;

    for (int i = 0; i < numProducts; ++i)
    {
        cout << "Product [" << i + 1 << "]: \n";
        Product prod;
        cout << "Product Name :\t";
        cin >> prod.name;
        cout << "Product Quantity:\t";
        cin >> prod.quantity;
        addToList(products, prod);
    }
    return products;
}
void addProducts(List & products)
{
   
    cout << "How many products you want to add to this drug? \t";
    int numProducts;
    cin >> numProducts;

    for (int i = 0; i < numProducts; ++i)
    {
        cout << "Product [" << i + 1 << "]: \n";
        Product prod;
        cout << "Product Name :\t";
        cin >> prod.name;
        cout << "Product Quantity:\t";
        cin >> prod.quantity;
        addToList(products, prod);
    }
    return ;
}
Tree createTree(Drug drug)
{
    Tree newTree = new TreeNode();
    newTree->element = drug;
    return newTree;
}
Drug createDrug()
{
    Drug drug;
    cout << "Enter drug ID:\t ";
    cin >> drug.ID;
    cout << "Enter drug label:\t ";
    cin >> drug.label;
    cout << "Enter drug category:\t ";
    cin >> drug.category;
    cout << "Enter drug unit price: \t";
    cin >> drug.unitPrice;

    drug.products = addProducts();
    return drug;
}

void insert(Tree &tree, Drug drug)
{
    if (tree == NULL)
    {
        tree = createTree(drug);
    }
    else if (drug.ID < tree->element.ID)
    {
        insert(tree->left, drug);
    }
    else if (drug.ID > tree->element.ID)
    {
        insert(tree->right, drug);
    }
     else
    {
     
        cout << "Already exists \n ";
    }
}

void displayProduct(Product p)
{
    cout << "|  ";
    cout << "Product Name:      \t[ " << p.name << " ]" << endl;
    cout << "|\n";
    cout << "|  ";
    cout << "Product Quantity: \t[ " << p.quantity << " ]";
    cout << "|\n";
}
void displayList(List list)
{
    List current = list;
    while (current != NULL)
    {
        cout << "------------------------------\n";

        displayProduct(current->prod);

        cout << "------------------------------\n";
        current = current->next;
    }
}

// 2) Fill in the list of products that make up a drug identified by its number. If the drug does not exist
// in the tree, the program must display an error message.

void searchAndAdd(Tree &tree, int id)
{
    if (tree == NULL)
    {
        cout << "Drug not found. Would you like to add it? (Y/N): ";
        char choice;
        cin >> choice;
        if (toupper(choice) == 'Y')
        {
            insert(tree, createDrug());
        }
        return;
    }

    if (id == tree->element.ID)
    {
          addProducts(tree->element.products);
    }
    else if (id < tree->element.ID)
    {
        searchAndAdd(tree->left, id);
    }
    else
    {
        searchAndAdd(tree->right, id);
    }
}

// 3) Display drugs produced by the laboratory (display of drug labels)
void HeaderMsg()
{
    cout << "\n------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "                                    **  Drugs List  **\n";
    cout << "\n------------------------------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------\n";

    cout << "ID\tLabel\t\tUnit Price\tCategory\t\tProducts" << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n";
}

void displayDrugs(Tree tree)
{
    if (tree == NULL)
    {
        return;
    }

    displayDrugs(tree->left);

    cout << tree->element.ID << "\t" << tree->element.label << "\t\t" << tree->element.unitPrice << "\t\t" << tree->element.category << "\t\t";

    List c = tree->element.products;
    string products = "";
    while (c != NULL)
    {
        products += c->prod.name + " (" + to_string(c->prod.quantity) + ")";
        c = c->next;
        if (c != NULL)
            products += ", ";
    }

    cout << products << endl;

    displayDrugs(tree->right);
}

// 4) Search for a drug by its unique number and display its main information along with the list of
// products required for its composition.

void DrugCard(Drug drug)
{
    cout << "\n==============DRUG CARD===============\n";
    cout << "ID: \t" << drug.ID << endl;
    cout << "Label: \t" << drug.label << endl;
    cout << "Price: \t" << drug.unitPrice << endl;
    cout << "Category: \t" << drug.category << endl;
    cout << "Products: \n";
    displayList(drug.products);
    cout << "============================================\n";
}

void searchAndDisplay(Tree tree, int id)
{
    if (tree == NULL)
    {
        cout << "\n***** DRUG NOT FOUND *****\n";
        return;
    }

    if (id == tree->element.ID)
    {
        DrugCard(tree->element);
    }
    else if (id < tree->element.ID)
    {
        searchAndDisplay(tree->left, id);
    }
    else
    {
        searchAndDisplay(tree->right, id);
    }
}

// Part 2:

// 1) Delete a drug identified by its number from the drug tree.
Tree FindMin(Tree a)
{
    while (a->left != NULL)
    {
        a = a->left;
    }
    return a;
}
bool IsLeaf(Tree a)
{
    if ((a->right == NULL) && (a->left == NULL))
    {
        return true;
    }
    return false;
}

void deleteDrug(Tree &a, int Identifier)
{
    if (a == NULL)
    {
        cout << "\n****DRUG NOT FOUND*****\n";
        return;
    }
    else if (a->element.ID == Identifier)
    {
        if (IsLeaf(a))
        {
            Tree temp = a;
            a = NULL;
            delete temp;
        }
        else if (a->left == NULL)
        {
            Tree temp = a;
            a = a->right;
            delete temp;
        }
        else if (a->right == NULL)
        {
            Tree temp = a;
            a = a->left;
            delete temp;
        }
        else
        {
            Tree temp = FindMin(a->right);
            a->element = temp->element;
            deleteDrug(a->right, temp->element.ID);
        }
    }
    else
    {
        if (a->element.ID > Identifier)
        {
            deleteDrug(a->left, Identifier);
        }
        else
        {
            deleteDrug(a->right, Identifier);
        }
    }
}
// 2) Remove a product, identified by its name, from the list of products required to compose a drug,
// identified by its unique number.
void removeListWithName(List &l, string Name)
{

    if (l == NULL)
    {
        return;
    }

    if (l->prod.name == Name)
    {
        List temp = l;
        l = l->next;
        delete temp;
        removeListWithName(l, Name);
    }
    else
    {

        removeListWithName(l->next, Name);
    }
}
void removeProductFromDrug(Tree &tree, int id, string ProductName)
{
    if (tree == NULL)
    {
        cout << "This Drug Doesn't Exist here :-(\n";
        return;
    }

    if (tree->element.ID == id)
    {
        removeListWithName(tree->element.products, ProductName);
        cout << "Product was deleted successfully :-)\n";
        return;
    }

    if (id < tree->element.ID)
    {
        removeProductFromDrug(tree->left, id, ProductName);
    }
    else
    {
        removeProductFromDrug(tree->right, id, ProductName);
    }
}

//  3) Search for and display all drugs that contain a product identified by its name.

void SearchNdDisplay(Tree tree, string Name)
{
    if (tree == NULL)
    {
        return;
    }
    List c = tree->element.products;
    while (c != NULL)
    {
        if (c->prod.name == Name)
        {
            DrugCard(tree->element);
            break;
        }
        c = c->next;
    }

    SearchNdDisplay(tree->left, Name);
    SearchNdDisplay(tree->right, Name);
}

// 4) Replace  one  product  with  another  in  all  the  lists  of  products  used  to  compose  the  laboratory's
// drugs.

void SearchNdReplace(Tree &tree, string newProd, string WeHave)
{
    if (tree == NULL)
    {
        return;
    }
    List c = tree->element.products;
    while (c != NULL)
    {
        if (c->prod.name == WeHave)
        {
            c->prod.name = newProd;
            break;
        }
        c = c->next;
    }

    SearchNdReplace(tree->left, newProd, WeHave);
    SearchNdReplace(tree->right, newProd, WeHave);
}

//  Part 3:
// 1) Display the laboratory's drug categories.

struct NodeCategory
{
    string category;
    TreeNode *Drugs;
    NodeCategory *Left, *Right;
};

typedef NodeCategory *categoryTree;

void insertDrugInTheCategory(categoryTree &Category, Drug drug)
{

    if (Category == NULL)
    {
        Category = new NodeCategory();
        Category->category = drug.category;
        Category->Drugs = NULL;
        Category->Left = NULL;
        Category->Right = NULL;

        insert(Category->Drugs, drug);
        return;
    }

    if (drug.category < Category->category)
    {
        insertDrugInTheCategory(Category->Left, drug);
    }
    else if (drug.category > Category->category)
    {
        insertDrugInTheCategory(Category->Right, drug);
    }
    else
    {
        insert(Category->Drugs, drug);
    }
}

void displayCategories( categoryTree Category)
{
    if (Category == NULL)
        return;

    displayCategories(Category->Left);
    cout << "\nCategorie " << Category->category << "\n";
    displayCategories(Category->Right);
}
// 2) Visualize the drug tree organized by category
void DrugCards(Tree Drugs)
{
    if (Drugs == NULL)
        return;

    DrugCards(Drugs->left);
    DrugCard(Drugs->element);
    DrugCards(Drugs->right);
}

void displayDrugsInCategory(categoryTree Category)
{
    if (Category == NULL)
        return;

    displayDrugsInCategory(Category->Left);

    cout << "\nIn The Category ** " << Category->category << " ** : \n";

    if (Category->Drugs == NULL)
    {
        cout << "No drugs available in this category.\n";
    }
    else
    {
        DrugCards(Category->Drugs);
    }

    displayDrugsInCategory(Category->Right);
}

// Part 4: Additional
// 3) Implement a feature to save the drug tree to a file.

string TransferOneDrugRecordToALine(Drug &Record)
{
    string Line = "";
    string Delim = "//#//";
    Line += to_string(Record.ID) + Delim;
    Line += Record.label + Delim;
    Line += to_string(Record.unitPrice) + Delim;
    Line += Record.category;

    string DelimForProd = "µµµµ";
    List current = Record.products;

    if (current != NULL)
    {
        Line += Delim + DelimForProd;
        while (current != NULL)
        {
            Line += current->prod.name + "**" + to_string(current->prod.quantity);
            current = current->next;
            if (current != NULL)
                Line += DelimForProd;
        }
    }

    return Line;
}

// Function to split a string by a delimiter
vector<string> splitString(string str,string Delim){
    int ps=0;
    string sword;
   vector<string> result;
    while((ps=str.find(Delim))!=string::npos){// ida kayen delim m3naha mazal kayen klmat mch m9somin basically

        result.push_back(str.substr(0,ps));
        str.erase(0,ps+Delim.length());
    }
    //to add the last word;
    result.push_back(str.substr(0,ps));
    return result;
}
// transfer one line to a record
Drug TransferOneLineToARecord(string &Line)
{
    string delim = "//#//";
    string delimForProd = "µµµµ";
    vector<string> drugs = splitString(Line, delim);

    Drug drug;
    drug.ID = stoi(drugs[0]);
    drug.label = drugs[1];
    drug.unitPrice = stof(drugs[2]);
    drug.category = drugs[3];

    if (drugs.size() > 4)
    {
        vector<string> prodData =splitString(drugs[4], delimForProd);
        for ( string &prod : prodData)
        {
            if (prod.empty())
                continue;

            size_t pos = prod.find("**");
            if (pos == string::npos)
                continue;

            Product product;
            product.name = prod.substr(0, pos);
            product.quantity = stoi(prod.substr(pos + 2));

            addToList(drug.products, product);
        }
    }

    return drug;
}

// save one line to a file
void LineToFile(string FileName, string Line)
{
    fstream DrugFile;
     DrugFile.open(FileName, ios::out |ios::app);
    if (DrugFile.is_open())
    {
        
        DrugFile << Line << endl;
        cout<<"One File Uploaded ...\n";
        DrugFile.close();
    }
}
void DrugsToFile(string &fileName, Tree drugTree)
{
    if (drugTree == NULL)
        return;

    DrugsToFile(fileName, drugTree->left);

    string Line = TransferOneDrugRecordToALine(drugTree->element);
    LineToFile(fileName, Line);

    DrugsToFile(fileName, drugTree->right);
}

// extract data from file to a  drug record
vector<Drug> FileToRecords(string FileName)
{
    vector<Drug> drugs;
    fstream DrugFile;
    string Line;
    DrugFile.open(FileName, ios::in);
    if (DrugFile.is_open())
    {
        while (getline(DrugFile, Line))
        {
            drugs.push_back(TransferOneLineToARecord(Line));
        }
        DrugFile.close();
    }
    return drugs;
}
void clearFile(string fileName){
   
    fstream DrugsFile;
    DrugsFile.open(fileName, ios::out);
    if(DrugsFile.is_open()){
        
      
       DrugsFile.close();
       
    }
    else{
        cout<<"file not open and not cleared ";
    }
    return;
}

// 4) Add a functionality to delete all drugs within a specified category.

void deleteTree(Tree &root)
{
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = NULL;
}

void deleteCategories(categoryTree &category)
{
    if (category == NULL)
        return;

    deleteCategories(category->Left);
    deleteCategories(category->Right);
    deleteTree(category->Drugs);
    delete category;
    category = NULL;
}
choic Choice()
{
    int choice;
    cout << "enter ur choice:\t";
    do
    {
        cin >> choice;
    } while (choice < 0 || choice > 13);
    return (choic)choice;
}
void menu()
{
    cout << "=========================================================================\n";
    cout << "\t\t            Pharmaceutical Management System\n";
    cout << "==========================================================================\n";
    cout << "  \t[1] Add a new drug.\n";
    cout << "  \t[2] Display all drugs.\n";
    cout << "  \t[3] Search for a drug by ID.\n";
    cout << "  \t[4] Add a product to an existing drug.\n";
    cout << "  \t[5] Remove a product from a drug.\n";
    cout << "  \t[6] Search and display drugs by product name.\n";
    cout << "  \t[7] Replace a product in all drugs.\n";
    cout << "  \t[8] Manage categories .\n";
    cout << "  \t[9] Save drugs to file.\n";
    cout << "  \t[10] Load drugs from file.\n";
    cout << "  \t[11] Delete a drug by ID.\n";
    cout << "  \t[12] Delete all drugs in a category.\n";
    cout << "  \t[13] Clear File.\n";
    cout << "  \t[0] Exit.\n";
    cout << "========================================================================\n";
}
void startPharmaceuticalswitch(Tree &drugTree, categoryTree &categoryTree, string fileName)
{

    menu();

    switch (Choice())
    {
    
    case addDrug:
    {  system("cls");
        cout << "\n**************ADD NEW DRUG*******************\n";
        char addMore;
        do
        {
            Drug newDrug = createDrug();
            insert(drugTree, newDrug);
            insertDrugInTheCategory(categoryTree, newDrug);
            cout << "Do you want to add another drug? [Y\\N]: ";
            cin >> addMore;
            addMore = toupper(addMore);
        } while (addMore == 'Y');
        break;
    }
    case display:
    { // Display all drugs
    system("cls");
        cout << "\n**************DISPLAY*******************\n";
        if (drugTree == NULL)
        {
            cout << "No drugs found in the system. Please add some first.\n";
        }
        else
        {
            cout << "Displaying all drugs....:\n";
            HeaderMsg();

            displayDrugs(drugTree);
            cout << "\n------------------------------------------------------------------------------------------------\n";
        }
        break;
    }
    case search:
    { // Search by ID
    system("cls");
    cout << "\n**************SEARCH BY ID*******************\n";
        char searchAgain;
        do
        {
            int id;
            cout << "Enter the drug ID: ";
            cin >> id;
            searchAndDisplay(drugTree, id);
            cout << "Do you want to search for another drug? [Y\\N]: ";
            cin >> searchAgain;
            searchAgain = toupper(searchAgain);
        } while (searchAgain == 'Y');
        break;
    }
    case addProduct:
    { // Add a product to a drug
    system("cls");
       cout << "\n**************ADD A PRODUCT TO A DRUG*******************\n";
        char addProductAgain;
        do
        {
            int id;
            cout << "Enter the drug ID to add products: ";
            cin >> id;
            searchAndAdd(drugTree, id);
            cout << "Do you want to add products to another drug? [Y\\N]: ";
            cin >> addProductAgain;
            addProductAgain = toupper(addProductAgain);
        } while (addProductAgain == 'Y');
        break;
    }
    case RemoveProduct:
    system("cls");
    { // Remove a product from A drug
    cout << "\n**************REMOVE A PRODUCT FROM A DRUG*******************\n";
        char removeProductAgain;
        do
        {
            int id;
            string productName;
            cout << "Enter the drug ID: ";
            cin >> id;
            cout << "Enter the product name to remove: ";
            cin >> productName;
            removeProductFromDrug(drugTree, id, productName);
            cout << "Do you want to remove products from another drug? [Y/N]: ";
            cin >> removeProductAgain;
            removeProductAgain = toupper(removeProductAgain);
        } while (removeProductAgain == 'Y');
        break;
    }
    case SearchNdDisplayDrugByProductName:
    system("cls");
    {    cout << "\n**************SEARCH AND DISPLAY DRUG BY PRODUCT NAME*******************\n";
        char searchProductAgain;
        do
        {
            string productName;
            cout << "Enter the product name: ";
            cin >> productName;
            SearchNdDisplay(drugTree, productName);
            cout << "Do you want to search for another product? [Y/N]: ";
            cin >> searchProductAgain;
            searchProductAgain = toupper(searchProductAgain);
        } while (searchProductAgain == 'Y');
        break;
    }
    case ReplaceProdInAllDrugs:
    system("cls");
    {cout << "\n**************REPLACE A PRODUCT IN ALL DRUGS*******************\n";
        string oldProduct, newProduct;
        cout << "Enter the product name to replace: ";
        cin >> oldProduct;
        cout << "Enter the new product name: ";
        cin >> newProduct;
        SearchNdReplace(drugTree, newProduct, oldProduct);
        break;
    }
    case ManageCategories:
    system("cls");
    {   cout << "\n**************MANAGE CATEGORIES*******************\n";
        int subChoice;
        cout << "1. View categories\n";
        cout << "2. Display drugs by category\n";
        cout << "3. Delete all drugs in a category\n";
        cout << "\n***************************************************\n";
        cout << "Enter your choice: ";
        cin >> subChoice;
        if (subChoice == 1)
        {
            displayCategories(categoryTree);
        }
        else if (subChoice == 2)
        {
            displayDrugsInCategory(categoryTree);
        }
        else if (subChoice == 3)
        {
            deleteCategories(categoryTree);
        }

        break;
    }
    case SaveDrugsInFile:
    {  system("cls");
        DrugsToFile(fileName, drugTree);

        break;
    }
    case LoadDrugFromFile:
    { // Load drugs from file
        vector<Drug> drugs = FileToRecords(fileName);
        for (const Drug &drug : drugs)
        {
            insert(drugTree, drug);
            insertDrugInTheCategory(categoryTree, drug);
        }
        cout << "Drugs loaded from file successfully.\n";
        break;
    }
    case DeleteDrugById:
    { // Delete a drug by ID
        char deleteMore;
        do
        {
            int id;
            cout << "Enter the drug ID to delete: ";
            cin >> id;
            deleteDrug(drugTree, id);
            cout << "Do you want to delete another drug? [Y\\N]: ";
            cin >> deleteMore;
            deleteMore = toupper(deleteMore);
        } while (deleteMore == 'Y');
        break;
    }
    case DeleteallDrugsInCategory:
    { // Delete all drugs in a category
        string categoryName;
        cout << "Enter the category name to delete all drugs: ";
        cin >> categoryName;
        deleteCategories(categoryTree);
        break;
    }
         case Clear_File: 
    cout<<"before the call ";
      clearFile(fileName);
      break;
    case 0: // Exit
        cout << "Exiting ..... Goodbye!\n";
        return;
    }
    return;
}
void cleanup(Tree &drugTree, categoryTree &categoryTree)
{
    deleteTree(drugTree);
    deleteCategories(categoryTree);
}

void startPharmaceutical()
{
    char choice = 'N';
    Tree drugTree = NULL;
    categoryTree categoryTree = NULL;
    string fileName = "DrugRecords.txt";
    do
    {
        system("cls");

        startPharmaceuticalswitch(drugTree, categoryTree, fileName);
        cout << "do you want to enter to the pharmaceutical again???[Y\\N]\t";
        cin >> choice;
        choice = toupper(choice);
    } while (choice != 'N');
    cout << "Thank you for visiting ^^\n";
    cleanup(drugTree, categoryTree);
    return;
}
int main()
{

    startPharmaceutical();

    system("pause>0");
    return 0;
}
