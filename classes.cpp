#include "inventory.h"

// ============================================================
//          MODULE 1 : PRODUCT HIERARCHY CLASSES
// ============================================================


// -------------------------------------------------------
// CLASS 1 : product  (Abstract Base Class)
// -------------------------------------------------------

product::product()
{
    product_id   = "NONE";
    product_name = "Unknown";
    price        = 0.0;
    quantity     = 0;
}

product::product(string pid, string pname, double pprice, int pqty)
{
    product_id   = pid;
    product_name = pname;
    price        = (pprice >= 0) ? pprice : 0;
    quantity     = (pqty   >= 0) ? pqty   : 0;
}

product::product(const product& other)
{
    product_id   = other.product_id;
    product_name = other.product_name;
    price        = other.price;
    quantity     = other.quantity;
}

product& product::operator=(const product& other)
{
    if (this != &other)
    {
        product_id   = other.product_id;
        product_name = other.product_name;
        price        = other.price;
        quantity     = other.quantity;
    }
    return *this;
}

product::~product() {}

// Getters
string product::get_product_id()   { return product_id;   }
string product::get_product_name() { return product_name; }
double product::get_price()        { return price;        }
int    product::get_quantity()     { return quantity;     }

// Setters with basic validation
void product::set_price(double p)    { if (p >= 0)  price    = p; }
void product::set_quantity(int q)    { if (q >= 0)  quantity = q; }

void product::display_status()
{
    cout << "-------------------------------"     << endl;
    cout << "Product ID   : " << product_id       << endl;
    cout << "Name         : " << product_name     << endl;
    cout << "Price (PKR)  : " << price            << endl;
    cout << "Quantity     : " << quantity         << endl;
}

double product::calculate_value()
{
    return price * quantity;
}

double product::calculate_risk()
{
    return 0.0;
}

void product::apply_discount(double percent)
{
    if (percent > 0 && percent <= 100)
        price = price - (price * percent / 100);
}

bool product::operator==(product& other)
{
    return (product_id == other.product_id);
}

ostream& operator<<(ostream& out, product& p)
{
    out << "Product [" << p.product_id << "] : " << p.product_name
        << " | Price: " << p.price << " | Qty: " << p.quantity;
    return out;
}

void product::save_to_file(ofstream& file)
{
    file << product_id   << "\n";
    file << product_name << "\n";
    file << price        << "\n";
    file << quantity     << "\n";
}

void product::load_from_file(ifstream& file)
{
    getline(file, product_id);
    getline(file, product_name);
    file >> price >> quantity;
    file.ignore();
}


// -------------------------------------------------------
// CLASS 2 : electronic_product
// -------------------------------------------------------

electronic_product::electronic_product() : product()
{
    voltage        = 0;
    warranty_months = 0;
    brand_name     = new char[8];
    strcpy(brand_name, "Unknown");
}

electronic_product::electronic_product(string pid, string pname, double pprice, int pqty,
                                        int volt, int warranty, string brand)
    : product(pid, pname, pprice, pqty)
{
    voltage         = volt;
    warranty_months = warranty;
    brand_name      = new char[brand.length() + 1];
    strcpy(brand_name, brand.c_str());
}

// Rule of 3 : Copy Constructor
electronic_product::electronic_product(const electronic_product& other)
    : product(other)
{
    voltage         = other.voltage;
    warranty_months = other.warranty_months;
    brand_name      = new char[strlen(other.brand_name) + 1];
    strcpy(brand_name, other.brand_name);
}

// Rule of 3 : Copy Assignment
electronic_product& electronic_product::operator=(const electronic_product& other)
{
    if (this != &other)
    {
        product::operator=(other);
        voltage         = other.voltage;
        warranty_months = other.warranty_months;
        delete[] brand_name;
        brand_name = new char[strlen(other.brand_name) + 1];
        strcpy(brand_name, other.brand_name);
    }
    return *this;
}

// Rule of 3 : Destructor
electronic_product::~electronic_product()
{
    delete[] brand_name;
}

string electronic_product::get_brand_name() { return string(brand_name); }

void electronic_product::test_hardware()
{
    cout << "Testing hardware for: " << product_name << " (Brand: " << brand_name << ")" << endl;
    cout << "Voltage: " << voltage << "V | Warranty: " << warranty_months << " months" << endl;
}

void electronic_product::display_status()
{
    product::display_status();
    cout << "Brand        : " << brand_name      << endl;
    cout << "Voltage      : " << voltage         << "V" << endl;
    cout << "Warranty     : " << warranty_months << " months" << endl;
    cout << "Type         : Electronic Product"   << endl;
}

double electronic_product::calculate_risk()
{
    // basic risk based on voltage
    double risk = 0;
    if (voltage > 220) risk = 30.0;
    else               risk = 10.0;
    return risk;
}

void electronic_product::apply_discount(double percent)
{
    // Electronics only allow max 20% discount
    if (percent > 20) percent = 20;
    product::apply_discount(percent);
}

void electronic_product::save_to_file(ofstream& file)
{
    product::save_to_file(file);
    file << voltage         << "\n";
    file << warranty_months << "\n";
    file << brand_name      << "\n";
}

void electronic_product::load_from_file(ifstream& file)
{
    product::load_from_file(file);
    file >> voltage >> warranty_months;
    file.ignore();
    string temp;
    getline(file, temp);
    delete[] brand_name;
    brand_name = new char[temp.length() + 1];
    strcpy(brand_name, temp.c_str());
}


// -------------------------------------------------------
// CLASS 3 : fragile_electronics
// -------------------------------------------------------

fragile_electronics::fragile_electronics() : electronic_product()
{
    fragility_rating = 1;
    packaging_type   = "Standard";
}

fragile_electronics::fragile_electronics(string pid, string pname, double pprice, int pqty,
                                          int volt, int warranty, string brand,
                                          int frag_rating, string pkg_type)
    : electronic_product(pid, pname, pprice, pqty, volt, warranty, brand)
{
    fragility_rating = (frag_rating >= 1 && frag_rating <= 10) ? frag_rating : 5;
    packaging_type   = pkg_type;
}

fragile_electronics::fragile_electronics(const fragile_electronics& other)
    : electronic_product(other)
{
    fragility_rating = other.fragility_rating;
    packaging_type   = other.packaging_type;
}

fragile_electronics& fragile_electronics::operator=(const fragile_electronics& other)
{
    if (this != &other)
    {
        electronic_product::operator=(other);
        fragility_rating = other.fragility_rating;
        packaging_type   = other.packaging_type;
    }
    return *this;
}

fragile_electronics::~fragile_electronics() {}

double fragile_electronics::calculate_shipping_risk()
{
    // Higher fragility = higher shipping risk
    double risk = fragility_rating * 10.0;
    return risk;
}

void fragile_electronics::display_status()
{
    electronic_product::display_status();
    cout << "Fragility    : " << fragility_rating << " / 10" << endl;
    cout << "Packaging    : " << packaging_type   << endl;
    cout << "Ship Risk    : " << calculate_shipping_risk() << "%" << endl;
    cout << "Type         : Fragile Electronics" << endl;
}

double fragile_electronics::calculate_risk()
{
    return electronic_product::calculate_risk() + calculate_shipping_risk();
}

void fragile_electronics::apply_discount(double percent)
{
    // Fragile items allow max 10% discount
    if (percent > 10) percent = 10;
    product::apply_discount(percent);
}

void fragile_electronics::save_to_file(ofstream& file)
{
    electronic_product::save_to_file(file);
    file << fragility_rating << "\n";
    file << packaging_type   << "\n";
}

void fragile_electronics::load_from_file(ifstream& file)
{
    electronic_product::load_from_file(file);
    file >> fragility_rating;
    file.ignore();
    getline(file, packaging_type);
}


// -------------------------------------------------------
// CLASS 4 : grocery_product
// -------------------------------------------------------

grocery_product::grocery_product() : product()
{
    calories  = 0;
    is_halal  = true;
}

grocery_product::grocery_product(string pid, string pname, double pprice, int pqty,
                                  int cal, bool halal)
    : product(pid, pname, pprice, pqty)
{
    calories = (cal >= 0) ? cal : 0;
    is_halal = halal;
}

grocery_product::grocery_product(const grocery_product& other) : product(other)
{
    calories = other.calories;
    is_halal = other.is_halal;
}

grocery_product& grocery_product::operator=(const grocery_product& other)
{
    if (this != &other)
    {
        product::operator=(other);
        calories = other.calories;
        is_halal = other.is_halal;
    }
    return *this;
}

grocery_product::~grocery_product() {}

void grocery_product::check_safety()
{
    cout << "Safety Check for: " << product_name << endl;
    cout << "Calories : " << calories << " kcal" << endl;
    cout << "Halal    : " << (is_halal ? "Yes" : "No") << endl;
}

void grocery_product::display_status()
{
    product::display_status();
    cout << "Calories     : " << calories          << " kcal" << endl;
    cout << "Halal        : " << (is_halal ? "Yes" : "No")   << endl;
    cout << "Type         : Grocery Product"        << endl;
}

double grocery_product::calculate_risk()
{
    return 5.0;    // low risk for general groceries
}

void grocery_product::apply_discount(double percent)
{
    // Groceries allow up to 50% discount
    if (percent > 50) percent = 50;
    product::apply_discount(percent);
}

void grocery_product::save_to_file(ofstream& file)
{
    product::save_to_file(file);
    file << calories << "\n";
    file << is_halal << "\n";
}

void grocery_product::load_from_file(ifstream& file)
{
    product::load_from_file(file);
    file >> calories >> is_halal;
    file.ignore();
}


// -------------------------------------------------------
// CLASS 5 : perishable_grocery
// -------------------------------------------------------

perishable_grocery::perishable_grocery() : grocery_product()
{
    expiry_date  = "01-01-2025";
    storage_temp = 4.0;
}

perishable_grocery::perishable_grocery(string pid, string pname, double pprice, int pqty,
                                        int cal, bool halal,
                                        string exp_date, double s_temp)
    : grocery_product(pid, pname, pprice, pqty, cal, halal)
{
    expiry_date  = exp_date;
    storage_temp = s_temp;
}

perishable_grocery::perishable_grocery(const perishable_grocery& other)
    : grocery_product(other)
{
    expiry_date  = other.expiry_date;
    storage_temp = other.storage_temp;
}

perishable_grocery& perishable_grocery::operator=(const perishable_grocery& other)
{
    if (this != &other)
    {
        grocery_product::operator=(other);
        expiry_date  = other.expiry_date;
        storage_temp = other.storage_temp;
    }
    return *this;
}

perishable_grocery::~perishable_grocery() {}

bool perishable_grocery::check_expiry()
{
    // Simple check: for demo we assume products with expiry "EXPIRED" are expired
    if (expiry_date == "EXPIRED")
    {
        cout << "WARNING: " << product_name << " is EXPIRED!" << endl;
        return true;
    }
    cout << product_name << " expires on: " << expiry_date << endl;
    return false;
}

void perishable_grocery::display_status()
{
    grocery_product::display_status();
    cout << "Expiry Date  : " << expiry_date  << endl;
    cout << "Storage Temp : " << storage_temp << " C" << endl;
    cout << "Type         : Perishable Grocery" << endl;
    check_expiry();
}

double perishable_grocery::calculate_risk()
{
    // higher risk if near expiry or storage temp issue
    double risk = grocery_product::calculate_risk();
    if (expiry_date == "EXPIRED") risk += 80.0;
    else                           risk += 20.0;
    return risk;
}

void perishable_grocery::apply_discount(double percent)
{
    // Perishable items can get up to 70% discount (near expiry sales)
    if (percent > 70) percent = 70;
    product::apply_discount(percent);
}

void perishable_grocery::save_to_file(ofstream& file)
{
    grocery_product::save_to_file(file);
    file << expiry_date  << "\n";
    file << storage_temp << "\n";
}

void perishable_grocery::load_from_file(ifstream& file)
{
    grocery_product::load_from_file(file);
    getline(file, expiry_date);
    file >> storage_temp;
    file.ignore();
}


// -------------------------------------------------------
// CLASS 6 : non_perishable
// -------------------------------------------------------

non_perishable::non_perishable() : grocery_product()
{
    shelf_life_years   = 1;
    preservative_level = "Low";
}

non_perishable::non_perishable(string pid, string pname, double pprice, int pqty,
                                int cal, bool halal,
                                int shelf_yrs, string pres_level)
    : grocery_product(pid, pname, pprice, pqty, cal, halal)
{
    shelf_life_years   = (shelf_yrs >= 0) ? shelf_yrs : 1;
    preservative_level = pres_level;
}

non_perishable::non_perishable(const non_perishable& other)
    : grocery_product(other)
{
    shelf_life_years   = other.shelf_life_years;
    preservative_level = other.preservative_level;
}

non_perishable& non_perishable::operator=(const non_perishable& other)
{
    if (this != &other)
    {
        grocery_product::operator=(other);
        shelf_life_years   = other.shelf_life_years;
        preservative_level = other.preservative_level;
    }
    return *this;
}

non_perishable::~non_perishable() {}

string non_perishable::get_storage_instructions()
{
    string instructions = "Store in cool, dry place.";
    if (preservative_level == "High")
        instructions += " Can be stored at room temperature.";
    else if (preservative_level == "Low")
        instructions += " Avoid direct sunlight.";
    return instructions;
}

void non_perishable::display_status()
{
    grocery_product::display_status();
    cout << "Shelf Life   : " << shelf_life_years   << " years" << endl;
    cout << "Preservative : " << preservative_level << endl;
    cout << "Instructions : " << get_storage_instructions() << endl;
    cout << "Type         : Non-Perishable Grocery" << endl;
}

double non_perishable::calculate_risk()
{
    return 2.0;    // very low risk
}

void non_perishable::apply_discount(double percent)
{
    if (percent > 40) percent = 40;
    product::apply_discount(percent);
}

void non_perishable::save_to_file(ofstream& file)
{
    grocery_product::save_to_file(file);
    file << shelf_life_years   << "\n";
    file << preservative_level << "\n";
}

void non_perishable::load_from_file(ifstream& file)
{
    grocery_product::load_from_file(file);
    file >> shelf_life_years;
    file.ignore();
    getline(file, preservative_level);
}


// -------------------------------------------------------
// CLASS 7 : clothing_product
// -------------------------------------------------------

clothing_product::clothing_product() : product()
{
    size   = "M";
    fabric = "Cotton";
    gender = "Unisex";
}

clothing_product::clothing_product(string pid, string pname, double pprice, int pqty,
                                    string sz, string fab, string gen)
    : product(pid, pname, pprice, pqty)
{
    size   = sz;
    fabric = fab;
    gender = gen;
}

clothing_product::clothing_product(const clothing_product& other) : product(other)
{
    size   = other.size;
    fabric = other.fabric;
    gender = other.gender;
}

clothing_product& clothing_product::operator=(const clothing_product& other)
{
    if (this != &other)
    {
        product::operator=(other);
        size   = other.size;
        fabric = other.fabric;
        gender = other.gender;
    }
    return *this;
}

clothing_product::~clothing_product() {}

void clothing_product::fit_guide()
{
    cout << "Fit Guide for: " << product_name << endl;
    cout << "Size   : " << size   << endl;
    cout << "Fabric : " << fabric << endl;
    cout << "Gender : " << gender << endl;
}

void clothing_product::display_status()
{
    product::display_status();
    cout << "Size         : " << size   << endl;
    cout << "Fabric       : " << fabric << endl;
    cout << "Gender       : " << gender << endl;
    cout << "Type         : Clothing Product" << endl;
}

double clothing_product::calculate_risk()
{
    return 1.0;    // clothing has almost no risk
}

void clothing_product::apply_discount(double percent)
{
    if (percent > 60) percent = 60;
    product::apply_discount(percent);
}

void clothing_product::save_to_file(ofstream& file)
{
    product::save_to_file(file);
    file << size   << "\n";
    file << fabric << "\n";
    file << gender << "\n";
}

void clothing_product::load_from_file(ifstream& file)
{
    product::load_from_file(file);
    getline(file, size);
    getline(file, fabric);
    getline(file, gender);
}


// ============================================================
//          MODULE 2 : WAREHOUSE MANAGEMENT CLASSES
// ============================================================


// -------------------------------------------------------
// CLASS 8 : supplier
// -------------------------------------------------------

supplier::supplier()
{
    supplier_id       = "SUP000";
    supplier_name     = "Unknown Supplier";
    contract_terms    = "Standard";
    linked_product_id = "NONE";
}

supplier::supplier(string sid, string sname, string terms, string prod_id)
{
    supplier_id       = sid;
    supplier_name     = sname;
    contract_terms    = terms;
    linked_product_id = prod_id;
}

supplier::supplier(const supplier& other)
{
    supplier_id       = other.supplier_id;
    supplier_name     = other.supplier_name;
    contract_terms    = other.contract_terms;
    linked_product_id = other.linked_product_id;
}

supplier& supplier::operator=(const supplier& other)
{
    if (this != &other)
    {
        supplier_id       = other.supplier_id;
        supplier_name     = other.supplier_name;
        contract_terms    = other.contract_terms;
        linked_product_id = other.linked_product_id;
    }
    return *this;
}

supplier::~supplier() {}

string supplier::get_supplier_id()        { return supplier_id;       }
string supplier::get_supplier_name()      { return supplier_name;     }
string supplier::get_linked_product_id()  { return linked_product_id; }

void supplier::order_restock(int amount)
{
    cout << "Supplier [" << supplier_name << "] restocking " << amount
         << " units for product: " << linked_product_id << endl;
}

void supplier::generate_invoice()
{
    cout << "======= INVOICE ======="     << endl;
    cout << "Supplier  : " << supplier_name     << endl;
    cout << "ID        : " << supplier_id       << endl;
    cout << "Contract  : " << contract_terms    << endl;
    cout << "Product   : " << linked_product_id << endl;
    cout << "========================" << endl;
}

void supplier::display_supplier()
{
    cout << "-------------------------------"         << endl;
    cout << "Supplier ID   : " << supplier_id         << endl;
    cout << "Supplier Name : " << supplier_name       << endl;
    cout << "Contract      : " << contract_terms      << endl;
    cout << "Linked Product: " << linked_product_id   << endl;
}

bool supplier::operator==(supplier& other)
{
    return (supplier_id == other.supplier_id);
}

ostream& operator<<(ostream& out, supplier& s)
{
    out << "Supplier [" << s.supplier_id << "] : " << s.supplier_name
        << " -> Product: " << s.linked_product_id;
    return out;
}

void supplier::save_to_file(ofstream& file)
{
    file << supplier_id       << "\n";
    file << supplier_name     << "\n";
    file << contract_terms    << "\n";
    file << linked_product_id << "\n";
}

void supplier::load_from_file(ifstream& file)
{
    getline(file, supplier_id);
    getline(file, supplier_name);
    getline(file, contract_terms);
    getline(file, linked_product_id);
}


// -------------------------------------------------------
// CLASS 9 : inventory_section
// -------------------------------------------------------

inventory_section::inventory_section()
{
    aisle_number  = "A1";
    capacity      = 50;
    product_count = 0;

    for (int i = 0; i < 50; i++)
        products[i] = nullptr;
}

inventory_section::inventory_section(string aisle, int cap)
{
    aisle_number  = aisle;
    capacity      = cap;
    product_count = 0;

    for (int i = 0; i < 50; i++)
        products[i] = nullptr;
}

inventory_section::inventory_section(const inventory_section& other)
{
    aisle_number  = other.aisle_number;
    capacity      = other.capacity;
    product_count = other.product_count;

    for (int i = 0; i < 50; i++)
    {
        product_types[i] = other.product_types[i];
        products[i]      = nullptr;              // shallow copy reference only
        if (other.products[i] != nullptr)
            products[i] = other.products[i];    // sharing pointers (aggregation style)
    }
}

inventory_section& inventory_section::operator=(const inventory_section& other)
{
    if (this != &other)
    {
        aisle_number  = other.aisle_number;
        capacity      = other.capacity;
        product_count = other.product_count;

        for (int i = 0; i < 50; i++)
        {
            product_types[i] = other.product_types[i];
            products[i]      = other.products[i];
        }
    }
    return *this;
}

inventory_section::~inventory_section()
{
    // section does NOT own the product memory (warehouse/main does)
    // so we do not delete products here
    for (int i = 0; i < 50; i++)
        products[i] = nullptr;
}

void inventory_section::add_stock(product* p, string type)
{
    if (product_count >= capacity)
    {
        cout << "Section " << aisle_number << " is FULL!" << endl;
        return;
    }
    products[product_count]      = p;
    product_types[product_count] = type;
    product_count++;
    cout << "Added [" << p->get_product_name() << "] to section " << aisle_number << endl;
}

// Simple bubble sort by product_id string
void inventory_section::sort_by_id()
{
    for (int i = 0; i < product_count - 1; i++)
    {
        for (int j = 0; j < product_count - i - 1; j++)
        {
            if (products[j]->get_product_id() > products[j+1]->get_product_id())
            {
                // swap pointers
                product* temp_ptr    = products[j];
                products[j]          = products[j+1];
                products[j+1]        = temp_ptr;

                string temp_type     = product_types[j];
                product_types[j]     = product_types[j+1];
                product_types[j+1]   = temp_type;
            }
        }
    }
    cout << "Section " << aisle_number << " sorted by Product ID." << endl;
}

void inventory_section::display_section()
{
    cout << "==============================="  << endl;
    cout << "Section : " << aisle_number       << endl;
    cout << "Capacity: " << capacity           << endl;
    cout << "Count   : " << product_count      << endl;
    cout << "==============================="  << endl;

    for (int i = 0; i < product_count; i++)
    {
        if (products[i] != nullptr)
            products[i]->display_status();
    }
}

// operator[] for shelf access
product* inventory_section::operator[](int index)
{
    if (index >= 0 && index < product_count)
        return products[index];

    cout << "Index out of range for section " << aisle_number << endl;
    return nullptr;
}

int    inventory_section::get_product_count() { return product_count; }
string inventory_section::get_aisle_number()  { return aisle_number;  }
int    inventory_section::get_capacity()      { return capacity;       }

void inventory_section::save_to_file(ofstream& file)
{
    file << aisle_number  << "\n";
    file << capacity      << "\n";
    file << product_count << "\n";

    // save each product ID so warehouse can reference them
    for (int i = 0; i < product_count; i++)
    {
        if (products[i] != nullptr)
            file << products[i]->get_product_id() << "\n";
        else
            file << "NONE\n";
    }
}


// -------------------------------------------------------
// CLASS 10 : warehouse
// -------------------------------------------------------

warehouse::warehouse()
{
    location_id          = "WH000";
    total_square_footage = 0.0;
    section_count        = 0;
}

warehouse::warehouse(string loc_id, double sq_ft)
{
    location_id          = loc_id;
    total_square_footage = sq_ft;
    section_count        = 0;
}

warehouse::warehouse(const warehouse& other)
{
    location_id          = other.location_id;
    total_square_footage = other.total_square_footage;
    section_count        = other.section_count;

    for (int i = 0; i < section_count; i++)
        sections[i] = other.sections[i];
}

warehouse& warehouse::operator=(const warehouse& other)
{
    if (this != &other)
    {
        location_id          = other.location_id;
        total_square_footage = other.total_square_footage;
        section_count        = other.section_count;

        for (int i = 0; i < section_count; i++)
            sections[i] = other.sections[i];
    }
    return *this;
}

warehouse::~warehouse() {}

void warehouse::add_section(inventory_section& sec)
{
    if (section_count >= 10)
    {
        cout << "Warehouse is FULL. Cannot add more sections." << endl;
        return;
    }
    sections[section_count] = sec;
    section_count++;
    cout << "Section [" << sec.get_aisle_number() << "] added to warehouse." << endl;
}

double warehouse::get_global_value()
{
    double total = 0.0;
    for (int i = 0; i < section_count; i++)
    {
        for (int j = 0; j < sections[i].get_product_count(); j++)
        {
            product* p = sections[i][j];
            if (p != nullptr)
                total += p->calculate_value();
        }
    }
    return total;
}

void warehouse::find_shortages(int threshold)
{
    cout << "=== SHORTAGE REPORT (threshold: " << threshold << ") ===" << endl;
    for (int i = 0; i < section_count; i++)
    {
        for (int j = 0; j < sections[i].get_product_count(); j++)
        {
            product* p = sections[i][j];
            if (p != nullptr && p->get_quantity() < threshold)
            {
                cout << "LOW STOCK: [" << p->get_product_id() << "] "
                     << p->get_product_name()
                     << " | Qty: " << p->get_quantity() << endl;
            }
        }
    }
}

void warehouse::display_warehouse()
{
    cout << "***********************************"          << endl;
    cout << "WAREHOUSE   : " << location_id               << endl;
    cout << "Area (sqft) : " << total_square_footage      << endl;
    cout << "Sections    : " << section_count             << endl;
    cout << "Total Value : PKR " << get_global_value()    << endl;
    cout << "***********************************"          << endl;

    for (int i = 0; i < section_count; i++)
        sections[i].display_section();
}

void warehouse::save_warehouse_report(string filename)
{
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open file " << filename << endl;
        return;
    }

    file << location_id          << "\n";
    file << total_square_footage << "\n";
    file << section_count        << "\n";

    for (int i = 0; i < section_count; i++)
        sections[i].save_to_file(file);

    file.close();
    cout << "Warehouse report saved to: " << filename << endl;
}

void warehouse::load_warehouse_data(string filename)
{
    ifstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open file " << filename << endl;
        return;
    }

    getline(file, location_id);
    file >> total_square_footage >> section_count;
    file.ignore();

    for (int i = 0; i < section_count; i++)
    {
        string aisle;
        int cap, count;
        getline(file, aisle);
        file >> cap >> count;
        file.ignore();

        sections[i] = inventory_section(aisle, cap);

        // read product IDs (just for reference display, not re-linking objects)
        for (int j = 0; j < count; j++)
        {
            string pid;
            getline(file, pid);
            cout << "  Loaded product reference: " << pid << endl;
        }
    }

    file.close();
    cout << "Warehouse data loaded from: " << filename << endl;
}


// -------------------------------------------------------
// CLASS 11 : transaction_log<T>  (Template)
// -------------------------------------------------------

template <typename T>
transaction_log<T>::transaction_log()
{
    log_count = 0;
}

template <typename T>
void transaction_log<T>::record_action(string action, T& entity)
{
    if (log_count >= 100)
    {
        cout << "Log is full. Cannot record more actions." << endl;
        return;
    }
    // Use << operator (entity must support it)
    // We store the action string + entity info
    string entry = action;
    log_history[log_count] = entry;
    log_count++;

    cout << "LOG RECORDED: " << action << endl;
}

template <typename T>
void transaction_log<T>::print_audit_trail()
{
    cout << "======= AUDIT TRAIL =======" << endl;
    for (int i = 0; i < log_count; i++)
        cout << i + 1 << ". " << log_history[i] << endl;
    cout << "===========================" << endl;
}

template <typename T>
void transaction_log<T>::save_log_to_file(string filename)
{
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        cout << "Cannot open log file: " << filename << endl;
        return;
    }

    file << log_count << "\n";
    for (int i = 0; i < log_count; i++)
        file << log_history[i] << "\n";

    file.close();
    cout << "Audit log saved to: " << filename << endl;
}

// Explicit template instantiation so linker finds them
template class transaction_log<product>;
template class transaction_log<supplier>;