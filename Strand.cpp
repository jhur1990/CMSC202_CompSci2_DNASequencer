
#include "Strand.h"

// Strand
// Default constructor that has default setting for a new strand
Strand::Strand() {
    m_name = "Default Strand";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// Strand
// Overloaded constructor that creates a new strand with a passed name
Strand::Strand(string name) {
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// ~Strand
// Destructor that deallocates each DNA sequence including all dynamically allocated nodes
Strand::~Strand() {
    Node *current = m_head;
    Node *temp;
    
    // Iterates until end to delete nodes
    while (current != nullptr) {
        temp = current -> m_next;
        delete current;
        current = temp;
    }
}

// InsertEnd
// Inserts a node at the end of the strand
void Strand::InsertEnd(char data) {
    
    // Creates a new node for the character
    Node *newNode = new Node;
    
    // Sets the data for the new node
    newNode -> m_data = data;
    newNode -> m_next = nullptr;
    
    // Checks if the Strand is empty. If so, sets m_head and m_tail
    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;
        
    } else {
        
        // Updates the m_next pointer of the current m_tail to the new Node
        m_tail -> m_next = newNode;
        m_tail = newNode;
    }
    
    m_size++;
}

// GetName
// Returns the name of the strand
string Strand::GetName() {
    return m_name;
}

// GetSize
// Returns the total size of the strand
int Strand::GetSize() {
    return m_size;
}

// ReverseSequence
// Reverses the order of the characters in the DNA or mRNA strand
void Strand::ReverseSequence() {
    
    Node *prev = nullptr; // Initalizes the previous node pointer
    Node *current = m_head; // Sets the current node pointer the the head of the strand
    Node *next = nullptr; // Initalizes the next node pointer to nullptr
    
    // Iterates through the strand and reverses the pointers between nodes
    while (current != nullptr) {
        next = current -> m_next;
        current -> m_next = prev;
        prev = current;
        current = next;
    }
    
    // Update the head and tail of the strand to the original
    m_tail = m_head;
    m_head = prev;
}

// GetData
// Iterates the strand and returns a single character from a node
char Strand::GetData(int nodeNum) {
    int count = 0; // Initializes a counter to keep track of the current node position
    Node *current = m_head; // Sets the current node pointer to the head of the strand

    // Iterates through the strand until the specified position is reached or the end of the strand is reached
    while (current != nullptr && count < nodeNum) {
        current = current -> m_next;
        count++;
    }

    return current -> m_data;
}

// operator <<
// Returns an output stream of each strand
ostream &operator << (ostream &output, Strand &myStrand) {
    Node *current = myStrand.m_head; // Sets the current node pointer to the head of the strand
    
    // Iterates through the strand nodes
    while (current != nullptr) {
        output << current -> m_data;
        
        // Checks if there is a next node
        if (current -> m_next != nullptr) {
            output << " -> ";
        } else {
            output << " -> END";
        }
        
        // Moves the current node pointer one step forward
        current = current -> m_next;
    }
    
    return output;
}
