#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
	//
        // Connect to the database
	//
	//
        pqxx::connection C("dbname=mydb user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }

	//
        // Create a transactional object
	//
	//
        pqxx::work W(C);

	//
        // Create SQL statement
	//
	//
        std::string sql = "INSERT INTO testtbl(name, value) VALUES ('world', 1024);";

	// 
        // Execute SQL query
	//
	//
        W.exec(sql);
        W.commit();
        std::cout << "Tuple inserted successfully" << std::endl;


	//
	// Create a non-transactional object to query the database
	//
	//
        pqxx::nontransaction N(C);

	//
	// Create SQL statement to query all tuples
	//
	//
        std::string sqlSelect = "SELECT name, value FROM testtbl;";

	//
        // Execute SQL query to select all tuples
	//
	//
        pqxx::result R(N.exec(sqlSelect));

	//
        // Print the queried tuples
	//
	//
        std::cout << "Table testtbl contains the following tuples:\nname \tvalue" << std::endl;
        for (auto row : R) {
            std::cout << row["name"].as<std::string>() << " \t" << row["value"].as<int>() << std::endl;
        }

	//
        // Close the database connection
	//
	//
        C.disconnect();

	std::cout << "Disconnected from the database" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
