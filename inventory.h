#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// ============================================================
//                  FORWARD DECLARATIONS
// ============================================================

class product;
class electronic_product;
class fragile_electronics;
class grocery_product;
class perishable_grocery;
class non_perishable;
class clothing_product;
class supplier;
class inventory_section;
class warehouse;

// ============================================================
//              TEMPLATE CLASS - TRANSACTION LOG
// ============================================================

template <typename T>
class transaction_log
{
    private:
        string log_history[100];
        int log_count;

    public:
        transaction_log();
        void record_action(string action, T& entity);
        void print_audit_trail();
        void save_log_to_file(string filename);
};

// ============================================================
//                  CLASS DECLARATIONS
// ============================================================

// --- 1. Product (Abstract Base Class) ---
class product
{
    protected:
        string product_id;
        double price;
        int quantity;
        string product_name;

    public:
        product();
        product(string pid, string pname, double pprice, int pqty);
        product(const product& other);
        product& operator=(const product& other);
        virtual ~product();

        // Getters
        string get_product_id();
        string get_product_name();
        double get_price();
        int get_quantity();

        // Setters with validation
        void set_price(double p);
        void set_quantity(int q);

        // Virtual functions (polymorphism)
        virtual void display_status();
        virtual double calculate_value();
        virtual double calculate_risk();
        virtual void apply_discount(double percent);

        // Operator overloading
        bool operator==(product& other);
        friend ostream& operator<<(ostream& out, product& p);

        // File handling
        virtual void save_to_file(ofstream& file);
        virtual void load_from_file(ifstream& file);
};

// --- 2. ElectronicProduct ---
class electronic_product : public product
{
    protected:
        int voltage;
        int warranty_months;
        char* brand_name;                     // pointer for Rule of 3

    public:
        electronic_product();
        electronic_product(string pid, string pname, double pprice, int pqty,
                           int volt, int warranty, string brand);
        electronic_product(const electronic_product& other);
        electronic_product& operator=(const electronic_product& other);
        ~electronic_product();

        string get_brand_name();
        void test_hardware();

        void display_status() override;
        double calculate_risk() override;
        void apply_discount(double percent) override;

        void save_to_file(ofstream& file) override;
        void load_from_file(ifstream& file) override;
};

// --- 3. FragileElectronics ---
class fragile_electronics : public electronic_product
{
    private:
        int fragility_rating;                 // 1 to 10
        string packaging_type;

    public:
        fragile_electronics();
        fragile_electronics(string pid, string pname, double pprice, int pqty,
                            int volt, int warranty, string brand,
                            int frag_rating, string pkg_type);
        fragile_electronics(const fragile_electronics& other);
        fragile_electronics& operator=(const fragile_electronics& other);
        ~fragile_electronics();

        double calculate_shipping_risk();

        void display_status() override;
        double calculate_risk() override;
        void apply_discount(double percent) override;

        void save_to_file(ofstream& file) override;
        void load_from_file(ifstream& file) override;
};

// --- 4. GroceryProduct ---
class grocery_product : public product
{
    protected:
        int calories;
        bool is_halal;

    public:
        grocery_product();
        grocery_product(string pid, string pname, double pprice, int pqty,
                        int cal, bool halal);
        grocery_product(const grocery_product& other);
        grocery_product& operator=(const grocery_product& other);
        ~grocery_product();

        void check_safety();

        void display_status() override;
        double calculate_risk() override;
        void apply_discount(double percent) override;

        void save_to_file(ofstream& file) override;
        void load_from_file(ifstream& file) override;
};

// --- 5. PerishableGrocery ---
class perishable_grocery : public grocery_product
{
    private:
        string expiry_date;
        double storage_temp;

    public:
        perishable_grocery();
        perishable_grocery(string pid, string pname, double pprice, int pqty,
                           int cal, bool halal,
                           string exp_date, double s_temp);
        perishable_grocery(const perishable_grocery& other);
        perishable_grocery& operator=(const perishable_grocery& other);
        ~perishable_grocery();

        bool check_expiry();

        void display_status() override;
        double calculate_risk() override;
        void apply_discount(double percent) override;

        void save_to_file(ofstream& file) override;
        void load_from_file(ifstream& file) override;
};

// --- 6. NonPerishable ---
class non_perishable : public grocery_product
{
    private:
        int shelf_life_years;
        string preservative_level;

    public:
        non_perishable();
        non_perishable(string pid, string pname, double pprice, int pqty,
                       int cal, bool halal,
                       int shelf_yrs, string pres_level);
        non_perishable(const non_perishable& other);
        non_perishable& operator=(const non_perishable& other);
        ~non_perishable();

        string get_storage_instructions();

        void display_status() override;
        double calculate_risk() override;
        void apply_discount(double percent) override;

        void save_to_file(ofstream& file) override;
        void load_from_file(ifstream& file) override;
};

// --- 7. ClothingProduct ---
class clothing_product : public product
{
    private:
        string size;
        string fabric;
        string gender;

    public:
        clothing_product();
        clothing_product(string pid, string pname, double pprice, int pqty,
                         string sz, string fab, string gen);
        clothing_product(const clothing_product& other);
        clothing_product& operator=(const clothing_product& other);
        ~clothing_product();

        void fit_guide();

        void display_status() override;
        double calculate_risk() override;
        void apply_discount(double percent) override;

        void save_to_file(ofstream& file) override;
        void load_from_file(ifstream& file) override;
};

// --- 8. Supplier (Association with Product) ---
class supplier
{
    private:
        string supplier_id;
        string supplier_name;
        string contract_terms;
        string linked_product_id;

    public:
        supplier();
        supplier(string sid, string sname, string terms, string prod_id);
        supplier(const supplier& other);
        supplier& operator=(const supplier& other);
        ~supplier();

        string get_supplier_id();
        string get_supplier_name();
        string get_linked_product_id();

        void order_restock(int amount);
        void generate_invoice();

        void display_supplier();
        bool operator==(supplier& other);
        friend ostream& operator<<(ostream& out, supplier& s);

        void save_to_file(ofstream& file);
        void load_from_file(ifstream& file);
};

// --- 9. InventorySection (Composition - holds products) ---
class inventory_section
{
    private:
        string aisle_number;
        int capacity;
        int product_count;

        // Simple arrays instead of vectors
        product* products[50];
        string product_types[50];              // track which subclass each slot is

    public:
        inventory_section();
        inventory_section(string aisle, int cap);
        inventory_section(const inventory_section& other);
        inventory_section& operator=(const inventory_section& other);
        ~inventory_section();

        void add_stock(product* p, string type);
        void sort_by_id();
        void display_section();

        product* operator[](int index);

        int get_product_count();
        string get_aisle_number();
        int get_capacity();

        void save_to_file(ofstream& file);
};

// --- 10. Warehouse (Aggregation - holds sections) ---
class warehouse
{
    private:
        string location_id;
        double total_square_footage;
        int section_count;

        inventory_section sections[10];

    public:
        warehouse();
        warehouse(string loc_id, double sq_ft);
        warehouse(const warehouse& other);
        warehouse& operator=(const warehouse& other);
        ~warehouse();

        void add_section(inventory_section& sec);
        double get_global_value();
        void find_shortages(int threshold);
        void display_warehouse();

        void save_warehouse_report(string filename);
        void load_warehouse_data(string filename);
};

#endif