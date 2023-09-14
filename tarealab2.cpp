#include <iostream>
#include <vector>
using namespace std;


// Estructura de ventas
struct Venta {
    string customer_id;
    string product_id;
    string quantity;
    string purchase_date;
    double total_price;
    double key; // Clave para la cola de prioridad mínima

    // Constructor
    Venta(const string& cid, const string& pid, const string& q,
           const string& pda, double tp) : 
        customer_id(cid), 
        product_id(pid), 
        quantity(q),
        purchase_date(pda),
        total_price(tp),
        key(tp) {} // Inicializa la clave con el precio total
};
// Estructura de ventas (como se definió anteriormente)

class MinPriorityQueue {
private:
    vector<Venta> heap; // El montículo mínimo se almacena en un vector

    // Función auxiliar para mantener la propiedad del montículo mínimo
    void heapify(int i) {
        int min = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < heap.size() && heap[leftChild].key < heap[min].key)
            min = leftChild;

        if (rightChild < heap.size() && heap[rightChild].key < heap[min].key)
            min = rightChild;

        if (min != i) {
            swap(heap[i], heap[min]);
            heapify(min);
        }
    }

public:
    // Insertar una venta en la cola de prioridad mínima
    void insert(const Venta& venta) {
        heap.push_back(venta);
        int i = heap.size() - 1;

        // Mantener la propiedad del montículo mínimo
        while (i > 0 && heap[(i - 1) / 2].key > heap[i].key) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Ver el elemento mínimo (sin eliminarlo)
    const Venta& getMin() {
        if (!heap.empty())
            return heap[0];
        else
            throw runtime_error("La cola de prioridad mínima está vacía.");
    }

    // Extraer el elemento mínimo y devolverlo
    Venta extractMin() {
        if (heap.empty())
            throw runtime_error("La cola de prioridad mínima está vacía.");

        Venta minVenta = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        heapify(0); // Mantener la propiedad del montículo mínimo

        return minVenta;
    }

    // Reducir la clave de una venta en la cola
    void reduceKey(int index, double newKey) {
        if (index < 0 || index >= heap.size())
            throw out_of_range("Índice fuera de rango.");

        if (newKey > heap[index].key)
            throw runtime_error("La nueva clave es mayor que la clave actual.");

        heap[index].key = newKey;

        // Reorganizar el montículo si es necesario
        while (index > 0 && heap[(index - 1) / 2].key > heap[index].key) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Comprobar si la cola de prioridad mínima está vacía
    bool isEmpty() const {
        return heap.empty();
    }
};



int main() {
    MinPriorityQueue minPriorityQueue;
    
    string cusid, prodid, quan, dat;
    float pri;
    bool m = true;
    bool n = true;

    while(m){
        cout<<"Insertar venta: \n";
        cout<<"ID de cliente: ";cin>>cusid;
        cout<<"\nID de producto: ";cin>>prodid;
        cout<<"\nCantidad: ";cin>>quan;
        cout<<"\nFecha de compra: ";cin>>dat;
        cout<<"\nPrecio: ";cin>>pri;

        minPriorityQueue.insert(Venta(cusid, prodid, quan, dat, pri));
        while (n)
        {
            char r = 'n';
            cout << "¿Insertar otra venta?(y/n) \n";
            cin >> r;
            if (r == 'n')
            {
                m = false;
                n=false;
            }
            else if (r == 'y')
            {
                m = true;
                n=false;
            }
            else
            {
                cout << "su respuesta no es válida";
                n=true;
            }
        }
    }

    // Ver el mínimo
    cout << "Venta mínima: " << minPriorityQueue.getMin().total_price << endl;

    // Extraer el mínimo
    Venta minVenta = minPriorityQueue.extractMin();
    cout << "Venta extraída mínima: " << minVenta.total_price << endl;

    // Reducir la clave
    minPriorityQueue.reduceKey(1, 25.0);

    // Ver el nuevo mínimo
    cout << "Venta mínima después de reducir clave: " << minPriorityQueue.getMin().total_price << endl;

    return 0;
}
