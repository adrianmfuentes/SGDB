#include <iostream>
#include "database.h"

int main() {
    Database db;
    db.createTable("Usuarios", {"ID", "Nombre", "Edad"});

    db.insertRow("Usuarios", {"1", "Alice", "30"});
    db.insertRow("Usuarios", {"2", "Bob", "25"});
    db.printTable("Usuarios");

    return 0;
}
