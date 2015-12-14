
#ifndef HashTable_h
#define HashTable_h

#include "linked_list.hpp"

template<class T>
class cListAdapter {
public:
    
};

int numRandom(int a,int b)
{
    random_device rand;
    mt19937 mt(rand());
    uniform_real_distribution<double> dist(a,b+1);
    return int(dist(mt));
}

uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed) {
    //Valores predeterminados por el autor.
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m  = 5;
    uint32_t n  = 0xe6546b64;
    uint32_t h  = 0; // bloque del hash
    uint32_t k  = 0; // bloque de la llave (4 bytes)
    uint8_t *d  = (uint8_t *) key;  // 32 bits(4 bytes) de la llave
    const uint32_t *chunks  = NULL; // pedazo
    const uint8_t  *tail    = NULL; // la cola - ultimos 8 bytes
    int i   = 0;
    int l   = len / 4; // tamano del pedazo
    
    h = seed;
    
    chunks  = (const uint32_t *) (d + l * 4); // cuerpo
    tail    = (const uint8_t  *) (d + l * 4); //ultimos 8 bytes de la llave
    
    // por cada 4 bytes de la llave
    for (i = -l; i != 0; ++i) {
        // los siguientes 4 bytes de la llave
        k = chunks[i];
        // modificamos los siguientes 4 bytes de la llave
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        // lo anadimos al hash
        h ^= k;
        h = (h << r2) | (h >> (32 - r2));
        h = h * m + n;
    }
    
    k = 0;
    
    // resto
    switch (len & 3) { // `len % 4'
        case 3: k ^= (tail[2] << 16);
        case 2: k ^= (tail[1] << 8);
            
        case 1:
            k ^= tail[0];
            k *= c1;
            k = (k << r1) | (k >> (32 - r1));
            k *= c2;
            h ^= k;
    }
    
    h ^= len;
    
    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);
    
    return h;
}

// Clase Hash

template<class T>
class HashTable
{
private:
    
    typedef unsigned int uint32;
    // Array es una referencia a un array de listas enlazadas.
    cList<T> * array;
    
    // El tamano de array.
    int length;
    
    // Retorna una posicion del array dada una clave.
    //int hash( string itemKey );
    int hash(T);
    int seed;
public:
    
    
    // constructor
    //HashTable( int tableLength = 701 );
    HashTable( int tableLength = 1<<8 );
    // inserta un item en la tabla
    void insertItem(T);

    // Elimina un Item de la tabla por llave.
    bool removeItem(T);
    
    // Retorna un item de la tabla por su llave.
    T getItemByKey(T);
    
    // Imprimimos el contenido de la Hash Table.
    void printTable();
    
    // Imprimimos un histograma para ver la distribucion de los Items.
    void printHistogram();
    
    // Retorna el tamano de Array
    int getLength();
    
    // Retorna el numero de items
    int getNumberOfItems();
    
    // Destructor
    ~HashTable();
};

//
template<class T>
HashTable<T>::HashTable( int tableLength )
{
    if (tableLength <= 0) tableLength = 1<<8;
    array   = new cList<T>[ tableLength ];
    length  = tableLength;
    seed    = numRandom(1, 2000000);
}

//
template<class T>
int HashTable<T>::hash(T x)
{
    //FUNCION CON MODULO SIMPLE
    /*
    int value = 0;
    for (int i = 0; i < x.length(); i++)
        value += x[i];
    return (x.length() * value) % length;
     */
    
    //FUNCION FNV (modulo)
    /*
    uint32 hval = 2166136261;
    uint32 primo = 16777619;
    
    for(unsigned int i = 0; i < x.length(); i++){
        //hval ^= (uint32)x[i];
        hval ^= (uint32)x[i];
        hval *= primo;
    }
    
    return hval % 13;// % HASH_TABLE_SIZE;*/
    
    //cout << "tamano string en bytes: " << x.size() << endl;
    return murmurhash(x.c_str(), uint32_t(x.size()), uint32_t(seed)) & ((1<<8) - 1);
}

//
template<class T>
void HashTable<T>::insertItem(T x)
{
    int index = hash(x);
    
    //lock_guard<mutex> bloqueo(barrier);
    array[ index ].insert( x );
}

//
template<class T>
bool HashTable<T>::removeItem(T itemKey )
{
    int index = hash( itemKey );
    return array[ index ].remove( itemKey );
}

//
template<class T>
T HashTable<T>::getItemByKey( T x )
{
    cNode<T> ** t;
    int index = hash( x );
    //return array[index].find(x,t);
    array[index].find(x,t);
    if ((*t)->m_data!=x) {
        return "No se encontro el dato.";
    }
    return (*t)->m_data;
}

//
template<class T>
void HashTable<T>::printTable()
{
    cout << "\nHash Table:\n";
    for (int i = 0,j=0; i < length; i++)
    {
        cout << "Contenedor " << i+1 << ": ";
        //array[i].printList();
        cout << "Numero de Elementos: " << array[i].get_size() << endl;
    }
}

//
template<class T>
void HashTable<T>::printHistogram()
{
    cout << "\n\nContenido:\n";
    cout << getNumberOfItems() << " elementos en total.\n";
    for (int i = 0; i < length; i++)
    {
        cout << i + 1 << ":\t";
        for (int j = 0; j < array[i].getLength(); j++)
            cout << ".";
        cout << "\n";
    }
}

//
template<class T>
int HashTable<T>::getLength()
{
    return length;
}

//
template<class T>
int HashTable<T>::getNumberOfItems()
{
    int itemCount = 0;
    for (int i = 0; i < length; i++)
        itemCount += array[i].getLength();
    return itemCount;
}

//
template<class T>
HashTable<T>::~HashTable()
{
    delete [] array;
}




#endif


