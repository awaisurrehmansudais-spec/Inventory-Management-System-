#include "inventory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//    ENTERPRISE INVENTORY MANAGEMENT SYSTEM
//    OOP Open Ended Lab - Main File
//    File: main.cpp

//  Global product storage 


product* all_products[100];
string    all_product_types[100];
int       total_products = 0;

supplier  all_suppliers[50];
int       total_suppliers = 0;


//  Helper : print separator line


void print_line()
{
    cout << "-------------------------------------------" << endl;
}


//  Save all products to file


void save_all_products(string filename)
{
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open " << filename << endl;
        return;
    }

    file << total_products << "\n";

    for (int i = 0; i < total_products; i++)
    {
        file << all_product_types[i] << "\n";

        if (all_product_types[i] == "fragile")
        {
            fragile_electronics* fe = (fragile_electronics*) all_products[i];
            fe->save_to_file(file);
        }
        else if (all_product_types[i] == "electronic")
        {
            electronic_product* ep = (electronic_product*) all_products[i];
            ep->save_to_file(file);
        }
        else if (all_product_types[i] == "perishable")
        {
            perishable_grocery* pg = (perishable_grocery*) all_products[i];
            pg->save_to_file(file);
        }
        else if (all_product_types[i] == "nonperishable")
        {
            non_perishable* np = (non_perishable*) all_products[i];
            np->save_to_file(file);
        }
        else if (all_product_types[i] == "grocery")
        {
            grocery_product* gp = (grocery_product*) all_products[i];
            gp->save_to_file(file);
        }
        else if (all_product_types[i] == "clothing")
        {
            clothing_product* cp = (clothing_product*) all_products[i];
            cp->save_to_file(file);
        }
    }

    file.close();
    cout << "All products saved to: " << filename << endl;
}

// -------------------------------------------------------
//  Load all products from file
// -------------------------------------------------------

void load_all_products(string filename)
{
    ifstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "No existing file found: " << filename << " (starting fresh)" << endl;
        return;
    }

    // Free old memory
    for (int i = 0; i < total_products; i++)
    {
        delete all_products[i];
        all_products[i] = nullptr;
    }
    total_products = 0;

    int count;
    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++)
    {
        string type;
        getline(file, type);

        if (type == "fragile")
        {
            fragile_electronics* fe = new fragile_electronics();
            fe->load_from_file(file);
            all_products[total_products]      = fe;
            all_product_types[total_products] = type;
            total_products++;
        }
        else if (type == "electronic")
        {
            electronic_product* ep = new electronic_product();
            ep->load_from_file(file);
            all_products[total_products]      = ep;
            all_product_types[total_products] = type;
            total_products++;
        }
        else if (type == "perishable")
        {
            perishable_grocery* pg = new perishable_grocery();
            pg->load_from_file(file);
            all_products[total_products]      = pg;
            all_product_types[total_products] = type;
            total_products++;
        }
        else if (type == "nonperishable")
        {
            non_perishable* np = new non_perishable();
            np->load_from_file(file);
            all_products[total_products]      = np;
            all_product_types[total_products] = type;
            total_products++;
        }
        else if (type == "grocery")
        {
            grocery_product* gp = new grocery_product();
            gp->load_from_file(file);
            all_products[total_products]      = gp;
            all_product_types[total_products] = type;
            total_products++;
        }
        else if (type == "clothing")
        {
            clothing_product* cp = new clothing_product();
            cp->load_from_file(file);
            all_products[total_products]      = cp;
            all_product_types[total_products] = type;
            total_products++;
        }
    }

    file.close();
    cout << "Loaded " << total_products << " products from: " << filename << endl;
}

// -------------------------------------------------------
//  Save all suppliers to file
// -------------------------------------------------------

void save_all_suppliers(string filename)
{
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open " << filename << endl;
        return;
    }

    file << total_suppliers << "\n";
    for (int i = 0; i < total_suppliers; i++)
        all_suppliers[i].save_to_file(file);

    file.close();
    cout << "All suppliers saved to: " << filename << endl;
}

// -------------------------------------------------------
//  Load all suppliers from file
// -------------------------------------------------------

void load_all_suppliers(string filename)
{
    ifstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "No existing file found: " << filename << " (starting fresh)" << endl;
        return;
    }

    int count;
    file >> count;
    file.ignore();
    total_suppliers = 0;

    for (int i = 0; i < count; i++)
    {
        all_suppliers[total_suppliers].load_from_file(file);
        total_suppliers++;
    }

    file.close();
    cout << "Loaded " << total_suppliers << " suppliers from: " << filename << endl;
}

// -------------------------------------------------------
//  Add Product Menu
// -------------------------------------------------------

void menu_add_product()
{
    print_line();
    cout << "SELECT PRODUCT TYPE TO ADD:" << endl;
    cout << "1. Fragile Electronics"      << endl;
    cout << "2. Electronic Product"       << endl;
    cout << "3. Perishable Grocery"       << endl;
    cout << "4. Non-Perishable Grocery"   << endl;
    cout << "5. Clothing Product"         << endl;
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    string pid, pname, brand, pkg_type, exp_date, pres_level, size, fabric, gender;
    double pprice, storage_temp;
    int pqty, voltage, warranty, frag_rating, calories, shelf_years;
    bool is_halal_input;
    int halal_int;

    // Common inputs
    cout << "Enter Product ID   : "; getline(cin, pid);
    cout << "Enter Product Name : "; getline(cin, pname);
    cout << "Enter Price (PKR)  : "; cin >> pprice;
    cout << "Enter Quantity     : "; cin >> pqty;
    cin.ignore();

    if (choice == 1)
    {
        cout << "Enter Brand Name   : "; getline(cin, brand);
        cout << "Enter Voltage      : "; cin >> voltage;
        cout << "Enter Warranty (months): "; cin >> warranty;
        cout << "Enter Fragility Rating (1-10): "; cin >> frag_rating;
        cin.ignore();
        cout << "Enter Packaging Type: "; getline(cin, pkg_type);

        fragile_electronics* fe = new fragile_electronics(
            pid, pname, pprice, pqty, voltage, warranty, brand, frag_rating, pkg_type
        );
        all_products[total_products]      = fe;
        all_product_types[total_products] = "fragile";
        total_products++;
        cout << "Fragile Electronic added successfully!" << endl;
    }
    else if (choice == 2)
    {
        cout << "Enter Brand Name   : "; getline(cin, brand);
        cout << "Enter Voltage      : "; cin >> voltage;
        cout << "Enter Warranty (months): "; cin >> warranty;
        cin.ignore();

        electronic_product* ep = new electronic_product(
            pid, pname, pprice, pqty, voltage, warranty, brand
        );
        all_products[total_products]      = ep;
        all_product_types[total_products] = "electronic";
        total_products++;
        cout << "Electronic Product added successfully!" << endl;
    }
    else if (choice == 3)
    {
        cout << "Enter Calories     : "; cin >> calories;
        cout << "Is Halal? (1=Yes, 0=No): "; cin >> halal_int;
        cin.ignore();
        is_halal_input = (halal_int == 1);
        cout << "Enter Expiry Date (DD-MM-YYYY): "; getline(cin, exp_date);
        cout << "Enter Storage Temp (C): "; cin >> storage_temp;
        cin.ignore();

        perishable_grocery* pg = new perishable_grocery(
            pid, pname, pprice, pqty, calories, is_halal_input, exp_date, storage_temp
        );
        all_products[total_products]      = pg;
        all_product_types[total_products] = "perishable";
        total_products++;
        cout << "Perishable Grocery added successfully!" << endl;
    }
    else if (choice == 4)
    {
        cout << "Enter Calories     : "; cin >> calories;
        cout << "Is Halal? (1=Yes, 0=No): "; cin >> halal_int;
        cout << "Enter Shelf Life (years): "; cin >> shelf_years;
        cin.ignore();
        is_halal_input = (halal_int == 1);
        cout << "Enter Preservative Level (Low/Medium/High): "; getline(cin, pres_level);

        non_perishable* np = new non_perishable(
            pid, pname, pprice, pqty, calories, is_halal_input, shelf_years, pres_level
        );
        all_products[total_products]      = np;
        all_product_types[total_products] = "nonperishable";
        total_products++;
        cout << "Non-Perishable Grocery added successfully!" << endl;
    }
    else if (choice == 5)
    {
        cout << "Enter Size (S/M/L/XL): "; getline(cin, size);
        cout << "Enter Fabric         : "; getline(cin, fabric);
        cout << "Enter Gender (Male/Female/Unisex): "; getline(cin, gender);

        clothing_product* cp = new clothing_product(
            pid, pname, pprice, pqty, size, fabric, gender
        );
        all_products[total_products]      = cp;
        all_product_types[total_products] = "clothing";
        total_products++;
        cout << "Clothing Product added successfully!" << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

// -------------------------------------------------------
//  Display All Products (Polymorphism demo)
// -------------------------------------------------------

void menu_display_all_products()
{
    if (total_products == 0)
    {
        cout << "No products found." << endl;
        return;
    }

    cout << "===== ALL PRODUCTS (" << total_products << ") =====" << endl;
    for (int i = 0; i < total_products; i++)
    {
        cout << "[" << i + 1 << "] ";
        all_products[i]->display_status();     // polymorphic call
        cout << "Risk Level: " << all_products[i]->calculate_risk() << "%" << endl;
        print_line();
    }
}

// -------------------------------------------------------
//  Apply Discount to a Product
// -------------------------------------------------------

void menu_apply_discount()
{
    if (total_products == 0)
    {
        cout << "No products to apply discount on." << endl;
        return;
    }

    cout << "Enter Product ID to apply discount: ";
    string pid;
    cin.ignore();
    getline(cin, pid);

    double percent;
    cout << "Enter Discount Percentage: ";
    cin >> percent;
    cin.ignore();

    bool found = false;
    for (int i = 0; i < total_products; i++)
    {
        if (all_products[i]->get_product_id() == pid)
        {
            all_products[i]->apply_discount(percent);    // polymorphic call
            cout << "Discount applied! New price: PKR " << all_products[i]->get_price() << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Product not found." << endl;
}

// -------------------------------------------------------
//  Compare Two Products using == operator
// -------------------------------------------------------

void menu_compare_products()
{
    cout << "Enter first Product ID : ";
    string pid1, pid2;
    cin.ignore();
    getline(cin, pid1);
    cout << "Enter second Product ID: ";
    getline(cin, pid2);

    product* p1 = nullptr;
    product* p2 = nullptr;

    for (int i = 0; i < total_products; i++)
    {
        if (all_products[i]->get_product_id() == pid1) p1 = all_products[i];
        if (all_products[i]->get_product_id() == pid2) p2 = all_products[i];
    }

    if (p1 == nullptr || p2 == nullptr)
    {
        cout << "One or both products not found." << endl;
        return;
    }

    if (*p1 == *p2)
        cout << "Both products are the SAME (same ID)." << endl;
    else
        cout << "Products are DIFFERENT." << endl;

    // Also demo the << operator
    cout << *p1 << endl;
    cout << *p2 << endl;
}

// -------------------------------------------------------
//  Add Supplier
// -------------------------------------------------------

void menu_add_supplier()
{
    print_line();
    cout << "ADD SUPPLIER" << endl;

    string sid, sname, terms, prod_id;
    cin.ignore();
    cout << "Enter Supplier ID       : "; getline(cin, sid);
    cout << "Enter Supplier Name     : "; getline(cin, sname);
    cout << "Enter Contract Terms    : "; getline(cin, terms);
    cout << "Enter Linked Product ID : "; getline(cin, prod_id);

    all_suppliers[total_suppliers] = supplier(sid, sname, terms, prod_id);
    total_suppliers++;
    cout << "Supplier added successfully!" << endl;
}

// -------------------------------------------------------
//  Display All Suppliers
// -------------------------------------------------------

void menu_display_all_suppliers()
{
    if (total_suppliers == 0)
    {
        cout << "No suppliers found." << endl;
        return;
    }

    cout << "===== ALL SUPPLIERS (" << total_suppliers << ") =====" << endl;
    for (int i = 0; i < total_suppliers; i++)
    {
        cout << all_suppliers[i] << endl;   // using << operator
        all_suppliers[i].generate_invoice();
        print_line();
    }
}

// -------------------------------------------------------
//  Warehouse Section Demo
// -------------------------------------------------------

void menu_warehouse_demo()
{
    if (total_products == 0)
    {
        cout << "Add some products first to demo the warehouse." << endl;
        return;
    }

    // Create a warehouse
    warehouse my_warehouse("WH-LHR-01", 50000.0);

    // Create two sections
    inventory_section sec_a("A1-Electronics", 20);
    inventory_section sec_b("B2-Grocery",     20);

    // Add products to sections based on type
    for (int i = 0; i < total_products; i++)
    {
        string type = all_product_types[i];
        if (type == "fragile" || type == "electronic")
            sec_a.add_stock(all_products[i], type);
        else
            sec_b.add_stock(all_products[i], type);
    }

    // Sort sections by product ID (operator[] demo inside sort)
    sec_a.sort_by_id();
    sec_b.sort_by_id();

    // Demo operator[] for section access
    cout << "\nFirst product in Electronics section (via operator[]):" << endl;
    if (sec_a.get_product_count() > 0)
    {
        product* first = sec_a[0];
        if (first != nullptr)
            cout << *first << endl;
    }

    // Add sections to warehouse (aggregation)
    my_warehouse.add_section(sec_a);
    my_warehouse.add_section(sec_b);

    // Display full warehouse
    my_warehouse.display_warehouse();

    // Check shortages
    my_warehouse.find_shortages(5);

    // Save warehouse report to file
    my_warehouse.save_warehouse_report("warehouse_report.txt");
}

// -------------------------------------------------------
//  Transaction Log Demo
// -------------------------------------------------------

void menu_transaction_log_demo()
{
    transaction_log<product>  product_log;
    transaction_log<supplier> supplier_log;

    // Record some actions
    for (int i = 0; i < total_products && i < 3; i++)
    {
        string action = "Product added: " + all_products[i]->get_product_name()
                        + " | ID: " + all_products[i]->get_product_id();
        product_log.record_action(action, *all_products[i]);
    }

    for (int i = 0; i < total_suppliers && i < 3; i++)
    {
        string action = "Supplier registered: " + all_suppliers[i].get_supplier_name()
                        + " | ID: " + all_suppliers[i].get_supplier_id();
        supplier_log.record_action(action, all_suppliers[i]);
    }

    product_log.print_audit_trail();
    supplier_log.print_audit_trail();

    product_log.save_log_to_file("product_audit_log.txt");
    supplier_log.save_log_to_file("supplier_audit_log.txt");
}

// -------------------------------------------------------
//  Load Data at startup
// -------------------------------------------------------

void load_all_data()
{
    load_all_products("products_data.txt");
    load_all_suppliers("suppliers_data.txt");
}

// -------------------------------------------------------
//  Save Data before exit
// -------------------------------------------------------

void save_all_data()
{
    save_all_products("products_data.txt");
    save_all_suppliers("suppliers_data.txt");
}

// -------------------------------------------------------
//  Free all heap memory before exit
// -------------------------------------------------------

void free_memory()
{
    for (int i = 0; i < total_products; i++)
    {
        delete all_products[i];
        all_products[i] = nullptr;
    }
    total_products = 0;
}

// -------------------------------------------------------
//  MAIN MENU
// -------------------------------------------------------

int main()
{
    cout << "============================================" << endl;
    cout << "  ENTERPRISE INVENTORY MANAGEMENT SYSTEM   " << endl;
    cout << "============================================" << endl;

    // Login Authentication Loop
    string username = "";
    string password = "";
    bool logged_in = false;

    while (!logged_in)
    {
        cout << "\n--- LOGIN REQUIRED ---" << endl;
        cout << "Enter Username: ";
        getline(cin, username);
        cout << "Enter Password: ";
        getline(cin, password);

        if (username == "admin" && password == "admin 123")
        {
            cout << "\nLogin Successful! Access Granted.\n" << endl;
            logged_in = true;
        }
        else
        {
            cout << "\nIncorrect username or password. Please try again." << endl;
        }
    }

    // Load saved data at startup
    load_all_data();

    int choice = 0;

    while (choice != 9)
    {
        print_line();
        cout << "MAIN MENU:"                              << endl;
        cout << "1. Add Product"                          << endl;
        cout << "2. Display All Products"                 << endl;
        cout << "3. Apply Discount to a Product"          << endl;
        cout << "4. Compare Two Products (== operator)"   << endl;
        cout << "5. Add Supplier"                         << endl;
        cout << "6. Display All Suppliers"                << endl;
        cout << "7. Warehouse Demo (sections + sorting)"  << endl;
        cout << "8. Transaction Log Demo (template class)"<< endl;
        cout << "9. Save & Exit"                          << endl;
        print_line();
        cout << "Enter choice: ";
        cin  >> choice;

        if (choice == 1)       menu_add_product();
        else if (choice == 2)  menu_display_all_products();
        else if (choice == 3)  menu_apply_discount();
        else if (choice == 4)  menu_compare_products();
        else if (choice == 5)  menu_add_supplier();
        else if (choice == 6)  menu_display_all_suppliers();
        else if (choice == 7)  menu_warehouse_demo();
        else if (choice == 8)  menu_transaction_log_demo();
        else if (choice == 9)
        {
            save_all_data();
            cout << "Data saved. Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    // Free all heap memory
    free_memory();

    return 0;
}