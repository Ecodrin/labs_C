#include "ex7.h"


int main(){
	Warehouse warehouse;
	Product* product1 = new PerishableProduct("Perishable Product", 1, 1.0, 10.0, 30, time(0) + 7 * 24 * 60 * 60);
	Product* product2 = new ElectronicProduct("Electronic Product", 2, 1.0, 10.0, 30, 12, 65);
	warehouse += product1;
	warehouse += product2;
	std::vector<Product*> products = warehouse.get_products_by_category("PerishableProduct");
	for(const auto  & el: products){
		el->displayInfo();
	}

}