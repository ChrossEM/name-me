#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estructura de ventas
struct Ventas {
    string customer_id;
    string product_id;
    string quantity;
    string purchase_date;
    double total_price;

    // Ventas(const string& cid, const string& pid, const string& q,
    //        const string& pda, double tp) : 
    //     customer_id(cid), 
    //     product_id(pid), 
    //     quantity(q),
    //     purchase_date(pda),
    //     total_price(tp){}
};

bool compareSales(const Ventas& a, const Ventas& b) {
    return a.total_price > b.total_price; // '>' for min-heap
}

void heapify(vector<Ventas>& Ventas, int n, int IDraiz) {
    int min = IDraiz;
    int leftChild = 2 * IDraiz + 1;
    int rightChild = 2 * IDraiz + 2;

    // hijo izquierdo < raiz
    if (leftChild < n && compareSales(Ventas[leftChild], Ventas[min]))
        min = leftChild;
    // min != raiz
    if (min != IDraiz) {
        
        swap(Ventas[IDraiz], Ventas[min]);

        heapify(Ventas, n, min);
    }
    
}

void heapSort(vector<Ventas>& Ventas) {
    int n = Ventas.size();

    // min heap --> VentaId
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(Ventas, n, i);

    // Extraer
    for (int i = n - 1; i > 0; i--) {
        swap(Ventas[0], Ventas[i]);
        heapify(Ventas, i, 0);
    }
}

void load_data(Ventas *data, const int rows = 1000, const int cols = 5)
{
    // Define the file name
    string filename = "sales.txt";

    const int numRows = rows;    // Number of rows
    const int numColumns = cols; // Number of columns

    // Open the file
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return;
    }

    for (int i = 0; i < numRows; i++)
    {
        string line;
        if (getline(file, line))
        {
            size_t start = 0;
            size_t end = line.find('\t');
            int j = 0; // Column index

            // Store the remaining columns in the FlightInfo structure
            while (end != string::npos && j < numColumns)
            {
                if (j == 0)
                    data[i].customer_id = line.substr(start, end - start);
                if (j == 1)
                    data[i].product_id = line.substr(start, end - start);
                if (j == 2)
                    data[i].quantity = line.substr(start, end - start);
                if (j == 3)
                {
                    string price = line.substr(start, end - start);
                    data[i].total_price = stod(price);
                }

                if (j == 4)
                    data[i].purchase_date = line.substr(start, end - start);
                start = end + 1;
                end = line.find('\t', start);
                j++;
            }
        }
        else
        {
            cerr << "Error: Not enough lines in the file." << endl;
            break;
        }
    }



    // Close the file
    file.close();
}

int main() {
    vector<Ventas> Ventas; 
    load_data(Ventas); //lock and load txt
    heapSort(Ventas);

    cout << "Sorted Ventas by Venta ID:" << endl;
    for (const Ventas& Venta : Ventas) {
        
        
    }

    return 0;
}